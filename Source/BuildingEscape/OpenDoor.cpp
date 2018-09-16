// All rights reserved. MOBILEDEV.

#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor() {
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}


// Called when the game starts
void UOpenDoor::BeginPlay() {
    Super::BeginPlay();

    FString ObjectName = GetOwner()->GetName();
    UE_LOG(LogTemp, Warning, TEXT("Object name is: %s"), *ObjectName);

    ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (PressurePlate != nullptr && PressurePlate->IsOverlappingActor(ActorThatOpens)) {
        OpenDoorAnimated();
    }
}

void UOpenDoor::OpenDoor() {
    AActor *Owner = GetOwner();
    FRotator RotationTransform = Owner->GetActorRotation();

    RotationTransform.Yaw = -OpenAngle;
    Owner->SetActorRotation(RotationTransform, ETeleportType::TeleportPhysics);
}

void UOpenDoor::OpenDoorAnimated() {
    AActor *Owner = GetOwner();
    FRotator RotationTransform = Owner->GetActorRotation();

    if (bOpenDoor) {
        if (RotationTransform.Yaw > -40) {
            RotationTransform.Yaw -= 0.5;
            Owner->SetActorRotation(RotationTransform, ETeleportType::TeleportPhysics);
        } else {
            bOpenDoor = false;
        }
    } else {
        if (RotationTransform.Yaw < 0) {
            RotationTransform.Yaw += 0.5;
            Owner->SetActorRotation(RotationTransform, ETeleportType::TeleportPhysics);
        } else {
            bOpenDoor = true;
        }
    }
}

void UOpenDoor::CloseDoor() {

}

