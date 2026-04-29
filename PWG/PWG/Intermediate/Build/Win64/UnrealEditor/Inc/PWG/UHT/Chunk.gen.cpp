// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Chunk.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeChunk() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor();
PCG_API UClass* Z_Construct_UClass_UPCGComponent_NoRegister();
PROCEDURALMESHCOMPONENT_API UClass* Z_Construct_UClass_UProceduralMeshComponent_NoRegister();
PWG_API UClass* Z_Construct_UClass_AChunk();
PWG_API UClass* Z_Construct_UClass_AChunk_NoRegister();
UPackage* Z_Construct_UPackage__Script_PWG();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AChunk *******************************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_AChunk;
UClass* AChunk::GetPrivateStaticClass()
{
	using TClass = AChunk;
	if (!Z_Registration_Info_UClass_AChunk.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("Chunk"),
			Z_Registration_Info_UClass_AChunk.InnerSingleton,
			StaticRegisterNativesAChunk,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_AChunk.InnerSingleton;
}
UClass* Z_Construct_UClass_AChunk_NoRegister()
{
	return AChunk::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AChunk_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "Chunk.h" },
		{ "ModuleRelativePath", "Public/Chunk.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProceduralMesh_MetaData[] = {
		{ "Category", "Terrain" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Chunk.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChunkPCG_MetaData[] = {
		{ "Category", "PCG" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Chunk.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class AChunk constinit property declarations ***********************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ProceduralMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ChunkPCG;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class AChunk constinit property declarations *************************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AChunk>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_AChunk_Statics

// ********** Begin Class AChunk Property Definitions **********************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AChunk_Statics::NewProp_ProceduralMesh = { "ProceduralMesh", nullptr, (EPropertyFlags)0x00200800000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AChunk, ProceduralMesh), Z_Construct_UClass_UProceduralMeshComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProceduralMesh_MetaData), NewProp_ProceduralMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AChunk_Statics::NewProp_ChunkPCG = { "ChunkPCG", nullptr, (EPropertyFlags)0x002008000008000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AChunk, ChunkPCG), Z_Construct_UClass_UPCGComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChunkPCG_MetaData), NewProp_ChunkPCG_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AChunk_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AChunk_Statics::NewProp_ProceduralMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AChunk_Statics::NewProp_ChunkPCG,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AChunk_Statics::PropPointers) < 2048);
// ********** End Class AChunk Property Definitions ************************************************
UObject* (*const Z_Construct_UClass_AChunk_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_PWG,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AChunk_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AChunk_Statics::ClassParams = {
	&AChunk::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_AChunk_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_AChunk_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AChunk_Statics::Class_MetaDataParams), Z_Construct_UClass_AChunk_Statics::Class_MetaDataParams)
};
void AChunk::StaticRegisterNativesAChunk()
{
}
UClass* Z_Construct_UClass_AChunk()
{
	if (!Z_Registration_Info_UClass_AChunk.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AChunk.OuterSingleton, Z_Construct_UClass_AChunk_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AChunk.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AChunk);
AChunk::~AChunk() {}
// ********** End Class AChunk *********************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_Chunk_h__Script_PWG_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AChunk, AChunk::StaticClass, TEXT("AChunk"), &Z_Registration_Info_UClass_AChunk, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AChunk), 2990189491U) },
	};
}; // Z_CompiledInDeferFile_FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_Chunk_h__Script_PWG_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_Chunk_h__Script_PWG_3535796852{
	TEXT("/Script/PWG"),
	Z_CompiledInDeferFile_FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_Chunk_h__Script_PWG_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_Chunk_h__Script_PWG_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
