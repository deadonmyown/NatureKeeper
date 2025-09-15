// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "IntVector2D.generated.h"

/**
 *	Custom implementation of 2d integer vector. Cause for some reason default Epic's 2d vector has no math methods.
 */

USTRUCT(BlueprintType)
struct FIntVector2D
{
	GENERATED_BODY()

	FIntVector2D()
		:X(0), Y(0)
	{}

	FIntVector2D(int InInt)
		:X(InInt), Y(InInt)
	{}

	FIntVector2D(int InX, int InY)
		:X(InX), Y(InY)
	{}

	/** Truncate values of float vector */
	FIntVector2D(FVector2D InVec2)
		:X(FMath::TruncToInt(InVec2.X)), Y(FMath::TruncToInt(InVec2.Y))
	{}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	int X;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	int Y;

	bool operator==(const FIntVector2D& Other) const
	{
		return X == Other.X && Y == Other.Y;
	}

	bool operator!=(const FIntVector2D& Other) const
	{
		return !(*this == Other);
	}

	FIntVector2D& operator=(const FIntVector2D& Other)
	{
		X = Other.X;
		Y = Other.Y;

		return *this;
	}

	FIntVector2D& operator+=(const FIntVector2D& Other)
	{
		X += Other.X;
		Y += Other.Y;

		return *this;
	}
	FIntVector2D& operator+=(const int Offset)
	{
		X += Offset;
		Y += Offset;

		return *this;
	}
	FIntVector2D& operator-=(const FIntVector2D& Other)
	{
		X -= Other.X;
		Y -= Other.Y;

		return *this;
	}
	FIntVector2D& operator-=(const int Offset)
	{
		X -= Offset;
		Y -= Offset;

		return *this;
	}
	FIntVector2D& operator*=(const FIntVector2D& Other)
	{
		X *= Other.X;
		Y *= Other.Y;

		return *this;
	}
	FIntVector2D& operator*=(const int Scale)
	{
		X *= Scale;
		Y *= Scale;

		return *this;
	}
	FIntVector2D& operator/=(const FIntVector2D& Other)
	{
		X /= Other.X;
		Y /= Other.Y;

		return *this;
	}
	FIntVector2D& operator/=(const int Divisor)
	{
		X /= Divisor;
		Y /= Divisor;

		return *this;
	}

	FIntVector2D operator+(const FIntVector2D& Other)
	{
		return FIntVector2D(*this) += Other;
	}
	FIntVector2D operator+(const int Offset)
	{
		return FIntVector2D(*this) += Offset;
	}
	FIntVector2D operator-(const FIntVector2D& Other)
	{
		return FIntVector2D(*this) -= Other;
	}
	FIntVector2D operator-(const int Offset)
	{
		return FIntVector2D(*this) -= Offset;
	}
	FIntVector2D operator*(const FIntVector2D& Other)
	{
		return FIntVector2D(*this) *= Other;
	}
	FIntVector2D operator*(const int Scale)
	{
		return FIntVector2D(*this) *= Scale;
	}
	FIntVector2D operator/(const FIntVector2D& Other)
	{
		return FIntVector2D(*this) /= Other;
	}
	FIntVector2D operator/(const int Divisor)
	{
		return FIntVector2D(*this) /= Divisor;
	}

	FIntVector2D operator>>(const int Shift)
	{
		return FIntVector2D(X >> Shift, Y >> Shift);
	}
	FIntVector2D operator<<(const int Shift)
	{
		return FIntVector2D(X << Shift, Y << Shift);
	}
	
	FIntVector2D operator&(const int Value)
	{
		return FIntVector2D(X & Value, Y & Value);
	}
	FIntVector2D operator|(const int Value)
	{
		return FIntVector2D(X | Value, Y | Value);
	}
	FIntVector2D operator^(const int Value)
	{
		return FIntVector2D(X ^ Value, Y ^ Value);
	}
	
	FVector2D ToVector2D() const
	{
		return FVector2D(X, Y);
	}
	FVector ToVector() const
	{
		return FVector(X, Y, 0.f);
	}
	FIntVector ToIntVector() const
	{
		return FIntVector(X, Y, 0);
	}

	FString ToString() const
	{
		return FString::Printf(TEXT("X=%i Y=%i"), X, Y);
	}

	float Size() const
	{
		return FMath::Sqrt(float(X*X + Y*Y));
	}
};

FORCEINLINE uint32 GetTypeHash(const FIntVector2D& Vector2D)
{
	return FCrc::MemCrc32(&Vector2D, sizeof(Vector2D));
}

FORCEINLINE FArchive& operator<<(FArchive& Arch, FIntVector2D& Struct)
{
	Arch << Struct.X;
	Arch << Struct.Y;

	return Arch;
}