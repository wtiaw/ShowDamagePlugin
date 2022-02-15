// Fill out your copyright notice in the Description page of Project Settings.


#include "ShowDamageStyle.h"
#include "DamageToShow.h"

UShowDamageStyle::UShowDamageStyle()
{
	static ConstructorHelpers::FClassFinder<UDamageToShow> WidgetFinder(TEXT("WidgetBlueprint'/ShowDamagePlugin/UMG/WBP_DamageToShow.WBP_DamageToShow_C'"));
	if(WidgetFinder.Succeeded())
	{
		WidgetClass = WidgetFinder.Class;
	}
	
	static ConstructorHelpers::FObjectFinderOptional<UTexture2D> WaterIconFinder(TEXT("Texture2D'/ShowDamagePlugin/Texture/Water.Water'"));
	UTexture2D* WaterIcon = nullptr;
	if(WaterIconFinder.Succeeded())
	{
		WaterIcon = WaterIconFinder.Get();
	}

	static ConstructorHelpers::FObjectFinderOptional<UTexture2D> FireIconFinder(TEXT("Texture2D'/ShowDamagePlugin/Texture/Fire.Fire'"));
	UTexture2D* FireIcon = nullptr;
	if(FireIconFinder.Succeeded())
	{
		FireIcon = FireIconFinder.Get();
	}

	static ConstructorHelpers::FObjectFinderOptional<UTexture2D> LightIconFinder(TEXT("Texture2D'/ShowDamagePlugin/Texture/Light.Light'"));
	UTexture2D* LightIcon = nullptr;
	if(LightIconFinder.Succeeded())
	{
		LightIcon = LightIconFinder.Get();
	}

	static ConstructorHelpers::FObjectFinderOptional<UTexture2D> DarkIconFinder(TEXT("Texture2D'/ShowDamagePlugin/Texture/Dark.Dark'"));
	UTexture2D* DarkIcon = nullptr;
	if(DarkIconFinder.Succeeded())
	{
		DarkIcon = DarkIconFinder.Get();
	}

	DamageColor.Add(EDamageAttributeType::Normal,FLinearColor(1,1,1,1));
	DamageIcon.Add(EDamageAttributeType::Normal,nullptr);

	DamageColor.Add(EDamageAttributeType::Water,FLinearColor(0,0.23,1,1));
	DamageIcon.Add(EDamageAttributeType::Water,WaterIcon);

	DamageColor.Add(EDamageAttributeType::Fire,FLinearColor(1,0,0,1));
	DamageIcon.Add(EDamageAttributeType::Fire,FireIcon);

	DamageColor.Add(EDamageAttributeType::Light,FLinearColor(0.82,1,0.3,1));
	DamageIcon.Add(EDamageAttributeType::Light,LightIcon);

	DamageColor.Add(EDamageAttributeType::Dark,FLinearColor(0.31,0,0.31,1));
	DamageIcon.Add(EDamageAttributeType::Dark,DarkIcon);

	CritColor = FLinearColor(1,0.51,0,1);
}
