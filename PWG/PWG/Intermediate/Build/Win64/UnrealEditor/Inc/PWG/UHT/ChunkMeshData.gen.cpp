// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ChunkMeshData.h"
#include "ProceduralMeshComponent.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeChunkMeshData() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FTransform();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector2D();
PROCEDURALMESHCOMPONENT_API UScriptStruct* Z_Construct_UScriptStruct_FProcMeshTangent();
PWG_API UScriptStruct* Z_Construct_UScriptStruct_FChunkMeshData();
PWG_API UScriptStruct* Z_Construct_UScriptStruct_FInstanceData();
UPackage* Z_Construct_UPackage__Script_PWG();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FInstanceData *****************************************************
struct Z_Construct_UScriptStruct_FInstanceData_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FInstanceData); }
	static inline consteval int16 GetStructAlignment() { return alignof(FInstanceData); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/ChunkMeshData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TypeIndex_MetaData[] = {
		{ "ModuleRelativePath", "Public/ChunkMeshData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Transform_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// 0 for Tree, 1 for Rock, etc.\n" },
#endif
		{ "ModuleRelativePath", "Public/ChunkMeshData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "0 for Tree, 1 for Rock, etc." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FInstanceData constinit property declarations *********************
	static const UECodeGen_Private::FIntPropertyParams NewProp_TypeIndex;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Transform;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FInstanceData constinit property declarations ***********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FInstanceData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FInstanceData_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FInstanceData;
class UScriptStruct* FInstanceData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FInstanceData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FInstanceData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FInstanceData, (UObject*)Z_Construct_UPackage__Script_PWG(), TEXT("InstanceData"));
	}
	return Z_Registration_Info_UScriptStruct_FInstanceData.OuterSingleton;
	}

