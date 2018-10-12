// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "Public/QTMConnect.h"
#include "Classes/QualisysClient.h"
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
		extern QTMCONNECT_API uint32 Get_Z_Construct_UScriptStruct_FQualisysRigidBodyInfo_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FQualisysRigidBodyInfo, Z_Construct_UPackage__Script_QTMConnect(), TEXT("QualisysRigidBodyInfo"), sizeof(FQualisysRigidBodyInfo), Get_Z_Construct_UScriptStruct_FQualisysRigidBodyInfo_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FQualisysRigidBodyInfo(FQualisysRigidBodyInfo::StaticStruct, TEXT("/Script/QTMConnect"), TEXT("QualisysRigidBodyInfo"), false, nullptr, nullptr);
static struct FScriptStruct_QTMConnect_StaticRegisterNativesFQualisysRigidBodyInfo
{
	FScriptStruct_QTMConnect_StaticRegisterNativesFQualisysRigidBodyInfo()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("QualisysRigidBodyInfo")),new UScriptStruct::TCppStructOps<FQualisysRigidBodyInfo>);
	}
} ScriptStruct_QTMConnect_StaticRegisterNativesFQualisysRigidBodyInfo;
	UScriptStruct* Z_Construct_UScriptStruct_FQualisysRigidBodyInfo()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FQualisysRigidBodyInfo_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_QTMConnect();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("QualisysRigidBodyInfo"), sizeof(FQualisysRigidBodyInfo), Get_Z_Construct_UScriptStruct_FQualisysRigidBodyInfo_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "ModuleRelativePath", "Classes/QualisysClient.h" },
				{ "ToolTip", "RigidBody structure" },
			};
#endif
			auto NewStructOpsLambda = []() -> void* { return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FQualisysRigidBodyInfo>(); };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Orientation_MetaData[] = {
				{ "Category", "Qualisys" },
				{ "ModuleRelativePath", "Classes/QualisysClient.h" },
				{ "ToolTip", "Orientation of the rigid body" },
			};
