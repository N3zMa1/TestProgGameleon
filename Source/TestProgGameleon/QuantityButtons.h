// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "ItemData.h"
#include "QuantityButtons.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlusClicked,FItem, Item);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMinusClicked, FItem, Item);

UCLASS()
class TESTPROGGAMELEON_API UQuantityButtons : public UUserWidget
{
	GENERATED_BODY()
	
public :
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintAssignable, Category = "Refresh Cart")
		FOnPlusClicked PlusClicked;

	UPROPERTY(BlueprintAssignable, Category = "Refresh Cart")
		FOnMinusClicked MinusClicked;

	UFUNCTION(BlueprintCallable)
		void ResetQuantity();

	UFUNCTION(BlueprintCallable)
		void SetMaxQuantity(int32 _maxQuantity);

protected:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* MinusButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* PlusButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBlock* QuantityText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FItem Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MaxQuantity = 99;

	UFUNCTION()
	void OnMinusClick();

	UFUNCTION()
	void OnPlusClick();

	UFUNCTION()
	void RefreshQuantityText();

private : 

	int32 _quantity = 0;
};
