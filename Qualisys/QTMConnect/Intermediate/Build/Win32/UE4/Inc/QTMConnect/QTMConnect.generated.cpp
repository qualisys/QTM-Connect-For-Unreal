// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "GeneratedCppIncludes.h"
#include "../../../../../../../../../Program Files/Epic Games/UE_4.16/Engine/Source/Runtime/Core/Public/CoreMinimal.h"
#include "QTMConnect.generated.dep.h"
PRAGMA_DISABLE_OPTIMIZATION
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCode1QTMConnect() {}
#if USE_COMPILED_IN_NATIVES
// Cross Module References
	COREUOBJECT_API class UScriptStruct* Z_Construct_UScriptStruct_FQuat();
	COREUOBJECT_API class UScriptStruct* Z_Construct_UScriptStruct_FVector();
	ENGINE_API class UClass* Z_Construct_UClass_UWorld_NoRegister();
	ENGINE_API class UClass* Z_Construct_UClass_AActor();
	ENGINE_API class UClass* Z_Construct_UClass_UActorComponent();

	QTMCONNECT_API class UScriptStruct* Z_Construct_UScriptStruct_FQualisysRigidBodyPose();
	QTMCONNECT_API class UFunction* Z_Construct_UFunction_AQualisysClient_FindQualisysClient();
	QTMCONNECT_API class UFunction* Z_Construct_UFunction_AQualisysClient_GetRigidBodyPose();
	QTMCONNECT_API class UClass* Z_Construct_UClass_AQualisysClient_NoRegister();
	QTMCONNECT_API class UClass* Z_Construct_UClass_AQualisysClient();
	QTMCONNECT_API class UClass* Z_Construct_UClass_UQualisysRigidBody_NoRegister();
	QTMCONNECT_API class UClass* Z_Construct_UClass_UQualisysRigidBody();
	QTMCONNECT_API class UPackage* Z_Construct_UPackage__Script_QTMConnect();
