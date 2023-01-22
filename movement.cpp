#include "CharacterComponent.h"
#include "Character.h"

void movement::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (UpdatedComponent)
    {
        FVector Input = ConsumeInputVector();
        bool bSprint = IsSprinting();

        if (Input.SizeSquared() > 1.0f)
        {
            Input.Normalize();
        }

        float DesiredSpeed = bSprint ? SprintingSpeed : WalkingSpeed;
        Input *= DesiredSpeed;

        if (!bJumping && IsJumping())
        {
            bJumping = true;
            Velocity.Z = JumpZVelocity;
        }

        if (IsSitting())
        {
            Input = FVector::ZeroVector;
        }
      
        Velocity += Input * DeltaTime;
        FVector NewLocation = UpdatedComponent->GetComponentLocation() + Velocity * DeltaTime;
        UpdatedComponent->SetWorldLocation(NewLocation);
    }
}
