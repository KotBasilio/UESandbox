// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CoolPawnMC.h"
#include "CoolPawn.generated.h"

UCLASS()
class SANDBOX_API ACoolPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACoolPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

   UPROPERTY()
      class UParticleSystemComponent* OurParticleSystem;

   UPROPERTY()
      class UCoolPawnMC* OurMovementComponent;

	virtual UPawnMovementComponent* GetMovementComponent() const override { return OurMovementComponent; }

   void MoveForward(float AxisValue);
   void MoveRight(float AxisValue);
   void Turn(float AxisValue);
   void ParticleToggle();
};
