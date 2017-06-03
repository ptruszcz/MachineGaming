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
    def __init__(self, x, y):
        fullname = os.path.join('../../res/Asteroids/sprites', 'spaceship.png')
        image = pygame.image.load(fullname)

        MovingObject.__init__(self, image=image,
                              coordinates=Coordinates(x, y),
                              velocity=Vector(0, 0),
                              direction=random.randint(0, 360),
                              image_scale=0.25)

        self.last_shot = 0
        self._slows_down_after_bounce = True

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
        self.last_shot = pygame.time.get_ticks()
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
