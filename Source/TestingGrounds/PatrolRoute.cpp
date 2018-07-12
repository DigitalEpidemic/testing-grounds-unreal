// Copyright 2018 Jeffrey Polasz. All Rights Reserved.

#include "PatrolRoute.h"

TArray<AActor*> UPatrolRoute::GetPatrolPoints() const
{
	return PatrolPoints;
}