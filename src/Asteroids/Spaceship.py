import os
import pygame
import math
from MovingObject import MovingObject
from Vector import Vector
from Missile import Missile
from Coordinates import Coordinates

MAIN_BOOSTER_POWER = 0.09
SIDE_BOOSTER_POWER = 3 # in degrees
FIRE_POWER = 5
SLOW_DOWN_RATE = 0.01


class Spaceship(MovingObject):
    def __init__(self, coordinates, velocity=Vector(0, 0), direction=0):
        fullname = os.path.join('../../res/Asteroids/sprites', 'spaceship.png')
        image = pygame.image.load(fullname)

        MovingObject.__init__(self, image, coordinates, velocity, direction)

    def move(self):
        self._slow_down()
        MovingObject.move(self)

    def steer(self, key):
        if key == pygame.K_w:
            self._accelerate(MAIN_BOOSTER_POWER)
        elif key == pygame.K_s:
            self._accelerate(-MAIN_BOOSTER_POWER)
        elif key == pygame.K_d:
            self._rotate(SIDE_BOOSTER_POWER)
        elif key == pygame.K_a:
            self._rotate(-SIDE_BOOSTER_POWER)

    def fire(self):
        out_velocity = Vector()
        out_velocity.x = math.cos(math.radians(self._direction)) * FIRE_POWER
        out_velocity.y = math.sin(math.radians(self._direction)) * FIRE_POWER
        return Missile(Coordinates(self._coordinates.x, self._coordinates.y), out_velocity, self._direction)

    def _slow_down(self):
        if abs(self._velocity.x) > SLOW_DOWN_RATE or abs(self._velocity.y) > SLOW_DOWN_RATE:
            self._velocity.x -= math.copysign(SLOW_DOWN_RATE, self._velocity.x)
            self._velocity.y -= math.copysign(SLOW_DOWN_RATE, self._velocity.y)

    def _accelerate(self, value):
        self._velocity.x += math.cos(math.radians(self._direction)) * value
        self._velocity.y += math.sin(math.radians(self._direction)) * value

    def _rotate(self, value):
        self._direction = (value + self._direction) % 360