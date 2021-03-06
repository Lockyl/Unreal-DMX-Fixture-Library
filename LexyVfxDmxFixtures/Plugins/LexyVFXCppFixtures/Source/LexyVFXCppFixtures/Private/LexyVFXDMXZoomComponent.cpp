// Fill out your copyright notice in the Description page of Project Settings.


#include "LexyVFXDMXZoomComponent.h"

void ULexyVFXDMXZoomComponent::BeginPlay()
{
	Super::BeginPlay();
	this->SetParentDMXRef();
	this->InitDMXFunctionNames(TArray<FName>({ "Zoom" }));

	SPRef_LensSpringArm = Cast<USpringArmComponent>(this->FindComponentsByName(USpringArmComponent::StaticClass(), TArray<FString>({ "spring" }))[0]);

	SpotRef_Light = Cast<USpotLightComponent>(this->FindComponentsByName(USpotLightComponent::StaticClass(), TArray<FString>({ "spot" }))[0]);

	SMRef_Beam = Cast<UStaticMeshComponent>(this->FindComponentsByName(UStaticMeshComponent::StaticClass(), TArray<FString>({ "beam" }))[0]);

	miBeam = SMRef_Beam->CreateDynamicMaterialInstance(0, SMRef_Beam->GetMaterial(0));
}

void ULexyVFXDMXZoomComponent::UpdateDMX(TMap<FDMXAttributeName, int32> DImapDMXFunctionValues, TArray<FName> nDMXComponentFunctions)
{
	this->UpdateDMXSpringArm(zoomBitDepth, SPRef_LensSpringArm, fBeamRangeLinear, DImapDMXFunctionValues, this->FunctionNames.nDMXComponentFunctions[0]);

	this->UpdateDMXMaterialScalarParameter(miBeam, zoomBitDepth, FName("DMX Zoom"), 1.3f, fBeamRangeMax, fBeamRangeMin, DImapDMXFunctionValues, this->FunctionNames.nDMXComponentFunctions[0]);

	this->UpdateDMXSpotConeAngle(zoomBitDepth, SpotRef_Light, fBeamRangeMax, fBeamRangeMin, DImapDMXFunctionValues, this->FunctionNames.nDMXComponentFunctions[0]);
}