// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "QTMConnect/Classes/QualisysClient.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeQualisysClient() {}
// Cross Module References
	QTMCONNECT_API UScriptStruct* Z_Construct_UScriptStruct_FQualisysRigidBodyInfo();
	UPackage* Z_Construct_UPackage__Script_QTMConnect();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FQuat();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	QTMCONNECT_API UScriptStruct* Z_Construct_UScriptStruct_FQualisysTrajectoryInfo();
	QTMCONNECT_API UClass* Z_Construct_UClass_AQualisysClient_NoRegister();
	QTMCONNECT_API UClass* Z_Construct_UClass_AQualisysClient();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	QTMCONNECT_API UFunction* Z_Construct_UFunction_AQualisysClient_FindQualisysClient();
	ENGINE_API UClass* Z_Construct_UClass_UWorld_NoRegister();
	QTMCONNECT_API UFunction* Z_Construct_UFunction_AQualisysClient_GetMarkerPosition();
	QTMCONNECT_API UFunction* Z_Construct_UFunction_AQualisysClient_GetRigidBody();
// End Cross Module References
class UScriptStruct* FQualisysRigidBodyInfo::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern QTMCONNECT_API uint32 Get_Z_Construct_UScriptStruct_FQualisysRigidBodyInfo_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FQualisysRigidBodyInfo, Z_Construct_UPackage__Script_QTMConnect(), TEXT("QualisysRigidBodyInfo"), sizeof(FQualisysRigidBodyInfo), Get_Z_Construct_UScriptStruct_FQualisysRigidBodyInfo_Hash());
	}
	return Singleton;
}
template<> QTMCONNECT_API UScriptStruct* StaticStruct<FQualisysRigidBodyInfo>()
{
	return FQualisysRigidBodyInfo::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FQualisysRigidBodyInfo(FQualisysRigidBodyInfo::StaticStruct, TEXT("/Script/QTMConnect"), TEXT("QualisysRigidBodyInfo"), false, nullptr, nullptr);
static struct FScriptStruct_QTMConnect_StaticRegisterNativesFQualisysRigidBodyInfo
{
	FScriptStruct_QTMConnect_StaticRegisterNativesFQualisysRigidBodyInfo()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("QualisysRigidBodyInfo")),new UScriptStruct::TCppStructOps<FQualisysRigidBodyInfo>);
	}
} ScriptStruct_QTMConnect_StaticRegisterNativesFQualisysRigidBodyInfo;
	struct Z_Construct_UScriptStruct_FQualisysRigidBodyInfo_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Orientation_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Orientation;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Position_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Position;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FQualisysRigidBodyInfo_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "// RigidBody structure\n" },
		{ "ModuleRelativePath", "Classes/QualisysClient.h" },
		{ "ToolTip", "RigidBody structure" },
	};
