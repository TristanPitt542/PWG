// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodePWG_init() {}
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_PWG;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_PWG()
	{
		if (!Z_Registration_Info_UPackage__Script_PWG.OuterSingleton)
		{
		static const UECodeGen_Private::FPackageParams PackageParams = {
			"/Script/PWG",
			nullptr,
			0,
			PKG_CompiledIn | 0x00000000,
			0xE15528E3,
			0x6D995E3C,
			METADATA_PARAMS(0, nullptr)
		};
		UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_PWG.OuterSingleton, PackageParams);
	}
	return Z_Registration_Info_UPackage__Script_PWG.OuterSingleton;
}
static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_PWG(Z_Construct_UPackage__Script_PWG, TEXT("/Script/PWG"), Z_Registration_Info_UPackage__Script_PWG, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0xE15528E3, 0x6D995E3C));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
