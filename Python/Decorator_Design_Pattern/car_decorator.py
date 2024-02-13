# Current working directory is "Low Level Design"
from car import Car

class CarDecorator(Car):

    def __init__(self,car):
        self.car = car
    
    def assemble(self):
        self.car.assemble()


class SportsCar(CarDecorator):

    def __init__(self, car):
        super().__init__(car)

    def assemble(self):
        self.car.assemble()
        print("Sport Car Parts added")


class LuxuryCar(CarDecorator):

    def __init__(self, car):
        super().__init__(car)
    
    def assemble(self):
        self.car.assemble()
        print("Luxury Car Parts Added")