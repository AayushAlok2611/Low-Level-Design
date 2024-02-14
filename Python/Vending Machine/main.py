from vending_machine import VendingMachine
from inventory_utils import generate_inventory
"""
Assumption -> Shelves contain items of only one kind

Used State Design Pattern to implement the Vending Machine

The states for the Vending Machine are

1) Idle State 
    Operations that can be performed 
    a) Ask user if they want to buy an item , if they dont want to buy then end the vending machine CLI app
    b) If they want to buy an item, then display the inventory and move to "Select Product" state

2) Select Product State
    Operations that can be performed
    a) Ask if user want to cancel the trannsaction , if yes then move to "Idle" state
    b) If no, then ask the user to provide the shelf code for the shelf from which to buy the item , if item not available then move to "Idle" state.
    If item is available then ssave the item being purchased (for later price calculations) and move to "Acquire Money" state

3) Acquire Money State
    Operations that can be performed
    a) Ask if user want to cancel the trannsaction , if yes then move to "Idle" state
    b) If no, then ask user to provide the money , if money < required money then inform the user and invalidate the saved item to be purchased and move to "Idle" state
    if money >= required money then return the change if any , and move to "Dispense Item" state

4) Dispense Item State
    Operations that can be performed
    a) Ask if user want to cancel the trannsaction , if yes then refund the entrie amount charged and move to "Idle" state
    b) If no, then take the item from the shelf and update the inventory, and also inform the user about the item purchased , and move to "Idle" state


"""

if __name__ == "__main__":
    inventory = generate_inventory()
    vm = VendingMachine(inventory)

    while 1:
        vending_machine_state = vm.get_state()
        vending_machine_state.print_state()

        should_stop_loop = False
        try:
            should_stop_loop = vending_machine_state.perform_operation(vm)
        except Exception as e:
            print(e)

        if should_stop_loop:
            break