// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageToShow.h"
#include "Components/SceneComponent.h"
#include "ShowDamageComponent.generated.h"

UENUM(BlueprintType)
enum class EDamageAttributeType : uint8
{
	Normal,

	
};

UCLASS( ClassGroup=(Custom), BlueprintType,  meta=(BlueprintSpawnableComponent) )
class SHOWDAMAGEPLUGIN_API UShowDamageComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UShowDamageComponent();

	UPROPERTY(EditAnywhere)
	int InitNumber;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UDamageToShow> WidgetClass;

	UPROPERTY(EditAnywhere)
	TMap<EDamageAttributeType, FLinearColor> DamageColor;

	UPROPERTY(EditAnywhere)
	TMap<EDamageAttributeType, UTexture2D*> DamageIcon;

	UPROPERTY(EditAnywhere)
	FLinearColor CritColor;
	
private:
	UPROPERTY()
	TArray<UDamageToShow*> Widgets;
	
	TQueue<uint8> Unused;

public:
	UFUNCTION(BlueprintCallable)
	void TakeDamage(int Damage, EDamageAttributeType DamageAttribute, bool bCrit = false, FLinearColor InCritColor = FLinearColor(1,1,0,1));

	void ReturnIndex(uint8 Index);
	
protected:
	virtual void BeginPlay() override;

private:
	void CreateNewWidget();
};
