#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ValveBase.generated.h"

class UStaticMeshComponent;

// Avisamos al manager al girar
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnValveRotated);

UCLASS()
class ESCAPETHEMANSION_API AValveBase : public AActor
{
	GENERATED_BODY()

public:
	AValveBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* ValveMesh;

	

	// Número de veces girado
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Valve Logic")
	int32 CurrentTurns;

public:
	//En el editor configuramos cuantas vueltas son correctas
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Valve Logic")
	int32 TargetTurns;

	//Avisamos de que la válvula se ha movido
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnValveRotated OnValveRotatedDelegate;

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Interact();

	//Comprobamos si está correcta
	UFUNCTION(BlueprintCallable, Category = "Valve Logic")
	bool IsCorrect();

protected:
	//Le damos al Blueprint el nuevo ángulo
	UFUNCTION(BlueprintImplementableEvent, Category = "Interaction")
	void OnValveInteracted(float NewAngle);
};