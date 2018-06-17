// All rights reserved. MOBILEDEV.

#include "PositionReporter.h"


// Sets default values for this component's properties
UPositionReporter::UPositionReporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    UE_LOG(LogTemp, Warning, TEXT("PositionReporter::Constructor"));
}


// Called when the game starts
void UPositionReporter::BeginPlay()
{
	Super::BeginPlay();

	FString ObjectName = GetOwner()->GetName();

	FVector DefaultLocation = GetOwner()->GetTransform().GetLocation();
	FVector NewStartLocation = DefaultLocation;
	NewStartLocation.X = 200;
	GetOwner()->GetTransform().SetLocation(NewStartLocation);

	UE_LOG(LogTemp, Warning, TEXT("New location is %s"), *(NewStartLocation.ToString()));

	FString ObjectPos = GetOwner()->GetActorLocation().ToString();
    UE_LOG(LogTemp, Warning, TEXT("%s is at %s"), *ObjectName, *ObjectPos);
}


// Called every frame
void UPositionReporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

