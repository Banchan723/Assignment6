#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Step.generated.h"

UCLASS()
class PROJECT1_API AStep : public AActor
{
	GENERATED_BODY()

public:
	AStep();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UStaticMeshComponent* StaticMeshComp;

	bool bIsMoving = true; // 이동 중인지 확인하는 변수

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveSettings")
	float MoveSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveSettings")
	float MovementUpdateRate = 0.016f; // 이동 주기 (0.1초마다 이동)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveSettings")
	float MinMoveRange = 100.0f; // 최소 이동 거리

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveSettings")
	float MaxMoveRange = 500.0f; // 최대 이동 거리

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveSettings")
	FVector MoveDirection = FVector(1, 0, 0); // 블루프린트에서 이동 축을 설정할 수 있도록 변경

	FVector StartLocation;
	UPROPERTY()
	float MaxRange; // 현재 이동할 거리

	UPROPERTY()
	FTimerHandle MovementTimerHandle; // 이동 타이머

	UPROPERTY()
	FTimerHandle PauseTimerHandle; // 멈춤 타이머

	void MoveActor();
	void PauseMovement();
	void ResumeMovement();

	virtual void BeginPlay() override;
};
