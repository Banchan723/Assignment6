#include "Step2.h"
#include "Math/UnrealMathUtility.h" // 랜덤 함수 사용을 위한 헤더

// 생성자: 기본 설정 초기화
AStep2::AStep2()
{
	// 루트 컴포넌트 설정
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	// 메시 설정
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/Wall_400x400.Wall_400x400"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Wood_Oak.M_Wood_Oak"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	// Tick을 사용하지 않고 타이머로 제어할 것이므로 기본적으로 비활성화
	PrimaryActorTick.bCanEverTick = false;
}

// 게임 시작 시 실행되는 함수
void AStep2::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	// 랜덤한 회전 속도 설정
	RotationSpeed = FMath::RandRange(MinRotationSpeed, MaxRotationSpeed);

	// 회전 시작
	StartRotation();

	// 일정 시간마다 회전을 멈추는 타이머 설정 (5초마다 StopRotation 실행)
	GetWorld()->GetTimerManager().SetTimer(
		PauseTimerHandle,
		this,
		&AStep2::StopRotation,
		5.0f,
		true
	);
}

// 일정 간격마다 호출되는 함수: 회전 중지
void AStep2::StopRotation()
{
	// 회전 중지
	bIsRotating = false;
	GetWorld()->GetTimerManager().ClearTimer(RotationTimerHandle); // 회전 타이머 제거

	// 3초 후 다시 회전 시작
	GetWorld()->GetTimerManager().SetTimer(
		RotationTimerHandle,
		this,
		&AStep2::StartRotation,
		3.0f,
		false
	);
}

// 일정 시간이 지난 후 호출되는 함수: 회전 시작
void AStep2::StartRotation()
{
	// 랜덤 회전 속도 적용 (다시 새로운 랜덤 속도 설정)
	RotationSpeed = FMath::RandRange(MinRotationSpeed, MaxRotationSpeed);

	// 회전 활성화
	bIsRotating = true;

	// 60FPS마다 RotateActor() 호출하여 회전 업데이트
	GetWorld()->GetTimerManager().SetTimer(
		RotationTimerHandle,
		this,
		&AStep2::RotateActor,
		0.016f,
		true
	);
}

// 일정 간격마다 실행되어 회전을 적용하는 함수
void AStep2::RotateActor()
{
	if (bIsRotating)
	{
		// 현재 회전값에 RotationSpeed를 적용하여 회전 업데이트
		AddActorLocalRotation(FRotator(0.0f, RotationSpeed * 0.016f, 0.0f));
	}
}
