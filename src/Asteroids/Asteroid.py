import os
import pygame
from Vector import Vector
from MovingObject import MovingObject

"""
File created by: Piotr Truszczynski
Modified by: Jakub Fajkowski
"""


class Asteroid(MovingObject):
    def __init__(self, coordinates, velocity=Vector(0, 0), scale=0.25, rotation_rate=-0.5):
        fullname = os.path.join('../../res/Asteroids/sprites', 'asteroid.png')
        image = pygame.image.load(fullname)

        MovingObject.__init__(self, image, coordinates, velocity, image_scale=scale)

        self._rotation_rate = rotation_rate

    def update(self, surface):
        self.move()
        MovingObject.update(self, surface)

    def move(self):
        self._rotate(self._rotation_rate)
        MovingObject.move(self)

    def _rotate(self, value):
        self._direction = (value + self._direction) % 360
