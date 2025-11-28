#include "Game/CXGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/CXPlayerController.h"

void ACXGameStateBase::MulticastRPCBroadcastLoginMessage_Implementation(const FString& InNameString)
{
	if (!HasAuthority())
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (IsValid(PC))
		{
			ACXPlayerController* CXPC = Cast<ACXPlayerController>(PC);
			if (IsValid(CXPC))
			{
				FString NotificationString = InNameString + TEXT("has joined the game");
				CXPC->PrintChatMessageString(NotificationString);
			}
		}
	}
}
