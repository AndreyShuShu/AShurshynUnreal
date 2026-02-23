// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeThisProject_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_ThisProject;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_ThisProject()
	{
		if (!Z_Registration_Info_UPackage__Script_ThisProject.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/ThisProject",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000000,
				0x3596AF67,
				0x053F01C6,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_ThisProject.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_ThisProject.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_ThisProject(Z_Construct_UPackage__Script_ThisProject, TEXT("/Script/ThisProject"), Z_Registration_Info_UPackage__Script_ThisProject, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x3596AF67, 0x053F01C6));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
