# Data Classes
class Item:
    def __init__(self, price, name):
        self.price = price
        self.name = name

    def print_item(self):
        print(f"The item is {self.name} and its price is {self.price}")


class ItemShelf:
    def __init__(self, item, count_of_items, code):
        self.item = item
        self.count_of_items = count_of_items
        self.code = code

    def is_shelf_empty(self):
        return self.count_of_items == 0

    def get_item(self):
        return self.item

    def print_item_shelf(self):
        print(f" ==============  Items for shelf with code {self.code} are : ==========================")
        self.item.print_item()
        print(f"The count of such items in this shelf is {self.count_of_items}")

    def take_item_from_shelf(self):
        if self.count_of_items == 0:
            raise Exception("Shelf is empty can't take items from shelf")
        
        self.count_of_items -= 1
        return self.item