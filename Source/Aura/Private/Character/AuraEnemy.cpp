// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraEnemy.h"
#include "Aura.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraEnemy::AAuraEnemy()
{
	// 메쉬의 충돌 채널을 설정합니다. (Visibility 충돌 허용)
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	// AbilitySystemComponent를 상속받은 UAuraAbilitySystemComponent를 생성합니다.
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	// AbilitySystemComponent를 복제하도록 설정합니다.
	AbilitySystemComponent->SetIsReplicated(true);

	// 복제 모드를 선택합니다.
	// - Minimal(Multiplayer, AI-Controlled)	: Gameplay Effect는 복제 X, Gameplay Cue, Gameplay Tags는 모든 클라이언트에게 복제 O 
	// - Mixed(Multiplayer, Player-Controlled)	: Gameplay Effect는 복제 O(소유권이 있는 클라이언트), Gameplay Cue, Gameplay Tags는 모든 클라이언트에게 복제 O 
	// - Full(Singleplayer)						: Gameplay Effect는 모든 클라이언트에게 복제 O
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	// AttributeSet을 상속받은 UAuraAttributeSet을 생성합니다.
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>(TEXT("AttributeSet"));
}

void AAuraEnemy::HighlightActor()
{
	// 캐릭터 메쉬의 Custom Depth를 활성화하고 250의 값을 설정합니다.
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	// 무기 메쉬의 Custom Depth를 활성화하고 250의 값을 설정합니다.
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::UnHighlightActor()
{
	// 캐릭터 메쉬의 Custom Depth를 비활성화합니다.
	GetMesh()->SetRenderCustomDepth(false);
	// 무기 메쉬의 Custom Depth를 비활성화합니다.
	Weapon->SetRenderCustomDepth(false);
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();

	// AbilitySystemComponent의 Owner, Avatar 액터를 설정합니다.
	// * Enemy의 경우 둘이 동일합니다.
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
