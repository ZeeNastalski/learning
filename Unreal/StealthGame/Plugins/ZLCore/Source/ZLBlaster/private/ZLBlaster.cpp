#include "IInputDevice.h"
#include "InputCoreTypes.h"
#include "IInputDeviceModule.h"
#include "ZLCoreBlueprintFunctionLibrary.h"
#include "ZLCallbackHandler.h"
#include "Containers/Queue.h"

#define LOCTEXT_NAMESPACE "ZLBlaster"

DEFINE_LOG_CATEGORY_STATIC(LogZLBlaster, Log, All);

#define BLASTERDISCONNECTEDTIMEOUTSECONDS 5
#define BUTTONREPEATMILLISECONDS 200

/**
* Buttons on the ZeroLatencyVR Blaster
*/
enum EZLBlasterButton
{
	Trigger,
	BottomButton,
	SideButton,
	PumpForward,
	PumpBack,
	Pump,
	TotalButtonCount
};

const FGamepadKeyNames::Type ZLBlasterKeyNames[EZLBlasterButton::TotalButtonCount] =
{
	FGamepadKeyNames::Type("Zerolatency_Blaster_Trigger"),
	FGamepadKeyNames::Type("Zerolatency_Blaster_BottomButton"),
	FGamepadKeyNames::Type("Zerolatency_Blaster_SideButton"),
	FGamepadKeyNames::Type("Zerolatency_Blaster_PumpForward"),
	FGamepadKeyNames::Type("Zerolatency_Blaster_PumpBack"),
	FGamepadKeyNames::Type("Zerolatency_Blaster_Pump")
};

const FKey ZLBlasterKeys[EZLBlasterButton::TotalButtonCount] =
{
	FKey("Zerolatency_Blaster_Trigger"),
	FKey("Zerolatency_Blaster_BottomButton"),
	FKey("Zerolatency_Blaster_SideButton"),
	FKey("Zerolatency_Blaster_PumpForward"),
	FKey("Zerolatency_Blaster_PumpBack"),
	FKey("Zerolatency_Blaster_Pump")

};

class FZLBlaster : public IInputDevice
{
private:
	TQueue<TTuple<EZLBlasterButton, float>> ButtonEventQueue;

	FDateTime LastInputTime;
	bool bConnected;

	FZLBlasterInput LastInput;

	FDateTime LastButtonPressedEventTimes[EZLBlasterButton::TotalButtonCount];

	/** handler to send all messages to */
	TSharedRef<FGenericApplicationMessageHandler> MessageHandler;

public:
	FZLBlaster(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) :
		MessageHandler(InMessageHandler)
	{
		for (int ButtonIdx = 0; ButtonIdx < EZLBlasterButton::TotalButtonCount; ButtonIdx++)
		{
			LastButtonPressedEventTimes[ButtonIdx] = FDateTime::MaxValue();
		}

		EKeys::AddKey(FKeyDetails(ZLBlasterKeys[EZLBlasterButton::Trigger], LOCTEXT("Zerolatency_Blaster_Trigger", "Zerolatency Blaster Trigger"), FKeyDetails::GamepadKey | FKeyDetails::FloatAxis));
		EKeys::AddKey(FKeyDetails(ZLBlasterKeys[EZLBlasterButton::BottomButton], LOCTEXT("Zerolatency_Blaster_BottomButton", "Zerolatency Blaster Bottom Button"), FKeyDetails::GamepadKey | FKeyDetails::FloatAxis));
		EKeys::AddKey(FKeyDetails(ZLBlasterKeys[EZLBlasterButton::SideButton], LOCTEXT("Zerolatency_Blaster_SideButton", "Zerolatency Blaster Side Button"), FKeyDetails::GamepadKey | FKeyDetails::FloatAxis));
		EKeys::AddKey(FKeyDetails(ZLBlasterKeys[EZLBlasterButton::PumpForward], LOCTEXT("Zerolatency_Blaster_Pump_Forward", "Zerolatency Blaster Pump Forward"), FKeyDetails::GamepadKey | FKeyDetails::FloatAxis));
		EKeys::AddKey(FKeyDetails(ZLBlasterKeys[EZLBlasterButton::PumpBack], LOCTEXT("Zerolatency_Blaster_Pump_Back", "Zerolatency Blaster Pump Back"), FKeyDetails::GamepadKey | FKeyDetails::FloatAxis));
		EKeys::AddKey(FKeyDetails(ZLBlasterKeys[EZLBlasterButton::Pump], LOCTEXT("Zerolatency_Blaster_Pump", "Zerolatency Blaster Pump"), FKeyDetails::FloatAxis | FKeyDetails::GamepadKey));

		LastInputTime = FDateTime::MinValue();
		bConnected = false;

		auto ZLCallbackHandler = UZLCoreBlueprintFunctionLibrary::GetCallbackHandler();
		if (!ZLCallbackHandler)
		{
			UE_LOG(LogZLBlaster, Warning, TEXT("Failed to find the zero latency callback handler while initialising the blaster."));
		}
		else
		{
			ZLCallbackHandler->OnBlasterInputUpdated.AddRaw(this, &FZLBlaster::OnBlasterInputUpdated);
		}
	}

	//IInputDevice
	/** Tick the interface (e.g. check for new controllers) */
	void Tick(float DeltaTime) override
	{
		if ((FDateTime::Now() - LastInputTime).GetSeconds() > BLASTERDISCONNECTEDTIMEOUTSECONDS)
		{
			bConnected = false;
		}
	}

