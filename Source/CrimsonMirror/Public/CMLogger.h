#pragma once


// logging macros
// class / line number functionality taken from
//   https://wiki.unrealengine.com/Logs,_Printing_Class_Name,_Function_Name,_Line_Number_of_your_Calling_Code!

//Current Class Name + Function Name where this is called!
#define CM_CUR_CLASS_FUNC (FString(__FUNCTION__))

//Current Class where this is called!
#define CM_CUR_CLASS (FString(__FUNCTION__).Left(FString(__FUNCTION__).Find(TEXT(":"))) )

//Current Function Name where this is called!
#define CM_CUR_FUNC (FString(__FUNCTION__).Right(FString(__FUNCTION__).Len() - FString(__FUNCTION__).Find(TEXT("::")) - 2 ))
  
//Current Line Number in the code where this is called!
#define CM_CUR_LINE  (FString::FromInt(__LINE__))

//Current Class and Line Number where this is called!
#define CM_CUR_CLASS_LINE (CM_CUR_CLASS + "(" + CM_CUR_LINE + ")")
  
// Current Function Signature where this is called!
// #define CM_CUR_FUNCSIG (FString(__FUNCSIG__))

#define CM_LOG(LogCat, FormatString , ...) UE_LOG(LogCat,Warning,TEXT("%s: %s"), *CM_CUR_CLASS_LINE, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__ ) )

// example on-screen debug message
// #define VSCREENMSGF(Param1,Param2) (GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *(JOYSTR_CUR_CLASS_LINE + ": " + Param1 + " " + FString::SanitizeFloat(Param2))) )