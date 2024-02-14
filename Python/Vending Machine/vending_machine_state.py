from constants import VendingMachineStateEnum

# VendingMachineState Class Hierarchy
class VendingMachineState:
    def print_state(self):
        raise NotImplementedError

    def perform_operation(self, vm):
        raise NotImplementedError


class IdleState(VendingMachineState):
    def print_state(self):
        print("Vending Machine in Idle state")

    def perform_operation(self, vm):
        ans = input("Do you wish to buy an item [Y/N]: ").upper()

        while ans not in ['Y', 'N']:
            print("Answer should be Y or N")
            ans = input("Do you wish to buy an item [Y/N]: ").upper()

        if ans == 'N':
            return True  # End the vending machine app

        vm.display_inventory()
        vm.set_state(VendingMachineStateEnum.SELECT_PRODUCT)
        return False


class SelectProductState(VendingMachineState):
    def print_state(self):
        print("Vending Machine in Select Product State")

    def perform_operation(self, vm):
        ans = input("Do you wish to cancel transaction? [Y/N]: ").upper()

        while ans not in ['Y', 'N']:
            print("Answer should be Y or N")
            ans = input("Do you wish to cancel transaction? [Y/N]: ").upper()

        if ans == 'Y':
            vm.set_state(VendingMachineStateEnum.IDLE)
            return False

        shelf_code = int(input("Enter shelf code of product to be bought: "))

        if not vm.is_item_available(shelf_code):
            print("Item not available")
            vm.set_state(VendingMachineStateEnum.IDLE)
            return False

        vm.set_item_being_purchased(shelf_code)
        vm.set_state(VendingMachineStateEnum.ACQUIRE_MONEY)
        return False


class AcquireMoneyState(VendingMachineState):
    def print_state(self):
        print("Vending machine is in Acquiring Money state")

    def perform_operation(self, vm):
        ans = input("Do you wish to cancel transaction? [Y/N]: ").upper()

        while ans not in ['Y', 'N']:
            print("Answer should be Y or N")
            ans = input("Do you wish to cancel transaction? [Y/N]: ").upper()

        if ans == 'Y':
            vm.set_state(VendingMachineStateEnum.IDLE)
            return False

        money = int(input("Enter money: "))
        price_of_item_being_purchased = vm.get_price_of_item_being_purchased()

        if money < price_of_item_being_purchased:
            print("Insufficient Money")
            vm.set_state(VendingMachineStateEnum.IDLE)
            return False

        change_to_return = money - price_of_item_being_purchased

        if change_to_return > 0:
            vm.return_change(change_to_return)

        vm.set_state(VendingMachineStateEnum.DISPENSE_ITEM)
        return False


class DispenseItemState(VendingMachineState):
    def print_state(self):
        print("Vending Machine is in Dispense Item state")

    def perform_operation(self, vm):
        ans = input("Do you wish to cancel transaction? [Y/N]: ").upper()

        while ans not in ['Y', 'N']:
            print("Answer should be Y or N")
            ans = input("Do you wish to cancel transaction? [Y/N]: ").upper()

        if ans == 'Y':
            price_of_item_being_purchased = vm.get_price_of_item_being_purchased()
            vm.return_amount(price_of_item_being_purchased)
            vm.set_state(VendingMachineStateEnum.IDLE)
            return False

        vm.take_item_to_be_purchased_from_shelf()
        vm.set_state(VendingMachineStateEnum.IDLE)
