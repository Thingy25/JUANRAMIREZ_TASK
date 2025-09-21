// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseObstacle.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "InteractionInterface.h"

// Sets default values
ABaseObstacle::ABaseObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ObstacleMesh->SetupAttachment(RootComponent);
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ScoreCollision"));
	BoxCollision->SetupAttachment(ObstacleMesh);

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseObstacle::OnOverlapBegin);

	Score = 50;

}

// Called when the game starts or when spawned
void ABaseObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseObstacle::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
	{
		if (!OverlappedActors.Contains(OtherActor))
		{
			OverlappedActors.Add(OtherActor);
			IInteractionInterface::Execute_OnObstaclePassed(OtherActor, Score);
		}
	}

	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow,
			FString::Printf(TEXT("%s"), *OtherActor->GetName()));
	}*/
}