#endif
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_Orientation = { UE4CodeGen_Private::EPropertyClass::Struct, "Orientation", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000014, 1, nullptr, STRUCT_OFFSET(FQualisysRigidBodyInfo, Orientation), Z_Construct_UScriptStruct_FQuat, METADATA_PARAMS(NewProp_Orientation_MetaData, ARRAY_COUNT(NewProp_Orientation_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Position_MetaData[] = {
				{ "Category", "Qualisys" },
				{ "ModuleRelativePath", "Classes/QualisysClient.h" },
				{ "ToolTip", "Position of the rigid body" },
			};
#endif
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_Position = { UE4CodeGen_Private::EPropertyClass::Struct, "Position", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000014, 1, nullptr, STRUCT_OFFSET(FQualisysRigidBodyInfo, Position), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(NewProp_Position_MetaData, ARRAY_COUNT(NewProp_Position_MetaData)) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Orientation,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Position,
			};
			static const UE4CodeGen_Private::FStructParams ReturnStructParams = {
				(UObject* (*)())Z_Construct_UPackage__Script_QTMConnect,
				nullptr,
				&UE4CodeGen_Private::TNewCppStructOpsWrapper<decltype(NewStructOpsLambda)>::NewCppStructOps,
				"QualisysRigidBodyInfo",
				RF_Public|RF_Transient|RF_MarkAsNative,
				EStructFlags(0x00000001),
				sizeof(FQualisysRigidBodyInfo),
				alignof(FQualisysRigidBodyInfo),
				PropPointers, ARRAY_COUNT(PropPointers),
				METADATA_PARAMS(Struct_MetaDataParams, ARRAY_COUNT(Struct_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FQualisysRigidBodyInfo_CRC() { return 2426608944U; }
class UScriptStruct* FQualisysTrajectoryInfo::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern QTMCONNECT_API uint32 Get_Z_Construct_UScriptStruct_FQualisysTrajectoryInfo_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FQualisysTrajectoryInfo, Z_Construct_UPackage__Script_QTMConnect(), TEXT("QualisysTrajectoryInfo"), sizeof(FQualisysTrajectoryInfo), Get_Z_Construct_UScriptStruct_FQualisysTrajectoryInfo_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FQualisysTrajectoryInfo(FQualisysTrajectoryInfo::StaticStruct, TEXT("/Script/QTMConnect"), TEXT("QualisysTrajectoryInfo"), false, nullptr, nullptr);
static struct FScriptStruct_QTMConnect_StaticRegisterNativesFQualisysTrajectoryInfo
{
	FScriptStruct_QTMConnect_StaticRegisterNativesFQualisysTrajectoryInfo()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("QualisysTrajectoryInfo")),new UScriptStruct::TCppStructOps<FQualisysTrajectoryInfo>);
	}
} ScriptStruct_QTMConnect_StaticRegisterNativesFQualisysTrajectoryInfo;
	UScriptStruct* Z_Construct_UScriptStruct_FQualisysTrajectoryInfo()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FQualisysTrajectoryInfo_CRC();
		UPackage* Outer = Z_Construct_UPackage__Script_QTMConnect();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("QualisysTrajectoryInfo"), sizeof(FQualisysTrajectoryInfo), Get_Z_Construct_UScriptStruct_FQualisysTrajectoryInfo_CRC(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "ModuleRelativePath", "Classes/QualisysClient.h" },
				{ "ToolTip", "Trajectory" },
			};
#endif
			auto NewStructOpsLambda = []() -> void* { return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FQualisysTrajectoryInfo>(); };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Position_MetaData[] = {
				{ "Category", "Qualisys" },
				{ "ModuleRelativePath", "Classes/QualisysClient.h" },
				{ "ToolTip", "Position of the trajectory" },
			};
#endif
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_Position = { UE4CodeGen_Private::EPropertyClass::Struct, "Position", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000014, 1, nullptr, STRUCT_OFFSET(FQualisysTrajectoryInfo, Position), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(NewProp_Position_MetaData, ARRAY_COUNT(NewProp_Position_MetaData)) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Position,
			};
			static const UE4CodeGen_Private::FStructParams ReturnStructParams = {
				(UObject* (*)())Z_Construct_UPackage__Script_QTMConnect,
				nullptr,
				&UE4CodeGen_Private::TNewCppStructOpsWrapper<decltype(NewStructOpsLambda)>::NewCppStructOps,
				"QualisysTrajectoryInfo",
				RF_Public|RF_Transient|RF_MarkAsNative,
				EStructFlags(0x00000001),
				sizeof(FQualisysTrajectoryInfo),
				alignof(FQualisysTrajectoryInfo),
				PropPointers, ARRAY_COUNT(PropPointers),
				METADATA_PARAMS(Struct_MetaDataParams, ARRAY_COUNT(Struct_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FQualisysTrajectoryInfo_CRC() { return 2332650283U; }
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
	UFunction* Z_Construct_UFunction_AQualisysClient_FindQualisysClient()
	{
		struct QualisysClient_eventFindQualisysClient_Parms
		{
			UWorld* World;
			AQualisysClient* ReturnValue;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue = { UE4CodeGen_Private::EPropertyClass::Object, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000580, 1, nullptr, STRUCT_OFFSET(QualisysClient_eventFindQualisysClient_Parms, ReturnValue), Z_Construct_UClass_AQualisysClient_NoRegister, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FObjectPropertyParams NewProp_World = { UE4CodeGen_Private::EPropertyClass::Object, "World", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(QualisysClient_eventFindQualisysClient_Parms, World), Z_Construct_UClass_UWorld_NoRegister, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_World,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "Qualisys" },
				{ "ModuleRelativePath", "Classes/QualisysClient.h" },
				{ "ToolTip", "Convenience function for finding a Qualisys Client actor streaming object.\n@return The first AQualisysClient actor found in @World." },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_AQualisysClient, "FindQualisysClient", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04022401, sizeof(QualisysClient_eventFindQualisysClient_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_AQualisysClient_GetMarkerPosition()
	{
		struct QualisysClient_eventGetMarkerPosition_Parms
		{
			FString trajectoryName;
			FQualisysTrajectoryInfo trajectory;
			bool ReturnValue;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			auto NewProp_ReturnValue_SetBit = [](void* Obj){ ((QualisysClient_eventGetMarkerPosition_Parms*)Obj)->ReturnValue = 1; };
			static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue = { UE4CodeGen_Private::EPropertyClass::Bool, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000580, 1, nullptr, sizeof(bool), UE4CodeGen_Private::ENativeBool::Native, sizeof(QualisysClient_eventGetMarkerPosition_Parms), &UE4CodeGen_Private::TBoolSetBitWrapper<decltype(NewProp_ReturnValue_SetBit)>::SetBit, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_trajectory = { UE4CodeGen_Private::EPropertyClass::Struct, "trajectory", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000180, 1, nullptr, STRUCT_OFFSET(QualisysClient_eventGetMarkerPosition_Parms, trajectory), Z_Construct_UScriptStruct_FQualisysTrajectoryInfo, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FStrPropertyParams NewProp_trajectoryName = { UE4CodeGen_Private::EPropertyClass::Str, "trajectoryName", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(QualisysClient_eventGetMarkerPosition_Parms, trajectoryName), METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_trajectory,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_trajectoryName,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "Qualisys" },
				{ "ModuleRelativePath", "Classes/QualisysClient.h" },
				{ "ToolTip", "Retrieves available FQualisysTrajectory for the given trajectory name.\n@param Name of the Trajectory\n@param Trajectory Receives latest available trajectory position (if any).\n@return True if any trajectory information was available for the specified name." },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_AQualisysClient, "GetMarkerPosition", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04420401, sizeof(QualisysClient_eventGetMarkerPosition_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_AQualisysClient_GetRigidBody()
	{
		struct QualisysClient_eventGetRigidBody_Parms
		{
			FString rigidBodyName;
			FQualisysRigidBodyInfo rigidBody;
			bool ReturnValue;
		};
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			auto NewProp_ReturnValue_SetBit = [](void* Obj){ ((QualisysClient_eventGetRigidBody_Parms*)Obj)->ReturnValue = 1; };
			static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue = { UE4CodeGen_Private::EPropertyClass::Bool, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000580, 1, nullptr, sizeof(bool), UE4CodeGen_Private::ENativeBool::Native, sizeof(QualisysClient_eventGetRigidBody_Parms), &UE4CodeGen_Private::TBoolSetBitWrapper<decltype(NewProp_ReturnValue_SetBit)>::SetBit, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FStructPropertyParams NewProp_rigidBody = { UE4CodeGen_Private::EPropertyClass::Struct, "rigidBody", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000180, 1, nullptr, STRUCT_OFFSET(QualisysClient_eventGetRigidBody_Parms, rigidBody), Z_Construct_UScriptStruct_FQualisysRigidBodyInfo, METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FStrPropertyParams NewProp_rigidBodyName = { UE4CodeGen_Private::EPropertyClass::Str, "rigidBodyName", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(QualisysClient_eventGetRigidBody_Parms, rigidBodyName), METADATA_PARAMS(nullptr, 0) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_rigidBody,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_rigidBodyName,
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
				{ "Category", "Qualisys" },
				{ "ModuleRelativePath", "Classes/QualisysClient.h" },
				{ "ToolTip", "Retrieves available FQualisysRigidBody for the given rigid body name.\n@param Name of the rigid body\n@param RigidBody Receives latest available rigid body transform (if any).\n@return True if any rigid body transform was available for the specified name." },
			};
#endif
			static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_AQualisysClient, "GetRigidBody", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04420401, sizeof(QualisysClient_eventGetRigidBody_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_AQualisysClient_NoRegister()
	{
		return AQualisysClient::StaticClass();
	}
	UClass* Z_Construct_UClass_AQualisysClient()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			static UObject* (*const DependentSingletons[])() = {
				(UObject* (*)())Z_Construct_UClass_AActor,
				(UObject* (*)())Z_Construct_UPackage__Script_QTMConnect,
			};
			static const FClassFunctionLinkInfo FuncInfo[] = {
				{ &Z_Construct_UFunction_AQualisysClient_FindQualisysClient, "FindQualisysClient" }, // 3620218942
				{ &Z_Construct_UFunction_AQualisysClient_GetMarkerPosition, "GetMarkerPosition" }, // 1536069783
				{ &Z_Construct_UFunction_AQualisysClient_GetRigidBody, "GetRigidBody" }, // 1827244323
			};
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
				{ "IncludePath", "QualisysClient.h" },
				{ "ModuleRelativePath", "Classes/QualisysClient.h" },
				{ "ToolTip", "Qualisys streaming client actor" },
			};
#endif
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DebugDrawing_MetaData[] = {
				{ "Category", "Qualisys" },
				{ "ModuleRelativePath", "Classes/QualisysClient.h" },
				{ "ToolTip", "Debug flag for viewing all rigid body coordinate system and all labeled trajectories" },
			};
#endif
			auto NewProp_DebugDrawing_SetBit = [](void* Obj){ ((AQualisysClient*)Obj)->DebugDrawing = 1; };
			static const UE4CodeGen_Private::FBoolPropertyParams NewProp_DebugDrawing = { UE4CodeGen_Private::EPropertyClass::Bool, "DebugDrawing", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000005, 1, nullptr, sizeof(bool), UE4CodeGen_Private::ENativeBool::Native, sizeof(AQualisysClient), &UE4CodeGen_Private::TBoolSetBitWrapper<decltype(NewProp_DebugDrawing_SetBit)>::SetBit, METADATA_PARAMS(NewProp_DebugDrawing_MetaData, ARRAY_COUNT(NewProp_DebugDrawing_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_StreamRate_MetaData[] = {
				{ "Category", "Qualisys" },
				{ "ModuleRelativePath", "Classes/QualisysClient.h" },
				{ "ToolTip", "Streaming rate (0 = As fast as possible)" },
			};
#endif
			static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_StreamRate = { UE4CodeGen_Private::EPropertyClass::Int, "StreamRate", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000005, 1, nullptr, STRUCT_OFFSET(AQualisysClient, StreamRate), METADATA_PARAMS(NewProp_StreamRate_MetaData, ARRAY_COUNT(NewProp_StreamRate_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_UdpPort_MetaData[] = {
				{ "Category", "Qualisys" },
				{ "ModuleRelativePath", "Classes/QualisysClient.h" },
				{ "ToolTip", "UDP port for streaming (0 = uses TCP for streaming instead of UDP)" },
			};
#endif
			static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_UdpPort = { UE4CodeGen_Private::EPropertyClass::Int, "UdpPort", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000005, 1, nullptr, STRUCT_OFFSET(AQualisysClient, UdpPort), METADATA_PARAMS(NewProp_UdpPort_MetaData, ARRAY_COUNT(NewProp_UdpPort_MetaData)) };
#if WITH_METADATA
			static const UE4CodeGen_Private::FMetaDataPairParam NewProp_IPAddressToQTMServer_MetaData[] = {
				{ "Category", "Qualisys" },
				{ "ModuleRelativePath", "Classes/QualisysClient.h" },
				{ "ToolTip", "IP address to the machine running Qualisys Track Manager" },
			};
#endif
			static const UE4CodeGen_Private::FStrPropertyParams NewProp_IPAddressToQTMServer = { UE4CodeGen_Private::EPropertyClass::Str, "IPAddressToQTMServer", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000005, 1, nullptr, STRUCT_OFFSET(AQualisysClient, IPAddressToQTMServer), METADATA_PARAMS(NewProp_IPAddressToQTMServer_MetaData, ARRAY_COUNT(NewProp_IPAddressToQTMServer_MetaData)) };
			static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_DebugDrawing,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_StreamRate,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_UdpPort,
				(const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_IPAddressToQTMServer,
			};
			static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
				TCppClassTypeTraits<AQualisysClient>::IsAbstract,
			};
			static const UE4CodeGen_Private::FClassParams ClassParams = {
				&AQualisysClient::StaticClass,
				DependentSingletons, ARRAY_COUNT(DependentSingletons),
				0x00900080u,
				FuncInfo, ARRAY_COUNT(FuncInfo),
				PropPointers, ARRAY_COUNT(PropPointers),
				nullptr,
				&StaticCppClassTypeInfo,
				nullptr, 0,
				METADATA_PARAMS(Class_MetaDataParams, ARRAY_COUNT(Class_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUClass(OuterClass, ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AQualisysClient, 4082633167);
	static FCompiledInDefer Z_CompiledInDefer_UClass_AQualisysClient(Z_Construct_UClass_AQualisysClient, &AQualisysClient::StaticClass, TEXT("/Script/QTMConnect"), TEXT("AQualisysClient"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AQualisysClient);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
