// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ChunkManager.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeChunkManager() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FIntPoint();
ENGINE_API UClass* Z_Construct_UClass_UTickableWorldSubsystem();
PWG_API UClass* Z_Construct_UClass_AChunk_NoRegister();
PWG_API UClass* Z_Construct_UClass_UChunkManager();
PWG_API UClass* Z_Construct_UClass_UChunkManager_NoRegister();
PWG_API UClass* Z_Construct_UClass_UChunkSettings_NoRegister();
UPackage* Z_Construct_UPackage__Script_PWG();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UChunkManager Function LoadTerrainSettings *******************************
struct Z_Construct_UFunction_UChunkManager_LoadTerrainSettings_Statics
{
	struct ChunkManager_eventLoadTerrainSettings_Parms
	{
		UChunkSettings* NewSettings;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Terrain" },
		{ "ModuleRelativePath", "Public/ChunkManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function LoadTerrainSettings constinit property declarations *******************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NewSettings;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function LoadTerrainSettings constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function LoadTerrainSettings Property Definitions ******************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UChunkManager_LoadTerrainSettings_Statics::NewProp_NewSettings = { "NewSettings", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ChunkManager_eventLoadTerrainSettings_Parms, NewSettings), Z_Construct_UClass_UChunkSettings_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UChunkManager_LoadTerrainSettings_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UChunkManager_LoadTerrainSettings_Statics::NewProp_NewSettings,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UChunkManager_LoadTerrainSettings_Statics::PropPointers) < 2048);
// ********** End Function LoadTerrainSettings Property Definitions ********************************
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UChunkManager_LoadTerrainSettings_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UChunkManager, nullptr, "LoadTerrainSettings", 	Z_Construct_UFunction_UChunkManager_LoadTerrainSettings_Statics::PropPointers, 
	UE_ARRAY_COUNT(Z_Construct_UFunction_UChunkManager_LoadTerrainSettings_Statics::PropPointers), 
sizeof(Z_Construct_UFunction_UChunkManager_LoadTerrainSettings_Statics::ChunkManager_eventLoadTerrainSettings_Parms),
RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UChunkManager_LoadTerrainSettings_Statics::Function_MetaDataParams), Z_Construct_UFunction_UChunkManager_LoadTerrainSettings_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UChunkManager_LoadTerrainSettings_Statics::ChunkManager_eventLoadTerrainSettings_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UChunkManager_LoadTerrainSettings()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UChunkManager_LoadTerrainSettings_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UChunkManager::execLoadTerrainSettings)
{
	P_GET_OBJECT(UChunkSettings,Z_Param_NewSettings);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->LoadTerrainSettings(Z_Param_NewSettings);
	P_NATIVE_END;
}
// ********** End Class UChunkManager Function LoadTerrainSettings *********************************

// ********** Begin Class UChunkManager ************************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UChunkManager;
UClass* UChunkManager::GetPrivateStaticClass()
{
	using TClass = UChunkManager;
	if (!Z_Registration_Info_UClass_UChunkManager.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("ChunkManager"),
			Z_Registration_Info_UClass_UChunkManager.InnerSingleton,
			StaticRegisterNativesUChunkManager,
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
	return Z_Registration_Info_UClass_UChunkManager.InnerSingleton;
}
UClass* Z_Construct_UClass_UChunkManager_NoRegister()
{
	return UChunkManager::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UChunkManager_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "ChunkManager.h" },
		{ "ModuleRelativePath", "Public/ChunkManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentSettings_MetaData[] = {
		{ "ModuleRelativePath", "Public/ChunkManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActiveChunks_MetaData[] = {
		{ "ModuleRelativePath", "Public/ChunkManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UChunkManager constinit property declarations ****************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CurrentSettings;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ActiveChunks_ValueProp;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ActiveChunks_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_ActiveChunks;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UChunkManager constinit property declarations ******************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("LoadTerrainSettings"), .Pointer = &UChunkManager::execLoadTerrainSettings },
	};
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UChunkManager_LoadTerrainSettings, "LoadTerrainSettings" }, // 3875914028
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UChunkManager>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UChunkManager_Statics

// ********** Begin Class UChunkManager Property Definitions ***************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UChunkManager_Statics::NewProp_CurrentSettings = { "CurrentSettings", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UChunkManager, CurrentSettings), Z_Construct_UClass_UChunkSettings_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentSettings_MetaData), NewProp_CurrentSettings_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UChunkManager_Statics::NewProp_ActiveChunks_ValueProp = { "ActiveChunks", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, Z_Construct_UClass_AChunk_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UChunkManager_Statics::NewProp_ActiveChunks_Key_KeyProp = { "ActiveChunks_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FIntPoint, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams Z_Construct_UClass_UChunkManager_Statics::NewProp_ActiveChunks = { "ActiveChunks", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UChunkManager, ActiveChunks), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActiveChunks_MetaData), NewProp_ActiveChunks_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UChunkManager_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UChunkManager_Statics::NewProp_CurrentSettings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UChunkManager_Statics::NewProp_ActiveChunks_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UChunkManager_Statics::NewProp_ActiveChunks_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UChunkManager_Statics::NewProp_ActiveChunks,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UChunkManager_Statics::PropPointers) < 2048);
// ********** End Class UChunkManager Property Definitions *****************************************
UObject* (*const Z_Construct_UClass_UChunkManager_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UTickableWorldSubsystem,
	(UObject* (*)())Z_Construct_UPackage__Script_PWG,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UChunkManager_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UChunkManager_Statics::ClassParams = {
	&UChunkManager::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UChunkManager_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UChunkManager_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UChunkManager_Statics::Class_MetaDataParams), Z_Construct_UClass_UChunkManager_Statics::Class_MetaDataParams)
};
void UChunkManager::StaticRegisterNativesUChunkManager()
{
	UClass* Class = UChunkManager::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, MakeConstArrayView(Z_Construct_UClass_UChunkManager_Statics::Funcs));
}
UClass* Z_Construct_UClass_UChunkManager()
{
	if (!Z_Registration_Info_UClass_UChunkManager.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UChunkManager.OuterSingleton, Z_Construct_UClass_UChunkManager_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UChunkManager.OuterSingleton;
}
UChunkManager::UChunkManager() {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UChunkManager);
UChunkManager::~UChunkManager() {}
// ********** End Class UChunkManager **************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkManager_h__Script_PWG_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UChunkManager, UChunkManager::StaticClass, TEXT("UChunkManager"), &Z_Registration_Info_UClass_UChunkManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UChunkManager), 1838484470U) },
	};
}; // Z_CompiledInDeferFile_FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkManager_h__Script_PWG_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkManager_h__Script_PWG_2651946659{
	TEXT("/Script/PWG"),
	Z_CompiledInDeferFile_FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkManager_h__Script_PWG_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkManager_h__Script_PWG_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
