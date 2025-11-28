#pragma once

#include "CoreMinimal.h"

class ChatXFunctionLibrary
{
public:
	static void MyPrintString(const AActor* InWorldContextActor, const FString& InString, float InTimeToDisplay = 1.f,
		FColor InColor = FColor::Cyan)
	{
		//UEngine* GEngine(Global Engine) = 언리얼 전역 엔진 포인터가 유효한가? - 언리얼이 제대로 초기화된 상태 
		//InWorldContextActor = 월드를 특정할 수 있는 엑터(World | World에 속한 엑터)
		if (IsValid(GEngine) && IsValid(InWorldContextActor))
		{
			if (InWorldContextActor->GetNetMode() == NM_Client || InWorldContextActor->GetNetMode() == NM_ListenServer)
			{
				GEngine->AddOnScreenDebugMessage(01, InTimeToDisplay, InColor, InString);
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("%s"), *InString);
			}
		}
	}
	
	static FString GetNetModeString(const AActor* InWorldContextActor)
	{
		FString NetModeString = TEXT("None");

		if (IsValid(InWorldContextActor))
		{
			ENetMode NetMode = InWorldContextActor->GetNetMode();
			if (NetMode == NM_Client)
			{
				NetModeString = TEXT("Client");
			}
			else
			{
				if (NetMode == NM_Standalone)
				{
					NetModeString = TEXT("StandAlone");
				}
				else
				{
					NetModeString = TEXT("Server");
				}
			}
		}
		return NetModeString; 
	}

	static FString GetRoleString(const AActor* InActor)
	{
		FString RoleString = TEXT("None");

		if (IsValid(InActor))
		{
			//UEnum::GetValueAsString() => Enum 값을 String으로 변환 
			FString LocalRoleString = UEnum::GetValueAsString(TEXT("Engine.ENetRole"), InActor->GetLocalRole());
			FString RemotoRoleString = UEnum::GetValueAsString(TEXT("Engine.ENetRole"), InActor->GetRemoteRole());
		}
		return RoleString;
	}
};