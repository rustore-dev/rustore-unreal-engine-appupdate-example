#pragma once

#include "CoreMinimal.h"
#include "RuStoreListener.h"

namespace RuStoreSDK
{
	class RUSTORECORE_API UnrealPlayerImpl : public RuStoreListener
	{
	public:
		UnrealPlayerImpl() : RuStoreListener("com/Plugins/RuStoreCore/UnrealPlayerWrapper", "ru/rustore/unrealsdk/core/IPlayerProvider") { }
		virtual ~UnrealPlayerImpl() { }
	};
}
