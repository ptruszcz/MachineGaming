from Vector import Vector
from Asteroid import Asteroid
from Coordinates import Coordinates
import pygame
import random
import math


def spawn_asteroids(self, asteroids_number):
    """spawn asteroids outside the screen, with velocity vector pointed towards the screen"""
    for _ in range(asteroids_number):
        _spawn_single_asteroid(self)


def _spawn_single_asteroid(self):
    position = _randomize_spawn_point()
    velocity = _create_vector_towards_screen(position)

    self._asteroids.add(Asteroid(position,
                                 velocity))
    self._last_asteroid_spawn = pygame.time.get_ticks()


def _randomize_spawn_point():
    import GameWindow
    SPAWN_MARGIN = GameWindow.SPAWN_MARGIN
    WINDOW_SIZE_X = GameWindow.WINDOW_SIZE_X
    WINDOW_SIZE_Y = GameWindow.WINDOW_SIZE_Y

    border_number = random.randint(1, 4)
    # get random point on outer rectangle (bigger than screen by SPAWN_MARGIN in every direction)
    if border_number == 1:
        position = Coordinates(-SPAWN_MARGIN,
                               random.randint(-SPAWN_MARGIN, WINDOW_SIZE_Y + SPAWN_MARGIN))
    elif border_number == 2:
        position = Coordinates(WINDOW_SIZE_X + SPAWN_MARGIN,
                               random.randint(-SPAWN_MARGIN, WINDOW_SIZE_Y + SPAWN_MARGIN))
    elif border_number == 3:
        position = Coordinates(random.randint(-SPAWN_MARGIN,
                                              WINDOW_SIZE_X + SPAWN_MARGIN), -SPAWN_MARGIN)
    else:
        position = Coordinates(random.randint(-SPAWN_MARGIN,
                                              WINDOW_SIZE_X + SPAWN_MARGIN), WINDOW_SIZE_Y + SPAWN_MARGIN)

    return position


def _create_vector_towards_screen(origin_coordinates):
    import GameWindow
    WINDOW_SIZE_X = GameWindow.WINDOW_SIZE_X
    WINDOW_SIZE_Y = GameWindow.WINDOW_SIZE_Y
    ASTEROIDS_MAX_VELOCITY = GameWindow.ASTEROIDS_MAX_VELOCITY

    max_vel_sqrt = math.sqrt(ASTEROIDS_MAX_VELOCITY)

    # random point on screen towards which asteroid will be flying
    random_screen_coordinates = Coordinates(random.randint(0, WINDOW_SIZE_X),
                                            random.randint(0, WINDOW_SIZE_Y))
    # distance between spawn point and random point on screen
    distance = (random_screen_coordinates.x - origin_coordinates.x,
                random_screen_coordinates.y - origin_coordinates.y)
    norm = math.sqrt(distance[0] ** 2 + distance[1] ** 2)
    # unit vector of direction
    direction = (distance[0] / norm, distance[1] / norm)

    return Vector(direction[0] * max_vel_sqrt, direction[1] * max_vel_sqrt)