// All rights reserved. MOBILEDEV.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include <PhysicsEngine/PhysicsHandleComponent.h>
#include <Components/InputComponent.h>

#include "Grabber.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UGrabber : public UActorComponent {

    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UGrabber();

protected:
    // Called when the game starts
    void BeginPlay() override;

public:
    // Called every frame
    void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:

    float Reach{100.0f};

    UPhysicsHandleComponent *PhysicsHandleComponent{nullptr};
    UInputComponent *InputComponent{nullptr};

    void Grab();

    void Release();

    void FindPhysicsHandleComponent();

    void SetUpInputComponent();

    FHitResult GetFirstPhysicsBodyInReach() const;

    inline FVector CalculateLineTraceEnd() const;
};
