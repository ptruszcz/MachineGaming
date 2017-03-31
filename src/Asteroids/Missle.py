import pygame


class Missle(pygame.sprite.Sprite):
    def __init__(self, coordinates, velocity=0):
        pygame.sprite.Sprite.__init__(self, self.groups)
        self.coordinates = coordinates
        self.velocity = velocity