class UScriptStruct* FQualisysRigidBodyPose::StaticStruct()
{
	extern QTMCONNECT_API class UPackage* Z_Construct_UPackage__Script_QTMConnect();
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern QTMCONNECT_API class UScriptStruct* Z_Construct_UScriptStruct_FQualisysRigidBodyPose();
		extern QTMCONNECT_API uint32 Get_Z_Construct_UScriptStruct_FQualisysRigidBodyPose_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FQualisysRigidBodyPose, Z_Construct_UPackage__Script_QTMConnect(), TEXT("QualisysRigidBodyPose"), sizeof(FQualisysRigidBodyPose), Get_Z_Construct_UScriptStruct_FQualisysRigidBodyPose_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FQualisysRigidBodyPose(FQualisysRigidBodyPose::StaticStruct, TEXT("/Script/QTMConnect"), TEXT("QualisysRigidBodyPose"), false, nullptr, nullptr);
static struct FScriptStruct_QTMConnect_StaticRegisterNativesFQualisysRigidBodyPose
{
	FScriptStruct_QTMConnect_StaticRegisterNativesFQualisysRigidBodyPose()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("QualisysRigidBodyPose")),new UScriptStruct::TCppStructOps<FQualisysRigidBodyPose>);
	}
} ScriptStruct_QTMConnect_StaticRegisterNativesFQualisysRigidBodyPose;
	UScriptStruct* Z_Construct_UScriptStruct_FQualisysRigidBodyPose()
	{
		UPackage* Outer = Z_Construct_UPackage__Script_QTMConnect();
		extern uint32 Get_Z_Construct_UScriptStruct_FQualisysRigidBodyPose_CRC();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("QualisysRigidBodyPose"), sizeof(FQualisysRigidBodyPose), Get_Z_Construct_UScriptStruct_FQualisysRigidBodyPose_CRC(), false);
		if (!ReturnStruct)
		{
			ReturnStruct = new(EC_InternalUseOnlyConstructor, Outer, TEXT("QualisysRigidBodyPose"), RF_Public|RF_Transient|RF_MarkAsNative) UScriptStruct(FObjectInitializer(), NULL, new UScriptStruct::TCppStructOps<FQualisysRigidBodyPose>, EStructFlags(0x00000001));
			UProperty* NewProp_Orientation = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("Orientation"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(CPP_PROPERTY_BASE(Orientation, FQualisysRigidBodyPose), 0x0010000000000014, Z_Construct_UScriptStruct_FQuat());
			UProperty* NewProp_Position = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("Position"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(CPP_PROPERTY_BASE(Position, FQualisysRigidBodyPose), 0x0010000000000014, Z_Construct_UScriptStruct_FVector());
			ReturnStruct->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnStruct->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnStruct, TEXT("BlueprintType"), TEXT("true"));
			MetaData->SetValue(ReturnStruct, TEXT("ModuleRelativePath"), TEXT("Classes/QualisysClient.h"));
			MetaData->SetValue(ReturnStruct, TEXT("ToolTip"), TEXT("// Marker\nUSTRUCT(BlueprintType)\nstruct FQualisysMarker\n{\n    GENERATED_USTRUCT_BODY()\n\n    // Position of the marker\n    UPROPERTY(BlueprintReadOnly, Category = \"Qualisys\")\n    FVector Position;\n};\n// RigidBodyPose structure"));
			MetaData->SetValue(NewProp_Orientation, TEXT("Category"), TEXT("Qualisys"));
			MetaData->SetValue(NewProp_Orientation, TEXT("ModuleRelativePath"), TEXT("Classes/QualisysClient.h"));
			MetaData->SetValue(NewProp_Orientation, TEXT("ToolTip"), TEXT("Orientation of the rigid body"));
			MetaData->SetValue(NewProp_Position, TEXT("Category"), TEXT("Qualisys"));
			MetaData->SetValue(NewProp_Position, TEXT("ModuleRelativePath"), TEXT("Classes/QualisysClient.h"));
			MetaData->SetValue(NewProp_Position, TEXT("ToolTip"), TEXT("Position of the rigid body"));
#endif
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FQualisysRigidBodyPose_CRC() { return 3475762377U; }
	void AQualisysClient::StaticRegisterNativesAQualisysClient()
	{
		UClass* Class = AQualisysClient::StaticClass();
		static const TNameNativePtrPair<ANSICHAR> AnsiFuncs[] = {
			{ "FindQualisysClient", (Native)&AQualisysClient::execFindQualisysClient },
			{ "GetRigidBodyPose", (Native)&AQualisysClient::execGetRigidBodyPose },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, AnsiFuncs, 2);
	}
	UFunction* Z_Construct_UFunction_AQualisysClient_FindQualisysClient()
	{
		struct QualisysClient_eventFindQualisysClient_Parms
		{
			UWorld* World;
			AQualisysClient* ReturnValue;
		};
		UObject* Outer=Z_Construct_UClass_AQualisysClient();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("FindQualisysClient"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), NULL, 0x04022401, 65535, sizeof(QualisysClient_eventFindQualisysClient_Parms));
			UProperty* NewProp_ReturnValue = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("ReturnValue"), RF_Public|RF_Transient|RF_MarkAsNative) UObjectProperty(CPP_PROPERTY_BASE(ReturnValue, QualisysClient_eventFindQualisysClient_Parms), 0x0010000000000580, Z_Construct_UClass_AQualisysClient_NoRegister());
			UProperty* NewProp_World = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("World"), RF_Public|RF_Transient|RF_MarkAsNative) UObjectProperty(CPP_PROPERTY_BASE(World, QualisysClient_eventFindQualisysClient_Parms), 0x0010000000000080, Z_Construct_UClass_UWorld_NoRegister());
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Qualisys"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Classes/QualisysClient.h"));
			MetaData->SetValue(ReturnFunction, TEXT("ToolTip"), TEXT("* Convenience function for finding a Qualisys Client actor streaming object.\n* @return The first AQualisysClient actor found in @World."));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_AQualisysClient_GetRigidBodyPose()
	{
		struct QualisysClient_eventGetRigidBodyPose_Parms
		{
			FString RigidBody;
			FQualisysRigidBodyPose RigidBodyPose;
			bool ReturnValue;
		};
		UObject* Outer=Z_Construct_UClass_AQualisysClient();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("GetRigidBodyPose"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), NULL, 0x04420401, 65535, sizeof(QualisysClient_eventGetRigidBodyPose_Parms));
			CPP_BOOL_PROPERTY_BITMASK_STRUCT(ReturnValue, QualisysClient_eventGetRigidBodyPose_Parms, bool);
			UProperty* NewProp_ReturnValue = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("ReturnValue"), RF_Public|RF_Transient|RF_MarkAsNative) UBoolProperty(FObjectInitializer(), EC_CppProperty, CPP_BOOL_PROPERTY_OFFSET(ReturnValue, QualisysClient_eventGetRigidBodyPose_Parms), 0x0010000000000580, CPP_BOOL_PROPERTY_BITMASK(ReturnValue, QualisysClient_eventGetRigidBodyPose_Parms), sizeof(bool), true);
			UProperty* NewProp_RigidBodyPose = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("RigidBodyPose"), RF_Public|RF_Transient|RF_MarkAsNative) UStructProperty(CPP_PROPERTY_BASE(RigidBodyPose, QualisysClient_eventGetRigidBodyPose_Parms), 0x0010000000000180, Z_Construct_UScriptStruct_FQualisysRigidBodyPose());
			UProperty* NewProp_RigidBody = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("RigidBody"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(RigidBody, QualisysClient_eventGetRigidBodyPose_Parms), 0x0010000000000080);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Qualisys"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Classes/QualisysClient.h"));
			MetaData->SetValue(ReturnFunction, TEXT("ToolTip"), TEXT("* Retrieves available FQualisysRigidBodyPose for the rigid body.\n* The translation of the Qualisys Client actor is applied to the pose.\n*\n* @param RigidBody Name of the rigid body\n* @param RigidBodyPose Receives latest available rigid body state (if any).\n* @return True if any rigid body state was available for the specified name."));
