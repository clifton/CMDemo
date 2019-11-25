// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CustomAnimNode/Public/AnimNode_OrientationWarping.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAnimNode_OrientationWarping() {}
// Cross Module References
	CUSTOMANIMNODE_API UScriptStruct* Z_Construct_UScriptStruct_FAnimMode_OrientationWarping();
	UPackage* Z_Construct_UPackage__Script_CustomAnimNode();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FAnimNode_Base();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FBoneReference();
	CUSTOMANIMNODE_API UScriptStruct* Z_Construct_UScriptStruct_FBoneRef();
	CUSTOMANIMNODE_API UScriptStruct* Z_Construct_UScriptStruct_FAxisSettings();
	ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FPoseLink();
	COREUOBJECT_API UEnum* Z_Construct_UEnum_CoreUObject_EAxis();
// End Cross Module References
class UScriptStruct* FAnimMode_OrientationWarping::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern CUSTOMANIMNODE_API uint32 Get_Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAnimMode_OrientationWarping, Z_Construct_UPackage__Script_CustomAnimNode(), TEXT("AnimMode_OrientationWarping"), sizeof(FAnimMode_OrientationWarping), Get_Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Hash());
	}
	return Singleton;
}
template<> CUSTOMANIMNODE_API UScriptStruct* StaticStruct<FAnimMode_OrientationWarping>()
{
	return FAnimMode_OrientationWarping::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAnimMode_OrientationWarping(FAnimMode_OrientationWarping::StaticStruct, TEXT("/Script/CustomAnimNode"), TEXT("AnimMode_OrientationWarping"), false, nullptr, nullptr);
static struct FScriptStruct_CustomAnimNode_StaticRegisterNativesFAnimMode_OrientationWarping
{
	FScriptStruct_CustomAnimNode_StaticRegisterNativesFAnimMode_OrientationWarping()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AnimMode_OrientationWarping")),new UScriptStruct::TCppStructOps<FAnimMode_OrientationWarping>);
	}
} ScriptStruct_CustomAnimNode_StaticRegisterNativesFAnimMode_OrientationWarping;
	struct Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_IKFootRootBone_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_IKFootRootBone;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SpineBones_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_SpineBones;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_SpineBones_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Settings_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Settings;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_LocomotionAngle_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_LocomotionAngle;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BasePose_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_BasePose;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/AnimNode_OrientationWarping.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAnimMode_OrientationWarping>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::NewProp_IKFootRootBone_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/AnimNode_OrientationWarping.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::NewProp_IKFootRootBone = { "IKFootRootBone", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FAnimMode_OrientationWarping, IKFootRootBone), Z_Construct_UScriptStruct_FBoneReference, METADATA_PARAMS(Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::NewProp_IKFootRootBone_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::NewProp_IKFootRootBone_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::NewProp_SpineBones_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/AnimNode_OrientationWarping.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::NewProp_SpineBones = { "SpineBones", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FAnimMode_OrientationWarping, SpineBones), METADATA_PARAMS(Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::NewProp_SpineBones_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::NewProp_SpineBones_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::NewProp_SpineBones_Inner = { "SpineBones", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FBoneRef, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::NewProp_Settings_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/AnimNode_OrientationWarping.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::NewProp_Settings = { "Settings", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FAnimMode_OrientationWarping, Settings), Z_Construct_UScriptStruct_FAxisSettings, METADATA_PARAMS(Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::NewProp_Settings_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::NewProp_Settings_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::NewProp_LocomotionAngle_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/AnimNode_OrientationWarping.h" },
		{ "PinShownByDefault", "" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::NewProp_LocomotionAngle = { "LocomotionAngle", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FAnimMode_OrientationWarping, LocomotionAngle), METADATA_PARAMS(Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::NewProp_LocomotionAngle_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::NewProp_LocomotionAngle_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::NewProp_BasePose_MetaData[] = {
		{ "Category", "Links" },
		{ "ModuleRelativePath", "Public/AnimNode_OrientationWarping.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::NewProp_BasePose = { "BasePose", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FAnimMode_OrientationWarping, BasePose), Z_Construct_UScriptStruct_FPoseLink, METADATA_PARAMS(Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::NewProp_BasePose_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::NewProp_BasePose_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::NewProp_IKFootRootBone,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::NewProp_SpineBones,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::NewProp_SpineBones_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::NewProp_Settings,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::NewProp_LocomotionAngle,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::NewProp_BasePose,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_CustomAnimNode,
		Z_Construct_UScriptStruct_FAnimNode_Base,
		&NewStructOps,
		"AnimMode_OrientationWarping",
		sizeof(FAnimMode_OrientationWarping),
		alignof(FAnimMode_OrientationWarping),
		Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::PropPointers,
		ARRAY_COUNT(Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAnimMode_OrientationWarping()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_CustomAnimNode();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AnimMode_OrientationWarping"), sizeof(FAnimMode_OrientationWarping), Get_Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAnimMode_OrientationWarping_Hash() { return 50452165U; }
class UScriptStruct* FBoneRef::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern CUSTOMANIMNODE_API uint32 Get_Z_Construct_UScriptStruct_FBoneRef_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FBoneRef, Z_Construct_UPackage__Script_CustomAnimNode(), TEXT("BoneRef"), sizeof(FBoneRef), Get_Z_Construct_UScriptStruct_FBoneRef_Hash());
	}
	return Singleton;
}
template<> CUSTOMANIMNODE_API UScriptStruct* StaticStruct<FBoneRef>()
{
	return FBoneRef::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FBoneRef(FBoneRef::StaticStruct, TEXT("/Script/CustomAnimNode"), TEXT("BoneRef"), false, nullptr, nullptr);
static struct FScriptStruct_CustomAnimNode_StaticRegisterNativesFBoneRef
{
	FScriptStruct_CustomAnimNode_StaticRegisterNativesFBoneRef()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("BoneRef")),new UScriptStruct::TCppStructOps<FBoneRef>);
	}
} ScriptStruct_CustomAnimNode_StaticRegisterNativesFBoneRef;
	struct Z_Construct_UScriptStruct_FBoneRef_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Bone_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Bone;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FBoneRef_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/AnimNode_OrientationWarping.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FBoneRef_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBoneRef>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FBoneRef_Statics::NewProp_Bone_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/AnimNode_OrientationWarping.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FBoneRef_Statics::NewProp_Bone = { "Bone", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FBoneRef, Bone), Z_Construct_UScriptStruct_FBoneReference, METADATA_PARAMS(Z_Construct_UScriptStruct_FBoneRef_Statics::NewProp_Bone_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FBoneRef_Statics::NewProp_Bone_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FBoneRef_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBoneRef_Statics::NewProp_Bone,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBoneRef_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_CustomAnimNode,
		nullptr,
		&NewStructOps,
		"BoneRef",
		sizeof(FBoneRef),
		alignof(FBoneRef),
		Z_Construct_UScriptStruct_FBoneRef_Statics::PropPointers,
		ARRAY_COUNT(Z_Construct_UScriptStruct_FBoneRef_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FBoneRef_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FBoneRef_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FBoneRef()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FBoneRef_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_CustomAnimNode();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("BoneRef"), sizeof(FBoneRef), Get_Z_Construct_UScriptStruct_FBoneRef_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FBoneRef_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FBoneRef_Hash() { return 1375275629U; }
class UScriptStruct* FAxisSettings::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern CUSTOMANIMNODE_API uint32 Get_Z_Construct_UScriptStruct_FAxisSettings_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FAxisSettings, Z_Construct_UPackage__Script_CustomAnimNode(), TEXT("AxisSettings"), sizeof(FAxisSettings), Get_Z_Construct_UScriptStruct_FAxisSettings_Hash());
	}
	return Singleton;
}
template<> CUSTOMANIMNODE_API UScriptStruct* StaticStruct<FAxisSettings>()
{
	return FAxisSettings::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FAxisSettings(FAxisSettings::StaticStruct, TEXT("/Script/CustomAnimNode"), TEXT("AxisSettings"), false, nullptr, nullptr);
static struct FScriptStruct_CustomAnimNode_StaticRegisterNativesFAxisSettings
{
	FScriptStruct_CustomAnimNode_StaticRegisterNativesFAxisSettings()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("AxisSettings")),new UScriptStruct::TCppStructOps<FAxisSettings>);
	}
} ScriptStruct_CustomAnimNode_StaticRegisterNativesFAxisSettings;
	struct Z_Construct_UScriptStruct_FAxisSettings_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BodyOrientationAlpha_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_BodyOrientationAlpha;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_YawRotationAxis_MetaData[];
#endif
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_YawRotationAxis;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAxisSettings_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/AnimNode_OrientationWarping.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FAxisSettings_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FAxisSettings>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAxisSettings_Statics::NewProp_BodyOrientationAlpha_MetaData[] = {
		{ "Category", "FAxisSettings" },
		{ "ModuleRelativePath", "Public/AnimNode_OrientationWarping.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FAxisSettings_Statics::NewProp_BodyOrientationAlpha = { "BodyOrientationAlpha", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FAxisSettings, BodyOrientationAlpha), METADATA_PARAMS(Z_Construct_UScriptStruct_FAxisSettings_Statics::NewProp_BodyOrientationAlpha_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAxisSettings_Statics::NewProp_BodyOrientationAlpha_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FAxisSettings_Statics::NewProp_YawRotationAxis_MetaData[] = {
		{ "Category", "FAxisSettings" },
		{ "ModuleRelativePath", "Public/AnimNode_OrientationWarping.h" },
	};
#endif
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FAxisSettings_Statics::NewProp_YawRotationAxis = { "YawRotationAxis", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FAxisSettings, YawRotationAxis), Z_Construct_UEnum_CoreUObject_EAxis, METADATA_PARAMS(Z_Construct_UScriptStruct_FAxisSettings_Statics::NewProp_YawRotationAxis_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FAxisSettings_Statics::NewProp_YawRotationAxis_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FAxisSettings_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAxisSettings_Statics::NewProp_BodyOrientationAlpha,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FAxisSettings_Statics::NewProp_YawRotationAxis,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FAxisSettings_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_CustomAnimNode,
		nullptr,
		&NewStructOps,
		"AxisSettings",
		sizeof(FAxisSettings),
		alignof(FAxisSettings),
		Z_Construct_UScriptStruct_FAxisSettings_Statics::PropPointers,
		ARRAY_COUNT(Z_Construct_UScriptStruct_FAxisSettings_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FAxisSettings_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FAxisSettings_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FAxisSettings()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FAxisSettings_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_CustomAnimNode();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("AxisSettings"), sizeof(FAxisSettings), Get_Z_Construct_UScriptStruct_FAxisSettings_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FAxisSettings_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FAxisSettings_Hash() { return 1919203498U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
