#include "AndroidJavaClass.h"

AndroidJavaClass::AndroidJavaClass(FString className)
{
#if PLATFORM_ANDROID
    javaClass = FAndroidApplication::FindJavaClass(TCHAR_TO_ANSI(*className));

    _className = className;
    _classSignature = FString::Printf(TEXT("L%s;"), *_className);
#endif
}

AndroidJavaClass::~AndroidJavaClass()
{
}
