from concrete_shapes import Circle,Square,Rectangle

class ShapeFactory:
    def get_shape(self, shape_type):
        if shape_type == "Circle":
            return Circle()
        elif shape_type == "Square":
            return Square()
        elif shape_type == "Rectangle":
            return Rectangle()