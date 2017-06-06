import os
import pygame
import Config as c
from Vector import Vector
from MovingObject import MovingObject

## @brief Class representing obstacle - Asteroid
#  @authors Piotr Truszczynski, Jakub Fajkowski
class Asteroid(MovingObject):
    def __init__(self, coordinates, velocity=Vector(0, 0), scale=0.10, rotation_rate=-0.5):
        file_path = os.path.dirname(__file__)
        fullname = os.path.join(file_path, '../../res/Asteroids', 'asteroid.png')
        image = pygame.image.load(fullname)

        MovingObject.__init__(self, image, coordinates, c.ASTEROIDS_BOUNCE, velocity,
                              image_scale=scale)

        self._rotation_rate = rotation_rate

    def update(self, surface):
        self.move()
        MovingObject.update(self, surface)

    def move(self):
        self._rotate(self._rotation_rate)
        MovingObject.move(self)

    def _rotate(self, value):
        self.direction = (value + self.direction) % 360
