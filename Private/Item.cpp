#include "Item.h"

AItem::AItem()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));

	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/Wall_400x200.Wall_400x200"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Brick_Clay_New.M_Brick_Clay_New"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	PrimaryActorTick.bCanEverTick = true; // Item액터 Tick함수 활성화

	LocationSpeed = 100.0f; // 이동 속도는 100
	MaxHeight = 500.0f; // 최고 높이는 500
	MinHeight = 0.0f; // 최소 높이는 0
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector(300.0f, 200.0f, 100.0f));
	SetActorRotation(FRotator(0.0f, 45.0f, 0.0f));
	SetActorScale3D(FVector(2.0f, 2.0f, 2.0f));

}

// Tick() 구현부
void AItem::Tick(float DeltaTime)
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





