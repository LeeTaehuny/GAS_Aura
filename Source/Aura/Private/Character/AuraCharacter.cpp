// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// 서버에서 실행되는 함수
	// *  AbilitySystemComponent의 Owner, Avatar 액터를 초기화합니다.
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// 클라이언트에서 실행되는 함수
	// *  AbilitySystemComponent의 Owner, Avatar 액터를 초기화합니다.
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	// * AuraPlayerState를 받아와 유효한지 체크합니다.
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);

	// AbilitySystemComponent에 Owner, Avatar 액터를 설정합니다.
	// * 플레이어의 경우 여러 캐릭터로 변경이 가능하므로 Owner는 언제나 사용하는 AuraPlayerState가 됩니다.
	// * Avatar의 경우 빙의 시 선택한 액터로 지정합니다.
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);

	// CharacterBase에 선언되어 있는 캐싱 변수들의 값을 채워줍니다.
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();
}