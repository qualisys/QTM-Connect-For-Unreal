// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "QTMConnectLiveLink/Public/QualisysLiveLinkRetargetAsset.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeQualisysLiveLinkRetargetAsset() {}
// Cross Module References
	QTMCONNECTLIVELINK_API UClass* Z_Construct_UClass_UQualisysLiveLinkRetargetAsset_NoRegister();
	QTMCONNECTLIVELINK_API UClass* Z_Construct_UClass_UQualisysLiveLinkRetargetAsset();
	LIVELINK_API UClass* Z_Construct_UClass_ULiveLinkRetargetAsset();
	UPackage* Z_Construct_UPackage__Script_QTMConnectLiveLink();
// End Cross Module References
	void UQualisysLiveLinkRetargetAsset::StaticRegisterNativesUQualisysLiveLinkRetargetAsset()
	{
	}
	UClass* Z_Construct_UClass_UQualisysLiveLinkRetargetAsset_NoRegister()
	{
		return UQualisysLiveLinkRetargetAsset::StaticClass();
	}
	struct Z_Construct_UClass_UQualisysLiveLinkRetargetAsset_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FNamePropertyParams NewProp_BoneMapping_ValueProp;
		static const UE4CodeGen_Private::FNamePropertyParams NewProp_BoneMapping_Key_KeyProp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BoneMapping_MetaData[];
#endif
		static const UE4CodeGen_Private::FMapPropertyParams NewProp_BoneMapping;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DebugTPose_MetaData[];
#endif
		static void NewProp_DebugTPose_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_DebugTPose;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UQualisysLiveLinkRetargetAsset_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ULiveLinkRetargetAsset,
		(UObject* (*)())Z_Construct_UPackage__Script_QTMConnectLiveLink,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UQualisysLiveLinkRetargetAsset_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "QualisysLiveLinkRetargetAsset.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/QualisysLiveLinkRetargetAsset.h" },
	};
#endif
	const UE4CodeGen_Private::FNamePropertyParams Z_Construct_UClass_UQualisysLiveLinkRetargetAsset_Statics::NewProp_BoneMapping_ValueProp = { "BoneMapping", nullptr, (EPropertyFlags)0x0000000000000001, UE4CodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, 1, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FNamePropertyParams Z_Construct_UClass_UQualisysLiveLinkRetargetAsset_Statics::NewProp_BoneMapping_Key_KeyProp = { "BoneMapping_Key", nullptr, (EPropertyFlags)0x0000000000000001, UE4CodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UQualisysLiveLinkRetargetAsset_Statics::NewProp_BoneMapping_MetaData[] = {
		{ "Category", "Bone Mapping" },
		{ "ModuleRelativePath", "Public/QualisysLiveLinkRetargetAsset.h" },
	};
#endif
	const UE4CodeGen_Private::FMapPropertyParams Z_Construct_UClass_UQualisysLiveLinkRetargetAsset_Statics::NewProp_BoneMapping = { "BoneMapping", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UQualisysLiveLinkRetargetAsset, BoneMapping), EMapPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UQualisysLiveLinkRetargetAsset_Statics::NewProp_BoneMapping_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UQualisysLiveLinkRetargetAsset_Statics::NewProp_BoneMapping_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UQualisysLiveLinkRetargetAsset_Statics::NewProp_DebugTPose_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/QualisysLiveLinkRetargetAsset.h" },
	};
#endif
	void Z_Construct_UClass_UQualisysLiveLinkRetargetAsset_Statics::NewProp_DebugTPose_SetBit(void* Obj)
	{
		((UQualisysLiveLinkRetargetAsset*)Obj)->DebugTPose = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UQualisysLiveLinkRetargetAsset_Statics::NewProp_DebugTPose = { "DebugTPose", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UQualisysLiveLinkRetargetAsset), &Z_Construct_UClass_UQualisysLiveLinkRetargetAsset_Statics::NewProp_DebugTPose_SetBit, METADATA_PARAMS(Z_Construct_UClass_UQualisysLiveLinkRetargetAsset_Statics::NewProp_DebugTPose_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UQualisysLiveLinkRetargetAsset_Statics::NewProp_DebugTPose_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UQualisysLiveLinkRetargetAsset_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UQualisysLiveLinkRetargetAsset_Statics::NewProp_BoneMapping_ValueProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UQualisysLiveLinkRetargetAsset_Statics::NewProp_BoneMapping_Key_KeyProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UQualisysLiveLinkRetargetAsset_Statics::NewProp_BoneMapping,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UQualisysLiveLinkRetargetAsset_Statics::NewProp_DebugTPose,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UQualisysLiveLinkRetargetAsset_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UQualisysLiveLinkRetargetAsset>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UQualisysLiveLinkRetargetAsset_Statics::ClassParams = {
		&UQualisysLiveLinkRetargetAsset::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UQualisysLiveLinkRetargetAsset_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UQualisysLiveLinkRetargetAsset_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UQualisysLiveLinkRetargetAsset_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UQualisysLiveLinkRetargetAsset_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UQualisysLiveLinkRetargetAsset()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UQualisysLiveLinkRetargetAsset_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UQualisysLiveLinkRetargetAsset, 650728848);
	template<> QTMCONNECTLIVELINK_API UClass* StaticClass<UQualisysLiveLinkRetargetAsset>()
	{
		return UQualisysLiveLinkRetargetAsset::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UQualisysLiveLinkRetargetAsset(Z_Construct_UClass_UQualisysLiveLinkRetargetAsset, &UQualisysLiveLinkRetargetAsset::StaticClass, TEXT("/Script/QTMConnectLiveLink"), TEXT("UQualisysLiveLinkRetargetAsset"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UQualisysLiveLinkRetargetAsset);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
