// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingActor.h"

// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

   // code from  https://docs.unrealengine.com/4.27/en-US/ProgrammingAndScripting/ProgrammingWithCPP/CPPProgrammingQuickStart/
   VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
   VisualMesh->SetupAttachment(RootComponent);

   static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

   if (CubeVisualAsset.Succeeded()) {
      VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
      VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
   }
}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

   // code from  https://docs.unrealengine.com/4.27/en-US/ProgrammingAndScripting/ProgrammingWithCPP/CPPProgrammingQuickStart/
   FVector NewLocation = GetActorLocation();
   FRotator NewRotation = GetActorRotation();
   float RunningTime = GetGameTimeSinceCreation();
   float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
   NewLocation.Z += DeltaHeight * FloatSpeed;       //Scale our height by a factor of FloatSpeed
   NewLocation.X += DeltaHeight * ShiftSpeed;
   
   float DeltaRotation = DeltaTime * RotationSpeed;    //Rotate by a number of degrees equal to RotationSpeed each second
   NewRotation.Yaw += DeltaRotation;
   SetActorLocationAndRotation(NewLocation, NewRotation);
}