	/** Poll for controller state and send events if needed */
	void SendControllerEvents() override
	{
		// Pump the message queue
		TTuple<EZLBlasterButton, float> ButtonEvent;
		
		while (ButtonEventQueue.Dequeue(ButtonEvent))
		{
			EZLBlasterButton button = ButtonEvent.Get<0>();
			FName buttonName = ZLBlasterKeyNames[button];			
			float axisValue = ButtonEvent.Get<1>();

			// Process button state changes
			switch (button)
			{
				case EZLBlasterButton::Trigger:
				case EZLBlasterButton::BottomButton:
				case EZLBlasterButton::SideButton:
				case EZLBlasterButton::PumpForward:
				case EZLBlasterButton::PumpBack:
					{
						if (axisValue == 1.f || axisValue == -1.f)
						{
							MessageHandler->OnControllerButtonPressed(buttonName, 0, false);
							LastButtonPressedEventTimes[button] = FDateTime::Now();
						}
						else
						{
							MessageHandler->OnControllerButtonReleased(buttonName, 0, false);
							LastButtonPressedEventTimes[button] = FDateTime::MaxValue();
						}
						break;
					}
				case EZLBlasterButton::Pump:
					{
						MessageHandler->OnControllerAnalog(buttonName, 0, axisValue);						
						break;
					}
				default:
					break;
				}
		}

		
		// Fire off button repeat events
		for (int ButtonIdx = 0; ButtonIdx < EZLBlasterButton::TotalButtonCount; ButtonIdx++)
		{
			if ((FDateTime::Now() - LastButtonPressedEventTimes[ButtonIdx]).GetTotalMilliseconds() > BUTTONREPEATMILLISECONDS)
			{
				MessageHandler->OnControllerButtonPressed(ZLBlasterKeyNames[ButtonIdx], 0, true);
			}
		}
		
	}

	/** Set which MessageHandler will get the events from SendControllerEvents. */
	void SetMessageHandler(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) override
	{
		MessageHandler = InMessageHandler;
	}

	/** Exec handler to allow console commands to be passed through for debugging */
	bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override
	{
		return false;
	}

	/**
	 * IForceFeedbackSystem pass through functions
	 */
	void SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override
	{
	}

	void SetChannelValues(int32 ControllerId, const FForceFeedbackValues &values) override
	{
	}

	bool IsGamepadAttached() const override
	{
		//TODO: timeout on attachment
		return bConnected;
	}
	//~IInputDevice

private:

	void OnBlasterInputUpdated(const FZLBlasterInput& NewInput)
	{

		// Buttons
		if (LastInput.TriggerPulled != NewInput.TriggerPulled)
		{
			ButtonEventQueue.Enqueue(TTuple<EZLBlasterButton, float>(EZLBlasterButton::Trigger, NewInput.TriggerPulled ? 1.0f : 0.f));
		}

		if (LastInput.BottomButtonPressed != NewInput.BottomButtonPressed)
		{
			ButtonEventQueue.Enqueue(TTuple<EZLBlasterButton, float>(EZLBlasterButton::BottomButton, NewInput.BottomButtonPressed ? 1.0f : 0.f));
		}

		if (LastInput.SideButtonPressed != NewInput.SideButtonPressed)
		{
			ButtonEventQueue.Enqueue(TTuple<EZLBlasterButton, float>(EZLBlasterButton::SideButton, NewInput.SideButtonPressed ? 1.0f : 0.f));
		}
		

		// Pump State Buttons
		if (LastInput.PumpState != EBlasterPumpState::PUMP_FORWARD && NewInput.PumpState == EBlasterPumpState::PUMP_FORWARD)
		{
			//pump forward pressed
			ButtonEventQueue.Enqueue(TTuple<EZLBlasterButton, float>(EZLBlasterButton::PumpForward, 1.0f));
		}

		if (LastInput.PumpState != EBlasterPumpState::PUMP_BACK && NewInput.PumpState == EBlasterPumpState::PUMP_BACK)
		{
			//pump back pressed
			ButtonEventQueue.Enqueue(TTuple<EZLBlasterButton, float>(EZLBlasterButton::PumpBack, 1.0f));
		}

		if (LastInput.PumpState == EBlasterPumpState::PUMP_FORWARD && NewInput.PumpState != EBlasterPumpState::PUMP_FORWARD)
		{
			//pump forward released
			ButtonEventQueue.Enqueue(TTuple<EZLBlasterButton, float>(EZLBlasterButton::PumpForward, 0.0f));
		}

		if (LastInput.PumpState == EBlasterPumpState::PUMP_BACK && NewInput.PumpState != EBlasterPumpState::PUMP_BACK)
		{
			//pump back released
			ButtonEventQueue.Enqueue(TTuple<EZLBlasterButton, float>(EZLBlasterButton::PumpBack, 0.0f));
		}


		// Pump Axis
		if (LastInput.PumpState != NewInput.PumpState)
		{

			float pumpAxisValue = 0.0f;
			
			if (NewInput.PumpState == EBlasterPumpState::PUMP_FORWARD)
			{
				pumpAxisValue = 1.0f;				
			}

			if (NewInput.PumpState == EBlasterPumpState::PUMP_BACK)
			{
				pumpAxisValue = -1.0f;				
			}

			ButtonEventQueue.Enqueue(TTuple<EZLBlasterButton, float>(EZLBlasterButton::Pump, pumpAxisValue));
		}

		LastInput = NewInput;
	}
};


class FZeroLatencyBlasterPluginModule : public IInputDeviceModule
{
public:
	TSharedPtr<IInputDevice> CreateInputDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler) override
	{
		return TSharedPtr<IInputDevice>(new FZLBlaster(InMessageHandler));
	}
};

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE( FZeroLatencyBlasterPluginModule, ZLBlaster)