#endif
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_AQualisysClient_NoRegister()
	{
		return AQualisysClient::StaticClass();
	}
	UClass* Z_Construct_UClass_AQualisysClient()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_AActor();
			Z_Construct_UPackage__Script_QTMConnect();
			OuterClass = AQualisysClient::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= 0x20900080;

				OuterClass->LinkChild(Z_Construct_UFunction_AQualisysClient_FindQualisysClient());
				OuterClass->LinkChild(Z_Construct_UFunction_AQualisysClient_GetRigidBodyPose());

PRAGMA_DISABLE_DEPRECATION_WARNINGS
				UProperty* NewProp_StreamRate = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("StreamRate"), RF_Public|RF_Transient|RF_MarkAsNative) UUnsizedIntProperty(CPP_PROPERTY_BASE(StreamRate, AQualisysClient), 0x0010000000000005);
				UProperty* NewProp_UdpPort = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("UdpPort"), RF_Public|RF_Transient|RF_MarkAsNative) UUnsizedIntProperty(CPP_PROPERTY_BASE(UdpPort, AQualisysClient), 0x0010000000000005);
				UProperty* NewProp_IPAddressToQTMServer = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("IPAddressToQTMServer"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(IPAddressToQTMServer, AQualisysClient), 0x0010000000000005);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_AQualisysClient_FindQualisysClient(), "FindQualisysClient"); // 3896889613
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_AQualisysClient_GetRigidBodyPose(), "GetRigidBodyPose"); // 4011714212
				static TCppClassTypeInfo<TCppClassTypeTraits<AQualisysClient> > StaticCppClassTypeInfo;
				OuterClass->SetCppTypeInfo(&StaticCppClassTypeInfo);
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("QualisysClient.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("Classes/QualisysClient.h"));
				MetaData->SetValue(OuterClass, TEXT("ToolTip"), TEXT("Qualisys streaming client actor"));
				MetaData->SetValue(NewProp_StreamRate, TEXT("Category"), TEXT("Qualisys"));
				MetaData->SetValue(NewProp_StreamRate, TEXT("ModuleRelativePath"), TEXT("Classes/QualisysClient.h"));
				MetaData->SetValue(NewProp_StreamRate, TEXT("ToolTip"), TEXT("Streaming rate (0 = As fast as possible)"));
				MetaData->SetValue(NewProp_UdpPort, TEXT("Category"), TEXT("Qualisys"));
				MetaData->SetValue(NewProp_UdpPort, TEXT("ModuleRelativePath"), TEXT("Classes/QualisysClient.h"));
				MetaData->SetValue(NewProp_UdpPort, TEXT("ToolTip"), TEXT("UDP port for streaming (0 = uses TCP for streaming instead of UDP)"));
				MetaData->SetValue(NewProp_IPAddressToQTMServer, TEXT("Category"), TEXT("Qualisys"));
				MetaData->SetValue(NewProp_IPAddressToQTMServer, TEXT("ModuleRelativePath"), TEXT("Classes/QualisysClient.h"));
				MetaData->SetValue(NewProp_IPAddressToQTMServer, TEXT("ToolTip"), TEXT("IP address to the machine running Qualisys Track Manager"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	IMPLEMENT_CLASS(AQualisysClient, 3136015629);
	static FCompiledInDefer Z_CompiledInDefer_UClass_AQualisysClient(Z_Construct_UClass_AQualisysClient, &AQualisysClient::StaticClass, TEXT("/Script/QTMConnect"), TEXT("AQualisysClient"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AQualisysClient);
	void UQualisysRigidBody::StaticRegisterNativesUQualisysRigidBody()
	{
	}
	UClass* Z_Construct_UClass_UQualisysRigidBody_NoRegister()
	{
		return UQualisysRigidBody::StaticClass();
	}
	UClass* Z_Construct_UClass_UQualisysRigidBody()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_UActorComponent();
			Z_Construct_UPackage__Script_QTMConnect();
			OuterClass = UQualisysRigidBody::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= 0x20B00080;


PRAGMA_DISABLE_DEPRECATION_WARNINGS
				UProperty* NewProp_QualisysClient = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("QualisysClient"), RF_Public|RF_Transient|RF_MarkAsNative) UObjectProperty(CPP_PROPERTY_BASE(QualisysClient, UQualisysRigidBody), 0x0010040000000005, Z_Construct_UClass_AQualisysClient_NoRegister());
				UProperty* NewProp_Name = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("Name"), RF_Public|RF_Transient|RF_MarkAsNative) UStrProperty(CPP_PROPERTY_BASE(Name, UQualisysRigidBody), 0x0010000000000005);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
				static TCppClassTypeInfo<TCppClassTypeTraits<UQualisysRigidBody> > StaticCppClassTypeInfo;
				OuterClass->SetCppTypeInfo(&StaticCppClassTypeInfo);
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("BlueprintSpawnableComponent"), TEXT(""));
				MetaData->SetValue(OuterClass, TEXT("ClassGroupNames"), TEXT("Qualisys"));
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("QualisysRigidBody.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("Classes/QualisysRigidBody.h"));
				MetaData->SetValue(OuterClass, TEXT("ToolTip"), TEXT("RigidBody component"));
				MetaData->SetValue(NewProp_QualisysClient, TEXT("Category"), TEXT("Qualisys"));
				MetaData->SetValue(NewProp_QualisysClient, TEXT("ModuleRelativePath"), TEXT("Classes/QualisysRigidBody.h"));
				MetaData->SetValue(NewProp_QualisysClient, TEXT("ToolTip"), TEXT("Set to the Qualisys Client actor. If not set it will default to the first found in the World."));
				MetaData->SetValue(NewProp_Name, TEXT("Category"), TEXT("Qualisys"));
				MetaData->SetValue(NewProp_Name, TEXT("ModuleRelativePath"), TEXT("Classes/QualisysRigidBody.h"));
				MetaData->SetValue(NewProp_Name, TEXT("ToolTip"), TEXT("Name of the rigid body"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	IMPLEMENT_CLASS(UQualisysRigidBody, 4268397808);
	static FCompiledInDefer Z_CompiledInDefer_UClass_UQualisysRigidBody(Z_Construct_UClass_UQualisysRigidBody, &UQualisysRigidBody::StaticClass, TEXT("/Script/QTMConnect"), TEXT("UQualisysRigidBody"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UQualisysRigidBody);
	UPackage* Z_Construct_UPackage__Script_QTMConnect()
	{
		static UPackage* ReturnPackage = nullptr;
		if (!ReturnPackage)
		{
			ReturnPackage = CastChecked<UPackage>(StaticFindObjectFast(UPackage::StaticClass(), nullptr, FName(TEXT("/Script/QTMConnect")), false, false));
			ReturnPackage->SetPackageFlags(PKG_CompiledIn | 0x00000000);
			FGuid Guid;
			Guid.A = 0x219C9BA6;
			Guid.B = 0x3A72DD14;
			Guid.C = 0x00000000;
			Guid.D = 0x00000000;
			ReturnPackage->SetGuid(Guid);

		}
		return ReturnPackage;
	}
#endif
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
PRAGMA_ENABLE_OPTIMIZATION
