#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PlayerSaveGame.generated.h"

UCLASS()
class YOURGAME_API UPlayerSaveGame : public USaveGame
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, Category = "Basic")
    FVector PlayerLocation;

    UPROPERTY(VisibleAnywhere, Category = "Basic")
    FRotator PlayerRotation;

    UPROPERTY(VisibleAnywhere, Category = "Basic")
    float PlayerHealth;

    UPROPERTY(VisibleAnywhere, Category = "Inventory")
    TArray<FString> InventoryItems;
};




