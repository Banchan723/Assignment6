#include "Step.h"
#include "Math/UnrealMathUtility.h" // 랜덤 값 생성을 위한 FMath 함수 사용

// 생성자: 액터의 기본 컴포넌트를 설정
AStep::AStep()
{
	// 루트 컴포넌트 생성 및 설정
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	// 스태틱 메시 컴포넌트 생성 및 루트에 부착
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	// 메시 설정
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/Wall_400x400.Wall_400x400"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	// 머티리얼 설정
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Wood_Floor_Walnut_Polished.M_Wood_Floor_Walnut_Polished"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	// Tick 함수 비활성화 (타이머를 사용하여 이동)
	PrimaryActorTick.bCanEverTick = false;
}

// 게임이 시작되면 실행되는 함수
void AStep::BeginPlay()
{
	Super::BeginPlay();

	// 초기 위치 저장
	StartLocation = GetActorLocation();

	// 이동할 최대 거리 랜덤 설정
	MaxRange = FMath::RandRange(MinMoveRange, MaxMoveRange);

	// 50% 확률로 이동 방향 반전
	if (FMath::RandBool())
	{
		MoveDirection *= -1;
	}

	// 일정 간격마다 MoveActor() 실행 (이동 타이머 시작)
	GetWorld()->GetTimerManager().SetTimer(
		MovementTimerHandle,
		this,
		&AStep::MoveActor,
		MovementUpdateRate,
		true
	);

	// 5초마다 PauseMovement() 실행 (이동을 멈추는 타이머 시작)
	GetWorld()->GetTimerManager().SetTimer(
		PauseTimerHandle,
		this,
		&AStep::PauseMovement,
		5.0f,
		true
	);
}

// 액터를 이동시키는 함수 (타이머에 의해 반복 호출됨)
void AStep::MoveActor()
{
	// 이동 중이 아닐 경우 실행하지 않음
	if (!bIsMoving) return;

	// 현재 위치 가져오기
	FVector CurrentLocation = GetActorLocation();

	// 설정된 이동 방향과 속도를 기반으로 위치 업데이트
	CurrentLocation += MoveDirection * MoveSpeed * MovementUpdateRate;

	// 이동 범위를 초과하면 방향을 반전
	if (FVector::Dist(StartLocation, CurrentLocation) >= MaxRange)
	{
		MoveDirection *= -1;
	}

	// 새로운 위치 적용
	SetActorLocation(CurrentLocation);
}

// 5초마다 실행되는 함수: 액터를 일시적으로 멈춘다
void AStep::PauseMovement()
{
	// 이동 중지
	bIsMoving = false;

	// 이동 타이머 정지
	GetWorld()->GetTimerManager().ClearTimer(MovementTimerHandle);

	// 3초 후 ResumeMovement()실행 (다시 이동 시작)
	GetWorld()->GetTimerManager().SetTimer(
		MovementTimerHandle,
		this,
		&AStep::ResumeMovement,
		3.0f,
		false
	);
}

// 3초 후 실행되는 함수: 액터 이동을 다시 시작한다
void AStep::ResumeMovement()
{
	// 이동 활성화
	bIsMoving = true;

	// 이동 타이머 재시작
	GetWorld()->GetTimerManager().SetTimer(
		MovementTimerHandle,
		this,
		&AStep::MoveActor,
		MovementUpdateRate,
		true
	);
}
