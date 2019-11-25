// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef CUSTOMANIMNODE_AnimNode_SpeedWarping_generated_h
#error "AnimNode_SpeedWarping.generated.h already included, missing '#pragma once' in AnimNode_SpeedWarping.h"
#endif
#define CUSTOMANIMNODE_AnimNode_SpeedWarping_generated_h

#define CrimsonMirror_Plugins_CustomAnimNode_Source_CustomAnimNode_Public_AnimNode_SpeedWarping_h_88_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics; \
	static class UScriptStruct* StaticStruct(); \
	typedef FAnimNode_SkeletalControlBase Super;


template<> CUSTOMANIMNODE_API UScriptStruct* StaticStruct<struct FAnimNode_SpeedWarping>();

#define CrimsonMirror_Plugins_CustomAnimNode_Source_CustomAnimNode_Public_AnimNode_SpeedWarping_h_70_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FPelvisAdjustmentInterp_Statics; \
	CUSTOMANIMNODE_API static class UScriptStruct* StaticStruct();


template<> CUSTOMANIMNODE_API UScriptStruct* StaticStruct<struct FPelvisAdjustmentInterp>();

#define CrimsonMirror_Plugins_CustomAnimNode_Source_CustomAnimNode_Public_AnimNode_SpeedWarping_h_42_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FIKFootLocation_Statics; \
	CUSTOMANIMNODE_API static class UScriptStruct* StaticStruct();


template<> CUSTOMANIMNODE_API UScriptStruct* StaticStruct<struct FIKFootLocation>();

#define CrimsonMirror_Plugins_CustomAnimNode_Source_CustomAnimNode_Public_AnimNode_SpeedWarping_h_26_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FIKBones_Statics; \
	CUSTOMANIMNODE_API static class UScriptStruct* StaticStruct();


template<> CUSTOMANIMNODE_API UScriptStruct* StaticStruct<struct FIKBones>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID CrimsonMirror_Plugins_CustomAnimNode_Source_CustomAnimNode_Public_AnimNode_SpeedWarping_h


#define FOREACH_ENUM_EIKFOOTROOTLOCALAXIS(op) \
	op(EIKFootRootLocalAxis::NONE) \
	op(EIKFootRootLocalAxis::X) \
	op(EIKFootRootLocalAxis::Y) \
	op(EIKFootRootLocalAxis::Z) 

enum class EIKFootRootLocalAxis : uint8;
template<> CUSTOMANIMNODE_API UEnum* StaticEnum<EIKFootRootLocalAxis>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
