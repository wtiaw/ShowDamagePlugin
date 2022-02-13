// Fill out your copyright notice in the Description page of Project Settings.


#include "ShowDamageComponent.h"

UShowDamageComponent::UShowDamageComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	InitNumber = 10;

	static ConstructorHelpers::FClassFinder<UDamageToShow> WidgetFinder(TEXT("WidgetBlueprint'/ShowDamagePlugin/UMG/WBP_DamageToShow.WBP_DamageToShow_C'"));
	if(WidgetFinder.Succeeded())
	{
		WidgetClass = WidgetFinder.Class;
	}

	DamageColor.Add(EDamageAttributeType::Normal,FLinearColor(1,1,1,1));
	DamageIcon.Add(EDamageAttributeType::Normal,nullptr);
}


void UShowDamageComponent::TakeDamage(int Damage, EDamageAttributeType DamageAttribute, bool bCrit, FLinearColor InCritColor)
{
	if (Unused.IsEmpty())
	{
		CreateNewWidget();
	}
	
	uint8 Index;
	Unused.Dequeue(Index);

	Widgets[Index]->ShowDamageText(Damage,*DamageColor.Find(DamageAttribute),*DamageIcon.Find(DamageAttribute),bCrit,InCritColor);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("%d"), Index));
}

void UShowDamageComponent::ReturnIndex(uint8 Index)
{
	Unused.Enqueue(Index);
}

// Called when the game starts
void UShowDamageComponent::BeginPlay()
{
	Super::BeginPlay();

	for(int i = 0;i<InitNumber;i++)
	{
		CreateNewWidget();
	}
}

void UShowDamageComponent::CreateNewWidget()
{
	auto Widget = CreateWidget<UDamageToShow>(GetWorld()->GetFirstPlayerController(),WidgetClass);

	const int Index = Widgets.Emplace(Widget);
	Unused.Enqueue(Index);
	
	Widget->Index = Index;
	Widget->Component = this;
	Widget->AddToViewport();
}


