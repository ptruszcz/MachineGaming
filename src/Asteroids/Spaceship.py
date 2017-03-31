import pygame
import math
from Vector import Vector
from Coordinates import Coordinates


MAIN_BOOSTER_POWER = 0.05
SLOW_DOWN_RATE = 0.01  # TODO: change to atmosphere viscosity


# hardcoded and ugly - will be fixed soon :)
# will be sprite later
class Spaceship:
    def __init__(self, coordinates, velocity=Vector(0, 0), direction=0):
        self._coordinates = coordinates
        self._velocity = velocity
        self._direction = direction    # from 0 to 359 where 0 is right and 90 is down

    def draw(self, screen, color):
        rect = pygame.Surface((20, 20))
        rect.fill(color)
        screen.blit(rect, (self._coordinates.x, self._coordinates.y))

    def steer(self, key):
        if key == pygame.K_w:
            self._accelerate(MAIN_BOOSTER_POWER)
        elif key == pygame.K_s:
            self._accelerate(-MAIN_BOOSTER_POWER)
        elif key == pygame.K_d:
            self._rotate(clockwise=True)
        elif key == pygame.K_a:
            self._rotate(clockwise=False)
        elif key == pygame.K_RETURN:
            print("pew pew pew")

    def move(self):
        self._slow_down()
        self._update_coordinates()
        self._display_info()

    def _slow_down(self):
        if abs(self._velocity.x_value) > SLOW_DOWN_RATE or abs(self._velocity.y_value) > SLOW_DOWN_RATE:
            self._velocity.x_value -= math.copysign(SLOW_DOWN_RATE, self._velocity.x_value)
            self._velocity.y_value -= math.copysign(SLOW_DOWN_RATE, self._velocity.y_value)

    def _accelerate(self, value):
        self._velocity.x_value += math.cos(math.radians(self._direction)) * value
        self._velocity.y_value += math.sin(math.radians(self._direction)) * value

    def _rotate(self, clockwise):
        if clockwise:
            self._direction += 5
        else:
            self._direction -= 5
        self._direction = self._direction % 360

    def _update_coordinates(self):
        self._coordinates.x += self._velocity.x_value
        self._coordinates.y += self._velocity.y_value

    def _display_info(self):
        print("\nDirection: " + str(self._direction))
        print("Velocity x: " + str(self._velocity.x_value) + "\nVelocity y: " + str(self._velocity.y_value))
