// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlot.h"

void UInventorySlot::RefreshSlot(FItem _item, bool _showQuantity)
{
	ItemIcon->SetBrushFromTexture(_item.Icon);
	if (_showQuantity)
	{
		ItemNameAndQuantity->SetText(FText::FromString(_item.Name.ToString() + " ( " + FString::FromInt(_item.Quantity) + " )"));
	}
	else
	{
		ItemNameAndQuantity->SetText(FText::FromString(_item.Name.ToString()));
	}
}
