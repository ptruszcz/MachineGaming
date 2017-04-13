import pygame
from Vector import Vector


red = (255, 0, 0)


def scale_image(image, scale):
    scaled_width = int(image.get_width()*scale)
    scaled_height = int(image.get_height()*scale)
    scaled_image = pygame.transform.scale(image, (scaled_width, scaled_height))
    return scaled_image


class MovingObject(pygame.sprite.Sprite):
    def __init__(self, image, coordinates, velocity=Vector(0, 0), direction=0, image_scale=1):
        pygame.sprite.Sprite.__init__(self)
        self._image = scale_image(image, image_scale)
        self.rect = self._image.get_rect()
        self._coordinates = coordinates
        self._velocity = velocity
        self._direction = direction    # from 0 to 359 where 0 is right and 90 is down

    def update(self, surface):
        # minus before self._direction is because transform.rotate counts rotation in counter-clockwise direction
        rotated = self.rotate_image(-self._direction)
        topleft = (self._coordinates.x - self._image.get_width()/2,
                   self._coordinates.y - self._image.get_height()/2)
        surface.blit(rotated, topleft)
        # draw collision detection border
        self.rect.topleft = topleft
        pygame.draw.rect(surface, red, self.rect, 1)

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

    def is_collided_with(self, other_object):
        return self.rect.colliderect(other_object.rect)
