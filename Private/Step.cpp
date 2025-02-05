#include "Step.h"

AStep::AStep()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/Wall_400x400.Wall_400x400"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Wood_Floor_Walnut_Polished.M_Wood_Floor_Walnut_Polished"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	PrimaryActorTick.bCanEverTick = true;

	LocationSpeed = 180.0f; // 위치 이동 속도 설정

	MaxHeight = 400.0f; // 최고 높이 설정
	MinHeight = 100.0f; // 최저 높이 설정
}

void AStep::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector(500.0f, 100.0f, 100.0f));
	SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
	SetActorScale3D(FVector(1.0f));
}

void AStep::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();

	NewLocation.Z += LocationSpeed * DeltaTime;

	if (NewLocation.Z >= MaxHeight || NewLocation.Z <= MinHeight)
	{
		LocationSpeed *= -1;
	}

	SetActorLocation(NewLocation);
}