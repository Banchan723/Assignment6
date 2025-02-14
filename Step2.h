#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Step2.generated.h"

UCLASS()
class PROJECT1_API AStep2 : public AActor
{
	GENERATED_BODY()

public:
	AStep2();

protected:
	// 루트 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = "Component")
	USceneComponent* SceneRoot;

	// 스태틱 메시 컴포넌트
	UPROPERTY(EditAnywhere, Category = "Component")
	UStaticMeshComponent* StaticMeshComp;

	// 회전 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float RotationSpeed;

	// 회전 속도의 최소값과 최대값 (랜덤 범위)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MinRotationSpeed = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxRotationSpeed = 300.0f;

	FVector StartLocation;

	// 일정 시간마다 회전을 멈추는 기능을 위한 타이머
	UPROPERTY()
	FTimerHandle RotationTimerHandle;

	UPROPERTY()
	FTimerHandle PauseTimerHandle;

	// 회전 여부
	bool bIsRotating = true;

	// 회전 관련 함수
	void StartRotation();
	void StopRotation();
	void RotateActor(); // 새롭게 추가한 회전 함수 (Tick 대체)

	virtual void BeginPlay() override;
};
