// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ShowDamageStyle.generated.h"


class UDamageToShow;
/**
 * @brief 伤害属性
 */
UENUM(BlueprintType)
enum class EDamageAttributeType : uint8
{
	None,

	/**
	 * @brief 普通属性
	 */
	Normal,

	/**
	 * @brief 水属性
	 */
	Water,

	/**
	 * @brief 火属性
	 */
	Fire,

	/**
	 * @brief 光属性
	 */
	Light,

	/**
	 * @brief 暗属性
	 */
	Dark,
};

/**
 * 
 */
UCLASS(BlueprintType)
class SHOWDAMAGEPLUGIN_API UShowDamageStyle : public UObject
{
	GENERATED_BODY()

public:
	UShowDamageStyle();

	/**
	 * 需要生成的 Widget Class
	 */
	UPROPERTY(EditAnywhere, Category = "Show Damage Component|Normal")
	TSubclassOf<UDamageToShow> WidgetClass;
	
	/**
	 * 伤害属性以及对应的伤害颜色
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Show Damage Component|Font")
	TMap<EDamageAttributeType, FLinearColor> DamageColor;

	/**
	 * 伤害属性以及对应的伤害 Icon
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Show Damage Component|Font")
	TMap<EDamageAttributeType, UTexture2D*> DamageIcon;

	/**
	 * 暴击时的伤害颜色
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Show Damage Component|Font")
	FLinearColor CritColor;
};
