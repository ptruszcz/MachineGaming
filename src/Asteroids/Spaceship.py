import os
import pygame
import math
from Vector import Vector
from Missile import Missile
from Coordinates import Coordinates

MAIN_BOOSTER_POWER = 0.09
SIDE_BOOSTER_POWER = 3 # in degrees
FIRE_POWER = 10
SLOW_DOWN_RATE = 0.01


class Spaceship(pygame.sprite.Sprite):
    def __init__(self, coordinates, velocity=Vector(0, 0), direction=0):
        pygame.sprite.Sprite.__init__(self)
        self._coordinates = coordinates
        self._velocity = velocity
        self._direction = direction    # from 0 to 359 where 0 is right and 90 is down
        self.image = pygame.Surface([20, 20])

        fullname = os.path.join('../../res/Asteroids/sprites', 'spaceship.png')
        self.image = pygame.image.load(fullname)

    def update(self, surface):
        # minus before self._direction is because transform.rotate counts rotation in counter-clockwise direction
        rotated = self.rot_center(self.image, -self._direction)
        surface.blit(rotated, (self._coordinates.x, self._coordinates.y))

    def rot_center(self, image, angle):
        """rotate an image while keeping its center and size"""
        orig_rect = image.get_rect()
        rot_image = pygame.transform.rotate(image, angle)
        rot_rect = orig_rect.copy()
        rot_rect.center = rot_image.get_rect().center
        rot_image = rot_image.subsurface(rot_rect).copy()
        return rot_image

    def steer(self, key):
        if key == pygame.K_w:
            self._accelerate(MAIN_BOOSTER_POWER)
        elif key == pygame.K_s:
            self._accelerate(-MAIN_BOOSTER_POWER)
        elif key == pygame.K_d:
            self._rotate(SIDE_BOOSTER_POWER)
        elif key == pygame.K_a:
            self._rotate(-SIDE_BOOSTER_POWER)

    def fire(self):
        out_velocity = Vector()
        out_velocity.x_value = math.cos(math.radians(self._direction)) * FIRE_POWER
        out_velocity.y_value = math.sin(math.radians(self._direction)) * FIRE_POWER
        return Missile(Coordinates(self._coordinates.x, self._coordinates.y), out_velocity, self._direction)

    def move(self):
        self._slow_down()
        self._update_coordinates()
        self._display_info()

    def _slow_down(self):
        if abs(self._velocity.x_value) > SLOW_DOWN_RATE or abs(self._velocity.y_value) > SLOW_DOWN_RATE:
            self._velocity.x_value -= math.copysign(SLOW_DOWN_RATE, self._velocity.x_value)
            self._velocity.y_value -= math.copysign(SLOW_DOWN_RATE, self._velocity.y_value)

    def _accelerate(self, value):
        self._velocity.x_value += math.cos(math.radians(self._direction)) * value
        self._velocity.y_value += math.sin(math.radians(self._direction)) * value

    def _rotate(self, value):
        self._direction = (value + self._direction) % 360

    def _update_coordinates(self):
        self._coordinates.x += self._velocity.x_value
        self._coordinates.y += self._velocity.y_value

    def _display_info(self):
        print("\nDirection: " + str(self._direction))
        print("Velocity x: " + str(self._velocity.x_value) + "\nVelocity y: " + str(self._velocity.y_value))
