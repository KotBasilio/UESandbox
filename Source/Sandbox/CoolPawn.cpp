// Fill out your copyright notice in the Description page of Project Settings.


#include "CoolPawn.h"

#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACoolPawn::ACoolPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

   // Our root component will be a sphere that reacts to physics
   USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
   RootComponent = SphereComponent;
   SphereComponent->InitSphereRadius(40.0f);
   SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

   // Create and position a mesh component so we can see where our sphere is
   UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
   SphereVisual->SetupAttachment(RootComponent);
   static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
   if (SphereVisualAsset.Succeeded()) {
      SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
      SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
      SphereVisual->SetWorldScale3D(FVector(0.8f));
   }

   // Create a particle system that we can activate or deactivate
   OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
   OurParticleSystem->SetupAttachment(SphereVisual);
   OurParticleSystem->bAutoActivate = false;
   OurParticleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f));
   static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
   if (ParticleAsset.Succeeded()) {
      OurParticleSystem->SetTemplate(ParticleAsset.Object);
   }

   // Use a spring arm to give the camera smooth, natural-feeling motion.
   USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
   SpringArm->SetupAttachment(RootComponent);
   SpringArm->SetRelativeRotation(FRotator(-25.f, 0.f, 0.f));
   SpringArm->TargetArmLength = 400.0f;
   SpringArm->bEnableCameraLag = true;
   SpringArm->CameraLagSpeed = 3.0f;

   // Create a camera and attach to our spring arm
   UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
   Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

   // Take control of the default player
   AutoPossessPlayer = EAutoReceiveInput::Player0;

   // Create an instance of our movement component, and tell it to update the root.
   OurMovementComponent = CreateDefaultSubobject<UCoolPawnMC>(TEXT("CustomMovementComponent"));
   OurMovementComponent->UpdatedComponent = RootComponent;

}

// Called when the game starts or when spawned
void ACoolPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoolPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACoolPawn::SetupPlayerInputComponent(UInputComponent* InInputComponent)
{
	Super::SetupPlayerInputComponent(InInputComponent);

   InInputComponent->BindAction("ParticleToggle", IE_Pressed, this, &ACoolPawn::ParticleToggle);

   InInputComponent->BindAxis("MoveForward", this, &ACoolPawn::MoveForward);
   InInputComponent->BindAxis("MoveRight", this, &ACoolPawn::MoveRight);
   InInputComponent->BindAxis("Turn", this, &ACoolPawn::Turn);
}

void ACoolPawn::MoveForward(float AxisValue)
{
   if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
   {
      OurMovementComponent->AddInputVector(GetActorForwardVector() * AxisValue);
   }

}

void ACoolPawn::MoveRight(float AxisValue)
{
   if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
   {
      OurMovementComponent->AddInputVector(GetActorRightVector() * AxisValue);
   }
}

void ACoolPawn::Turn(float AxisValue)
{
   FRotator NewRotation = GetActorRotation();
   NewRotation.Yaw += AxisValue;
   SetActorRotation(NewRotation);
}

void ACoolPawn::ParticleToggle()
{
   if (OurParticleSystem && OurParticleSystem->Template)
   {
      OurParticleSystem->ToggleActive();
   }
}

