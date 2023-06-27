#pragma once

#include "CoreMinimal.h"

class IAndroidClasses {
public:
    virtual FString GetName() = 0;
    
#if PLATFORM_ANDROID
    virtual jobject GetJObject() = 0;
#endif
};
