#include "EnvQueryGenerator_Grid3D.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Location.h"
#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"

UEnvQueryGenerator_Grid3D::UEnvQueryGenerator_Grid3D()
{
    ItemType = UEnvQueryItemType_Location::StaticClass();

    GridHalfSize.DefaultValue = 1000.0f;
    SpaceBetween.DefaultValue = 300.0f;
    ZLayers.DefaultValue = 5;

    GenerateAround = UEnvQueryContext_Querier::StaticClass();
}

void UEnvQueryGenerator_Grid3D::GenerateItems(FEnvQueryInstance& QueryInstance) const
{
    float Radius = 0.0f;
    float Density = 0.0f;
    int32 Layers = 0;

    if (!GridHalfSize.GetValue(QueryInstance.QueryID, Radius) ||
        !SpaceBetween.GetValue(QueryInstance.QueryID, Density) ||
        !ZLayers.GetValue(QueryInstance.QueryID, Layers))
    {
        return;
    }

    const int32 ItemCountX = FMath::FloorToInt(Radius / Density);
    const int32 ItemCountY = FMath::FloorToInt(Radius / Density);
    const float LayerHeight = Density;

    TArray<FVector> ContextLocations;
    QueryInstance.PrepareContext(GenerateAround, ContextLocations);

    for (const FVector& ContextLocation : ContextLocations)
    {
        for (int32 z = -Layers; z <= Layers; z++)
        {
            for (int32 x = -ItemCountX; x <= ItemCountX; x++)
            {
                for (int32 y = -ItemCountY; y <= ItemCountY; y++)
                {
                    FVector Point = ContextLocation + FVector(x * Density, y * Density, z * LayerHeight);
                    QueryInstance.AddItemData<UEnvQueryItemType_Location>(Point);
                }
            }
        }
    }
}