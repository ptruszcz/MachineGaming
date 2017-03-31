import os
import pygame
from Vector import Vector


class Asteroid(pygame.sprite.Sprite):
    def __init__(self, coordinates, velocity=Vector(0, 0)):
        pygame.sprite.Sprite.__init__(self)
        self._coordinates = coordinates
        self._velocity = velocity

        self.image = pygame.Surface([20, 20])

        fullname = os.path.join('sprites', 'asteroid.png')
        self.image = pygame.image.load(fullname)
        self.rect = self.image.get_rect()

    def update(self, surface):
        self._update_coordinates()
        scaled = pygame.transform.scale(self.image, (100, 100))
        surface.blit(scaled, (self._coordinates.x, self._coordinates.y))

    def _update_coordinates(self):
        self._coordinates.x += self._velocity.x_value
        self._coordinates.y += self._velocity.y_value
