// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraEnemy.h"
#include "Aura.h"

AAuraEnemy::AAuraEnemy()
{
	// 메쉬의 충돌 채널을 설정합니다. (Visibility 충돌 허용)
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
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
