// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPCPawnServer.h"
#include "GEOCameraComponent.h"
#include "WorldManager.h"
#include <queue> 
#include "VehiclePawn.generated.h"

class UCameraComponent;

UCLASS(Abstract)
class GEOSIMULATOR_API AVehiclePawn : public ARPCPawnServer
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVehiclePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PostActorCreated() override;

private:
	int indexCamera = 1;
	bool isDepth = false;

	FVector NewLocation;
	FVector NewLookAt;

	//Save image variables
	UGameViewportClient* game_viewport_;
	TPromise<int>* promise;
	FDelegateHandle end_draw_handle_;
	FDelegateHandle end_draw_handle2_;
public:	
	// Override API UE4
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BindFunctions(rpc::server* server) override;

	UGEOCameraComponent* CreateCamera(FVector position, FRotator rotation, USceneComponent* root);
	
	//Events
	void ChangeCamera();
	void ChangeTexture();
	void HiddenVehicle();
	void ToggleDepth();

	//Depth
	void ActivateDepth();
	void DeactivateDepth();

	//Save Images
	void SaveImage();
	void SaveImage(int cameraId, const TCHAR* pathname);
	FTextureRenderTargetResource* GetImageResource(int camera);
	void GetImageBmp(FTextureRenderTargetResource* resource, TArray<FColor>& output);

	//Functions RPC
	void SetLocation(double x, double y, double z);
	void SetRotationByLookAt(double x, double y, double z);
	void SetCameraLookAt(int cameraId, double x, double y, double z);

	UPROPERTY(EditAnywhere)
	TArray<UGEOCameraComponent*> cameras;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* staticMeshComponent;

	UStaticMesh* staticMesh;
    
    AWorldManager* worldManager;
};
