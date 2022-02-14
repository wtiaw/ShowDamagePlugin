// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageToShow.h"
#include "Components/SceneComponent.h"
#include "ShowDamageComponent.generated.h"

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
 * @brief 挂载在 Actor 身上的 Component
 */
UCLASS( ClassGroup=(Custom), BlueprintType,  meta=(BlueprintSpawnableComponent) )
class SHOWDAMAGEPLUGIN_API UShowDamageComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UShowDamageComponent();

	/**
	 * Widget 对象池的初始化数量
	 */
	UPROPERTY(EditAnywhere, Category = "Show Damage Component|Normal")
	int InitNumber;

	/**
	 * 需要生成的 Widget Class
	 */
	UPROPERTY(EditAnywhere, Category = "Show Damage Component|Normal")
	TSubclassOf<UDamageToShow> WidgetClass;

	/**
	 * X 偏移的最小值
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Show Damage Component|Normal|Random Offset")
	int32 RandomXMin;

	/**
	 * X 偏移的最小值
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Show Damage Component|Normal|Random Offset")
	int32 RandomXMax;

	/**
	 * Y 偏移的最大值
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Show Damage Component|Normal|Random Offset")
	int32 RandomYMin;

	/**
	 * Y 偏移的最小值
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Show Damage Component|Normal|Random Offset")
	int32 RandomYMax;

	/**
	 * 伤害文本字体设置
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Show Damage Component|Font", meta=(AllowedClasses="Font", DisplayName="Font Family"))
	UObject* FontObject;

	/**
	 * 普通的字体大小
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Show Damage Component|Font")
	int NormalFontSize;

	/**
	 * 暴击时的字体大小
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Show Damage Component|Font")
	int CritFontSize;
	
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
	
private:
	/**
	 * @brief Widget 对象池
	 */
	UPROPERTY()
	TArray<UDamageToShow*> Widgets;

	/**
	 * @brief 存放未在使用的下标
	 */
	TQueue<uint8> Unused;

public:
	/**
	 * @brief 造成伤害时调用
	 * @param Damage 造成的伤害
	 * @param DamageAttribute 伤害的属性类型
	 * @param bCrit 是否暴击
	 * @param InCritColor 暴击的文本颜色
	 */
	UFUNCTION(BlueprintCallable)
	void TakeDamage(int Damage, EDamageAttributeType DamageAttribute, bool bCrit = false, FLinearColor InCritColor = FLinearColor(1,1,0,1));

	/**
	 * @brief 把下标放回队列中
	 * @param Index 需要放回的下标
	 */
	void ReturnIndex(uint8 Index);
	
protected:
	virtual void BeginPlay() override;

private:
	/**
	 * @brief 创建新的 Widget
	 */
	void CreateNewWidget();
};
