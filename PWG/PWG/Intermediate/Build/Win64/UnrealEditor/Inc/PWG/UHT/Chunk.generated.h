// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Chunk.h"

#ifdef PWG_Chunk_generated_h
#error "Chunk.generated.h already included, missing '#pragma once' in Chunk.h"
#endif
#define PWG_Chunk_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AChunk *******************************************************************
struct Z_Construct_UClass_AChunk_Statics;
PWG_API UClass* Z_Construct_UClass_AChunk_NoRegister();

#define FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_Chunk_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAChunk(); \
	friend struct ::Z_Construct_UClass_AChunk_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend PWG_API UClass* ::Z_Construct_UClass_AChunk_NoRegister(); \
public: \
	DECLARE_CLASS2(AChunk, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/PWG"), Z_Construct_UClass_AChunk_NoRegister) \
	DECLARE_SERIALIZER(AChunk)


#define FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_Chunk_h_14_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AChunk(AChunk&&) = delete; \
	AChunk(const AChunk&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AChunk); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AChunk); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AChunk) \
	NO_API virtual ~AChunk();


#define FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_Chunk_h_11_PROLOG
#define FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_Chunk_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_Chunk_h_14_INCLASS_NO_PURE_DECLS \
	FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_Chunk_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AChunk;

// ********** End Class AChunk *********************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_Chunk_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
