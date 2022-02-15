// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageToShow.h"

#include "ShowDamageComponent.h"
#include "Kismet/KismetTextLibrary.h"

void UDamageToShow::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	// SetLocation();
}

void UDamageToShow::OnAnimationStartedPlaying(UUMGSequencePlayer& Player)
{
	Super::OnAnimationStartedPlaying(Player);
}

void UDamageToShow::OnAnimationFinishedPlaying(UUMGSequencePlayer& Player)
{
	Super::OnAnimationFinishedPlaying(Player);

	Component->ReturnIndex(Index);

	SetVisibility(ESlateVisibility::Collapsed);
}

void UDamageToShow::ShowDamageText(int Damage, FLinearColor Color, UTexture2D* InDamageIcon, bool bCrit)
{
	SetVisibility(ESlateVisibility::HitTestInvisible);

	SetLocation();
	
	SetRandomXY();
	
	DamageText->SetText(UKismetTextLibrary::Conv_IntToText(Damage));
	
	if(InDamageIcon)
	{
		DamageIcon->SetVisibility(ESlateVisibility::HitTestInvisible);
		DamageIcon->SetBrushFromTexture(InDamageIcon);
		DamageIcon->SetColorAndOpacity(Color);
	}
	else
	{
		DamageIcon->SetVisibility(ESlateVisibility::Collapsed);
	}

	if(bCrit)
	{
		FSlateFontInfo Font = DamageText->Font;
		Font.Size = CritFontSize;

		DamageText->SetFont(Font);
		DamageText->SetColorAndOpacity(CritColor);

		DamageIcon->SetColorAndOpacity(CritColor);
	}
	else
	{
		FSlateFontInfo Font = DamageText->Font;
		Font.Size = NormalFontSize;

		DamageText->SetFont(Font);
		DamageText->SetColorAndOpacity(Color);
	}


	TargetX->FloatCurve.UpdateOrAddKey(0,0);
	TargetY->FloatCurve.UpdateOrAddKey(0,0);
	TargetX->FloatCurve.UpdateOrAddKey(1,RandomX);
	TargetY->FloatCurve.UpdateOrAddKey(1,RandomY);

	
	Test();
	// PlayAnimation(ShowDamage);
}

void UDamageToShow::SetNormalFontSize(int NewNormalFontSize)
{
	NormalFontSize = NewNormalFontSize;
}

void UDamageToShow::SetCritFontSize(int NewCritFontSize)
{
	CritFontSize = NewCritFontSize;
}

void UDamageToShow::SetRandomX(int32 XMin, int32 XMax)
{
	RandomXMin = XMin;
	RandomXMax = XMax;
}

void UDamageToShow::SetRandomY(int32 YMin, int32 YMax)
{
	RandomYMin = YMin;
	RandomYMax = YMax;
}

void UDamageToShow::SetCritColor(FLinearColor NewCritColor)
{
	CritColor = NewCritColor;
}

void UDamageToShow::UpdateOrAddKey(UCurveFloat* CurveFloat, float InTime, float InValue, const bool bUnwindRotation, ERichCurveInterpMode NewInterpMode,
	bool bAutoSetTangents)
{
	FKeyHandle KeyHandle = CurveFloat->FloatCurve.UpdateOrAddKey(InTime, InValue, bUnwindRotation);

	CurveFloat->FloatCurve.SetKeyInterpMode(KeyHandle, NewInterpMode, bAutoSetTangents);
}

void UDamageToShow::SetLocation()
{
	const FVector WorldLocation = Component->GetComponentLocation();
	FVector2D ScreenLocation;
	GetWorld()->GetFirstPlayerController()->ProjectWorldLocationToScreen(WorldLocation, ScreenLocation);

	const FVector2D TextPosition = FVector2D(ScreenLocation.X + RandomX, ScreenLocation.Y + RandomY);
	SetPositionInViewport(TextPosition);
}

void UDamageToShow::SetRandomXY()
{
	RandomX = FMath::RandRange(RandomXMin, RandomXMax);
	RandomY = FMath::RandRange(RandomYMin, RandomYMax);
}

void UDamageToShow::SetFontStyle(const UObject* Font) const
{
	if(Font)
	{
		FSlateFontInfo FontInfo = DamageText->Font;
		FontInfo.FontObject = Font;

		DamageText->SetFont(FontInfo);
	}
}
