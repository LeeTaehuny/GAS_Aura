// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerState.h"

AAuraPlayerState::AAuraPlayerState()
{
	// 네트워크 업데이트 빈도를 설정합니다.
	// * 서버가 클라이언트를 업데이트 하는 빈도
	// * 서버의 PlayerState가 변경되면 서버는 모든 클라이언트에게 변경 정보를 업데이트 하는 방식
	NetUpdateFrequency = 100.0f;
}
