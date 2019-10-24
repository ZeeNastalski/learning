#pragma once

#include "CoreMinimal.h"

#include "ZLIPCConnectionHandle.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHandleClosed);

class UGameInstance;

UCLASS()
class UZLIPCConnectionHandle : public UObject
{
	GENERATED_BODY()

public:
	FOnHandleClosed OnHandleClosed;

	void BeginDestroy() override;
};