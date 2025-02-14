#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class PROJECT1_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();

protected:

	USceneComponent* SceneRoot;
	UStaticMeshComponent* StaticMeshComp;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	float LocationSpeed;
	float MaxHeight;
	float MinHeight;

};