#endif
	void* Z_Construct_UScriptStruct_FQualisysRigidBodyInfo_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FQualisysRigidBodyInfo>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FQualisysRigidBodyInfo_Statics::NewProp_Orientation_MetaData[] = {
		{ "Category", "Qualisys" },
		{ "Comment", "// Orientation of the rigid body\n" },
		{ "ModuleRelativePath", "Classes/QualisysClient.h" },
		{ "ToolTip", "Orientation of the rigid body" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FQualisysRigidBodyInfo_Statics::NewProp_Orientation = { "Orientation", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FQualisysRigidBodyInfo, Orientation), Z_Construct_UScriptStruct_FQuat, METADATA_PARAMS(Z_Construct_UScriptStruct_FQualisysRigidBodyInfo_Statics::NewProp_Orientation_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FQualisysRigidBodyInfo_Statics::NewProp_Orientation_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FQualisysRigidBodyInfo_Statics::NewProp_Position_MetaData[] = {
		{ "Category", "Qualisys" },
		{ "Comment", "// Position of the rigid body\n" },
		{ "ModuleRelativePath", "Classes/QualisysClient.h" },
		{ "ToolTip", "Position of the rigid body" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FQualisysRigidBodyInfo_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FQualisysRigidBodyInfo, Position), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FQualisysRigidBodyInfo_Statics::NewProp_Position_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FQualisysRigidBodyInfo_Statics::NewProp_Position_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FQualisysRigidBodyInfo_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FQualisysRigidBodyInfo_Statics::NewProp_Orientation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FQualisysRigidBodyInfo_Statics::NewProp_Position,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FQualisysRigidBodyInfo_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_QTMConnect,
		nullptr,
		&NewStructOps,
		"QualisysRigidBodyInfo",
		sizeof(FQualisysRigidBodyInfo),
		alignof(FQualisysRigidBodyInfo),
		Z_Construct_UScriptStruct_FQualisysRigidBodyInfo_Statics::PropPointers,
		ARRAY_COUNT(Z_Construct_UScriptStruct_FQualisysRigidBodyInfo_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FQualisysRigidBodyInfo_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FQualisysRigidBodyInfo_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FQualisysRigidBodyInfo()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FQualisysRigidBodyInfo_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_QTMConnect();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("QualisysRigidBodyInfo"), sizeof(FQualisysRigidBodyInfo), Get_Z_Construct_UScriptStruct_FQualisysRigidBodyInfo_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FQualisysRigidBodyInfo_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FQualisysRigidBodyInfo_Hash() { return 4065875164U; }
class UScriptStruct* FQualisysTrajectoryInfo::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern QTMCONNECT_API uint32 Get_Z_Construct_UScriptStruct_FQualisysTrajectoryInfo_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FQualisysTrajectoryInfo, Z_Construct_UPackage__Script_QTMConnect(), TEXT("QualisysTrajectoryInfo"), sizeof(FQualisysTrajectoryInfo), Get_Z_Construct_UScriptStruct_FQualisysTrajectoryInfo_Hash());
	}
	return Singleton;
}
template<> QTMCONNECT_API UScriptStruct* StaticStruct<FQualisysTrajectoryInfo>()
{
	return FQualisysTrajectoryInfo::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FQualisysTrajectoryInfo(FQualisysTrajectoryInfo::StaticStruct, TEXT("/Script/QTMConnect"), TEXT("QualisysTrajectoryInfo"), false, nullptr, nullptr);
static struct FScriptStruct_QTMConnect_StaticRegisterNativesFQualisysTrajectoryInfo
{
	FScriptStruct_QTMConnect_StaticRegisterNativesFQualisysTrajectoryInfo()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("QualisysTrajectoryInfo")),new UScriptStruct::TCppStructOps<FQualisysTrajectoryInfo>);
	}
} ScriptStruct_QTMConnect_StaticRegisterNativesFQualisysTrajectoryInfo;
	struct Z_Construct_UScriptStruct_FQualisysTrajectoryInfo_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Position_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Position;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FQualisysTrajectoryInfo_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "// Trajectory\n" },
		{ "ModuleRelativePath", "Classes/QualisysClient.h" },
		{ "ToolTip", "Trajectory" },
	};
