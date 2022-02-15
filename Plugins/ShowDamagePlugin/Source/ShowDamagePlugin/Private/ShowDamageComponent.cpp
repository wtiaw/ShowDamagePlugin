// Fill out your copyright notice in the Description page of Project Settings.


#include "ShowDamageComponent.h"

UShowDamageComponent::UShowDamageComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinderOptional<UShowDamageStyle> StyleFinder(TEXT("ShowDamageStyle'/ShowDamagePlugin/ShowDamageStyle.ShowDamageStyle'"));
	if(StyleFinder.Succeeded())
	{
		ShowDamageStyle = StyleFinder.Get();
	}

	InitNumber = 10;

	NormalFontSize = 20;
	CritFontSize = 26;

	RandomXMin = -20;
	RandomXMax = 20;
	RandomYMin = 0;
	RandomYMax = 50;
}


void UShowDamageComponent::TakeDamage(int Damage, EDamageAttributeType DamageAttribute, bool bCrit, FLinearColor InCritColor)
{
	if(!ShowDamageStyle->DamageColor.Find(DamageAttribute))
	{
		UE_LOG(LogTemp,Warning,TEXT("该属性颜色没有设置！！"))
		return;
	}
	
 	if(!ShowDamageStyle->DamageIcon.Find(DamageAttribute))
 	{
 		UE_LOG(LogTemp,Warning,TEXT("该属性图标没有设置！！"))
 		return;
 	}
	
	if (Unused.IsEmpty())
	{
		CreateNewWidget();
	}
	
	uint8 Index;
	Unused.Dequeue(Index);
	
	Widgets[Index]->ShowDamageText(Damage,*ShowDamageStyle->DamageColor.Find(DamageAttribute),*ShowDamageStyle->DamageIcon.Find(DamageAttribute),bCrit);
}

void UShowDamageComponent::ReturnIndex(uint8 Index)
{
	Unused.Enqueue(Index);
}

void UShowDamageComponent::BeginPlay()
{
	Super::BeginPlay();

	for(int i = 0; i < InitNumber; i++)
	{
		CreateNewWidget();
	}
}

void UShowDamageComponent::CreateNewWidget()
{
	auto Widget = CreateWidget<UDamageToShow>(GetWorld()->GetFirstPlayerController(),ShowDamageStyle->WidgetClass);

	const int Index = Widgets.Emplace(Widget);
	Unused.Enqueue(Index);
	
	Widget->Index = Index;
	Widget->Component = this;
	Widget->SetNormalFontSize(NormalFontSize);
	Widget->SetCritFontSize(CritFontSize);
	Widget->SetRandomX(RandomXMin,RandomXMax);
	Widget->SetRandomY(RandomYMin,RandomYMax);
	Widget->SetCritColor(ShowDamageStyle->CritColor);
	Widget->SetFontStyle(FontObject);

	Widget->AddToViewport();
}


