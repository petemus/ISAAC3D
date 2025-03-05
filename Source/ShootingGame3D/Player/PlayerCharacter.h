// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Public/DamagedInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Item/Item.h"
#include "PlayerCharacter.generated.h"

UENUM()
enum class EAttackMode : uint8
{
	NormalAttack UMETA(DisplayName = "Normal Attak"),
	GreatAttack UMETA(DisplayName = "Great Attak"),
	TripleAttack  UMETA(DisplayName = "Triple Attak")
};


// 델리게이트 선언
DECLARE_DYNAMIC_DELEGATE(FOnAttackEvent);

class UStaticMeshComponent;
class UArrowComponent;
class ABullet;

UCLASS()
class SHOOTINGGAME3D_API APlayerCharacter : public ACharacter, public IDamagedInterface
{
	GENERATED_BODY()



// ** UPROPERTY 변수 **
// ----------------------------------------------------------------------------
protected:
	// Components
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UArrowComponent* ArrowComp;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UArrowComponent* LeftArrow;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UArrowComponent* RightArrow;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UArrowComponent* CircleArrow;


	// Input
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* PlayerInputIMC;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* MoveIA;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* FireIA;

	// Sound
	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
	class USoundBase* BulletSound;
	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
	class USoundBase* BulletBigSound;


	// Bullet 생성을 위한 Factory
	// content browser에서의 값을 할당할려면 TSubclassOf
	// detail 창에서 할당할려면 그냥 클래스 
	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
	TSubclassOf<ABullet> BulletFactory;
	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
	TSubclassOf<ABullet> BigBulletFactory;


public:		// *Settings* 
	// 설정 가능한 변수들 
	UPROPERTY(EditAnywhere, Category = "Settings")
	float MoveSpeed = 500;
	UPROPERTY(EditAnywhere, Category = "Settings")
	int32 Health = 6;
	UPROPERTY(EditAnywhere, Category = "Settings")
	float SpawnTime = 0.5f;
	// Default : 0.5
	UPROPERTY(EditAnywhere, Category = "Settings")
	int32 AttackStat = 1;

private:
	// event 변수
	UPROPERTY()
	FOnAttackEvent OnAttackEvent;


// ** 기본 생성함수 **
// ----------------------------------------------------------------------------

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// ** UFUNCTION 함수 **
// ----------------------------------------------------------------------------
public:
	UFUNCTION(BlueprintCallable)
	virtual void SetDamaged(int32 Amount) override;
	
private:
	// 회전 공격 델리게이트 호출시 실행되는 함수 
	UFUNCTION()
	void AttackCircle();

	// 충돌 이벤트 함수 
	UFUNCTION()
	void OnCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						  int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);


// ** Function 일반 멤버 함수 **
// ----------------------------------------------------------------------------
public:
	// enum은 전방선언 불가
	void SetAttackMode(EItemType type);

private:
	// 입력 이벤츠 처리 함수
	void Move(const struct FInputActionValue& Value);
	// Fire 입력 이벤츠 처리 함수
	void Fire(const struct FInputActionValue& Value);
	
	// 공격 이벤트에서 timer로 계속 반복하는 rotate 함수
	void RotateCircle();

	// 적과 충돌시 Knock-Back 
	void KnockBack(AActor* OtherActor);
	


	

// ** 일반 멤버 변수 **
// ----------------------------------------------------------------------------
private:
	// spawn time 
	float NowTime = SpawnTime;
	// attack mode 
	EAttackMode MyAttackMode = EAttackMode::NormalAttack;
	float AttackTime = 5;
	// Circel Attack의 각도와 시간 변수
	float RotateAmout = 15;
	float RotateTime = 0.05f;
	// circle attack timerhandle
	FTimerHandle TimerHandle;


	// 현재 circle arrow의 앵글을 저장할 변수
	float CircleArrowAngle = 0.0f;


// ----------------------------------------------------------------------------
// 일단 안씀
// Bullet Pool을 위한 임시
public:
	//
    class ABulletPool* BulletPool;
	void FireBullet();
	








};
