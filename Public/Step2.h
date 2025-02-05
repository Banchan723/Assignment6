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

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float RotationSpeed;
	// 회전 속도 변수

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};