// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UAuraAttributeSet();

protected:
	// Replicate를 사용하기 위해 변수를 등록하는 함수
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	// GAS에서 사용하는 Attribute는 FGameplayAttributeData로 관리됩니다.
	// 해당 변수가 서버에서 변경되면 복제가 일어나도록 매크로를 추가합니다.
	// * 체력
	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	// * 최대 체력
	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	// * 마나
	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes", ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;
	// * 최대 마나
	UPROPERTY(BlueprintReadOnly, Category = "Vital Attributes", ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;


public:
	// 체력이 복제되면 실행되는 함수(클라이언트)
	// * OldHealth : 기존 클라이언트에서 가지고 있던 Health값(서버 X)
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	// 최대 체력이 복제되면 실행되는 함수(클라이언트)
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	// 마나가 복제되면 실행되는 함수(클라이언트)
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	// 최대 마나가 복제되면 실행되는 함수(클라이언트)
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
};
