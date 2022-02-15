// Fill out your copyright notice in the Description page of Project Settings.


#include "ShowDamageStyleFactory.h"

#include "ShowDamageStyle.h"

UShowDamageStyleFactory::UShowDamageStyleFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UShowDamageStyle::StaticClass();
}

UObject* UShowDamageStyleFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
                                                   UObject* Context, FFeedbackContext* Warn)
{
	UShowDamageStyle* MyDefinedAsset = NewObject<UShowDamageStyle>(InParent, InName, Flags | RF_Transactional);
	return MyDefinedAsset;
}