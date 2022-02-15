// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShowDamageEditor.h"

#include "AssetToolsModule.h"
#include "AssetTypeCategories.h"
#include "ShowDamageStyleAssetActions.h"

#define LOCTEXT_NAMESPACE "FShowDamagePluginModule"

void FShowDamageEditorModule::StartupModule()
{
	RegisterAssetTools();
}

void FShowDamageEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::Get().GetModuleChecked<FAssetToolsModule>("AssetTools").Get();

		for(auto i : RegisteredAssetTypeActions)
		{
			AssetTools.UnregisterAssetTypeActions(i);
		}
	}
}

void FShowDamageEditorModule::RegisterAssetTools()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	
	EAssetTypeCategories::Type MyAssetType = AssetTools.RegisterAdvancedAssetCategory((TEXT("Show Damage Style")), FText::FromName(TEXT("Show Damage Style")));
		
	// Create Asset actions
	TSharedRef<IAssetTypeActions> Action = MakeShareable(new FShowDamageStyleAssetActions(MyAssetType));

	// Register Asset action
	AssetTools.RegisterAssetTypeActions(Action);

	RegisteredAssetTypeActions.Add(Action);
}

void FShowDamageEditorModule::UnRegisterAssetTools()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FShowDamageEditorModule, ShowDamageEditor)