import os
import pygame
from Vector import Vector
from MovingObject import MovingObject

"""
File created by: Piotr Truszczynski
Modified by: Jakub Fajkowski
"""


class Missile(MovingObject):
    def __init__(self, coordinates, velocity=Vector(0, 0), direction=0):
        fullname = os.path.join('../../res/Asteroids/sprites', 'missile.png')
        image = pygame.image.load(fullname)

        MovingObject.__init__(self, image, coordinates, velocity, direction, image_scale=0.10)
        self._does_it_bounce = False

    def update(self, surface):
        self.move()

        if not self.is_on_screen():
            self.kill()

        MovingObject.update(self, surface)