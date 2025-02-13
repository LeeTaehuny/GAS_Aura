// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()
	
public:
	AAuraCharacter();

	virtual void PossessedBy(AController* NewController) override;

	// Pawn에 선언되어 있는 함수(PlayerState 복제)
	virtual void OnRep_PlayerState() override;

private:
	// AbilitySystemComponent의 Owner, Avatar 액터를 초기화하기 위한 함수
	void InitAbilityActorInfo();
};
