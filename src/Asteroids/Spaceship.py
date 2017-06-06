import os
import pygame
import math
import random
import Config as c
from MovingObject import MovingObject
from Vector import Vector
from Missile import Missile
from Coordinates import Coordinates

"""
File created by: Piotr Truszczynski
Modified by: Jakub Fajkowski
"""


class Spaceship(MovingObject):
    def __init__(self, x, y, listener=None):
        file_path = os.path.dirname(__file__)
        fullname = os.path.join(file_path, '../../res/Asteroids', 'spaceship.png')
        image = pygame.image.load(fullname)

        MovingObject.__init__(self, image=image,
                              coordinates=Coordinates(x, y),
                              velocity=Vector(0, 0),
                              direction=90,
                              image_scale=0.20,
                              does_it_bounce=c.SPACESHIP_BOUNCE,
                              slows_down_after_bounce=True,
                              listener=listener)

        self.last_shot = 0

    def move(self):
        self._slow_down()
        MovingObject.move(self)

    def steer(self, key):
        if key == pygame.K_w:
            self._accelerate(c.MAIN_BOOSTER_POWER)
        elif key == pygame.K_s:
            self._accelerate(-c.MAIN_BOOSTER_POWER)
        elif key == pygame.K_d:
            self._rotate(c.SIDE_BOOSTER_POWER)
        elif key == pygame.K_a:
            self._rotate(-c.SIDE_BOOSTER_POWER)

    def fire(self):
        spaceship_speed = math.sqrt(self.velocity.x ** 2 + self.velocity.y ** 2)
        out_velocity = Vector()
        out_velocity.x = math.cos(math.radians(self.direction)) * (c.FIRE_POWER + spaceship_speed)
        out_velocity.y = - math.sin(math.radians(self.direction)) * (c.FIRE_POWER + spaceship_speed)
        return Missile(Coordinates(self.coordinates.x, self.coordinates.y), out_velocity, self.direction)

    def _slow_down(self):
        if abs(self.velocity.x) > c.SLOW_DOWN_RATE or abs(self.velocity.y) > c.SLOW_DOWN_RATE:
            self.velocity.x -= math.copysign(c.SLOW_DOWN_RATE, self.velocity.x)
            self.velocity.y -= math.copysign(c.SLOW_DOWN_RATE, self.velocity.y)

    def _accelerate(self, value):
        spaceship_speed = math.sqrt(self.velocity.x ** 2 + self.velocity.y ** 2)
        if spaceship_speed < c.MAX_SPEED:
            self.velocity.x += math.cos(math.radians(self.direction)) * value
            self.velocity.y -= math.sin(math.radians(self.direction)) * value

    def _rotate(self, value):
        self.direction = (-value + self.direction) % 360
