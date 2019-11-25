// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CustomAnimNode/Public/AnimNode_SpeedWarping.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAnimNode_SpeedWarping() {}
// Cross Module References
	CUSTOMANIMNODE_API UEnum* Z_Construct_UEnum_CustomAnimNode_EIKFootRootLocalAxis();
	UPackage* Z_Construct_UPackage__Script_CustomAnimNode();
	CUSTOMANIMNODE_API UScriptStruct* Z_Construct_UScriptStruct_FAnimNode_SpeedWarping();
	ANIMGRAPHRUNTIME_API UScriptStruct* Z_Construct_UScriptStruct_FAnimNode_SkeletalControlBase();
	CUSTOMANIMNODE_API UScriptStruct* Z_Construct_UScriptStruct_FPelvisAdjustmentInterp();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FBoneReference();
	CUSTOMANIMNODE_API UScriptStruct* Z_Construct_UScriptStruct_FIKBones();
	CUSTOMANIMNODE_API UScriptStruct* Z_Construct_UScriptStruct_FIKFootLocation();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
// End Cross Module References
	static UEnum* EIKFootRootLocalAxis_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_CustomAnimNode_EIKFootRootLocalAxis, Z_Construct_UPackage__Script_CustomAnimNode(), TEXT("EIKFootRootLocalAxis"));
		}
		return Singleton;
	}
	template<> CUSTOMANIMNODE_API UEnum* StaticEnum<EIKFootRootLocalAxis>()
	{
		return EIKFootRootLocalAxis_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EIKFootRootLocalAxis(EIKFootRootLocalAxis_StaticEnum, TEXT("/Script/CustomAnimNode"), TEXT("EIKFootRootLocalAxis"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_CustomAnimNode_EIKFootRootLocalAxis_Hash() { return 2993542582U; }
	UEnum* Z_Construct_UEnum_CustomAnimNode_EIKFootRootLocalAxis()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_CustomAnimNode();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EIKFootRootLocalAxis"), 0, Get_Z_Construct_UEnum_CustomAnimNode_EIKFootRootLocalAxis_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "EIKFootRootLocalAxis::NONE", (int64)EIKFootRootLocalAxis::NONE },
				{ "EIKFootRootLocalAxis::X", (int64)EIKFootRootLocalAxis::X },
				{ "EIKFootRootLocalAxis::Y", (int64)EIKFootRootLocalAxis::Y },
				{ "EIKFootRootLocalAxis::Z", (int64)EIKFootRootLocalAxis::Z },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "ModuleRelativePath", "Public/AnimNode_SpeedWarping.h" },
				{ "NONE.DisplayName", "NONE" },
				{ "NONE.Name", "EIKFootRootLocalAxis::NONE" },
				{ "X.DisplayName", "IKFootRootLocalX" },
				{ "X.Name", "EIKFootRootLocalAxis::X" },
				{ "Y.DisplayName", "IKFootRootLocalY" },
				{ "Y.Name", "EIKFootRootLocalAxis::Y" },
				{ "Z.DisplayName", "IKFootRootLocalZ" },
				{ "Z.Name", "EIKFootRootLocalAxis::Z" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_CustomAnimNode,
				nullptr,
				"EIKFootRootLocalAxis",
				"EIKFootRootLocalAxis",
				Enumerators,
				ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
class UScriptStruct* FAnimNode_SpeedWarping::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern CUSTOMANIMNODE_API uint32 Get_Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAnimNode_SpeedWarping, Z_Construct_UPackage__Script_CustomAnimNode(), TEXT("AnimNode_SpeedWarping"), sizeof(FAnimNode_SpeedWarping), Get_Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Hash());
	}
	return Singleton;
}
template<> CUSTOMANIMNODE_API UScriptStruct* StaticStruct<FAnimNode_SpeedWarping>()
{
	return FAnimNode_SpeedWarping::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAnimNode_SpeedWarping(FAnimNode_SpeedWarping::StaticStruct, TEXT("/Script/CustomAnimNode"), TEXT("AnimNode_SpeedWarping"), false, nullptr, nullptr);
static struct FScriptStruct_CustomAnimNode_StaticRegisterNativesFAnimNode_SpeedWarping
{
	FScriptStruct_CustomAnimNode_StaticRegisterNativesFAnimNode_SpeedWarping()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AnimNode_SpeedWarping")),new UScriptStruct::TCppStructOps<FAnimNode_SpeedWarping>);
	}
} ScriptStruct_CustomAnimNode_StaticRegisterNativesFAnimNode_SpeedWarping;
	struct Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ClampIKUsingFKLeg_MetaData[];
