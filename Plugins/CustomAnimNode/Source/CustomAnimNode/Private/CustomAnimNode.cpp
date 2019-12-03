// Copyright 2018 Sean Chen. All Rights Reserved.

#include "CustomAnimNode.h"

#define LOCTEXT_NAMESPACE "FCustomAnimNodeModule"

void FCustomAnimNodeModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

#if    WITH_EDITOR
	FModuleManager::Get().LoadModule(TEXT("BlueprintGraph"));
	// FModuleManager::Get().LoadModule(TEXT("AnimGraph"));
	FModuleManager::Get().LoadModule(TEXT("CustomAnimNodeEditor"));
#endif

}

void FCustomAnimNodeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCustomAnimNodeModule, CustomAnimNode)