// All rights reserved. MOBILEDEV.

#include "OpenDoor.h"

#include <Engine/World.h>
#include <GameFramework/Actor.h>
#include <GameFramework/PlayerController.h>

#include <Components/PrimitiveComponent.h>

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor() {
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay() {
    Super::BeginPlay();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (PressurePlate == nullptr) {
        UE_LOG(LogTemp, Error, TEXT("Error: PressurePlace is null!"))
        return;
    }

    if (GetTotalMassOfActorsOnPlate() > TriggerMass) {
        OnOpen.Broadcast();
    } else {
        OnClose.Broadcast();
    }
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() const {
    float TotalMass = 0.0f;

    TArray<AActor *> OverlappingActors;
    PressurePlate->GetOverlappingActors(OUT OverlappingActors);

    for (const auto &Actor : OverlappingActors) {
        TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
    }

    return TotalMass;
}

