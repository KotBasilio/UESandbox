// Fill out your copyright notice in the Description page of Project Settings.
#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

   const float TimeBetweenCameraChanges = 2.0f;
   const float SmoothBlendTime = 0.75f;

   TimeToNextCameraChange -= DeltaTime;
   if (TimeToNextCameraChange > 0.0f) {
      return;
   }
   TimeToNextCameraChange += TimeBetweenCameraChanges;

   // Find the actor that handles control for the local player.
   APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
   if (!OurPlayerController) {
      return;
   }

   // cam switch logic
   auto curTarget = OurPlayerController->GetViewTarget();
   if (CameraOne && !done1stSet ) {
      // first => cut instantly
      OurPlayerController->SetViewTarget(CameraOne);
      done1stSet = true;
      return;
   }
   if (CameraTwo && (curTarget == CameraOne)) {
      // Blend smoothly to camera two.
      OurPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
      return;
   }
   if (Camera3 && (curTarget == CameraTwo)) {
      // Blend smoothly to camera two.
      OurPlayerController->SetViewTargetWithBlend(Camera3, SmoothBlendTime);
      TimeToNextCameraChange += TimeBetweenCameraChanges;
      return;
   }
   if (CameraOne && curTarget == Camera3) {
      // blend back
      OurPlayerController->SetViewTargetWithBlend(CameraOne, SmoothBlendTime);
      return;
   }
}

