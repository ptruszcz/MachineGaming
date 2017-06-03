import pygame
import Spaceship
import math
import random
from Coordinates import Coordinates
from Vector import Vector
from Asteroid import Asteroid

"""
File created by: Piotr Truszczynski
Modified by: Jakub Fajkowski
"""

WINDOW_SIZE_X = 800
WINDOW_SIZE_Y = 600
DEFAULT_SPEED = 1
DEFAULT_TRACKED_ASTEROIDS = 5

COLOR_WHITE = (255, 255, 255)
COLOR_BLACK = (0, 0, 0)
COLOR_GREEN = (0, 255, 0)
COLOR_RED = (255, 0, 0)

ASTEROIDS_MAX_VELOCITY = 5
ASTEROIDS_POINTS_PER_HIT = 10
ASTEROIDS_PER_SPAWN = 1
ASTEROIDS_SPAWN_INTERVAL = 1000
ASTEROIDS_MAX_ON_SCREEN = 5
DIFFICULTY_INCREASE_INTERVAL = 10000
SPAWN_INTERVAL_DECREASE = 20
SPAWN_MARGIN = 100


class GameWindow:
    def __init__(self, game_over_listener=None, screen_update_listener=None):
        self._game_over_listener = game_over_listener
        self._screen_update_listener = screen_update_listener

        self.score = 0
        self.speed = DEFAULT_SPEED
        self.lines = False
        self.running = False

        self._screen = None
        self._clock = None
        self._pressed_buttons = set()
        self._asteroids = pygame.sprite.Group()
        self._tracked_asteroids = []
        self._missiles = pygame.sprite.Group()
        self._spaceship = Spaceship.Spaceship(
            coordinates=Coordinates(WINDOW_SIZE_X/2, WINDOW_SIZE_Y/2))
        self._last_asteroid_spawn = 0
        self._asteroids_spawn_interval = ASTEROIDS_SPAWN_INTERVAL
        self._asteroids_per_spawn = ASTEROIDS_PER_SPAWN
        self._asteroids_max_on_screen = ASTEROIDS_MAX_ON_SCREEN
        self._last_difficulty_increase = 0

    def _init(self):
        pygame.init()
        self._screen = pygame.display.set_mode((WINDOW_SIZE_X, WINDOW_SIZE_Y), pygame.HWSURFACE | pygame.DOUBLEBUF)
        self._clock = pygame.time.Clock()
        self.running = True

    def restart(self):
        self.score = 0
        self._clock = pygame.time.Clock()
        self._asteroids = pygame.sprite.Group()
        self._missiles = pygame.sprite.Group()
        self._spaceship = Spaceship.Spaceship(
            coordinates=Coordinates(WINDOW_SIZE_X/2, WINDOW_SIZE_Y/2))
        self._last_asteroid_spawn = 0
        self._asteroids_spawn_interval = ASTEROIDS_SPAWN_INTERVAL
        self._asteroids_per_spawn = ASTEROIDS_PER_SPAWN
        self._asteroids_max_on_screen = ASTEROIDS_MAX_ON_SCREEN
        self._last_difficulty_increase = 0

    def run(self):
        self._init()

        while self.running:
            self._clock.tick(60 * self.speed)

            for event in pygame.event.get():
                if event is not pygame.MOUSEMOTION:
                    self._handle_event(event)
            if self._screen_update_listener is not None:
                asteroids = [a for a in self._asteroids]
                asteroids.sort(key=lambda a: calculate_distance(self._spaceship, a), reverse=False)
                self._tracked_asteroids = asteroids[:DEFAULT_TRACKED_ASTEROIDS]
                self._pressed_buttons = self._screen_update_listener.on_screen_update(
                    player=self._spaceship,
                    obstacles=self._tracked_asteroids)

            for key in self._pressed_buttons:
                if key == pygame.K_RETURN:
                    if pygame.time.get_ticks() - self._spaceship.last_shot > Spaceship.MISSILE_RELOAD_TIME:
                        missile = self._spaceship.fire()
                        self._missiles.add(missile)
                else:
                    self._spaceship.steer(key)

            self._spaceship.move()
            spaceship_crashed = pygame.sprite.spritecollideany(self._spaceship, self._asteroids)
            if spaceship_crashed:
                if self._game_over_listener is not None:
                    self._game_over_listener.on_game_over()
                self.restart()

            destroyed_asteroids = pygame.sprite.groupcollide(self._missiles, self._asteroids,
                                                             True, True)
            if destroyed_asteroids:
                self.score += ASTEROIDS_POINTS_PER_HIT

            if pygame.time.get_ticks() - self._last_asteroid_spawn > ASTEROIDS_SPAWN_INTERVAL \
               and len(self._asteroids.sprites()) < ASTEROIDS_MAX_ON_SCREEN:
                self._spawn_asteroids(ASTEROIDS_PER_SPAWN)

            # time based difficulty - can easily be changed to score based
            if pygame.time.get_ticks() - self._last_difficulty_increase > DIFFICULTY_INCREASE_INTERVAL:
                self._increase_difficulty()

            self._render()

        pygame.quit()

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
        self._screen.fill(COLOR_BLACK)
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
        if self._asteroids_spawn_interval > 0:
            self._asteroids_spawn_interval -= SPAWN_INTERVAL_DECREASE
        elif self._asteroids_per_spawn < 10:
            self._asteroids_per_spawn += 1
        elif self._asteroids_max_on_screen < 30:
            self._asteroids_max_on_screen += 1

        self._last_difficulty_increase = pygame.time.get_ticks()

    def _display_score(self):
        font = pygame.font.SysFont("Courier New", 20)
        label = font.render("Score: " + str(self.score), 1, COLOR_WHITE)
        self._screen.blit(label, (10, 10))

    def _display_fps(self):
        font = pygame.font.SysFont("Courier New", 20)
        label = font.render("FPS: " + str(int(self._clock.get_fps())), 1, COLOR_WHITE)
        self._screen.blit(label, (10, 30))

    def _spawn_asteroids(self, asteroids_number):
        """spawn asteroids outside the screen, with velocity vector pointed towards the screen"""
        for _ in range(asteroids_number):
            self._spawn_single_asteroid()

    def _spawn_single_asteroid(self):
        position = _randomize_spawn_point()
        velocity = _create_vector_towards_screen(position)

        self._asteroids.add(Asteroid(position, velocity))
        self._last_asteroid_spawn = pygame.time.get_ticks()

    def _display_tracking_rays(self):
        for asteroid in self._tracked_asteroids:
            pygame.draw.line(self._screen,
                             COLOR_RED,
                             (self._spaceship.coordinates.x, self._spaceship.coordinates.y),
                             (asteroid.coordinates.x, asteroid.coordinates.y))

    def _display_crosshair(self):
        endpoint_x = math.cos(math.radians(self._spaceship.direction)) * 1000000
        endpoint_y = - math.sin(math.radians(self._spaceship.direction)) * 1000000
        pygame.draw.line(self._screen,
                         COLOR_GREEN,
                         (self._spaceship.coordinates.x, self._spaceship.coordinates.y),
                         (endpoint_x, endpoint_y))


