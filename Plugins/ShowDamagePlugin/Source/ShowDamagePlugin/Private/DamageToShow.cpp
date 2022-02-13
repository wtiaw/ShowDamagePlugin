// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageToShow.h"

#include "ShowDamageComponent.h"
#include "Kismet/KismetTextLibrary.h"

void UDamageToShow::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	SetLocation();
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

void UDamageToShow::ShowDamageText(int Damage, FLinearColor Color, UTexture2D* InDamageIcon, bool bCrit, FLinearColor InCritColor)
{
	SetVisibility(ESlateVisibility::HitTestInvisible);

	SetLocation();
	
	RandomX = FMath::RandRange(-30, 30);
	RandomY = FMath::RandRange(-30, 30);
	
	DamageText->SetText(UKismetTextLibrary::Conv_IntToText(Damage));
	
	if(InDamageIcon)
	{
		DamageIcon->SetVisibility(ESlateVisibility::HitTestInvisible);
		DamageIcon->SetBrushFromTexture(InDamageIcon);
	}
	else
	{
		DamageIcon->SetVisibility(ESlateVisibility::Collapsed);
	}
	
	if(bCrit)
	{
		CanvasPanel->SetRenderScale(FVector2D(1.2,1.2));

		DamageText->SetColorAndOpacity(InCritColor);
	}
	else
	{
		CanvasPanel->SetRenderScale(FVector2D(1,1));

		DamageText->SetColorAndOpacity(Color);
	}
	
	PlayAnimation(ShowDamage);
}

void UDamageToShow::SetLocation()
{
	const FVector WorldLocation = Component->GetComponentLocation();
	FVector2D ScreenLocation;
	GetWorld()->GetFirstPlayerController()->ProjectWorldLocationToScreen(WorldLocation, ScreenLocation);

	const FVector2D TextPosition = FVector2D(ScreenLocation.X + RandomX, ScreenLocation.Y + RandomY);
	SetPositionInViewport(TextPosition);
}
