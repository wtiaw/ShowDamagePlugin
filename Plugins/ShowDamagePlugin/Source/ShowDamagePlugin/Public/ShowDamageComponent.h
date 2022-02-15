// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageToShow.h"
#include "ShowDamageStyle.h"
#include "Components/SceneComponent.h"
#include "ShowDamageComponent.generated.h"


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

	

	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category = "Show Damage Component")
	UShowDamageStyle* ShowDamageStyle;

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
