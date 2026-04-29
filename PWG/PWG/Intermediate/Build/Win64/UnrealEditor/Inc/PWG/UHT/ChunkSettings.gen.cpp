// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ChunkSettings.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeChunkSettings() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UClass_NoRegister();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FIntPoint();
ENGINE_API UClass* Z_Construct_UClass_UDataAsset();
ENGINE_API UClass* Z_Construct_UClass_UMaterialInterface_NoRegister();
PWG_API UClass* Z_Construct_UClass_AChunk_NoRegister();
PWG_API UClass* Z_Construct_UClass_UChunkSettings();
PWG_API UClass* Z_Construct_UClass_UChunkSettings_NoRegister();
UPackage* Z_Construct_UPackage__Script_PWG();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UChunkSettings ***********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UChunkSettings;
UClass* UChunkSettings::GetPrivateStaticClass()
{
	using TClass = UChunkSettings;
	if (!Z_Registration_Info_UClass_UChunkSettings.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("ChunkSettings"),
			Z_Registration_Info_UClass_UChunkSettings.InnerSingleton,
			StaticRegisterNativesUChunkSettings,
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
	return Z_Registration_Info_UClass_UChunkSettings.InnerSingleton;
}
UClass* Z_Construct_UClass_UChunkSettings_NoRegister()
{
	return UChunkSettings::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UChunkSettings_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "ChunkSettings.h" },
		{ "ModuleRelativePath", "Public/ChunkSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Size_MetaData[] = {
		{ "Category", "Terrain" },
		{ "ModuleRelativePath", "Public/ChunkSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Scale_MetaData[] = {
		{ "Category", "Terrain" },
		{ "ModuleRelativePath", "Public/ChunkSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NoiseScale_MetaData[] = {
		{ "Category", "Terrain" },
		{ "ModuleRelativePath", "Public/ChunkSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ZMultiplier_MetaData[] = {
		{ "Category", "Terrain" },
		{ "ModuleRelativePath", "Public/ChunkSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UVScale_MetaData[] = {
		{ "Category", "Terrain" },
		{ "ModuleRelativePath", "Public/ChunkSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RenderDistance_MetaData[] = {
		{ "Category", "Terrain" },
		{ "ModuleRelativePath", "Public/ChunkSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChunkMaterial_MetaData[] = {
		{ "Category", "Terrain" },
		{ "ModuleRelativePath", "Public/ChunkSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChunkClass_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/ChunkSettings.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UChunkSettings constinit property declarations ***************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Size;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Scale;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NoiseScale;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ZMultiplier;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_UVScale;
	static const UECodeGen_Private::FIntPropertyParams NewProp_RenderDistance;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ChunkMaterial;
	static const UECodeGen_Private::FClassPropertyParams NewProp_ChunkClass;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UChunkSettings constinit property declarations *****************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UChunkSettings>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UChunkSettings_Statics

// ********** Begin Class UChunkSettings Property Definitions **************************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UChunkSettings_Statics::NewProp_Size = { "Size", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UChunkSettings, Size), Z_Construct_UScriptStruct_FIntPoint, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Size_MetaData), NewProp_Size_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UChunkSettings_Statics::NewProp_Scale = { "Scale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UChunkSettings, Scale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Scale_MetaData), NewProp_Scale_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UChunkSettings_Statics::NewProp_NoiseScale = { "NoiseScale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UChunkSettings, NoiseScale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NoiseScale_MetaData), NewProp_NoiseScale_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UChunkSettings_Statics::NewProp_ZMultiplier = { "ZMultiplier", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UChunkSettings, ZMultiplier), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ZMultiplier_MetaData), NewProp_ZMultiplier_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UChunkSettings_Statics::NewProp_UVScale = { "UVScale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UChunkSettings, UVScale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UVScale_MetaData), NewProp_UVScale_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UChunkSettings_Statics::NewProp_RenderDistance = { "RenderDistance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UChunkSettings, RenderDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RenderDistance_MetaData), NewProp_RenderDistance_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UChunkSettings_Statics::NewProp_ChunkMaterial = { "ChunkMaterial", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UChunkSettings, ChunkMaterial), Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChunkMaterial_MetaData), NewProp_ChunkMaterial_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_UChunkSettings_Statics::NewProp_ChunkClass = { "ChunkClass", nullptr, (EPropertyFlags)0x0014000000000001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UChunkSettings, ChunkClass), Z_Construct_UClass_UClass_NoRegister, Z_Construct_UClass_AChunk_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChunkClass_MetaData), NewProp_ChunkClass_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UChunkSettings_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UChunkSettings_Statics::NewProp_Size,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UChunkSettings_Statics::NewProp_Scale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UChunkSettings_Statics::NewProp_NoiseScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UChunkSettings_Statics::NewProp_ZMultiplier,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UChunkSettings_Statics::NewProp_UVScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UChunkSettings_Statics::NewProp_RenderDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UChunkSettings_Statics::NewProp_ChunkMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UChunkSettings_Statics::NewProp_ChunkClass,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UChunkSettings_Statics::PropPointers) < 2048);
// ********** End Class UChunkSettings Property Definitions ****************************************
UObject* (*const Z_Construct_UClass_UChunkSettings_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDataAsset,
	(UObject* (*)())Z_Construct_UPackage__Script_PWG,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UChunkSettings_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UChunkSettings_Statics::ClassParams = {
	&UChunkSettings::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UChunkSettings_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UChunkSettings_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UChunkSettings_Statics::Class_MetaDataParams), Z_Construct_UClass_UChunkSettings_Statics::Class_MetaDataParams)
};
void UChunkSettings::StaticRegisterNativesUChunkSettings()
{
}
UClass* Z_Construct_UClass_UChunkSettings()
{
	if (!Z_Registration_Info_UClass_UChunkSettings.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UChunkSettings.OuterSingleton, Z_Construct_UClass_UChunkSettings_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UChunkSettings.OuterSingleton;
}
UChunkSettings::UChunkSettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UChunkSettings);
UChunkSettings::~UChunkSettings() {}
// ********** End Class UChunkSettings *************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkSettings_h__Script_PWG_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UChunkSettings, UChunkSettings::StaticClass, TEXT("UChunkSettings"), &Z_Registration_Info_UClass_UChunkSettings, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UChunkSettings), 3102016366U) },
	};
}; // Z_CompiledInDeferFile_FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkSettings_h__Script_PWG_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkSettings_h__Script_PWG_1866726485{
	TEXT("/Script/PWG"),
	Z_CompiledInDeferFile_FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkSettings_h__Script_PWG_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkSettings_h__Script_PWG_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
