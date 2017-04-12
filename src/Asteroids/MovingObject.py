import pygame
from Vector import Vector


def scale_image(image, scale):
    scaled_width = int(image.get_width()*scale)
    scaled_height = int(image.get_height()*scale)
    scaled_image = pygame.transform.scale(image, (scaled_width, scaled_height))
    return scaled_image


class MovingObject(pygame.sprite.Sprite):
    def __init__(self, image, coordinates, velocity=Vector(0, 0), direction=0, image_scale=1):
        pygame.sprite.Sprite.__init__(self)
        self._image = scale_image(image, image_scale)
        self._coordinates = coordinates
        self._velocity = velocity
        self._direction = direction    # from 0 to 359 where 0 is right and 90 is down

    def update(self, surface):
        # minus before self._direction is because transform.rotate counts rotation in counter-clockwise direction
        rotated = self.rotate_image(-self._direction)
        surface.blit(rotated, (self._coordinates.x - self._image.get_width()/2,
                               self._coordinates.y - self._image.get_height()/2))

    def rotate_image(self, angle):
        """rotate an image while keeping its center and size"""
        orig_rect = self._image.get_rect()
        rot_image = pygame.transform.rotate(self._image, angle)
        rot_rect = orig_rect.copy()
        rot_rect.center = rot_image.get_rect().center
        rot_image = rot_image.subsurface(rot_rect).copy()
        return rot_image

    def move(self):
        self._update_coordinates()

    def _update_coordinates(self):
        self._coordinates.x += self._velocity.x
        self._coordinates.y += self._velocity.y
