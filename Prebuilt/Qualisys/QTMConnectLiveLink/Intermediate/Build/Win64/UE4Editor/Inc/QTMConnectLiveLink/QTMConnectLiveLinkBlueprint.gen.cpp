// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "QTMConnectLiveLink/Public/QTMConnectLiveLinkBlueprint.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeQTMConnectLiveLinkBlueprint() {}
// Cross Module References
	QTMCONNECTLIVELINK_API UClass* Z_Construct_UClass_UQTMConnectLiveLinkBlueprint_NoRegister();
	QTMCONNECTLIVELINK_API UClass* Z_Construct_UClass_UQTMConnectLiveLinkBlueprint();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	UPackage* Z_Construct_UPackage__Script_QTMConnectLiveLink();
	LIVELINKINTERFACE_API UScriptStruct* Z_Construct_UScriptStruct_FLiveLinkSourceHandle();
// End Cross Module References
	DEFINE_FUNCTION(UQTMConnectLiveLinkBlueprint::execCreateQTMConnectLiveLinkSource)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_IpAddress);
		P_GET_UBOOL(Z_Param_AutoDiscover);
		P_GET_STRUCT_REF(FLiveLinkSourceHandle,Z_Param_Out_SourceHandle);
		P_FINISH;
		P_NATIVE_BEGIN;
		UQTMConnectLiveLinkBlueprint::CreateQTMConnectLiveLinkSource(Z_Param_IpAddress,Z_Param_AutoDiscover,Z_Param_Out_SourceHandle);
		P_NATIVE_END;
	}
	void UQTMConnectLiveLinkBlueprint::StaticRegisterNativesUQTMConnectLiveLinkBlueprint()
	{
		UClass* Class = UQTMConnectLiveLinkBlueprint::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "CreateQTMConnectLiveLinkSource", &UQTMConnectLiveLinkBlueprint::execCreateQTMConnectLiveLinkSource },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UQTMConnectLiveLinkBlueprint_CreateQTMConnectLiveLinkSource_Statics
	{
		struct QTMConnectLiveLinkBlueprint_eventCreateQTMConnectLiveLinkSource_Parms
		{
			FString IpAddress;
			bool AutoDiscover;
			FLiveLinkSourceHandle SourceHandle;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_SourceHandle;
		static void NewProp_AutoDiscover_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_AutoDiscover;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_IpAddress;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UQTMConnectLiveLinkBlueprint_CreateQTMConnectLiveLinkSource_Statics::NewProp_SourceHandle = { "SourceHandle", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(QTMConnectLiveLinkBlueprint_eventCreateQTMConnectLiveLinkSource_Parms, SourceHandle), Z_Construct_UScriptStruct_FLiveLinkSourceHandle, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UQTMConnectLiveLinkBlueprint_CreateQTMConnectLiveLinkSource_Statics::NewProp_AutoDiscover_SetBit(void* Obj)
	{
		((QTMConnectLiveLinkBlueprint_eventCreateQTMConnectLiveLinkSource_Parms*)Obj)->AutoDiscover = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UQTMConnectLiveLinkBlueprint_CreateQTMConnectLiveLinkSource_Statics::NewProp_AutoDiscover = { "AutoDiscover", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(QTMConnectLiveLinkBlueprint_eventCreateQTMConnectLiveLinkSource_Parms), &Z_Construct_UFunction_UQTMConnectLiveLinkBlueprint_CreateQTMConnectLiveLinkSource_Statics::NewProp_AutoDiscover_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UQTMConnectLiveLinkBlueprint_CreateQTMConnectLiveLinkSource_Statics::NewProp_IpAddress = { "IpAddress", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(QTMConnectLiveLinkBlueprint_eventCreateQTMConnectLiveLinkSource_Parms, IpAddress), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UQTMConnectLiveLinkBlueprint_CreateQTMConnectLiveLinkSource_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQTMConnectLiveLinkBlueprint_CreateQTMConnectLiveLinkSource_Statics::NewProp_SourceHandle,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQTMConnectLiveLinkBlueprint_CreateQTMConnectLiveLinkSource_Statics::NewProp_AutoDiscover,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UQTMConnectLiveLinkBlueprint_CreateQTMConnectLiveLinkSource_Statics::NewProp_IpAddress,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UQTMConnectLiveLinkBlueprint_CreateQTMConnectLiveLinkSource_Statics::Function_MetaDataParams[] = {
		{ "AutoDiscover", "true" },
		{ "Category", "Qualisys" },
		{ "DisplayName", "Create QTM Connect LiveLink Source" },
		{ "IpAddress", "127.0.0.1" },
		{ "ModuleRelativePath", "Public/QTMConnectLiveLinkBlueprint.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UQTMConnectLiveLinkBlueprint_CreateQTMConnectLiveLinkSource_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UQTMConnectLiveLinkBlueprint, nullptr, "CreateQTMConnectLiveLinkSource", nullptr, nullptr, sizeof(QTMConnectLiveLinkBlueprint_eventCreateQTMConnectLiveLinkSource_Parms), Z_Construct_UFunction_UQTMConnectLiveLinkBlueprint_CreateQTMConnectLiveLinkSource_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UQTMConnectLiveLinkBlueprint_CreateQTMConnectLiveLinkSource_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04442401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UQTMConnectLiveLinkBlueprint_CreateQTMConnectLiveLinkSource_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UQTMConnectLiveLinkBlueprint_CreateQTMConnectLiveLinkSource_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UQTMConnectLiveLinkBlueprint_CreateQTMConnectLiveLinkSource()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UQTMConnectLiveLinkBlueprint_CreateQTMConnectLiveLinkSource_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UQTMConnectLiveLinkBlueprint_NoRegister()
	{
		return UQTMConnectLiveLinkBlueprint::StaticClass();
	}
	struct Z_Construct_UClass_UQTMConnectLiveLinkBlueprint_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UQTMConnectLiveLinkBlueprint_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_QTMConnectLiveLink,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UQTMConnectLiveLinkBlueprint_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UQTMConnectLiveLinkBlueprint_CreateQTMConnectLiveLinkSource, "CreateQTMConnectLiveLinkSource" }, // 1569796353
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UQTMConnectLiveLinkBlueprint_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "QTMConnectLiveLinkBlueprint.h" },
		{ "ModuleRelativePath", "Public/QTMConnectLiveLinkBlueprint.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UQTMConnectLiveLinkBlueprint_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UQTMConnectLiveLinkBlueprint>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UQTMConnectLiveLinkBlueprint_Statics::ClassParams = {
		&UQTMConnectLiveLinkBlueprint::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UQTMConnectLiveLinkBlueprint_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UQTMConnectLiveLinkBlueprint_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UQTMConnectLiveLinkBlueprint()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UQTMConnectLiveLinkBlueprint_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UQTMConnectLiveLinkBlueprint, 2169812921);
	template<> QTMCONNECTLIVELINK_API UClass* StaticClass<UQTMConnectLiveLinkBlueprint>()
	{
		return UQTMConnectLiveLinkBlueprint::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UQTMConnectLiveLinkBlueprint(Z_Construct_UClass_UQTMConnectLiveLinkBlueprint, &UQTMConnectLiveLinkBlueprint::StaticClass, TEXT("/Script/QTMConnectLiveLink"), TEXT("UQTMConnectLiveLinkBlueprint"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UQTMConnectLiveLinkBlueprint);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
