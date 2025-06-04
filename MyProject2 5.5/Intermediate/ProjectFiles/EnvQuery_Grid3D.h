#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryGenerator.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvQuery_Grid3D.generated.h"

UCLASS(meta = (DisplayName = "3D Grid Points"))
class MYPROJECT2_API UEnvQuery_Grid3D : public UEnvQueryGenerator
{
    GENERATED_BODY()

public:
    UEnvQuery_Grid3D();

protected:
    virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const override;

public:
    UPROPERTY(EditDefaultsOnly, Category = "Grid")
    FVector GridSize = FVector(1000.f, 1000.f, 1000.f);

    UPROPERTY(EditDefaultsOnly, Category = "Grid")
    float DistanceBetweenPoints = 100.f;
};
