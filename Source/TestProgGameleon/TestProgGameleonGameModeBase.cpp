// Copyright Epic Games, Inc. All Rights Reserved.


#include "TestProgGameleonGameModeBase.h"

void ATestProgGameleonGameModeBase::AddItem(TArray<FItem> &_toList, FItem _item, int32 _quantity)
{
	for (int i = 0; i < _toList.Num(); i++)
	{
		if (_toList[i].Id == _item.Id)
		{
			_toList[i].Quantity += _quantity;
			return;
		}
	}
	_toList.Push(_item);
	AddItem(_toList,_item, _quantity);
}

void ATestProgGameleonGameModeBase::RemoveItem(TArray<FItem> &_toList,FItem _item, int32 _quantity)
{
	for (int i = 0; i < _toList.Num(); i++)
	{
		if (_toList[i].Id == _item.Id)
		{
			_toList[i].Quantity -= _quantity;

			if (_toList[i].Quantity <= 0)
			{
				_toList.RemoveAt(i);
			}
		}
	}
	return;
}

void ATestProgGameleonGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	Shop = { ItemData->Data[0],ItemData->Data[1],ItemData->Data[2],ItemData->Data[6] };

	SelectedCraft = CraftData->Recipes[0];

	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}

void ATestProgGameleonGameModeBase::AddToCart(FItem _item)
{
	AddItem(Cart, _item, 1);

	TotalToPay += _item.Value;

	RefreshUI.Broadcast();
}

void ATestProgGameleonGameModeBase::RemoveFromCart(FItem _item)
{
	RemoveItem(Cart, _item, 1);

	TotalToPay -= _item.Value;

	RefreshUI.Broadcast();
}

void ATestProgGameleonGameModeBase::AddToSell(FItem _item)
{
	_item.Quantity = 0;
	AddItem(SellCart, _item, 1);

	TotalToEarn += _item.Value;

	RefreshUI.Broadcast();
}

void ATestProgGameleonGameModeBase::RemoveFromSell(FItem _item)
{
	RemoveItem(SellCart, _item, 1);

	TotalToEarn -= _item.Value;

	RefreshUI.Broadcast();
}

bool ATestProgGameleonGameModeBase::PayAndAdd()
{
	if (Cart.Num() > 0)
	{
		if (Gold >= TotalToPay)
		{
			Gold -= TotalToPay;

			for (int i = 0; i < Cart.Num(); i++)
			{
				int32 tmpQuantity = Cart[i].Quantity;
				Cart[i].Quantity = 0;
				AddItem(Inventory, Cart[i], tmpQuantity);
			}

			Cart.Empty();
			TotalToPay = 0;

			InventoryChanged.Broadcast();

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool ATestProgGameleonGameModeBase::SellAndRemove()
{
	if (SellCart.Num() > 0)
	{
		Gold += TotalToEarn;
		for (int i = 0; i < SellCart.Num(); i++)
		{
			int32 tmpQuantity = SellCart[i].Quantity;
			SellCart[i].Quantity = 0;
			RemoveItem(Inventory, SellCart[i], tmpQuantity);
		}

		SellCart.Empty();

		TotalToEarn = 0;

		InventoryChanged.Broadcast();

		return true;
	}
	else
	{
		return false;
	}
}

void ATestProgGameleonGameModeBase::SetSelectedCraft(int index)
{
	SelectedCraft = CraftData->Recipes[index];
}

bool ATestProgGameleonGameModeBase::CanItBeCrafted()
{
	for (int i = 0; i < SelectedCraft.Ingredients.Num(); i++)
	{
		int32 index = SelectedCraft.Ingredients[i].ItemDataRowIndex;
		int32 quantity = SelectedCraft.Ingredients[i].Quantity;

		FItem item = ItemData->Data[index];
		item.Quantity = quantity;

		bool check = CheckIfItemIsInInventory(item);

		if (check)
		{
			continue;
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool ATestProgGameleonGameModeBase::CheckIfItemIsInInventory(FItem _item)
{
	for (int i = 0; i < Inventory.Num(); i++)
	{
		if (Inventory[i].Id == _item.Id && Inventory[i].Quantity >= _item.Quantity)
		{
			return true;
		}
	}
	return false;
}

void ATestProgGameleonGameModeBase::CraftItem()
{
	for (int i = 0; i < SelectedCraft.Ingredients.Num(); i++)
	{
		int32 index = SelectedCraft.Ingredients[i].ItemDataRowIndex;
		int32 quantity = SelectedCraft.Ingredients[i].Quantity;

		FItem item = ItemData->Data[index];
		item.Quantity = quantity;

		RemoveItem(Inventory,item,quantity);
	}
	int32 index = SelectedCraft.ItemDataResultIndex;
	FItem newItem = ItemData->Data[index];
	AddItem(Inventory, newItem, 1);

	RefreshUI.Broadcast();
	InventoryChanged.Broadcast();
}



