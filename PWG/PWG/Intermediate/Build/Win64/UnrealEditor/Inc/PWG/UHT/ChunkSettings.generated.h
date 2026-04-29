// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "ChunkSettings.h"

#ifdef PWG_ChunkSettings_generated_h
#error "ChunkSettings.generated.h already included, missing '#pragma once' in ChunkSettings.h"
#endif
#define PWG_ChunkSettings_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UChunkSettings ***********************************************************
struct Z_Construct_UClass_UChunkSettings_Statics;
PWG_API UClass* Z_Construct_UClass_UChunkSettings_NoRegister();

#define FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkSettings_h_10_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUChunkSettings(); \
	friend struct ::Z_Construct_UClass_UChunkSettings_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend PWG_API UClass* ::Z_Construct_UClass_UChunkSettings_NoRegister(); \
public: \
	DECLARE_CLASS2(UChunkSettings, UDataAsset, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/PWG"), Z_Construct_UClass_UChunkSettings_NoRegister) \
	DECLARE_SERIALIZER(UChunkSettings)


#define FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkSettings_h_10_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UChunkSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UChunkSettings(UChunkSettings&&) = delete; \
	UChunkSettings(const UChunkSettings&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UChunkSettings); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UChunkSettings); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UChunkSettings) \
	NO_API virtual ~UChunkSettings();


#define FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkSettings_h_7_PROLOG
#define FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkSettings_h_10_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkSettings_h_10_INCLASS_NO_PURE_DECLS \
	FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkSettings_h_10_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UChunkSettings;

// ********** End Class UChunkSettings *************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkSettings_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
