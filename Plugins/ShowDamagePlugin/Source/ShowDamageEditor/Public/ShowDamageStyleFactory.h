// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "ShowDamageStyleFactory.generated.h"

/**
 * 
 */
UCLASS()
class SHOWDAMAGEEDITOR_API UShowDamageStyleFactory : public UFactory
{
	GENERATED_BODY()

public:
	UShowDamageStyleFactory();

	//~ Begin UFactory Interface
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
		UObject* Context, FFeedbackContext* Warn) override;
};
