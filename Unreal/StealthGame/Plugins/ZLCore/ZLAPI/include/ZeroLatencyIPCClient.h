#pragma once 

#if !defined(ZEROLATENCYIPC_API)
#define ZEROLATENCYIPC_API __declspec(dllimport)
#endif

namespace zl
{
	enum ELoggingLevel;
	
	namespace proto
	{
		namespace networking
		{
			class Transmission;
		}	
	}
}

typedef void(*DispatchMessageCallbackFunc)(const void* const, int);

class ZEROLATENCYIPC_API IZeroLatencyIPCClient
{
public:
	virtual void UpdateFPS(const int FPS) = 0;
	virtual void PumpMessageQueue() = 0;
	virtual void SetDispatchMessageCallback(DispatchMessageCallbackFunc callback) = 0;
	virtual void SendTransmission(const void* data, int size) = 0;
};

extern "C"
{
	extern ZEROLATENCYIPC_API IZeroLatencyIPCClient* CreateZeroLatencyClient(zl::ELoggingLevel loggingLevel);
	extern ZEROLATENCYIPC_API void DestroyZeroLatencyClient(IZeroLatencyIPCClient* client);

	extern ZEROLATENCYIPC_API void UpdateFPS(IZeroLatencyIPCClient* client, const int FPS);
	extern ZEROLATENCYIPC_API void PumpMessageQueue(IZeroLatencyIPCClient* client);
	extern ZEROLATENCYIPC_API void SetDispatchMessageCallback(IZeroLatencyIPCClient* client, DispatchMessageCallbackFunc callback);
	extern ZEROLATENCYIPC_API void SendTransmission(IZeroLatencyIPCClient* client, const void* data, int size);
}