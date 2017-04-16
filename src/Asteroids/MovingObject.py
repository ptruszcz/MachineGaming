import pygame
from Vector import Vector
import GameWindow

red = (255, 0, 0)
SPEED_AFTER_BOUNCE = 0.7


def scale_image(image, scale):
    scaled_width = int(image.get_width() * scale)
    scaled_height = int(image.get_height() * scale)
    scaled_image = pygame.transform.scale(image, (scaled_width, scaled_height))
    return scaled_image


class MovingObject(pygame.sprite.Sprite):
    def __init__(self, image, coordinates, velocity=Vector(0, 0), direction=0, image_scale=1):
        pygame.sprite.Sprite.__init__(self)
        self._image = scale_image(image, image_scale)
        self.rect = self._image.get_rect()
        self._coordinates = coordinates
        self._velocity = velocity
        self._direction = direction  # from 0 to 359 where 0 is right and 90 is down
        self._does_it_bounce = True
        self._slows_down_after_bounce = False

    def update(self, surface):
        # minus before self._direction is because transform.rotate counts rotation in counter-clockwise direction
        rotated = self.rotate_image(-self._direction)
        topleft = (self._coordinates.x - self._image.get_width() / 2,
                   self._coordinates.y - self._image.get_height() / 2)
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
        # bounce only objects on the screen
        if self._does_it_bounce and self.is_on_screen():
            self._bounce()

        self._coordinates.x += self._velocity.x
        self._coordinates.y += self._velocity.y

    def is_on_screen(self):
        return 0 < self._coordinates.x < GameWindow.WINDOW_SIZE_X and 0 < self._coordinates.y < GameWindow.WINDOW_SIZE_Y

    def _bounce(self):
        next_x = self._coordinates.x + self._velocity.x
        next_y = self._coordinates.y + self._velocity.y

        if next_x <= 0 or next_x >= GameWindow.WINDOW_SIZE_X:
            self._velocity.x = -self._velocity.x
            if self._slows_down_after_bounce:
                self._velocity.x *= SPEED_AFTER_BOUNCE

        if next_y <= 0 or next_y >= GameWindow.WINDOW_SIZE_Y:
            self._velocity.y = -self._velocity.y
            if self._slows_down_after_bounce:
                self._velocity.y *= SPEED_AFTER_BOUNCE

