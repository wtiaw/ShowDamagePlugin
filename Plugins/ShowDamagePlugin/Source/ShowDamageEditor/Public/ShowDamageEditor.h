// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class IAssetTypeActions;

class FShowDamageEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void RegisterAssetTools();
	void UnRegisterAssetTools();

private: 
	TArray<TSharedRef<IAssetTypeActions>> RegisteredAssetTypeActions;
};
