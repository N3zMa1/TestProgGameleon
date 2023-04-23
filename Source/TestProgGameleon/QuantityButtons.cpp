// Fill out your copyright notice in the Description page of Project Settings.


#include "QuantityButtons.h"

void UQuantityButtons::NativeConstruct()
{
	MinusButton->OnClicked.AddDynamic(this, &UQuantityButtons::OnMinusClick);

	PlusButton->OnClicked.AddDynamic(this, &UQuantityButtons::OnPlusClick);
}

void UQuantityButtons::ResetQuantity()
{
	_quantity = 0;
	RefreshQuantityText();
}

void UQuantityButtons::SetMaxQuantity(int32 _maxQuantity)
{
	MaxQuantity = _maxQuantity;
}

void UQuantityButtons::OnMinusClick()
{
	if (_quantity > 0)
	{
		_quantity -= 1;
		MinusClicked.Broadcast(Item);
	}
	RefreshQuantityText();
}

void UQuantityButtons::OnPlusClick()
{
	if (_quantity < MaxQuantity)
	{
		_quantity += 1;
		PlusClicked.Broadcast(Item);
	}
	RefreshQuantityText();
}

void UQuantityButtons::RefreshQuantityText()
{
	QuantityText->SetText(FText::FromString(FString::FromInt(_quantity)));
}
