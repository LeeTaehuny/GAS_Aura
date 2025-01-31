// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

UCLASS()
class AURA_API AAuraCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

protected:
	virtual void BeginPlay() override;

protected:
	// TObjectPtr와 원시 포인터의 차이
	// - 기본적으로 일반적인 포인터처럼 동작하지만 에디터에서 몇 가지 추가 기능을 가짐
	// 1. 접근 추적(access tracking): 특정 포인터가 얼마나 자주 접근되거나 역참조되는지를 추적할 수 있습니다.
	// 2. 지연 로드(lazy loading): 실제로 필요할 때까지 에셋을 로드하지 않고 대기할 수 있도록 합니다.
	// 현재 언리얼 엔진에서는 멤버 변수로 TObjectPtr을 사용하는 방향으로 표준이 이동하고 있습니다.
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<class USkeletalMeshComponent> Weapon;
};
