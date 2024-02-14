from data_classes import Item,ItemShelf

def generate_inventory():
    inventory = []

    for i in range(2):
        item = Item(10, "Chips")
        count_of_items = 5
        code = i + 1
        shelf = ItemShelf(item, count_of_items, code)
        inventory.append(shelf)

    return inventory