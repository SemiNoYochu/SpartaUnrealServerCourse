// Fill out your copyright notice in the Description page of Project Settings.


#include "CXPlayerController.h"

#include "ChatX.h"
#include "EngineUtils.h"
#include "UI/CXChatInput.h"

void ACXPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsLocalController() == false)
	{
		return;
	}
	
	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);

	if (IsValid(ChatInputWidgetClass) == true)
	{
		ChatInputWidgetInstance = CreateWidget<UCXChatInput>(this, ChatInputWidgetClass);
		if (IsValid(ChatInputWidgetInstance) == true)
		{
			ChatInputWidgetInstance->AddToViewport();
		}
	}
}

void ACXPlayerController::SetChatMessageString(const FString& InChatMessageString)
{
	ChatMessageString = InChatMessageString;
	if (IsLocalController() == true)
	{
		ServerRPCPrintChatMessageString(InChatMessageString);
	}
}

void ACXPlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	ChatXFunctionLibrary::MyPrintString(this, InChatMessageString);
}

void ACXPlayerController::ClientRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	PrintChatMessageString(InChatMessageString);
}

void ACXPlayerController::ServerRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	// ServerRPC: Server에서 실행된다.
	// 내부 로직: Server에 존재하는 ACXPlayerController를 Iterator를 통해 순회하여, 등록된 모든 ACXPlayerController가 존재하는 Client에 ClientRPC 함수를 호출한다.
#pragma region ServerRPC
	// PrintChatMessageString(InChatMessageString);
	
	// for (TActorIterator<ACXPlayerController> It(GetWorld()); It; ++It)
	// {
	// 	ACXPlayerController* CXPlayerController = *It;
	// 	if (IsValid(CXPlayerController) == true)
	// 	{
	// 		CXPlayerController->ClientRPCPrintChatMessageString(InChatMessageString);
	// 	}
	// }
#pragma endregion 
	
	// NetMulticastRPC: Server + 모든 Actor에 호출하지만? 해당 Actor를 보유하지 않은 클라이언트는 실행되지 않고 Drop된다?
#pragma region NetMulticastRPC
	NetMulticastRPCPrintCastMessageString(InChatMessageString);
#pragma endregion
}

void ACXPlayerController::NetMulticastRPCPrintCastMessageString_Implementation(const FString& InChatMessageString)
{
	PrintChatMessageString(InChatMessageString);
}