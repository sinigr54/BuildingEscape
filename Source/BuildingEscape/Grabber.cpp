// All rights reserved. MOBILEDEV.

#include "Grabber.h"

#include <Public/DrawDebugHelpers.h>
#include <Public/CollisionQueryParams.h>

#include <Engine/World.h>
#include <GameFramework/Actor.h>
#include <GameFramework/PlayerController.h>

#include <Components/PrimitiveComponent.h>

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber() {
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
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

    if (PhysicsHandleComponent->GetGrabbedComponent() != nullptr) {
        auto LineTraceEnd = CalculateLineTraceEnd();

        PhysicsHandleComponent->SetTargetLocation(LineTraceEnd);
    }
}

void UGrabber::Grab() {
    auto HitResult = GetFirstPhysicsBodyInReach();
    auto ComponentToGrab = HitResult.GetComponent();

    auto ActorHit = HitResult.GetActor();

    if (ActorHit != nullptr) {
        PhysicsHandleComponent->GrabComponent(
                ComponentToGrab,
                NAME_None,
                ComponentToGrab->GetOwner()->GetActorLocation(),
                true
        );
    }
}

void UGrabber::Release() {
    PhysicsHandleComponent->ReleaseComponent();
}

void UGrabber::FindPhysicsHandleComponent() {
    PhysicsHandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (PhysicsHandleComponent == nullptr) {
        UE_LOG(LogTemp, Error, TEXT("Object %s don't have PhysicsHandleComponent component. Add it at UA editor!"),
               *GetOwner()->GetName()
        )
    }
}

void UGrabber::SetUpInputComponent() {
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (InputComponent == nullptr) {
        UE_LOG(LogTemp, Error, TEXT("Object %s don't have InputComponent component. Add it at UA editor!"),
               *GetOwner()->GetName()
        )
    } else {
        InputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
        InputComponent->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabber::Release);
    }
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const {
    /// Setup query parameters
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

    /// Line-trace (AKA ray-cast) out to reach distance
    FHitResult HitResult;
    GetWorld()->LineTraceSingleByObjectType(
            OUT HitResult,
            GetOwner()->GetActorLocation(),
            CalculateLineTraceEnd(),
            FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
            TraceParameters
    );

    return HitResult;
}

FVector UGrabber::CalculateLineTraceEnd() const {
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;

    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
            OUT PlayerViewPointLocation,
            OUT PlayerViewPointRotation
    );

    return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}


