// All rights reserved. MOBILEDEV.

#include "Grabber.h"
#include <Public/DrawDebugHelpers.h>
#include <Public/CollisionQueryParams.h>

#include <Engine/World.h>
#include <GameFramework/Actor.h>
#include <GameFramework/PlayerController.h>

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber() {
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}


// Called when the game starts
void UGrabber::BeginPlay() {
    Super::BeginPlay();

    FindPhysicsHandleComponent();
    SetUpInputComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

void UGrabber::Grab() {
    UE_LOG(LogTemp, Warning, TEXT("Player Grab key pressed!"))

    GetFirstPhysicsBodyInReach();
}

void UGrabber::Release() {
    UE_LOG(LogTemp, Warning, TEXT("Player Grab key released!"))
}

void UGrabber::FindPhysicsHandleComponent() {
    /// Look for attached Physics Handle
    PhysicsHandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (PhysicsHandleComponent == nullptr) {
        UE_LOG(LogTemp, Error, TEXT("Object %s don't have PhysicsHandleComponent component. Add it at UA editor!"),
               *GetOwner()->GetName()
        )
    }
}

void UGrabber::SetUpInputComponent() {
    /// Look for attached Input Component
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (InputComponent == nullptr) {
        UE_LOG(LogTemp, Error, TEXT("Object %s don't have InputComponent component. Add it at UA editor!"),
               *GetOwner()->GetName()
        )
    } else {
        UE_LOG(LogTemp, Warning, TEXT("Input Component found!"))

        /// Bind the input axis
        InputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
        InputComponent->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabber::Release);
    }
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const {

    // Get player view point this tick
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;

    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
            OUT PlayerViewPointLocation,
            OUT PlayerViewPointRotation
    );

    FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

    /// Setup query parameters
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

    /// Line-trace (AKA ray-cast) out to reach distance
    FHitResult Hit;
    GetWorld()->LineTraceSingleByObjectType(
            OUT Hit,
            PlayerViewPointLocation,
            LineTraceEnd,
            FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
            TraceParameters
    );

    AActor *actor = Hit.GetActor();
    if (actor != nullptr) {
        UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"),
               *(actor->GetName())
        )
    }

    return Hit;
}

