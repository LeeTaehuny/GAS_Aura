// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraPlayerState::AAuraPlayerState()
{
	// AbilitySystemComponent를 상속받은 UAuraAbilitySystemComponent를 생성합니다.
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	// AbilitySystemComponent를 복제하도록 설정합니다.
	AbilitySystemComponent->SetIsReplicated(true);

	// 복제 모드를 선택합니다.
	// - Minimal(Multiplayer, AI-Controlled)	: Gameplay Effect는 복제 X, Gameplay Cue, Gameplay Tags는 모든 클라이언트에게 복제 O 
	// - Mixed(Multiplayer, Player-Controlled)	: Gameplay Effect는 복제 O(소유권이 있는 클라이언트), Gameplay Cue, Gameplay Tags는 모든 클라이언트에게 복제 O 
	// - Full(Singleplayer)						: Gameplay Effect는 모든 클라이언트에게 복제 O
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	// AttributeSet을 상속받은 UAuraAttributeSet을 생성합니다.
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>(TEXT("AttributeSet"));

	// 네트워크 업데이트 빈도를 설정합니다.
	// * 서버가 클라이언트를 업데이트 하는 빈도
	// * 서버의 PlayerState가 변경되면 서버는 모든 클라이언트에게 변경 정보를 업데이트 하는 방식
	NetUpdateFrequency = 100.0f;
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
