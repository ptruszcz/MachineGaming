import os
import pygame
import Config as c
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

        MovingObject.__init__(self, image, coordinates,
                              c.MISSILE_BOUNCE, velocity, direction,
                              image_scale=0.10)

    def update(self, surface):
        self.move()
        MovingObject.update(self, surface)
