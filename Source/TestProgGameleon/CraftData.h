// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemData.h"
#include "CraftData.generated.h"

USTRUCT(BlueprintType)
struct FIngredient
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 ItemDataRowIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 Quantity;
};

USTRUCT(BlueprintType)
struct FCraft
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UItemData* ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FIngredient> Ingredients;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 ItemDataResultIndex;
};

UCLASS()
class TESTPROGGAMELEON_API UCraftData : public UDataAsset
{
	GENERATED_BODY()

public : 

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FCraft> Recipes;
};
