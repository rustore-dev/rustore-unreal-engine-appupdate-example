#pragma once

#include "CoreMinimal.h"

class RUSTORECORE_API CallbackHandler
{
public:
    static void AddCallback(TFunction<void()> callback);
};
