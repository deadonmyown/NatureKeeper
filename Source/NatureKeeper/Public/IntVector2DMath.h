// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "IntVector2DMath.generated.h"

struct FIntVector2D;

/**
 * Blueprint Function Library for FIntVector2D math
 */
UCLASS()
class NATUREKEEPER_API UIntVector2DMath : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Add vector A to vector B */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "IntVector2D + IntVector2D", CompactNodeTitle = "+", /*ScriptMethod = "Add", ScriptOperator = "+;+=", */Keywords = "+ add plus", CommutativeAssociativeBinaryOperator = "true"), Category = "Math|IntVector2D")
	static FIntVector2D Add_IntVector2D(FIntVector2D A, FIntVector2D B);
	/** Add value to both vector components */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "IntVector2D + Integer", CompactNodeTitle = "+", /*ScriptMethod = "AddInt", ScriptOperator = "+;+=", */Keywords = "+ add plus"), Category = "Math|IntVector2D")
	static FIntVector2D Add_Int(FIntVector2D A, int32 B);
	/** Subtract vector B from Vector A */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "IntVector2D - IntVector2D", CompactNodeTitle = "-", /*ScriptMethod = "Subtract", ScriptOperator = "-;-=", */Keywords = "- subtract minus", CommutativeAssociativeBinaryOperator = "true"), Category = "Math|IntVector2D")
	static FIntVector2D Subtract_IntVector2D(FIntVector2D A, FIntVector2D B);
	/** Subtract value from both vector components */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "IntVector2D - Integer", CompactNodeTitle = "-", /*ScriptMethod = "SubtractInt", ScriptOperator = "-;-=", */Keywords = "- subtract minus"), Category = "Math|IntVector2D")
	static FIntVector2D Subtract_Int(FIntVector2D A, int32 B);
	/** Multiply two vectors element-wise */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "IntVector2D * IntVector2D", CompactNodeTitle = "*", /*ScriptMethod = "Multiply", ScriptOperator = "*;*=", */Keywords = "* multiply", CommutativeAssociativeBinaryOperator = "true"), Category = "Math|IntVector2D")
	static FIntVector2D Multiply_IntVector2D(FIntVector2D A, FIntVector2D B);
	/** Multiply both vector components by value */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "IntVector2D * Integer", CompactNodeTitle = "*", /*ScriptMethod = "MultiplyInt", ScriptOperator = "*;*=", */Keywords = "* multiply"), Category = "Math|IntVector2D")
	static FIntVector2D Multiply_Int(FIntVector2D A, int32 B);
	/** Divide two vectors element-wise */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "IntVector2D / IntVector2D", CompactNodeTitle = "/", /*ScriptMethod = "Divide", ScriptOperator = "/;/=", */Keywords = "/ divide"), Category = "Math|IntVector2D")
	static FIntVector2D Divide_IntVector2D(FIntVector2D A, FIntVector2D B);
	/** Divide both vector components by value */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "IntVector2D / IntVector2D", CompactNodeTitle = "/", /*ScriptMethod = "DivideInt", ScriptOperator = "/;/=", */Keywords = "/ divide"), Category = "Math|IntVector2D")
	static FIntVector2D Divide_Int(FIntVector2D A, int32 B);
	/** Are vectors equal (A.x == B.x && A.y == B.y) */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "IntVector2D == IntVector2D", CompactNodeTitle = "==", /*ScriptMethod = "Equal", ScriptOperator = "==", */Keywords = "== equal"), Category = "Math|IntVector2D")
	static bool Equal_IntVector2D(FIntVector2D A, FIntVector2D B);
	/** Are vectors not equal (A.x != B.x || A.y != B.y) */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "IntVector2D != IntVector2D", CompactNodeTitle = "!=", /*ScriptMethod = "NotEqual", ScriptOperator = "!=", */Keywords = "!= not equal"), Category = "Math|IntVector2D")
	static bool NotEqual_IntVector2D(FIntVector2D A, FIntVector2D B);

	/** Convert Vector2D to IntVector2D by truncating its values */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To IntVector2D", CompactNodeTitle = "->", BlueprintAutocast), Category="Math|IntVector2D")
	static FIntVector2D Conv_FromVector2D(FVector2D InVec);
	/** Convert IntVector2D to Fector2D */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Vector2D", CompactNodeTitle = "->", BlueprintAutocast), Category="Math|IntVector2D")
	static FVector2D Conv_ToVector2D(FIntVector2D InVec);
	/** Convert IntVector2D to Vector (Z = 0) */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To Vector", CompactNodeTitle = "->", BlueprintAutocast), Category="Math|IntVector2D")
	static FVector Conv_ToVector(FIntVector2D InVec);
	/** Convert IntVector2D to IntVector (Z = 0) */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To IntVector", CompactNodeTitle = "->", BlueprintAutocast), Category="Math|IntVector2D")
	static FIntVector Conv_ToIntVector(FIntVector2D InVec);

	/** Convert IntVector2D to String */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "To String (IntVector2D)", CompactNodeTitle = "->", BlueprintAutocast), Category="Utilities|String")
	static FString Conv_ToString(FIntVector2D InVec);

	/** Calculate length of IntVector2D. Result is float. */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Size (IntVector2D)"), Category="Math|IntVector2D")
	static float IntVector2D_Size(FIntVector2D InVec);
};
