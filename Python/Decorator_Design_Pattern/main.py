# Current working directory is "Low Level Design"

# Here do not need to care where the python modules i.e python files (car.py and car_decorator.py) reside the 
# python interpreter takes care of it
from car import Car
from car_decorator import SportsCar,LuxuryCar

def main():
    basic_car = Car()
    basic_car.assemble()

    print("===="*10)

    sports_car = SportsCar(basic_car)
    sports_car.assemble()

    print("=="*20)

    luxury_car = LuxuryCar(basic_car)
    luxury_car.assemble()

    print('=='*20)

    sports_luxury_car = SportsCar(luxury_car)
    # Order of calling assemble Car->LuxuryCar -> SportsCar
    sports_luxury_car.assemble()

    print("=="*20)

    luxury_sports_car = LuxuryCar(sports_car)
    # Order of calling assemble Car->SportsCar->LuxuryCar
    luxury_sports_car.assemble()


# Call the function
main()
