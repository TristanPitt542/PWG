// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "ChunkManager.h"

#ifdef PWG_ChunkManager_generated_h
#error "ChunkManager.generated.h already included, missing '#pragma once' in ChunkManager.h"
#endif
#define PWG_ChunkManager_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UChunkSettings;

// ********** Begin Class UChunkManager ************************************************************
#define FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkManager_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execLoadTerrainSettings);


struct Z_Construct_UClass_UChunkManager_Statics;
PWG_API UClass* Z_Construct_UClass_UChunkManager_NoRegister();

#define FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkManager_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUChunkManager(); \
	friend struct ::Z_Construct_UClass_UChunkManager_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend PWG_API UClass* ::Z_Construct_UClass_UChunkManager_NoRegister(); \
public: \
	DECLARE_CLASS2(UChunkManager, UTickableWorldSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/PWG"), Z_Construct_UClass_UChunkManager_NoRegister) \
	DECLARE_SERIALIZER(UChunkManager)


#define FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkManager_h_14_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UChunkManager(); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UChunkManager(UChunkManager&&) = delete; \
	UChunkManager(const UChunkManager&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UChunkManager); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UChunkManager); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UChunkManager) \
	NO_API virtual ~UChunkManager();


#define FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkManager_h_11_PROLOG
#define FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkManager_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkManager_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkManager_h_14_INCLASS_NO_PURE_DECLS \
	FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkManager_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UChunkManager;

// ********** End Class UChunkManager **************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkManager_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
