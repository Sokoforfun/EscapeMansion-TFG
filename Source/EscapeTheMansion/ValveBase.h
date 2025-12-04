#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ValveBase.generated.h"

class UStaticMeshComponent;

// Declaramos un "Delegado" (una notificación) para avisar al Manager cuando giremos
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

	// --- CAMBIO IMPORTANTE: Contadores ---

	// Cuántas veces la hemos girado (Empieza en 0)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Valve Logic")
	int32 CurrentTurns;

public:
	// Cuántas vueltas necesita PARA SER CORRECTA (Lo configuraremos en el editor)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Valve Logic")
	int32 TargetTurns;

	// El "grito" que avisa que la válvula se movió
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnValveRotated OnValveRotatedDelegate;

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Interact();

	// Función para que el Manager pregunte: "¿Estás correcta?"
	UFUNCTION(BlueprintCallable, Category = "Valve Logic")
	bool IsCorrect();

protected:
	// Le pasamos el nuevo ángulo al Blueprint
	UFUNCTION(BlueprintImplementableEvent, Category = "Interaction")
	void OnValveInteracted(float NewAngle);
};