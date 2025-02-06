// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAuraPlayerController();

	// 플레이어 컨트롤러에서의 Ticjk 함수
	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(Editanywhere, Category = "Input")
	TObjectPtr<class UInputMappingContext> AuraContext;

	UPROPERTY(Editanywhere, Category = "Input")
	TObjectPtr<class UInputAction> MoveAction;

	// struct를 붙여 구조체 또한 전방 선언이 가능합니다.
	void Move(const struct FInputActionValue& InputActionValue);

private:
	// 커서 아래의 적 유무를 판별하기 위한 함수
	void CursorTrace();

	// 원시 포인터 대신 TScriptInterface를 사용해 안전하게 관리합니다.
	TScriptInterface<class IEnemyInterface> LastActor;
	TScriptInterface<class IEnemyInterface> ThisActor;
};
