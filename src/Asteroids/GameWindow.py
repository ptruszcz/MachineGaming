import pygame
import math
import random
import Config as c
import time
from Coordinates import Coordinates
from Vector import Vector
from Asteroid import Asteroid
from Spaceship import Spaceship

"""
File created by: Piotr Truszczynski
Modified by: Jakub Fajkowski
"""


def current_time():
    return int(round(time.time() * 1000))


class GameWindow:
    def __init__(self, game_over_listener=None, screen_update_listener=None,
                 headless=False):
        self._game_over_listener = game_over_listener
        self._screen_update_listener = screen_update_listener
        self._display_size = (c.WINDOW_SIZE_X, c.WINDOW_SIZE_Y)
        if headless:
            self._display_size = (1, 1)

        self.score = 0
        self.speed = c.DEFAULT_SPEED
        self.lines = False
        self.running = False

        self._screen = None
        self._clock = None
        self._pressed_buttons = set()
        self._asteroids = pygame.sprite.Group()
        self._tracked_asteroids = []
        self._missiles = pygame.sprite.Group()
        self._spaceship = Spaceship(x=c.CENTER_POINT.x,
                                    y=c.CENTER_POINT.y,
                                    listener=self)
        self._last_asteroid_spawn = current_time()
        self._asteroids_spawn_interval = c.ASTEROIDS_SPAWN_INTERVAL
        self._asteroids_per_spawn = c.ASTEROIDS_PER_SPAWN
        self._asteroids_max_on_screen = c.ASTEROIDS_MAX_ON_SCREEN
        self._last_difficulty_increase = current_time()

    def _init(self):
        pygame.init()
        self._screen = pygame.display.set_mode(self._display_size,
                                               pygame.HWSURFACE | pygame.DOUBLEBUF)
        self._clock = pygame.time.Clock()
        self.running = True

    def restart(self):
        self.score = 0
        self._clock = pygame.time.Clock()
        self._asteroids = pygame.sprite.Group()
        self._missiles = pygame.sprite.Group()
        self._spaceship = Spaceship(x=c.CENTER_POINT.x,
                                    y=c.CENTER_POINT.y,
                                    listener=self)
        self._last_asteroid_spawn = current_time()
        self._asteroids_spawn_interval = c.ASTEROIDS_SPAWN_INTERVAL
        self._asteroids_per_spawn = c.ASTEROIDS_PER_SPAWN
        self._asteroids_max_on_screen = c.ASTEROIDS_MAX_ON_SCREEN
        self._last_difficulty_increase = current_time()

    def run(self):
        self._init()

        while self.running:
            self._clock.tick(60 * self.speed)

            if c.POINTS_FOR_BEING_ALIVE:
                self.score += 1

            for event in pygame.event.get():
                if event is not pygame.MOUSEMOTION:
                    self._handle_event(event)
            if self._screen_update_listener is not None:
                asteroids = [a for a in self._asteroids]
                asteroids.sort(key=lambda a:
                               self._spaceship.coordinates.calculate_distance(a.coordinates),
                               reverse=False)
                self._tracked_asteroids = asteroids[:c.DEFAULT_TRACKED_ASTEROIDS]
                self._pressed_buttons = self._screen_update_listener.on_screen_update(
                    player=self._spaceship,
                    obstacles=self._tracked_asteroids)

            for key in self._pressed_buttons:
                if key == pygame.K_RETURN:
                    if current_time() - self._spaceship.last_shot > self._consider_fps(c.MISSILE_RELOAD_TIME):
                        missile = self._spaceship.fire()
                        self._missiles.add(missile)
                        self._spaceship.last_shot = current_time()
                else:
                    self._spaceship.steer(key)

            self._spaceship.move()
            spaceship_crashed = pygame.sprite.spritecollideany(self._spaceship, self._asteroids)
            if spaceship_crashed:
                self._spaceship.destroy()

            destroyed_asteroids = pygame.sprite.groupcollide(self._missiles, self._asteroids,
                                                             True, True)
            if destroyed_asteroids:
                self.score += c.ASTEROIDS_POINTS_PER_HIT

            if current_time() - self._last_asteroid_spawn > self._consider_fps(c.ASTEROIDS_SPAWN_INTERVAL) \
               and len(self._asteroids.sprites()) < self._asteroids_max_on_screen:
                self._spawn_single_asteroid()

            # time based difficulty - can easily be changed to score based
            if current_time() - self._last_difficulty_increase > self._consider_fps(c.DIFFICULTY_INCREASE_INTERVAL):
                self._increase_difficulty()

            self._render()

        pygame.quit()

    def _consider_fps(self, value):
        fps = self._clock.get_fps()
        if fps != 0:
            result = value * (60/fps)
        else:
            result = value
        return result

    def _handle_event(self, event):
        if event.type == pygame.KEYDOWN:
            self._pressed_buttons.add(event.key)
            if event.key == pygame.K_ESCAPE:
                self.running = False

        elif event.type == pygame.KEYUP:
            if self._pressed_buttons:
                self._pressed_buttons.remove(event.key)
        elif event.type == pygame.QUIT:
            self.running = False

    def _render(self):
        self._screen.fill(c.COLOR_BLACK)
        if self.lines:
            self._display_tracking_rays()
            self._display_crosshair()
        self._spaceship.update(self._screen)
        self._asteroids.update(self._screen)
        self._missiles.update(self._screen)
        self._display_score()
        self._display_fps()
        pygame.display.update()

    def _increase_difficulty(self):
        # if self._asteroids_spawn_interval > 0:
        #     self._asteroids_spawn_interval -= c.SPAWN_INTERVAL_DECREASE
        # if self._asteroids_per_spawn < 10:
        #     self._asteroids_per_spawn += 1
        if self._asteroids_max_on_screen < 10:
            self._asteroids_max_on_screen += 1

        self._last_difficulty_increase = current_time()

    def _display_score(self):
        font = pygame.font.SysFont("Courier New", 20)
        label = font.render("Score: " + str(self.score), 1, c.COLOR_WHITE)
        self._screen.blit(label, (10, 10))

    def _display_fps(self):
        font = pygame.font.SysFont("Courier New", 20)
        label = font.render("FPS: " + str(int(self._clock.get_fps())), 1, c.COLOR_WHITE)
        self._screen.blit(label, (10, 30))

    def _spawn_asteroids(self, asteroids_number):
        """spawn asteroids outside the screen, with velocity vector pointed towards the screen"""
        for _ in range(asteroids_number):
            self._spawn_single_asteroid()

    def _spawn_single_asteroid(self):
        position = _randomize_spawn_point()
        velocity = self._create_vector_towards_screen(position)

        self._asteroids.add(Asteroid(position, velocity))
        self._last_asteroid_spawn = current_time()

    def _display_tracking_rays(self):
        for asteroid in self._tracked_asteroids:
            pygame.draw.line(self._screen,
                             c.COLOR_RED,
                             (self._spaceship.coordinates.x, self._spaceship.coordinates.y),
                             (asteroid.coordinates.x, asteroid.coordinates.y))

    def _display_crosshair(self):
        endpoint_x = math.cos(math.radians(self._spaceship.direction)) * 1000000
        endpoint_y = - math.sin(math.radians(self._spaceship.direction)) * 1000000
        pygame.draw.line(self._screen,
                         c.COLOR_GREEN,
                         (self._spaceship.coordinates.x, self._spaceship.coordinates.y),
                         (endpoint_x, endpoint_y))

    def _create_vector_towards_screen(self, origin_coordinates):
        max_vel_sqrt = math.sqrt(c.ASTEROIDS_MAX_VELOCITY)

        # distance between spawn point and player point
        distance = (self._spaceship.coordinates.x - origin_coordinates.x,
                    self._spaceship.coordinates.y - origin_coordinates.y)
        norm = math.sqrt(distance[0] ** 2 + distance[1] ** 2)
        # unit vector of direction
        direction = (distance[0] / norm, distance[1] / norm)

        return Vector(direction[0] * max_vel_sqrt, direction[1] * max_vel_sqrt)

    def on_object_destroyed(self, o):
        if isinstance(o, Spaceship):
            if self._game_over_listener is not None:
                self._game_over_listener.on_game_over()
            self.restart()


def _randomize_spawn_point():
    border_number = random.randint(1, 4)
    # get random point on outer rectangle (bigger than screen by SPAWN_MARGIN in every direction)
    if border_number == 1:
        position = Coordinates(-c.SPAWN_MARGIN,
                               random.randint(-c.SPAWN_MARGIN, c.WINDOW_SIZE_Y + c.SPAWN_MARGIN))
    elif border_number == 2:
        position = Coordinates(c.WINDOW_SIZE_X + c.SPAWN_MARGIN,
                               random.randint(-c.SPAWN_MARGIN, c.WINDOW_SIZE_Y + c.SPAWN_MARGIN))
    elif border_number == 3:
        position = Coordinates(random.randint(-c.SPAWN_MARGIN, c.WINDOW_SIZE_X + c.SPAWN_MARGIN),
                               -c.SPAWN_MARGIN)
    else:
        position = Coordinates(random.randint(-c.SPAWN_MARGIN, c.WINDOW_SIZE_X + c.SPAWN_MARGIN),
                               c.WINDOW_SIZE_Y + c.SPAWN_MARGIN)

    return position


