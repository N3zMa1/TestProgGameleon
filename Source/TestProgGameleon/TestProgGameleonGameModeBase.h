#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CraftData.h"
#include "TestProgGameleonGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRefreshUI);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInventoryChanged);

UCLASS()
class TESTPROGGAMELEON_API ATestProgGameleonGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public : 

	virtual void BeginPlay() override;

#pragma region inventory
	void AddItem(TArray<FItem> &_toList, FItem _item, int32 _quantity);

	void RemoveItem(TArray<FItem> &_toList,FItem _item, int32 _quantity);
#pragma endregion

#pragma region Events
	UPROPERTY(BlueprintAssignable, Category = "UI")
		FRefreshUI RefreshUI;

	UPROPERTY(BlueprintAssignable, Category = "UI")
		FInventoryChanged InventoryChanged;
#pragma endregion

#pragma region buy and sell
	UFUNCTION(BlueprintCallable)
		void AddToCart(FItem _item);

	UFUNCTION(BlueprintCallable)
		void RemoveFromCart(FItem _item);

	UFUNCTION(BlueprintCallable)
		void AddToSell(FItem _item);

	UFUNCTION(BlueprintCallable)
		void RemoveFromSell(FItem _item);

	UFUNCTION(BlueprintCallable)
		bool PayAndAdd();

	UFUNCTION(BlueprintCallable)
		bool SellAndRemove();
#pragma endregion

#pragma region Craft
	UFUNCTION(BlueprintCallable)
	void SetSelectedCraft(int index);

	UFUNCTION(BlueprintCallable)
	bool CanItBeCrafted();

	bool CheckIfItemIsInInventory(FItem _item);

	UFUNCTION(BlueprintCallable)
		void CraftItem();
#pragma endregion

protected : 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		UItemData* ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Craft")
		UCraftData* CraftData;

#pragma region Inventory 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
		TArray<FItem> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
		int32 InventorySlotNumbers = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
		float Gold = 50.f;
#pragma endregion

#pragma region buy and sell
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop")
		TArray<FItem> Shop;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop")
		TArray<FItem> Cart;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shop")
		float TotalToPay = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sell")
		TArray<FItem> SellCart;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sell")
		float TotalToEarn = 0.f;
#pragma endregion

#pragma region Craft
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Craft")
		FCraft SelectedCraft;
#pragma endregion
};
