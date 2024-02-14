#include <iostream>
#include <vector>
#include <map>
using namespace std;
/*
Assumptions ->
1) All shelves will have the same type of items
*/
// ============Enums ====

enum VendingMachineStateEnum {IDLE, SELECT_PRODUCT, ACQUIRE_MONEY, DISPENSE_ITEM};

// =============================== Data Classes ====================

class Item{
    private:
    int price;
    string name;

    public:
    Item(){}
    Item(int price,string name):price(price),name(name){}

    void printItem(){ cout<<"The item is "<<name<<" and its price is "<<price<<endl;}

    int getPrice(){return price;}
};

class ItemShelf{
    private:
    Item item;
    int countOfItems;
    int code;

    public:
    ItemShelf(Item item,int countOfItems,int code):item(item),countOfItems(countOfItems),code(code){}

    ItemShelf(){}

    bool isShelfEmpty(){ return countOfItems==0 ;}

    Item getItem(){ 
        return item;
    }
    int getCode(){ return code;}
    void printItemShelf()
    {   
        cout<<" ==============  Items for shelf with code "<<code<<" are :"<<endl;
        item.printItem();
        cout<<"The count of such items in this shelf is "<<countOfItems<<endl;
        cout<<"========"<<endl;
    }
    Item takeItemFromShelf()
    {
        if(countOfItems == 0){
            // throw exception("Shelf is empty can't take items from shelf");
        }
        countOfItems--;
        return item;
    }
};

// Declaring thigs needed later 
class VendingMachineState;
class VendingMachine;

// ====================== VendingMachineStateClass =================

// State Interface
class VendingMachineState{
    public:

    virtual void printState() = 0;
    virtual bool performOperation(VendingMachine* vm) = 0; // return whether to end the vending machine app or not
};

class IdleState: public VendingMachineState{
    public:
    IdleState(){}
    void printState() override {
        cout<<"Vending Machine in Idle state"<<endl;
    }
    bool performOperation(VendingMachine* vm) override {   
        char ans;
        cout<<"Do you wish to buy an item[Y/N]"<<endl;
        cin>>ans;

        while(ans!='Y' && ans!='N')
        {
            cout<<"Answer should be Y or N"<<endl;
            cin>>ans;
        }

        if(ans == 'N') return true; // end the vending machine app

        vm->displayInventory();

        vm->setState(SELECT_PRODUCT);

        return false;
    }
};

class SelectProductState: public VendingMachineState{
    public:
    void printState() override {
        cout<<"Vending Machine in Select Product State"<<endl;
    }

    bool performOperation(VendingMachine* vm) override {   
        char ans;
        cout<<"Do you wish to cancel transaction?[Y/N]"<<endl;
        cin>>ans;

        while(ans!='Y' && ans!='N')
        {
            cout<<"Answer should be Y or N"<<endl;
            cin>>ans;
        }
        if(ans == 'Y'){
            vm->setState(IDLE);
            return false;
        }
        int shelfCode;
        cout<<"Enter shelf code of product to be bought"<<endl;
        cin>>shelfCode;

        bool isItemAvailable = vm->isItemAvailable(shelfCode);
        if(!isItemAvailable){
            cout<<"Item not available"<<endl; 
            vm->setState(IDLE);
            return false;
        }
        vm->setItemBeingPurchased(shelfCode);

        vm->setState(ACQUIRE_MONEY);

        return false;
    }
};

class AcquireMoneyState: public VendingMachineState{
    public:

    void printState() override {
        cout<<"Vending machine is in Acquiring Money state"<<endl;
    }

    bool performOperation(VendingMachine* vm) override {
        char ans;
        cout<<"Do you wish to cancel transaction?[Y/N]"<<endl;
        cin>>ans;

        while(ans!='Y' && ans!='N')
        {
            cout<<"Answer should be Y or N"<<endl;
            cin>>ans;
        }
        if(ans == 'Y'){
            vm->setState(IDLE);
            return false;
        }
        int money;
        cout<<"Enter money"<<endl;
        cin>>money;
        int priceOfItemBeingPurchased = vm->getPriceOfItemBeingPurchased();

        if(money < priceOfItemBeingPurchased)
        {
            cout<<"Insufficent Money"<<endl;
            vm->setState(IDLE);
            return false;
        }
        int changeToReturn = money - priceOfItemBeingPurchased;

        if(changeToReturn > 0)
        {
            vm->returnAmount(changeToReturn);
        }
        vm->setState(DISPENSE_ITEM);
        return false;
    }
};

