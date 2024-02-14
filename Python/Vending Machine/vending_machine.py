from data_classes import Item,ItemShelf
from constants import VendingMachineStateEnum
from vending_machine_state import IdleState,SelectProductState,AcquireMoneyState,DispenseItemState

# ======= Vending Machine class ============
class VendingMachine:
    def __init__(self, inv):
        self.inventory = {shelf.code: shelf for shelf in inv}
        self.state = IdleState()
        self.item_shelf_of_purchase = None
        self.money_collected = 0

    def display_inventory(self):
        print(" ==============Start of Inventory ==========")
        for shelf_code, shelf in self.inventory.items():
            shelf.print_item_shelf()
        print("================End of Inventory=============")

    def set_state(self, new_state):
        if new_state == VendingMachineStateEnum.IDLE:
            self.state = IdleState()
        elif new_state == VendingMachineStateEnum.SELECT_PRODUCT:
            self.state = SelectProductState()
        elif new_state == VendingMachineStateEnum.ACQUIRE_MONEY:
            self.state = AcquireMoneyState()
        elif new_state == VendingMachineStateEnum.DISPENSE_ITEM:
            self.state = DispenseItemState()
        else: # Default state
            self.state = IdleState()


    def get_state(self):
        return self.state
    
    def get_shelf(self,shelf_code):
        if shelf_code not in self.inventory:
            raise Exception(f"Shelf with shelf code {shelf_code} is not part of inventory")
        
        return self.inventory[shelf_code]

    def is_item_available(self, shelf_code):
        shelf: ItemShelf = self.get_shelf(shelf_code)
        return not shelf.is_shelf_empty()

    def set_item_being_purchased(self, shelf_code):
        shelf: ItemShelf = self.get_shelf(shelf_code)
        self.item_shelf_of_purchase = shelf

    def get_price_of_item_being_purchased(self):
        if not self.item_shelf_of_purchase:
            raise Exception("No item being purchased, so no price to display")
        
        return self.item_shelf_of_purchase.get_item().price

    def return_change(self, change_amount):
        print(f"{change_amount} is the amount of change returned")
    
    def return_amount(self,amount):
        print(f"{amount} is the amount being returned")

    def take_item_to_be_purchased_from_shelf(self):
        if not self.item_shelf_of_purchase:
            raise Exception("No item being purchased")
        
        item: Item = self.item_shelf_of_purchase.take_item_from_shelf()
        print("Purchased the item: ", end="")
        item.print_item()
        self.money_collected += item.price
    
    def set_inventory(self,inv):
        self.inventory = {shelf.code: shelf for shelf in inv}



    