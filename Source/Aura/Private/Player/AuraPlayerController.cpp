// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"

AAuraPlayerController::AAuraPlayerController()
{
	// 복제되도록 설정합니다.
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 입력이 존재하지 않는 것은 게임이 중단될 정도로 중요한 이슈입니다.
	// * Check 를 사용해 입력이 존재하지 않는 경우 게임을 중단하도록 만들어줍니다.
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);

	Subsystem->AddMappingContext(AuraContext, 0);

	// 마우스 커서를 보이게 합니다.
	bShowMouseCursor = true;
	// 기본 커서의 종류를 선택합니다.
	DefaultMouseCursor = EMouseCursor::Default;

	// 입력 모드를 Game&UI 모드로 설정합니다.
	FInputModeGameAndUI InputModeData;

	// 마우스 화면에 고정 X
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	// viewport에 마우스 커서가 캡처 되어도 커서를 숨김 X
	InputModeData.SetHideCursorDuringCapture(false);

	SetInputMode(InputModeData);
}
