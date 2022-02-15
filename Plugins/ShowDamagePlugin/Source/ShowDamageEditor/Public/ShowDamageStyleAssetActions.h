#pragma once

#include "AssetTypeActions_Base.h"
#include "ShowDamageStyle.h"

/**
 * 
 */
class  FShowDamageStyleAssetActions : public FAssetTypeActions_Base
{
public:
	FShowDamageStyleAssetActions(EAssetTypeCategories::Type InAssetCategory);

	virtual FColor GetTypeColor() const override { return FColor(97, 85, 212); }
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;

	// IAssetTypeActions Implementation
	virtual FText GetName() const override { return FText::FromName(TEXT("Show Damage Style")); }
	virtual UClass* GetSupportedClass() const override { return UShowDamageStyle::StaticClass(); }
	virtual uint32 GetCategories() override { return MyAssetCategory; }

private:
	EAssetTypeCategories::Type MyAssetCategory;
};
