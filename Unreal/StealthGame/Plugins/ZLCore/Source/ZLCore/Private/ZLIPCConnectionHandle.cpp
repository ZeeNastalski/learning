#include "ZLIPCConnectionHandle.h"

void UZLIPCConnectionHandle::BeginDestroy()
{
	Super::BeginDestroy();

	if (OnHandleClosed.IsBound())
	{
		OnHandleClosed.Broadcast();
	}
}