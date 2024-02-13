# include<iostream>
using namespace std;

//  Problem Statement -> https://www.digitalocean.com/community/tutorials/decorator-design-pattern-in-java-example

// ========== Defining Base classes ====
class Car{
    public:
    virtual void assemble()
    {
        cout<<"Basic car parts assembled"<<endl;
    }
};

// ============ Defining decorator base class ================
class CarDecorator:public Car{
    protected:
    Car* car;

    public:
    CarDecorator(Car* car){
        this->car = car;
    }

    virtual void assemble() override {
        car->assemble();
    }
};

// ========= Defining concrete decorator implementations ============
class SportsCar: public CarDecorator{

    public:
    SportsCar(Car* car):CarDecorator(car){}

    void assemble() override
    {   
        car->assemble();
        cout<<"Sports car parts added to car"<<endl;
    }
};

class LuxuryCar: public CarDecorator{
    public:
    LuxuryCar(Car* car):CarDecorator(car){}

    void assemble() override
    {   
        car->assemble();
        cout<<"Luxury car parts added to car"<<endl;
    }
};

int main(){
    Car basicCar = Car();
    basicCar.assemble();

    cout<<"=================="<<endl;

    SportsCar sportsCar(&basicCar);
    // assemble method of "SportsCar" class called
    sportsCar.assemble();

    cout<<"=================="<<endl;

    LuxuryCar luxuryCar(&basicCar);
    // assemble method of "LuxuryCar" class called
    luxuryCar.assemble();

    cout<<"=================="<<endl;


    LuxuryCar luxurySportsCar(&sportsCar);
    // decorator on basicCar , here the decorations are sports and luxury cars
    // order of calling assmeble methods Car -> SportsCar -> LuxuryCar
    luxurySportsCar.assemble();

    cout<<"=================="<<endl;

    SportsCar sportsLuxuryCar = SportsCar(&luxuryCar);
    // decorator on basicCar , here the decorations are sports and luxury cars
    // order of calling assmeble methods Car -> LuxuryCar -> SportsCar
    sportsLuxuryCar.assemble();

}