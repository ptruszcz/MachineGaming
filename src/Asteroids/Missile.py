import os
import pygame
from Vector import Vector


class Missile(pygame.sprite.Sprite):
    def __init__(self, coordinates, velocity=Vector(0, 0), direction=0):
        pygame.sprite.Sprite.__init__(self)
        self._coordinates = coordinates
        self._velocity = velocity
        self._direction = direction
        self.image = pygame.Surface([20, 20])

        fullname = os.path.join('../../res/Asteroids/sprites', 'missile.png')
        self.image = pygame.image.load(fullname)
        self.rect = self.image.get_rect()

    def update(self, surface):
        self._update_coordinates()
        center = self.image.get_rect().center
        # minus before self._direction is because transform.rotate counts rotation in counter-clockwise direction
        scaled = pygame.transform.scale(self.image, (100, 100))
        rotated = pygame.transform.rotate(scaled, -self._direction)
        rotated.get_rect().center = center
        surface.blit(rotated, (self._coordinates.x, self._coordinates.y))

    def _update_coordinates(self):
        self._coordinates.x += self._velocity.x_value
        self._coordinates.y += self._velocity.y_value