// ********** Begin ScriptStruct FInstanceData Property Definitions ********************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FInstanceData_Statics::NewProp_TypeIndex = { "TypeIndex", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FInstanceData, TypeIndex), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TypeIndex_MetaData), NewProp_TypeIndex_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FInstanceData_Statics::NewProp_Transform = { "Transform", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FInstanceData, Transform), Z_Construct_UScriptStruct_FTransform, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Transform_MetaData), NewProp_Transform_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FInstanceData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FInstanceData_Statics::NewProp_TypeIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FInstanceData_Statics::NewProp_Transform,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FInstanceData_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FInstanceData Property Definitions **********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FInstanceData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_PWG,
	nullptr,
	&NewStructOps,
	"InstanceData",
	Z_Construct_UScriptStruct_FInstanceData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FInstanceData_Statics::PropPointers),
	sizeof(FInstanceData),
	alignof(FInstanceData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FInstanceData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FInstanceData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FInstanceData()
{
	if (!Z_Registration_Info_UScriptStruct_FInstanceData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FInstanceData.InnerSingleton, Z_Construct_UScriptStruct_FInstanceData_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FInstanceData.InnerSingleton);
}
// ********** End ScriptStruct FInstanceData *******************************************************

// ********** Begin ScriptStruct FChunkMeshData ****************************************************
struct Z_Construct_UScriptStruct_FChunkMeshData_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FChunkMeshData); }
	static inline consteval int16 GetStructAlignment() { return alignof(FChunkMeshData); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/ChunkMeshData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Vertices_MetaData[] = {
		{ "Category", "Mesh Data" },
		{ "ModuleRelativePath", "Public/ChunkMeshData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Triangles_MetaData[] = {
		{ "Category", "Mesh Data" },
		{ "ModuleRelativePath", "Public/ChunkMeshData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Normals_MetaData[] = {
		{ "Category", "Mesh Data" },
		{ "ModuleRelativePath", "Public/ChunkMeshData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UV0_MetaData[] = {
		{ "Category", "Mesh Data" },
		{ "ModuleRelativePath", "Public/ChunkMeshData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Tangents_MetaData[] = {
		{ "Category", "Mesh Data" },
		{ "ModuleRelativePath", "Public/ChunkMeshData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Instances_MetaData[] = {
		{ "ModuleRelativePath", "Public/ChunkMeshData.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FChunkMeshData constinit property declarations ********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Vertices_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Vertices;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Triangles_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Triangles;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Normals_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Normals;
	static const UECodeGen_Private::FStructPropertyParams NewProp_UV0_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_UV0;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Tangents_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Tangents;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Instances_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Instances;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FChunkMeshData constinit property declarations **********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FChunkMeshData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FChunkMeshData_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FChunkMeshData;
class UScriptStruct* FChunkMeshData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FChunkMeshData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FChunkMeshData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FChunkMeshData, (UObject*)Z_Construct_UPackage__Script_PWG(), TEXT("ChunkMeshData"));
	}
	return Z_Registration_Info_UScriptStruct_FChunkMeshData.OuterSingleton;
	}

// ********** Begin ScriptStruct FChunkMeshData Property Definitions *******************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FChunkMeshData_Statics::NewProp_Vertices_Inner = { "Vertices", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FChunkMeshData_Statics::NewProp_Vertices = { "Vertices", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FChunkMeshData, Vertices), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Vertices_MetaData), NewProp_Vertices_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FChunkMeshData_Statics::NewProp_Triangles_Inner = { "Triangles", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FChunkMeshData_Statics::NewProp_Triangles = { "Triangles", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FChunkMeshData, Triangles), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Triangles_MetaData), NewProp_Triangles_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FChunkMeshData_Statics::NewProp_Normals_Inner = { "Normals", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FChunkMeshData_Statics::NewProp_Normals = { "Normals", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FChunkMeshData, Normals), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Normals_MetaData), NewProp_Normals_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FChunkMeshData_Statics::NewProp_UV0_Inner = { "UV0", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FChunkMeshData_Statics::NewProp_UV0 = { "UV0", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FChunkMeshData, UV0), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UV0_MetaData), NewProp_UV0_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FChunkMeshData_Statics::NewProp_Tangents_Inner = { "Tangents", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FProcMeshTangent, METADATA_PARAMS(0, nullptr) }; // 2375946553
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FChunkMeshData_Statics::NewProp_Tangents = { "Tangents", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FChunkMeshData, Tangents), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Tangents_MetaData), NewProp_Tangents_MetaData) }; // 2375946553
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FChunkMeshData_Statics::NewProp_Instances_Inner = { "Instances", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FInstanceData, METADATA_PARAMS(0, nullptr) }; // 3391676174
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FChunkMeshData_Statics::NewProp_Instances = { "Instances", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FChunkMeshData, Instances), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Instances_MetaData), NewProp_Instances_MetaData) }; // 3391676174
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FChunkMeshData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FChunkMeshData_Statics::NewProp_Vertices_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FChunkMeshData_Statics::NewProp_Vertices,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FChunkMeshData_Statics::NewProp_Triangles_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FChunkMeshData_Statics::NewProp_Triangles,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FChunkMeshData_Statics::NewProp_Normals_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FChunkMeshData_Statics::NewProp_Normals,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FChunkMeshData_Statics::NewProp_UV0_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FChunkMeshData_Statics::NewProp_UV0,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FChunkMeshData_Statics::NewProp_Tangents_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FChunkMeshData_Statics::NewProp_Tangents,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FChunkMeshData_Statics::NewProp_Instances_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FChunkMeshData_Statics::NewProp_Instances,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FChunkMeshData_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FChunkMeshData Property Definitions *********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FChunkMeshData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_PWG,
	nullptr,
	&NewStructOps,
	"ChunkMeshData",
	Z_Construct_UScriptStruct_FChunkMeshData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FChunkMeshData_Statics::PropPointers),
	sizeof(FChunkMeshData),
	alignof(FChunkMeshData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FChunkMeshData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FChunkMeshData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FChunkMeshData()
{
	if (!Z_Registration_Info_UScriptStruct_FChunkMeshData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FChunkMeshData.InnerSingleton, Z_Construct_UScriptStruct_FChunkMeshData_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FChunkMeshData.InnerSingleton);
}
// ********** End ScriptStruct FChunkMeshData ******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkMeshData_h__Script_PWG_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FInstanceData::StaticStruct, Z_Construct_UScriptStruct_FInstanceData_Statics::NewStructOps, TEXT("InstanceData"),&Z_Registration_Info_UScriptStruct_FInstanceData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FInstanceData), 3391676174U) },
		{ FChunkMeshData::StaticStruct, Z_Construct_UScriptStruct_FChunkMeshData_Statics::NewStructOps, TEXT("ChunkMeshData"),&Z_Registration_Info_UScriptStruct_FChunkMeshData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FChunkMeshData), 1372757524U) },
	};
}; // Z_CompiledInDeferFile_FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkMeshData_h__Script_PWG_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkMeshData_h__Script_PWG_2672507645{
	TEXT("/Script/PWG"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkMeshData_h__Script_PWG_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Unreal_Projects_PWG_PWG_Source_PWG_Public_ChunkMeshData_h__Script_PWG_Statics::ScriptStructInfo),
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