#endif
	void* Z_Construct_UScriptStruct_FQualisysTrajectoryInfo_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FQualisysTrajectoryInfo>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FQualisysTrajectoryInfo_Statics::NewProp_Position_MetaData[] = {
		{ "Category", "Qualisys" },
		{ "Comment", "// Position of the trajectory\n" },
		{ "ModuleRelativePath", "Classes/QualisysClient.h" },
		{ "ToolTip", "Position of the trajectory" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FQualisysTrajectoryInfo_Statics::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FQualisysTrajectoryInfo, Position), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(Z_Construct_UScriptStruct_FQualisysTrajectoryInfo_Statics::NewProp_Position_MetaData, ARRAY_COUNT(Z_Construct_UScriptStruct_FQualisysTrajectoryInfo_Statics::NewProp_Position_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FQualisysTrajectoryInfo_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FQualisysTrajectoryInfo_Statics::NewProp_Position,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FQualisysTrajectoryInfo_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_QTMConnect,
		nullptr,
		&NewStructOps,
		"QualisysTrajectoryInfo",
		sizeof(FQualisysTrajectoryInfo),
		alignof(FQualisysTrajectoryInfo),
		Z_Construct_UScriptStruct_FQualisysTrajectoryInfo_Statics::PropPointers,
		ARRAY_COUNT(Z_Construct_UScriptStruct_FQualisysTrajectoryInfo_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FQualisysTrajectoryInfo_Statics::Struct_MetaDataParams, ARRAY_COUNT(Z_Construct_UScriptStruct_FQualisysTrajectoryInfo_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FQualisysTrajectoryInfo()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FQualisysTrajectoryInfo_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_QTMConnect();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("QualisysTrajectoryInfo"), sizeof(FQualisysTrajectoryInfo), Get_Z_Construct_UScriptStruct_FQualisysTrajectoryInfo_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FQualisysTrajectoryInfo_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FQualisysTrajectoryInfo_Hash() { return 1489275129U; }
	void AQualisysClient::StaticRegisterNativesAQualisysClient()
	{
		UClass* Class = AQualisysClient::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "FindQualisysClient", &AQualisysClient::execFindQualisysClient },
			{ "GetMarkerPosition", &AQualisysClient::execGetMarkerPosition },
			{ "GetRigidBody", &AQualisysClient::execGetRigidBody },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_AQualisysClient_FindQualisysClient_Statics
	{
		struct QualisysClient_eventFindQualisysClient_Parms
		{
			UWorld* World;
			AQualisysClient* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_World;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AQualisysClient_FindQualisysClient_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(QualisysClient_eventFindQualisysClient_Parms, ReturnValue), Z_Construct_UClass_AQualisysClient_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_AQualisysClient_FindQualisysClient_Statics::NewProp_World = { "World", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(QualisysClient_eventFindQualisysClient_Parms, World), Z_Construct_UClass_UWorld_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AQualisysClient_FindQualisysClient_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AQualisysClient_FindQualisysClient_Statics::NewProp_ReturnValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AQualisysClient_FindQualisysClient_Statics::NewProp_World,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AQualisysClient_FindQualisysClient_Statics::Function_MetaDataParams[] = {
		{ "Category", "Qualisys" },
		{ "Comment", "// Finding a Qualisys Client actor streaming object in the world.\n// @return The first AQualisysClient actor found in @World.\n" },
		{ "ModuleRelativePath", "Classes/QualisysClient.h" },
		{ "ToolTip", "Finding a Qualisys Client actor streaming object in the world.\n@return The first AQualisysClient actor found in @World." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AQualisysClient_FindQualisysClient_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AQualisysClient, nullptr, "FindQualisysClient", nullptr, nullptr, sizeof(QualisysClient_eventFindQualisysClient_Parms), Z_Construct_UFunction_AQualisysClient_FindQualisysClient_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UFunction_AQualisysClient_FindQualisysClient_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AQualisysClient_FindQualisysClient_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UFunction_AQualisysClient_FindQualisysClient_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AQualisysClient_FindQualisysClient()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AQualisysClient_FindQualisysClient_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AQualisysClient_GetMarkerPosition_Statics
	{
		struct QualisysClient_eventGetMarkerPosition_Parms
		{
			FName trajectoryName;
			FQualisysTrajectoryInfo trajectory;
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_trajectory;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_trajectoryName_MetaData[];
#endif
		static const UE4CodeGen_Private::FNamePropertyParams NewProp_trajectoryName;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_AQualisysClient_GetMarkerPosition_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((QualisysClient_eventGetMarkerPosition_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AQualisysClient_GetMarkerPosition_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(QualisysClient_eventGetMarkerPosition_Parms), &Z_Construct_UFunction_AQualisysClient_GetMarkerPosition_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AQualisysClient_GetMarkerPosition_Statics::NewProp_trajectory = { "trajectory", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(QualisysClient_eventGetMarkerPosition_Parms, trajectory), Z_Construct_UScriptStruct_FQualisysTrajectoryInfo, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AQualisysClient_GetMarkerPosition_Statics::NewProp_trajectoryName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FNamePropertyParams Z_Construct_UFunction_AQualisysClient_GetMarkerPosition_Statics::NewProp_trajectoryName = { "trajectoryName", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(QualisysClient_eventGetMarkerPosition_Parms, trajectoryName), METADATA_PARAMS(Z_Construct_UFunction_AQualisysClient_GetMarkerPosition_Statics::NewProp_trajectoryName_MetaData, ARRAY_COUNT(Z_Construct_UFunction_AQualisysClient_GetMarkerPosition_Statics::NewProp_trajectoryName_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AQualisysClient_GetMarkerPosition_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AQualisysClient_GetMarkerPosition_Statics::NewProp_ReturnValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AQualisysClient_GetMarkerPosition_Statics::NewProp_trajectory,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AQualisysClient_GetMarkerPosition_Statics::NewProp_trajectoryName,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AQualisysClient_GetMarkerPosition_Statics::Function_MetaDataParams[] = {
		{ "Category", "Qualisys" },
		{ "Comment", "// Retrieves available FQualisysTrajectory for the given trajectory name.\n// @param Name of the Trajectory\n// @param Trajectory Receives latest available trajectory position (if any).\n// @return True if any trajectory information was available for the specified name.\n" },
		{ "ModuleRelativePath", "Classes/QualisysClient.h" },
		{ "ToolTip", "Retrieves available FQualisysTrajectory for the given trajectory name.\n@param Name of the Trajectory\n@param Trajectory Receives latest available trajectory position (if any).\n@return True if any trajectory information was available for the specified name." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AQualisysClient_GetMarkerPosition_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AQualisysClient, nullptr, "GetMarkerPosition", nullptr, nullptr, sizeof(QualisysClient_eventGetMarkerPosition_Parms), Z_Construct_UFunction_AQualisysClient_GetMarkerPosition_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UFunction_AQualisysClient_GetMarkerPosition_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AQualisysClient_GetMarkerPosition_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UFunction_AQualisysClient_GetMarkerPosition_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AQualisysClient_GetMarkerPosition()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AQualisysClient_GetMarkerPosition_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_AQualisysClient_GetRigidBody_Statics
	{
		struct QualisysClient_eventGetRigidBody_Parms
		{
			FName rigidBodyName;
			FQualisysRigidBodyInfo rigidBody;
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_rigidBody;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_rigidBodyName_MetaData[];
#endif
		static const UE4CodeGen_Private::FNamePropertyParams NewProp_rigidBodyName;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_AQualisysClient_GetRigidBody_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((QualisysClient_eventGetRigidBody_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_AQualisysClient_GetRigidBody_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(QualisysClient_eventGetRigidBody_Parms), &Z_Construct_UFunction_AQualisysClient_GetRigidBody_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_AQualisysClient_GetRigidBody_Statics::NewProp_rigidBody = { "rigidBody", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(QualisysClient_eventGetRigidBody_Parms, rigidBody), Z_Construct_UScriptStruct_FQualisysRigidBodyInfo, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AQualisysClient_GetRigidBody_Statics::NewProp_rigidBodyName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FNamePropertyParams Z_Construct_UFunction_AQualisysClient_GetRigidBody_Statics::NewProp_rigidBodyName = { "rigidBodyName", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(QualisysClient_eventGetRigidBody_Parms, rigidBodyName), METADATA_PARAMS(Z_Construct_UFunction_AQualisysClient_GetRigidBody_Statics::NewProp_rigidBodyName_MetaData, ARRAY_COUNT(Z_Construct_UFunction_AQualisysClient_GetRigidBody_Statics::NewProp_rigidBodyName_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_AQualisysClient_GetRigidBody_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AQualisysClient_GetRigidBody_Statics::NewProp_ReturnValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AQualisysClient_GetRigidBody_Statics::NewProp_rigidBody,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_AQualisysClient_GetRigidBody_Statics::NewProp_rigidBodyName,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AQualisysClient_GetRigidBody_Statics::Function_MetaDataParams[] = {
		{ "Category", "Qualisys" },
		{ "Comment", "// Retrieves available FQualisysRigidBody for the given rigid body name.\n// @param Name of the rigid body\n// @param RigidBody Receives latest available rigid body transform (if any).\n// @return True if any rigid body transform was available for the specified name.\n" },
		{ "ModuleRelativePath", "Classes/QualisysClient.h" },
		{ "ToolTip", "Retrieves available FQualisysRigidBody for the given rigid body name.\n@param Name of the rigid body\n@param RigidBody Receives latest available rigid body transform (if any).\n@return True if any rigid body transform was available for the specified name." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_AQualisysClient_GetRigidBody_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AQualisysClient, nullptr, "GetRigidBody", nullptr, nullptr, sizeof(QualisysClient_eventGetRigidBody_Parms), Z_Construct_UFunction_AQualisysClient_GetRigidBody_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UFunction_AQualisysClient_GetRigidBody_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_AQualisysClient_GetRigidBody_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UFunction_AQualisysClient_GetRigidBody_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_AQualisysClient_GetRigidBody()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_AQualisysClient_GetRigidBody_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_AQualisysClient_NoRegister()
	{
		return AQualisysClient::StaticClass();
	}
	struct Z_Construct_UClass_AQualisysClient_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DebugDrawingTrajectories_MetaData[];
#endif
		static void NewProp_DebugDrawingTrajectories_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_DebugDrawingTrajectories;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DebugDrawingRigidBodies_MetaData[];
#endif
		static void NewProp_DebugDrawingRigidBodies_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_DebugDrawingRigidBodies;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_StreamRate_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_StreamRate;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_UdpPort_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_UdpPort;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_IPAddressToQTMServer_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_IPAddressToQTMServer;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AutoDiscoverQTMServer_MetaData[];
#endif
		static void NewProp_AutoDiscoverQTMServer_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_AutoDiscoverQTMServer;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AQualisysClient_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_QTMConnect,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_AQualisysClient_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_AQualisysClient_FindQualisysClient, "FindQualisysClient" }, // 1591220283
		{ &Z_Construct_UFunction_AQualisysClient_GetMarkerPosition, "GetMarkerPosition" }, // 1254306841
		{ &Z_Construct_UFunction_AQualisysClient_GetRigidBody, "GetRigidBody" }, // 611470656
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AQualisysClient_Statics::Class_MetaDataParams[] = {
		{ "Comment", "// Qualisys streaming client actor\n" },
		{ "IncludePath", "QualisysClient.h" },
		{ "ModuleRelativePath", "Classes/QualisysClient.h" },
		{ "ToolTip", "Qualisys streaming client actor" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AQualisysClient_Statics::NewProp_DebugDrawingTrajectories_MetaData[] = {
		{ "Category", "Qualisys" },
		{ "Comment", "// Debug flag for viewing all streamed labeled trajectories\n" },
		{ "ModuleRelativePath", "Classes/QualisysClient.h" },
		{ "ToolTip", "Debug flag for viewing all streamed labeled trajectories" },
	};
#endif
	void Z_Construct_UClass_AQualisysClient_Statics::NewProp_DebugDrawingTrajectories_SetBit(void* Obj)
	{
		((AQualisysClient*)Obj)->DebugDrawingTrajectories = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AQualisysClient_Statics::NewProp_DebugDrawingTrajectories = { "DebugDrawingTrajectories", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(AQualisysClient), &Z_Construct_UClass_AQualisysClient_Statics::NewProp_DebugDrawingTrajectories_SetBit, METADATA_PARAMS(Z_Construct_UClass_AQualisysClient_Statics::NewProp_DebugDrawingTrajectories_MetaData, ARRAY_COUNT(Z_Construct_UClass_AQualisysClient_Statics::NewProp_DebugDrawingTrajectories_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AQualisysClient_Statics::NewProp_DebugDrawingRigidBodies_MetaData[] = {
		{ "Category", "Qualisys" },
		{ "Comment", "// Debug flag for viewing all streamed rigid bodies and their coordinate systems\n" },
		{ "ModuleRelativePath", "Classes/QualisysClient.h" },
		{ "ToolTip", "Debug flag for viewing all streamed rigid bodies and their coordinate systems" },
	};
#endif
	void Z_Construct_UClass_AQualisysClient_Statics::NewProp_DebugDrawingRigidBodies_SetBit(void* Obj)
	{
		((AQualisysClient*)Obj)->DebugDrawingRigidBodies = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AQualisysClient_Statics::NewProp_DebugDrawingRigidBodies = { "DebugDrawingRigidBodies", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(AQualisysClient), &Z_Construct_UClass_AQualisysClient_Statics::NewProp_DebugDrawingRigidBodies_SetBit, METADATA_PARAMS(Z_Construct_UClass_AQualisysClient_Statics::NewProp_DebugDrawingRigidBodies_MetaData, ARRAY_COUNT(Z_Construct_UClass_AQualisysClient_Statics::NewProp_DebugDrawingRigidBodies_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AQualisysClient_Statics::NewProp_StreamRate_MetaData[] = {
		{ "Category", "Qualisys" },
		{ "Comment", "// Streaming rate (0 = As fast as possible)\n" },
		{ "ModuleRelativePath", "Classes/QualisysClient.h" },
		{ "ToolTip", "Streaming rate (0 = As fast as possible)" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AQualisysClient_Statics::NewProp_StreamRate = { "StreamRate", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AQualisysClient, StreamRate), METADATA_PARAMS(Z_Construct_UClass_AQualisysClient_Statics::NewProp_StreamRate_MetaData, ARRAY_COUNT(Z_Construct_UClass_AQualisysClient_Statics::NewProp_StreamRate_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AQualisysClient_Statics::NewProp_UdpPort_MetaData[] = {
		{ "Category", "Qualisys" },
		{ "Comment", "// UDP port for streaming (0 = uses TCP for streaming instead of UDP)\n" },
		{ "ModuleRelativePath", "Classes/QualisysClient.h" },
		{ "ToolTip", "UDP port for streaming (0 = uses TCP for streaming instead of UDP)" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AQualisysClient_Statics::NewProp_UdpPort = { "UdpPort", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AQualisysClient, UdpPort), METADATA_PARAMS(Z_Construct_UClass_AQualisysClient_Statics::NewProp_UdpPort_MetaData, ARRAY_COUNT(Z_Construct_UClass_AQualisysClient_Statics::NewProp_UdpPort_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AQualisysClient_Statics::NewProp_IPAddressToQTMServer_MetaData[] = {
		{ "Category", "Qualisys" },
		{ "Comment", "// IP address to the machine running Qualisys Track Manager\n" },
		{ "ModuleRelativePath", "Classes/QualisysClient.h" },
		{ "ToolTip", "IP address to the machine running Qualisys Track Manager" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_AQualisysClient_Statics::NewProp_IPAddressToQTMServer = { "IPAddressToQTMServer", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AQualisysClient, IPAddressToQTMServer), METADATA_PARAMS(Z_Construct_UClass_AQualisysClient_Statics::NewProp_IPAddressToQTMServer_MetaData, ARRAY_COUNT(Z_Construct_UClass_AQualisysClient_Statics::NewProp_IPAddressToQTMServer_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AQualisysClient_Statics::NewProp_AutoDiscoverQTMServer_MetaData[] = {
		{ "Category", "Qualisys" },
		{ "ModuleRelativePath", "Classes/QualisysClient.h" },
	};
#endif
	void Z_Construct_UClass_AQualisysClient_Statics::NewProp_AutoDiscoverQTMServer_SetBit(void* Obj)
	{
		((AQualisysClient*)Obj)->AutoDiscoverQTMServer = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_AQualisysClient_Statics::NewProp_AutoDiscoverQTMServer = { "AutoDiscoverQTMServer", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(AQualisysClient), &Z_Construct_UClass_AQualisysClient_Statics::NewProp_AutoDiscoverQTMServer_SetBit, METADATA_PARAMS(Z_Construct_UClass_AQualisysClient_Statics::NewProp_AutoDiscoverQTMServer_MetaData, ARRAY_COUNT(Z_Construct_UClass_AQualisysClient_Statics::NewProp_AutoDiscoverQTMServer_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AQualisysClient_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AQualisysClient_Statics::NewProp_DebugDrawingTrajectories,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AQualisysClient_Statics::NewProp_DebugDrawingRigidBodies,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AQualisysClient_Statics::NewProp_StreamRate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AQualisysClient_Statics::NewProp_UdpPort,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AQualisysClient_Statics::NewProp_IPAddressToQTMServer,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AQualisysClient_Statics::NewProp_AutoDiscoverQTMServer,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AQualisysClient_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AQualisysClient>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AQualisysClient_Statics::ClassParams = {
		&AQualisysClient::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_AQualisysClient_Statics::PropPointers,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		ARRAY_COUNT(FuncInfo),
		ARRAY_COUNT(Z_Construct_UClass_AQualisysClient_Statics::PropPointers),
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_AQualisysClient_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_AQualisysClient_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AQualisysClient()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AQualisysClient_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AQualisysClient, 1302141891);
	template<> QTMCONNECT_API UClass* StaticClass<AQualisysClient>()
	{
		return AQualisysClient::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AQualisysClient(Z_Construct_UClass_AQualisysClient, &AQualisysClient::StaticClass, TEXT("/Script/QTMConnect"), TEXT("AQualisysClient"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AQualisysClient);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
