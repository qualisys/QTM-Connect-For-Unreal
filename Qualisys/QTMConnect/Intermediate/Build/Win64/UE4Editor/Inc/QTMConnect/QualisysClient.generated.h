// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectMacros.h"
#include "ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UWorld;
class AQualisysClient;
struct FQualisysTrajectoryInfo;
struct FQualisysRigidBodyInfo;
#ifdef QTMCONNECT_QualisysClient_generated_h
#error "QualisysClient.generated.h already included, missing '#pragma once' in QualisysClient.h"
#endif
#define QTMCONNECT_QualisysClient_generated_h

#define UE419Clean_Plugins_Qualisys_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_29_GENERATED_BODY \
	friend QTMCONNECT_API class UScriptStruct* Z_Construct_UScriptStruct_FQualisysRigidBodyInfo(); \
	QTMCONNECT_API static class UScriptStruct* StaticStruct();


#define UE419Clean_Plugins_Qualisys_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_16_GENERATED_BODY \
	friend QTMCONNECT_API class UScriptStruct* Z_Construct_UScriptStruct_FQualisysTrajectoryInfo(); \
	QTMCONNECT_API static class UScriptStruct* StaticStruct();


#define UE419Clean_Plugins_Qualisys_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_61_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execFindQualisysClient) \
	{ \
		P_GET_OBJECT(UWorld,Z_Param_World); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(AQualisysClient**)Z_Param__Result=AQualisysClient::FindQualisysClient(Z_Param_World); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetMarkerPosition) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_trajectoryName); \
		P_GET_STRUCT_REF(FQualisysTrajectoryInfo,Z_Param_Out_trajectory); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->GetMarkerPosition(Z_Param_trajectoryName,Z_Param_Out_trajectory); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetRigidBody) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_rigidBodyName); \
		P_GET_STRUCT_REF(FQualisysRigidBodyInfo,Z_Param_Out_rigidBody); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->GetRigidBody(Z_Param_rigidBodyName,Z_Param_Out_rigidBody); \
		P_NATIVE_END; \
	}


#define UE419Clean_Plugins_Qualisys_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_61_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execFindQualisysClient) \
	{ \
		P_GET_OBJECT(UWorld,Z_Param_World); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(AQualisysClient**)Z_Param__Result=AQualisysClient::FindQualisysClient(Z_Param_World); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetMarkerPosition) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_trajectoryName); \
		P_GET_STRUCT_REF(FQualisysTrajectoryInfo,Z_Param_Out_trajectory); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->GetMarkerPosition(Z_Param_trajectoryName,Z_Param_Out_trajectory); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetRigidBody) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_rigidBodyName); \
		P_GET_STRUCT_REF(FQualisysRigidBodyInfo,Z_Param_Out_rigidBody); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=P_THIS->GetRigidBody(Z_Param_rigidBodyName,Z_Param_Out_rigidBody); \
		P_NATIVE_END; \
	}


#define UE419Clean_Plugins_Qualisys_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_61_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAQualisysClient(); \
	friend QTMCONNECT_API class UClass* Z_Construct_UClass_AQualisysClient(); \
public: \
	DECLARE_CLASS(AQualisysClient, AActor, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/QTMConnect"), NO_API) \
	DECLARE_SERIALIZER(AQualisysClient) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define UE419Clean_Plugins_Qualisys_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_61_INCLASS \
private: \
	static void StaticRegisterNativesAQualisysClient(); \
	friend QTMCONNECT_API class UClass* Z_Construct_UClass_AQualisysClient(); \
public: \
	DECLARE_CLASS(AQualisysClient, AActor, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/QTMConnect"), NO_API) \
	DECLARE_SERIALIZER(AQualisysClient) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define UE419Clean_Plugins_Qualisys_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_61_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AQualisysClient(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AQualisysClient) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AQualisysClient); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AQualisysClient); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AQualisysClient(AQualisysClient&&); \
	NO_API AQualisysClient(const AQualisysClient&); \
public:


#define UE419Clean_Plugins_Qualisys_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_61_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AQualisysClient(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AQualisysClient(AQualisysClient&&); \
	NO_API AQualisysClient(const AQualisysClient&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AQualisysClient); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AQualisysClient); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AQualisysClient)


#define UE419Clean_Plugins_Qualisys_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_61_PRIVATE_PROPERTY_OFFSET
#define UE419Clean_Plugins_Qualisys_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_58_PROLOG
#define UE419Clean_Plugins_Qualisys_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_61_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	UE419Clean_Plugins_Qualisys_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_61_PRIVATE_PROPERTY_OFFSET \
	UE419Clean_Plugins_Qualisys_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_61_RPC_WRAPPERS \
	UE419Clean_Plugins_Qualisys_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_61_INCLASS \
	UE419Clean_Plugins_Qualisys_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_61_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define UE419Clean_Plugins_Qualisys_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_61_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	UE419Clean_Plugins_Qualisys_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_61_PRIVATE_PROPERTY_OFFSET \
	UE419Clean_Plugins_Qualisys_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_61_RPC_WRAPPERS_NO_PURE_DECLS \
	UE419Clean_Plugins_Qualisys_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_61_INCLASS_NO_PURE_DECLS \
	UE419Clean_Plugins_Qualisys_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_61_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class QualisysClient."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID UE419Clean_Plugins_Qualisys_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
