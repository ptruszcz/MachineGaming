import os
import pygame
import math
from MovingObject import MovingObject
from Vector import Vector
from Missile import Missile
from Coordinates import Coordinates

"""
File created by: Piotr Truszczynski
Modified by: Jakub Fajkowski
"""

MAIN_BOOSTER_POWER = 0.09
SIDE_BOOSTER_POWER = 3 # in degrees
FIRE_POWER = 7
SLOW_DOWN_RATE = 0.01
MISSILE_RELOAD_TIME = 500
MAX_SPEED = 7


class Spaceship(MovingObject):
    def __init__(self, coordinates, velocity=Vector(0, 0), direction=0):
        fullname = os.path.join('../../res/Asteroids/sprites', 'spaceship.png')
        image = pygame.image.load(fullname)

        MovingObject.__init__(self, image, coordinates, velocity, direction, image_scale=0.5)

        self.last_shot = 0
        self._slows_down_after_bounce = True

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
        spaceship_speed = math.sqrt(self._velocity.x ** 2 + self._velocity.y ** 2)
        out_velocity = Vector()
        out_velocity.x = math.cos(math.radians(self._direction)) * (FIRE_POWER + spaceship_speed)
        out_velocity.y = math.sin(math.radians(self._direction)) * (FIRE_POWER + spaceship_speed)
        self.last_shot = pygame.time.get_ticks()
        return Missile(Coordinates(self._coordinates.x, self._coordinates.y), out_velocity, self._direction)

    def _slow_down(self):
        if abs(self._velocity.x) > SLOW_DOWN_RATE or abs(self._velocity.y) > SLOW_DOWN_RATE:
            self._velocity.x -= math.copysign(SLOW_DOWN_RATE, self._velocity.x)
            self._velocity.y -= math.copysign(SLOW_DOWN_RATE, self._velocity.y)

    def _accelerate(self, value):
        spaceship_speed = math.sqrt(self._velocity.x ** 2 + self._velocity.y ** 2)
        if spaceship_speed < MAX_SPEED:
            self._velocity.x += math.cos(math.radians(self._direction)) * value
            self._velocity.y += math.sin(math.radians(self._direction)) * value

    def _rotate(self, value):
        self._direction = (value + self._direction) % 360
