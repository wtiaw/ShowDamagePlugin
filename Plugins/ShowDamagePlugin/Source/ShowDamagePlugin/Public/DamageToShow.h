// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "DamageToShow.generated.h"

enum class EDamageAttributeType : uint8;
class UShowDamageComponent;

/**
 * 
 */
UCLASS()
class SHOWDAMAGEPLUGIN_API UDamageToShow : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UImage* DamageIcon;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* DamageText;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* CanvasPanel;
	
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* ShowDamage;

	int Index;

	UPROPERTY(BlueprintReadOnly)
	UShowDamageComponent* Component;

	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	UCurveFloat* TargetX;

	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	UCurveFloat* TargetY;

private:
	int RandomX;
	int RandomXMin;
	int RandomXMax;
	
	int RandomY;
	int RandomYMin;
	int RandomYMax;

	int NormalFontSize;
	int CritFontSize;

	FLinearColor CritColor;

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void OnAnimationStartedPlaying(UUMGSequencePlayer& Player) override;
	virtual void OnAnimationFinishedPlaying(UUMGSequencePlayer& Player) override;
	
	void ShowDamageText(int Damage, FLinearColor Color, UTexture2D* InDamageIcon, bool bCrit);

	void SetNormalFontSize(int NewNormalFontSize);
	void SetCritFontSize(int NewCritFontSize);

	void SetRandomX(int32 XMin, int32 XMax);
	void SetRandomY(int32 YMin, int32 YMax);

	void SetCritColor(FLinearColor NewCritColor);

	void SetFontStyle(const UObject* Font) const;

	UFUNCTION(BlueprintImplementableEvent)
	void Test();

	UFUNCTION(BlueprintCallable)
	void UpdateOrAddKey(UCurveFloat* CurveFloat, float InTime, float InValue, const bool bUnwindRotation = false, ERichCurveInterpMode NewInterpMode = RCIM_Linear,bool bAutoSetTangents = false);

private:
	void SetLocation();

	void SetRandomXY();
};