def _randomize_spawn_point():
    border_number = random.randint(1, 4)
    # get random point on outer rectangle (bigger than screen by SPAWN_MARGIN in every direction)
    if border_number == 1:
        position = Coordinates(-SPAWN_MARGIN,
                               random.randint(-SPAWN_MARGIN, WINDOW_SIZE_Y + SPAWN_MARGIN))
    elif border_number == 2:
        position = Coordinates(WINDOW_SIZE_X + SPAWN_MARGIN,
                               random.randint(-SPAWN_MARGIN, WINDOW_SIZE_Y + SPAWN_MARGIN))
    elif border_number == 3:
        position = Coordinates(random.randint(-SPAWN_MARGIN, WINDOW_SIZE_X + SPAWN_MARGIN),
                               -SPAWN_MARGIN)
    else:
        position = Coordinates(random.randint(-SPAWN_MARGIN, WINDOW_SIZE_X + SPAWN_MARGIN),
                               WINDOW_SIZE_Y + SPAWN_MARGIN)

    return position


def _create_vector_towards_screen(origin_coordinates):
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


def calculate_distance(point_a, point_b):
    return math.sqrt((point_b.coordinates.x - point_a.coordinates.x) ** 2 +
                     (point_b.coordinates.y - point_a.coordinates.y) ** 2)
