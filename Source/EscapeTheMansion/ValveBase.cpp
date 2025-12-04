#include "ValveBase.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"

AValveBase::AValveBase()
{
	PrimaryActorTick.bCanEverTick = false;

	ValveMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ValveMesh"));
	RootComponent = ValveMesh;

	ValveMesh->SetMobility(EComponentMobility::Movable);
	ValveMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ValveMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	ValveMesh->SetGenerateOverlapEvents(true);

	// Inicializamos
	CurrentTurns = 0;
	TargetTurns = 0; // Valor por defecto para la válvula
}

void AValveBase::BeginPlay()
{
	Super::BeginPlay();
}

void AValveBase::Interact()
{
	// 1. Sumamos una vuelta
	CurrentTurns++;


	// Si llegamos al valor 4, es decir, 360 grados, empezamos de nuevo para arreglar el problema de que pasaba a 5.
	if (CurrentTurns >= 4)
	{
		CurrentTurns = 0;
	}

	// Calculamos el valor visual que tendremos, por ejemplo, si CurrentTurns es 0 entonces el ángulo de la válvula es de 0 grados
	float NewAngle = CurrentTurns * 90.0f;

	// Aquí estamos avisando al Blueprint para que haga la animación
	OnValveInteracted(NewAngle);

	// Debemos avisar del cambio al event manager
	OnValveRotatedDelegate.Broadcast();

	/* DEBUG PARA SABER QUE TODO ESTÁ FUNCIONANDO BIEN
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan,
			FString::Printf(TEXT("Posicion: %d | Objetivo: %d"), CurrentTurns, TargetTurns));
	}
	*/
}

// Aquí comprobamos si en esta válvula está todo correcto.
	bool AValveBase::IsCorrect()
{

	return CurrentTurns == TargetTurns;
}