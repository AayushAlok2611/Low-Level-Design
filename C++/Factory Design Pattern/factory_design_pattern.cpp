# include <iostream>
using namespace std;


// ======= Base Shape class(Interface/Abstarct class) ============
class Shape{
    public:
    virtual void printShape() = 0;
};

// ====== Concrete Shapes ======
class Circle: public Shape{

    public:
    Circle(){}

    void printShape() override{
        cout<<"The shape is circle"<<endl;
    }
};

class Sqaure: public Shape{
    public:
    Sqaure(){}

    void printShape() override{
        cout<<"The shape is sqaure"<<endl;
    }
};


class Rectangle:public Shape{
    public:
    Rectangle(){}
    void printShape() override{
        cout<<"The shape is rectangle"<<endl;
    }
};

// =============== Shape Factory =============
class ShapeFactory{
    public:
    Shape* getShape(string shapeType)
    {   
        Shape* ptrToShape = NULL;
        if(shapeType == "Circle")
        {
            Circle circle = Circle();
            ptrToShape = &circle;
        }
        else if(shapeType == "Sqaure")
        {
            Sqaure sqaure = Sqaure();
            ptrToShape = &sqaure;
        }
        else if(shapeType == "Rectangle")
        {
            Rectangle rectangle = Rectangle();
            ptrToShape = &rectangle;
        }
        return ptrToShape;
    }
};

int main()
{   
    ShapeFactory shapeFactory;
    Shape* shapePtr = shapeFactory.getShape("Circle");
    shapePtr->printShape();

    shapePtr = shapeFactory.getShape("Sqaure");
    shapePtr->printShape();

    shapePtr = shapeFactory.getShape("Rectangle");
    shapePtr->printShape();
}