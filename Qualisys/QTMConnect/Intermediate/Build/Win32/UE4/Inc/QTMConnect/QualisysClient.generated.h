// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectMacros.h"
#include "ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UWorld;
class AQualisysClient;
struct FQualisysRigidBodyPose;
#ifdef QTMCONNECT_QualisysClient_generated_h
#error "QualisysClient.generated.h already included, missing '#pragma once' in QualisysClient.h"
#endif
#define QTMCONNECT_QualisysClient_generated_h

#define HostProject_Plugins_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_27_GENERATED_BODY \
	friend QTMCONNECT_API class UScriptStruct* Z_Construct_UScriptStruct_FQualisysRigidBodyPose(); \
	QTMCONNECT_API static class UScriptStruct* StaticStruct();


#define HostProject_Plugins_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_42_RPC_WRAPPERS \
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
	DECLARE_FUNCTION(execGetRigidBodyPose) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_RigidBody); \
		P_GET_STRUCT_REF(FQualisysRigidBodyPose,Z_Param_Out_RigidBodyPose); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=this->GetRigidBodyPose(Z_Param_RigidBody,Z_Param_Out_RigidBodyPose); \
		P_NATIVE_END; \
	}


#define HostProject_Plugins_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_42_RPC_WRAPPERS_NO_PURE_DECLS \
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
	DECLARE_FUNCTION(execGetRigidBodyPose) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_RigidBody); \
		P_GET_STRUCT_REF(FQualisysRigidBodyPose,Z_Param_Out_RigidBodyPose); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=this->GetRigidBodyPose(Z_Param_RigidBody,Z_Param_Out_RigidBodyPose); \
		P_NATIVE_END; \
	}


#define HostProject_Plugins_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_42_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAQualisysClient(); \
	friend QTMCONNECT_API class UClass* Z_Construct_UClass_AQualisysClient(); \
public: \
	DECLARE_CLASS(AQualisysClient, AActor, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/QTMConnect"), NO_API) \
	DECLARE_SERIALIZER(AQualisysClient) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define HostProject_Plugins_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_42_INCLASS \
private: \
	static void StaticRegisterNativesAQualisysClient(); \
	friend QTMCONNECT_API class UClass* Z_Construct_UClass_AQualisysClient(); \
public: \
	DECLARE_CLASS(AQualisysClient, AActor, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/QTMConnect"), NO_API) \
	DECLARE_SERIALIZER(AQualisysClient) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define HostProject_Plugins_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_42_STANDARD_CONSTRUCTORS \
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


#define HostProject_Plugins_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_42_ENHANCED_CONSTRUCTORS \
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


#define HostProject_Plugins_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_42_PRIVATE_PROPERTY_OFFSET
#define HostProject_Plugins_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_39_PROLOG
#define HostProject_Plugins_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_42_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HostProject_Plugins_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_42_PRIVATE_PROPERTY_OFFSET \
	HostProject_Plugins_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_42_RPC_WRAPPERS \
	HostProject_Plugins_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_42_INCLASS \
	HostProject_Plugins_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_42_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define HostProject_Plugins_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_42_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HostProject_Plugins_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_42_PRIVATE_PROPERTY_OFFSET \
	HostProject_Plugins_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_42_RPC_WRAPPERS_NO_PURE_DECLS \
	HostProject_Plugins_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_42_INCLASS_NO_PURE_DECLS \
	HostProject_Plugins_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h_42_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class QualisysClient."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID HostProject_Plugins_QTMConnect_Source_QTMConnect_Classes_QualisysClient_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
