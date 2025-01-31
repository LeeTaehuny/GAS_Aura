// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacterBase.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// 무기를 장착하기 위한 컴포넌트를 생성하고 기본 메쉬에 부착시켜줍니다.
	// - 무기는 WeaponHandSocket에 부착되어야 하며, 충돌하지 않도록 설정합니다.
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

