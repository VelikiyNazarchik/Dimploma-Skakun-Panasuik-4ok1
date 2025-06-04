#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryGenerator.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvQueryGenerator_Grid3D.generated.h"

UCLASS(meta = (DisplayName = "3D Grid"))
class MYPROJECT2_API UEnvQueryGenerator_Grid3D : public UEnvQueryGenerator
{
    GENERATED_BODY()

public:
    UEnvQueryGenerator_Grid3D();

protected:
    virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const override;

public:
    UPROPERTY(EditDefaultsOnly, Category = Generator)
    FAIDataProviderFloatValue GridHalfSize;

    UPROPERTY(EditDefaultsOnly, Category = Generator)
    FAIDataProviderFloatValue SpaceBetween;

    UPROPERTY(EditDefaultsOnly, Category = Generator)
    FAIDataProviderIntValue ZLayers;

    UPROPERTY(EditDefaultsOnly, Category = Generator)
    TSubclassOf<UEnvQueryContext> GenerateAround;
};
