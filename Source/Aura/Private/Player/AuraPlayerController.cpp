// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include "Interaction/EnemyInterface.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

AAuraPlayerController::AAuraPlayerController()
{
	// 복제되도록 설정합니다.
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// 커서 아래의 적을 체크하는 것은 비용이 많이 소모되지 않음
	// * 매 프레임 적을 체크합니다.
	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	// 커서 아래의 물체를 체크합니다.
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, CursorHit);

	// 물체가 없는 경우 종료합니다.
	if (!CursorHit.bBlockingHit) return;

	// 현재 저장된 액터를 이전 액터로 변경하고 현재 액터는 새로 받아옵니다.
	LastActor = ThisActor;
	// * 원시 포인터의 경우 이렇게 매 프레임 Cast를 통해 체크를 해야 함
	//   ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());
	// * TScriptInterface를 사용하면 Cast를 사용하지 않아도 됨(효율적)
	ThisActor = CursorHit.GetActor();

	// A: 이전 액터가 null이고, 현재 액터도 null인 경우						- 아무것도 하지 않음
	// B: 이전 액터가 null이고, 현재 액터는 존재하는 경우					- 현재 액터만 HighlightActor() 함수 실행
	// C: 이전 액터는 존재하고, 현재 액터는 null인 경우						- 이전 액터만 UnHighlightActor() 함수 실행
	// D: 이전 액터도 존재하고, 현재 액터도 존재하는 경우 (두 액터가 다름)	- 이전 액터 UnHighlightActor(), 현재 액터 HighlightActor() 함수 실행
	// E: 이전 액터도 존재하고, 현재 액터도 존재하는 경우 (두 액터가 같음)  - 아무것도 하지 않음

	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			// Case B
			ThisActor->HighlightActor();
		}
		else {}// Case A : Do Noting
	}
	else
	{
		if (ThisActor == nullptr)
		{
			// Case C
			LastActor->UnHighlightActor();
		}
		else
		{
			if (LastActor != ThisActor)
			{
				// Case D
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else {} // Case E : Do Noting
		}
	}
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

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// 일반 입력 컴포넌트를 강화된 입력 컴포넌트의 포인터로 형변환 합니다.
	// * CastChecked : 형변환 실패 시 종료시켜주는 함수
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	// Action Binding
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	// 전달받은 값을 추출합니다.
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	// 플레이어의 전방 방향은 플레이어 컨트롤러가 바라보고 있는 전방 방향을 의미합니다.
	// * 플레이어 컨트롤러의 Yaw 값을 추출합니다.
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	// * 얻어온 Yaw값을 가지고 X(Forawrd)방향을 구해주도록 합니다.
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	// * 얻어온 Yaw값을 가지고 Y(Right)방향을 구해주도록 합니다.
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// 구한 방향 및 전달받은 값을 바탕으로 이동 명령을 내립니다.
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}