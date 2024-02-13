from shape_factory import ShapeFactory

if __name__ == "__main__":
    shape_factory = ShapeFactory()

    shape = shape_factory.get_shape("Circle")
    shape.print_shape()

    shape = shape_factory.get_shape("Square")
    shape.print_shape()

    shape = shape_factory.get_shape("Rectangle")
    shape.print_shape()