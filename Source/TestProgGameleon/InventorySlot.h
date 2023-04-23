// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ItemData.h"
#include "InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROGGAMELEON_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()

protected :

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UImage* ItemIcon;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBlock* ItemNameAndQuantity;

public: 

	UFUNCTION(BlueprintCallable)
	void RefreshSlot(FItem _item, bool _showQuantity);
};
