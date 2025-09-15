// Fill out your copyright notice in the Description page of Project Settings.


#include "IntVector2DMath.h"
#include "IntVector2D.h"

FIntVector2D UIntVector2DMath::Add_IntVector2D(FIntVector2D A, FIntVector2D B)
{
	return A + B;
}

FIntVector2D UIntVector2DMath::Add_Int(FIntVector2D A, int32 B)
{
	return A + B;
}

FIntVector2D UIntVector2DMath::Subtract_IntVector2D(FIntVector2D A, FIntVector2D B)
{
	return A - B;
}

FIntVector2D UIntVector2DMath::Subtract_Int(FIntVector2D A, int32 B)
{
	return A - B;
}

FIntVector2D UIntVector2DMath::Multiply_IntVector2D(FIntVector2D A, FIntVector2D B)
{
	return A * B;
}

FIntVector2D UIntVector2DMath::Multiply_Int(FIntVector2D A, int32 B)
{
	return A * B;
}

FIntVector2D UIntVector2DMath::Divide_IntVector2D(FIntVector2D A, FIntVector2D B)
{
	return A / B;
}

FIntVector2D UIntVector2DMath::Divide_Int(FIntVector2D A, int32 B)
{
	return A / B;
}

bool UIntVector2DMath::Equal_IntVector2D(FIntVector2D A, FIntVector2D B)
{
	return A == B;
}

bool UIntVector2DMath::NotEqual_IntVector2D(FIntVector2D A, FIntVector2D B)
{
	return A != B;
}

FIntVector2D UIntVector2DMath::Conv_FromVector2D(FVector2D InVec)
{
	return FIntVector2D(InVec);
}

FVector2D UIntVector2DMath::Conv_ToVector2D(FIntVector2D InVec)
{
	return InVec.ToVector2D();
}

FVector UIntVector2DMath::Conv_ToVector(FIntVector2D InVec)
{
	return InVec.ToVector();
}

FIntVector UIntVector2DMath::Conv_ToIntVector(FIntVector2D InVec)
{
	return InVec.ToIntVector();
}

FString UIntVector2DMath::Conv_ToString(FIntVector2D InVec)
{
	return InVec.ToString();
}

float UIntVector2DMath::IntVector2D_Size(FIntVector2D InVec)
{
	return InVec.Size();
}
