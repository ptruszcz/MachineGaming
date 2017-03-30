import pygame
import math
from Vector import Vector
from Coordinates import Coordinates


# hardcoded and ugly - will be fixed soon :)
# will be sprite later
class Spaceship:
    def __init__(self, coordinates, velocity=Vector(0, 0), direction=0, acceleration=0):
        self._coordinates = coordinates
        self._velocity = velocity
        self._direction = direction    # from 0 to 359 where 0 is right and 90 is up
        self._acceleration = acceleration

    def draw(self, screen, color):
        rect = pygame.Rect = (self._coordinates.x, self._coordinates.y, 20, 20)
        pygame.draw.rect(screen, color, rect)

    def steer(self, key):
        if key == pygame.K_w:
            self._accelerate(forward=True)
        elif key == pygame.K_s:
            self._accelerate(forward=False)
        elif key == pygame.K_d:
            self._rotate(clockwise=True)
        elif key == pygame.K_a:
            self._rotate(clockwise=False)
        elif key == pygame.K_RETURN:
            print("pew pew pew")

    def move(self):
        self._update_velocity()
        self._coordinates.x += self._velocity.x_value
        self._coordinates.y += self._velocity.y_value

    def _accelerate(self, forward):
        if forward:
            self._acceleration += 0.01
        else:
            self._acceleration -= 0.01

    def _rotate(self, clockwise):
        if clockwise:
            self._direction -= 1
        else:
            self._direction += 1
        self._direction = self._direction % 360

    def _update_velocity(self):
        self._velocity.x_value += math.cos(math.radians(self._direction)) * self._acceleration
        self._velocity.y_value += math.sin(math.radians(self._direction)) * self._acceleration

        print("\nDirection: " + str(self._direction))
        print("Acceleration: " + str(self._acceleration))
        print("Velocity x: " + str(self._velocity.x_value) + "\nVelocity y: " + str(self._velocity.y_value))
