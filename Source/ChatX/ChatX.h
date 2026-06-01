// ChatX.h

#pragma once

#include "CoreMinimal.h"

class ChatXFunctionLibrary
{
public:
	static void MyPrintString(const AActor* InWorldContextActor, const FString& InString, float InTimeToDisplay = 1.f, FColor InColor = FColor::Cyan)
	{
		if (IsValid(GEngine) == true && IsValid(InWorldContextActor) == true)
		{
			if (InWorldContextActor->GetNetMode() == NM_Client || InWorldContextActor->GetNetMode() == NM_ListenServer)
			{
				GEngine->AddOnScreenDebugMessage(-1, InTimeToDisplay, InColor, InString);
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-2, InTimeToDisplay, FColor::Red, InString);
			}
		}
	}
	
	static FString GetNetModeString(const AActor* InWorldContextActor)
	{
		FString NetModeString = FString();
		
		if (IsValid(InWorldContextActor) == true)
		{
			ENetMode NetMode = InWorldContextActor->GetNetMode();
			if (NetMode == NM_Client)
			{
				NetModeString = FString("Client");
			}
			else
			{
				if (NetMode == NM_Standalone)
				{
					NetModeString = FString("StandAlone");
				}
				else
				{
					NetModeString = FString("Server");
				}
			}
		}
		
		return NetModeString;
	}
	
};

