#include "EnvQuery_Grid3D.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Vector.h"

UEnvQuery_Grid3D::UEnvQuery_Grid3D()
{
    ItemType = UEnvQueryItemType_Vector::StaticClass();
}

void UEnvQuery_Grid3D::GenerateItems(FEnvQueryInstance& QueryInstance) const
{
    const FVector Center = QueryInstance.Owner.Get()->GetActorLocation();
    const int32 NumX = FMath::RoundToInt(GridSize.X / DistanceBetweenPoints);
    const int32 NumY = FMath::RoundToInt(GridSize.Y / DistanceBetweenPoints);
    const int32 NumZ = FMath::RoundToInt(GridSize.Z / DistanceBetweenPoints);

    TArray<FVector> Points;

    for (int32 X = -NumX / 2; X <= NumX / 2; ++X)
    {
        for (int32 Y = -NumY / 2; Y <= NumY / 2; ++Y)
        {
            for (int32 Z = -NumZ / 2; Z <= NumZ / 2; ++Z)
            {
                FVector Point = Center + FVector(X, Y, Z) * DistanceBetweenPoints;
                Points.Add(Point);
            }
        }
    }

    for (const FVector& Point : Points)
    {
        QueryInstance.AddItemData<UEnvQueryItemType_Vector>(Point);
    }
}