class DispenseItemState: public VendingMachineState{
    public:
    void printState() override {
        cout<<"Vending Machine is in Dispense Item state"<<endl;
    }
    bool performOperation(VendingMachine* vm) override {
        char ans;
        cout<<"Do you wish to cancel transaction?[Y/N]"<<endl;
        cin>>ans;

        while(ans!='Y' && ans!='N')
        {
            cout<<"Answer should be Y or N"<<endl;
            cin>>ans;
        }
        if(ans == 'Y'){

            int priceOfItemBeingPurchased = vm->getPriceOfItemBeingPurchased();
            vm->returnAmount(priceOfItemBeingPurchased); 

            vm->setState(IDLE);
            return false;
        }
        vm->takeItemToBePurchasedFromShelf();

        vm->setState(IDLE);
    }
};


// ======================= Vending Machine class ==============
class VendingMachine{
    map<int,ItemShelf> inventory;
    VendingMachineState* ptrToState;
    ItemShelf itemShelfOfPurchase;
    int moneyCollected;

    ItemShelf getItemShelf(int shelfCode)
    {
        if(inventory.find(shelfCode) == inventory.end())
        {
            // throw exception("Unknown Shelf code"); //TODO : Need to catch these exceptions
        }
        return inventory[shelfCode];
    }

    public:
    
    VendingMachine(vector<ItemShelf>& inv)
    {
        for(int i=0;i<inv.size();i++)
        {
            ItemShelf shelf = inv[i];
        }
        ptrToState = nullptr;
        moneyCollected = 0;
    }

    void displayInventory(){
        cout<<" ==============Start of Inventory =========="<<endl;
        for(auto it:inventory)
        {
            ItemShelf shelf = it.second;
            shelf.printItemShelf();
        }
        cout<<"================End of Inventory============="<<endl;
    }
    void setState(VendingMachineStateEnum newState)
    {   
        // Need to do memory management, deleting the old VendingMachineState* and freeing up its space
        // if( this->ptrToState ) delete this->ptrToState;

        // create object in heap to retain it even after it goes out of scope;
        VendingMachineState* ptrToNewState = NULL;
        if(newState == IDLE) ptrToNewState = new IdleState();
        else if(newState == SELECT_PRODUCT) ptrToNewState = new SelectProductState();
        else if(newState == ACQUIRE_MONEY) ptrToNewState = new AcquireMoneyState();
        else if(newState == DISPENSE_ITEM) ptrToNewState = new DispenseItemState();

        this->ptrToState = ptrToNewState;
    }
    VendingMachineState* getPtrToState(){return ptrToState;}

    bool isItemAvailable(int shelfCode)
    {
        ItemShelf shelf = getItemShelf(shelfCode);
        return !shelf.isShelfEmpty();
    }

    void setItemBeingPurchased (int shelfCode)
    {
        ItemShelf shelf = getItemShelf(shelfCode);
        itemShelfOfPurchase = shelf;
    }
    int getPriceOfItemBeingPurchased(){
        return itemShelfOfPurchase.getItem().getPrice();
    }
    void returnAmount(int amount)
    {
        cout<<amount<<" is the amount returned"<<endl;
    }
    void takeItemToBePurchasedFromShelf()
    {
        Item item = itemShelfOfPurchase.takeItemFromShelf();
        cout<<"Purchased the item: ";
        item.printItem();
        moneyCollected += item.getPrice();
    }
};


// =================== Utility functions ========================

vector<ItemShelf> generateInventory(){
    vector<ItemShelf> inventory;

    for(int i=0;i<2;i++)
    {
        Item item = Item(10,"Chips");
        int countOfItems = 5;
        int code = i+1;
        ItemShelf shelf = ItemShelf(item,countOfItems,code);
        inventory.push_back(shelf);
    }
    return inventory;
}


// =========== main code ================
int main(){
    vector<ItemShelf> inventory = generateInventory();
    VendingMachine vm = VendingMachine(inventory);
    vm.displayInventory();
}