#endif
		static void NewProp_ClampIKUsingFKLeg_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ClampIKUsingFKLeg;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PelvisAdjustmentInterp_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_PelvisAdjustmentInterp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_MaxIter_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_MaxIter;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PelvisAdjustmentAlpha_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_PelvisAdjustmentAlpha;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SpeedScaling_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_SpeedScaling;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SpeedWarpingAxisMode_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_SpeedWarpingAxisMode;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_SpeedWarpingAxisMode_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PelvisBone_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_PelvisBone;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FeetDefinitions_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_FeetDefinitions;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_FeetDefinitions_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_IkFootRootBone_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_IkFootRootBone;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintInternalUseOnly", "true" },
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/AnimNode_SpeedWarping.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAnimNode_SpeedWarping>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_ClampIKUsingFKLeg_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/AnimNode_SpeedWarping.h" },
	};
#endif
	void Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_ClampIKUsingFKLeg_SetBit(void* Obj)
	{
		((FAnimNode_SpeedWarping*)Obj)->ClampIKUsingFKLeg = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_ClampIKUsingFKLeg = { "ClampIKUsingFKLeg", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(FAnimNode_SpeedWarping), &Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_ClampIKUsingFKLeg_SetBit, METADATA_PARAMS(Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_ClampIKUsingFKLeg_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_ClampIKUsingFKLeg_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_PelvisAdjustmentInterp_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/AnimNode_SpeedWarping.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_PelvisAdjustmentInterp = { "PelvisAdjustmentInterp", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FAnimNode_SpeedWarping, PelvisAdjustmentInterp), Z_Construct_UScriptStruct_FPelvisAdjustmentInterp, METADATA_PARAMS(Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_PelvisAdjustmentInterp_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_PelvisAdjustmentInterp_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_MaxIter_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/AnimNode_SpeedWarping.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_MaxIter = { "MaxIter", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FAnimNode_SpeedWarping, MaxIter), METADATA_PARAMS(Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_MaxIter_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_MaxIter_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_PelvisAdjustmentAlpha_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/AnimNode_SpeedWarping.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_PelvisAdjustmentAlpha = { "PelvisAdjustmentAlpha", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FAnimNode_SpeedWarping, PelvisAdjustmentAlpha), METADATA_PARAMS(Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_PelvisAdjustmentAlpha_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_PelvisAdjustmentAlpha_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_SpeedScaling_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/AnimNode_SpeedWarping.h" },
		{ "PinShownByDefault", "" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_SpeedScaling = { "SpeedScaling", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FAnimNode_SpeedWarping, SpeedScaling), METADATA_PARAMS(Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_SpeedScaling_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_SpeedScaling_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_SpeedWarpingAxisMode_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/AnimNode_SpeedWarping.h" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_SpeedWarpingAxisMode = { "SpeedWarpingAxisMode", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FAnimNode_SpeedWarping, SpeedWarpingAxisMode), Z_Construct_UEnum_CustomAnimNode_EIKFootRootLocalAxis, METADATA_PARAMS(Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_SpeedWarpingAxisMode_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_SpeedWarpingAxisMode_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_SpeedWarpingAxisMode_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_PelvisBone_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/AnimNode_SpeedWarping.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_PelvisBone = { "PelvisBone", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FAnimNode_SpeedWarping, PelvisBone), Z_Construct_UScriptStruct_FBoneReference, METADATA_PARAMS(Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_PelvisBone_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_PelvisBone_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_FeetDefinitions_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/AnimNode_SpeedWarping.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_FeetDefinitions = { "FeetDefinitions", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FAnimNode_SpeedWarping, FeetDefinitions), METADATA_PARAMS(Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_FeetDefinitions_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_FeetDefinitions_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_FeetDefinitions_Inner = { "FeetDefinitions", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FIKBones, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_IkFootRootBone_MetaData[] = {
		{ "Category", "Settings" },
		{ "Comment", "/** Name of bone to control. This is the main bone chain to modify from. **/" },
		{ "ModuleRelativePath", "Public/AnimNode_SpeedWarping.h" },
		{ "ToolTip", "Name of bone to control. This is the main bone chain to modify from. *" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_IkFootRootBone = { "IkFootRootBone", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FAnimNode_SpeedWarping, IkFootRootBone), Z_Construct_UScriptStruct_FBoneReference, METADATA_PARAMS(Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_IkFootRootBone_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_IkFootRootBone_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_ClampIKUsingFKLeg,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_PelvisAdjustmentInterp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_MaxIter,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_PelvisAdjustmentAlpha,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_SpeedScaling,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_SpeedWarpingAxisMode,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_SpeedWarpingAxisMode_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_PelvisBone,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_FeetDefinitions,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_FeetDefinitions_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::NewProp_IkFootRootBone,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_CustomAnimNode,
		Z_Construct_UScriptStruct_FAnimNode_SkeletalControlBase,
		&NewStructOps,
		"AnimNode_SpeedWarping",
		sizeof(FAnimNode_SpeedWarping),
		alignof(FAnimNode_SpeedWarping),
		Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::PropPointers,
		ARRAY_COUNT(Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAnimNode_SpeedWarping()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_CustomAnimNode();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AnimNode_SpeedWarping"), sizeof(FAnimNode_SpeedWarping), Get_Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAnimNode_SpeedWarping_Hash() { return 3504812673U; }
class UScriptStruct* FPelvisAdjustmentInterp::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern CUSTOMANIMNODE_API uint32 Get_Z_Construct_UScriptStruct_FPelvisAdjustmentInterp_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FPelvisAdjustmentInterp, Z_Construct_UPackage__Script_CustomAnimNode(), TEXT("PelvisAdjustmentInterp"), sizeof(FPelvisAdjustmentInterp), Get_Z_Construct_UScriptStruct_FPelvisAdjustmentInterp_Hash());
	}
	return Singleton;
}
template<> CUSTOMANIMNODE_API UScriptStruct* StaticStruct<FPelvisAdjustmentInterp>()
{
	return FPelvisAdjustmentInterp::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FPelvisAdjustmentInterp(FPelvisAdjustmentInterp::StaticStruct, TEXT("/Script/CustomAnimNode"), TEXT("PelvisAdjustmentInterp"), false, nullptr, nullptr);
static struct FScriptStruct_CustomAnimNode_StaticRegisterNativesFPelvisAdjustmentInterp
{
	FScriptStruct_CustomAnimNode_StaticRegisterNativesFPelvisAdjustmentInterp()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("PelvisAdjustmentInterp")),new UScriptStruct::TCppStructOps<FPelvisAdjustmentInterp>);
	}
} ScriptStruct_CustomAnimNode_StaticRegisterNativesFPelvisAdjustmentInterp;
	struct Z_Construct_UScriptStruct_FPelvisAdjustmentInterp_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Dampen_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Dampen;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Stiffness_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Stiffness;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FPelvisAdjustmentInterp_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/AnimNode_SpeedWarping.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FPelvisAdjustmentInterp_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FPelvisAdjustmentInterp>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FPelvisAdjustmentInterp_Statics::NewProp_Dampen_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/AnimNode_SpeedWarping.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FPelvisAdjustmentInterp_Statics::NewProp_Dampen = { "Dampen", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FPelvisAdjustmentInterp, Dampen), METADATA_PARAMS(Z_Construct_UScriptStruct_FPelvisAdjustmentInterp_Statics::NewProp_Dampen_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FPelvisAdjustmentInterp_Statics::NewProp_Dampen_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FPelvisAdjustmentInterp_Statics::NewProp_Stiffness_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/AnimNode_SpeedWarping.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FPelvisAdjustmentInterp_Statics::NewProp_Stiffness = { "Stiffness", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FPelvisAdjustmentInterp, Stiffness), METADATA_PARAMS(Z_Construct_UScriptStruct_FPelvisAdjustmentInterp_Statics::NewProp_Stiffness_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FPelvisAdjustmentInterp_Statics::NewProp_Stiffness_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FPelvisAdjustmentInterp_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPelvisAdjustmentInterp_Statics::NewProp_Dampen,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FPelvisAdjustmentInterp_Statics::NewProp_Stiffness,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FPelvisAdjustmentInterp_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_CustomAnimNode,
		nullptr,
		&NewStructOps,
		"PelvisAdjustmentInterp",
		sizeof(FPelvisAdjustmentInterp),
		alignof(FPelvisAdjustmentInterp),
		Z_Construct_UScriptStruct_FPelvisAdjustmentInterp_Statics::PropPointers,
		ARRAY_COUNT(Z_Construct_UScriptStruct_FPelvisAdjustmentInterp_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FPelvisAdjustmentInterp_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FPelvisAdjustmentInterp_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FPelvisAdjustmentInterp()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FPelvisAdjustmentInterp_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_CustomAnimNode();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("PelvisAdjustmentInterp"), sizeof(FPelvisAdjustmentInterp), Get_Z_Construct_UScriptStruct_FPelvisAdjustmentInterp_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FPelvisAdjustmentInterp_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FPelvisAdjustmentInterp_Hash() { return 2894657304U; }
class UScriptStruct* FIKFootLocation::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern CUSTOMANIMNODE_API uint32 Get_Z_Construct_UScriptStruct_FIKFootLocation_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FIKFootLocation, Z_Construct_UPackage__Script_CustomAnimNode(), TEXT("IKFootLocation"), sizeof(FIKFootLocation), Get_Z_Construct_UScriptStruct_FIKFootLocation_Hash());
	}
	return Singleton;
}
template<> CUSTOMANIMNODE_API UScriptStruct* StaticStruct<FIKFootLocation>()
{
	return FIKFootLocation::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FIKFootLocation(FIKFootLocation::StaticStruct, TEXT("/Script/CustomAnimNode"), TEXT("IKFootLocation"), false, nullptr, nullptr);
static struct FScriptStruct_CustomAnimNode_StaticRegisterNativesFIKFootLocation
{
	FScriptStruct_CustomAnimNode_StaticRegisterNativesFIKFootLocation()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("IKFootLocation")),new UScriptStruct::TCppStructOps<FIKFootLocation>);
	}
} ScriptStruct_CustomAnimNode_StaticRegisterNativesFIKFootLocation;
	struct Z_Construct_UScriptStruct_FIKFootLocation_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_NewLocation_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_NewLocation;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ActualLocation_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ActualLocation;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OriginLocation_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_OriginLocation;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LimbRootLocation_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_LimbRootLocation;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FIKFootLocation_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/AnimNode_SpeedWarping.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FIKFootLocation_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FIKFootLocation>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FIKFootLocation_Statics::NewProp_NewLocation_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/AnimNode_SpeedWarping.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FIKFootLocation_Statics::NewProp_NewLocation = { "NewLocation", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FIKFootLocation, NewLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FIKFootLocation_Statics::NewProp_NewLocation_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FIKFootLocation_Statics::NewProp_NewLocation_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FIKFootLocation_Statics::NewProp_ActualLocation_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/AnimNode_SpeedWarping.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FIKFootLocation_Statics::NewProp_ActualLocation = { "ActualLocation", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FIKFootLocation, ActualLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FIKFootLocation_Statics::NewProp_ActualLocation_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FIKFootLocation_Statics::NewProp_ActualLocation_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FIKFootLocation_Statics::NewProp_OriginLocation_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/AnimNode_SpeedWarping.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FIKFootLocation_Statics::NewProp_OriginLocation = { "OriginLocation", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FIKFootLocation, OriginLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FIKFootLocation_Statics::NewProp_OriginLocation_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FIKFootLocation_Statics::NewProp_OriginLocation_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FIKFootLocation_Statics::NewProp_LimbRootLocation_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/AnimNode_SpeedWarping.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FIKFootLocation_Statics::NewProp_LimbRootLocation = { "LimbRootLocation", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FIKFootLocation, LimbRootLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FIKFootLocation_Statics::NewProp_LimbRootLocation_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FIKFootLocation_Statics::NewProp_LimbRootLocation_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FIKFootLocation_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FIKFootLocation_Statics::NewProp_NewLocation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FIKFootLocation_Statics::NewProp_ActualLocation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FIKFootLocation_Statics::NewProp_OriginLocation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FIKFootLocation_Statics::NewProp_LimbRootLocation,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FIKFootLocation_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_CustomAnimNode,
		nullptr,
		&NewStructOps,
		"IKFootLocation",
		sizeof(FIKFootLocation),
		alignof(FIKFootLocation),
		Z_Construct_UScriptStruct_FIKFootLocation_Statics::PropPointers,
		ARRAY_COUNT(Z_Construct_UScriptStruct_FIKFootLocation_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FIKFootLocation_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FIKFootLocation_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FIKFootLocation()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FIKFootLocation_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_CustomAnimNode();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("IKFootLocation"), sizeof(FIKFootLocation), Get_Z_Construct_UScriptStruct_FIKFootLocation_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FIKFootLocation_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FIKFootLocation_Hash() { return 2068632641U; }
class UScriptStruct* FIKBones::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern CUSTOMANIMNODE_API uint32 Get_Z_Construct_UScriptStruct_FIKBones_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FIKBones, Z_Construct_UPackage__Script_CustomAnimNode(), TEXT("IKBones"), sizeof(FIKBones), Get_Z_Construct_UScriptStruct_FIKBones_Hash());
	}
	return Singleton;
}
template<> CUSTOMANIMNODE_API UScriptStruct* StaticStruct<FIKBones>()
{
	return FIKBones::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FIKBones(FIKBones::StaticStruct, TEXT("/Script/CustomAnimNode"), TEXT("IKBones"), false, nullptr, nullptr);
static struct FScriptStruct_CustomAnimNode_StaticRegisterNativesFIKBones
{
	FScriptStruct_CustomAnimNode_StaticRegisterNativesFIKBones()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("IKBones")),new UScriptStruct::TCppStructOps<FIKBones>);
	}
} ScriptStruct_CustomAnimNode_StaticRegisterNativesFIKBones;
	struct Z_Construct_UScriptStruct_FIKBones_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_NumBonesInLimb_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_NumBonesInLimb;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_FKFootBone_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_FKFootBone;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_IKFootBone_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_IKFootBone;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FIKBones_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/AnimNode_SpeedWarping.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FIKBones_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FIKBones>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FIKBones_Statics::NewProp_NumBonesInLimb_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/AnimNode_SpeedWarping.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FIKBones_Statics::NewProp_NumBonesInLimb = { "NumBonesInLimb", nullptr, (EPropertyFlags)0x0010000000000015, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FIKBones, NumBonesInLimb), METADATA_PARAMS(Z_Construct_UScriptStruct_FIKBones_Statics::NewProp_NumBonesInLimb_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FIKBones_Statics::NewProp_NumBonesInLimb_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FIKBones_Statics::NewProp_FKFootBone_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/AnimNode_SpeedWarping.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FIKBones_Statics::NewProp_FKFootBone = { "FKFootBone", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FIKBones, FKFootBone), Z_Construct_UScriptStruct_FBoneReference, METADATA_PARAMS(Z_Construct_UScriptStruct_FIKBones_Statics::NewProp_FKFootBone_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FIKBones_Statics::NewProp_FKFootBone_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FIKBones_Statics::NewProp_IKFootBone_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/AnimNode_SpeedWarping.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FIKBones_Statics::NewProp_IKFootBone = { "IKFootBone", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FIKBones, IKFootBone), Z_Construct_UScriptStruct_FBoneReference, METADATA_PARAMS(Z_Construct_UScriptStruct_FIKBones_Statics::NewProp_IKFootBone_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FIKBones_Statics::NewProp_IKFootBone_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FIKBones_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FIKBones_Statics::NewProp_NumBonesInLimb,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FIKBones_Statics::NewProp_FKFootBone,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FIKBones_Statics::NewProp_IKFootBone,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FIKBones_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_CustomAnimNode,
		nullptr,
		&NewStructOps,
		"IKBones",
		sizeof(FIKBones),
		alignof(FIKBones),
		Z_Construct_UScriptStruct_FIKBones_Statics::PropPointers,
		ARRAY_COUNT(Z_Construct_UScriptStruct_FIKBones_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FIKBones_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FIKBones_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FIKBones()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FIKBones_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_CustomAnimNode();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("IKBones"), sizeof(FIKBones), Get_Z_Construct_UScriptStruct_FIKBones_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FIKBones_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FIKBones_Hash() { return 2679379931U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
