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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float LocationSpeed;
	// 위치 이동 속도 변수

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxHeight;
	//최고 높이 변수

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MinHeight;
	//최소 높이 변수
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};