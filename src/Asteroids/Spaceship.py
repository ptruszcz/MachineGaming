class Spaceship:
    def __init__(self, coordinates, velocity=0, direction=0, acceleration=0):
        self.coordinates = coordinates
        self.velocity = velocity
        self.direction = direction    # from 0 to 359
        self.acceleration = acceleration
