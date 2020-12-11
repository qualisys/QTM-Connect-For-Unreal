// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "QTMConnectLiveLinkEditor/Private/QTMConnectLiveLinkSourceFactory.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeQTMConnectLiveLinkSourceFactory() {}
// Cross Module References
	QTMCONNECTLIVELINKEDITOR_API UClass* Z_Construct_UClass_UQTMConnectLiveLinkSourceFactory_NoRegister();
	QTMCONNECTLIVELINKEDITOR_API UClass* Z_Construct_UClass_UQTMConnectLiveLinkSourceFactory();
	LIVELINKINTERFACE_API UClass* Z_Construct_UClass_ULiveLinkSourceFactory();
	UPackage* Z_Construct_UPackage__Script_QTMConnectLiveLinkEditor();
// End Cross Module References
	void UQTMConnectLiveLinkSourceFactory::StaticRegisterNativesUQTMConnectLiveLinkSourceFactory()
	{
	}
	UClass* Z_Construct_UClass_UQTMConnectLiveLinkSourceFactory_NoRegister()
	{
		return UQTMConnectLiveLinkSourceFactory::StaticClass();
	}
	struct Z_Construct_UClass_UQTMConnectLiveLinkSourceFactory_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UQTMConnectLiveLinkSourceFactory_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ULiveLinkSourceFactory,
		(UObject* (*)())Z_Construct_UPackage__Script_QTMConnectLiveLinkEditor,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UQTMConnectLiveLinkSourceFactory_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "QTMConnectLiveLinkSourceFactory.h" },
		{ "ModuleRelativePath", "Private/QTMConnectLiveLinkSourceFactory.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UQTMConnectLiveLinkSourceFactory_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UQTMConnectLiveLinkSourceFactory>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UQTMConnectLiveLinkSourceFactory_Statics::ClassParams = {
		&UQTMConnectLiveLinkSourceFactory::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x000000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UQTMConnectLiveLinkSourceFactory_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UQTMConnectLiveLinkSourceFactory_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UQTMConnectLiveLinkSourceFactory()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UQTMConnectLiveLinkSourceFactory_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UQTMConnectLiveLinkSourceFactory, 2740925728);
	template<> QTMCONNECTLIVELINKEDITOR_API UClass* StaticClass<UQTMConnectLiveLinkSourceFactory>()
	{
		return UQTMConnectLiveLinkSourceFactory::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UQTMConnectLiveLinkSourceFactory(Z_Construct_UClass_UQTMConnectLiveLinkSourceFactory, &UQTMConnectLiveLinkSourceFactory::StaticClass, TEXT("/Script/QTMConnectLiveLinkEditor"), TEXT("UQTMConnectLiveLinkSourceFactory"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UQTMConnectLiveLinkSourceFactory);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
