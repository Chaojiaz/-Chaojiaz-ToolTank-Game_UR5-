// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
// Constructor
ATank::ATank()
{
  SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
  SpringArm->SetupAttachment(RootComponent);

  Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
  Camera->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{

  Super::SetupPlayerInputComponent(PlayerInputComponent);

  PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
  PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
}

void ATank::Move(float Value)
{
  FVector DeltaLocation = FVector::ZeroVector;
  // X = Value * DeltaTime * Speed
  DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
  AddActorLocalOffset(DeltaLocation, true);
  // UE_LOG(LogTemp, Display, TEXT("The value is: %f"), Value);
}

void ATank::Turn(float Value)
{
  FRotator DeltaRotation = FRotator::ZeroRotator;
  // Yaw  = Values * DeltaTime * TurnRate
  DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
  AddActorLocalRotation(DeltaRotation, true);
}