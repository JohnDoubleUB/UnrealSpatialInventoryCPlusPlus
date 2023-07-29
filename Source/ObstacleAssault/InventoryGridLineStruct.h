#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryGridLineStruct.generated.h"

//If you want this to appear in BP, make sure to use this instead //USTRUCT(BlueprintType)
USTRUCT(BlueprintType) 
struct OBSTACLEASSAULT_API FInventoryGridLineStruct
{
    GENERATED_BODY()

    FInventoryGridLineStruct()
        : Start(FVector2D(0, 0))
        , End(FVector2D(0, 0))
    {}

    FInventoryGridLineStruct(FVector2D NewStart, FVector2D NewEnd)
    {
        Start = NewStart;
        End = NewEnd;
    }

    UPROPERTY(EditAnywhere)
    FVector2D Start;

    UPROPERTY(EditAnywhere)
    FVector2D End;

    void SetStart(FVector2D NewStart)
    {
        Start = NewStart;
    }

    void SetEnd(FVector2D NewEnd)
    {
        End = NewEnd;
    }

    FVector2D GetStart() 
    {
        return Start;
    }

    FVector2D GetEnd()
    {
        return End;
    }
};