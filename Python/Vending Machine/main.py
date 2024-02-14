from vending_machine import VendingMachine
from inventory_utils import generate_inventory

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