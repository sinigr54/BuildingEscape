// All rights reserved. MOBILEDEV.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorEvent);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent {

    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UOpenDoor();

protected:
    // Called when the game starts
    void BeginPlay() override;

public:
    // Called every frame
    void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

    UPROPERTY(BlueprintAssignable)
    FOnDoorEvent OnOpen;

    UPROPERTY(BlueprintAssignable)
    FOnDoorEvent OnClose;

private:

    UPROPERTY(EditAnywhere)
    float TriggerMass = 30.0f;

    UPROPERTY(EditAnywhere)
    ATriggerVolume *PressurePlate = nullptr;

private:

    float GetTotalMassOfActorsOnPlate() const;
};
