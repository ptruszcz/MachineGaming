import pygame
import random
import math
import Spaceship
from Coordinates import Coordinates
from Vector import Vector
from Asteroid import Asteroid
from Missile import Missile

WINDOW_SIZE_X = 1024
WINDOW_SIZE_Y = 768
white = (255, 255, 255)
black = (0, 0, 0)
ASTEROIDS_NUMBER = 20
ASTEROIDS_MAX_VELOCITY = 5

class GameWindow:
    def __init__(self):
        self._running = False
        self._screen = None
        self._clock = None
        self._pressed_buttons = set()
        self._asteroids = pygame.sprite.Group()
        self._missiles = pygame.sprite.Group()

        self._spaceship = Spaceship.Spaceship(Coordinates(0, 0))
        self._spawn_asteroids(ASTEROIDS_NUMBER, ASTEROIDS_MAX_VELOCITY)

    def _init(self):
        pygame.init()
        self._screen = pygame.display.set_mode((WINDOW_SIZE_X, WINDOW_SIZE_Y), pygame.HWSURFACE | pygame.DOUBLEBUF)
        self._clock = pygame.time.Clock()
        self._running = True

    def run(self):
        self._init()

        while self._running:
            self._clock.tick(60)

            for event in pygame.event.get():
                self._handle_event(event)
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
                print("JEB")

            destroyed_asteroids = pygame.sprite.groupcollide(self._missiles, self._asteroids,
                                                             True, True)

            self._render()

        pygame.quit()

    def _handle_event(self, event):
        if event.type == pygame.KEYDOWN:
            self._pressed_buttons.add(event.key)
        elif event.type == pygame.KEYUP:
            if self._pressed_buttons:
                self._pressed_buttons.remove(event.key)
        elif event.type == pygame.QUIT:
            self._running = False

    def _render(self):
        self._screen.fill(black)
        self._spaceship.update(self._screen)
        self._asteroids.update(self._screen)
        self._missiles.update(self._screen)
        pygame.display.update()

    def _spawn_asteroids(self, asteroids_number, max_velocity):
        max_vel_sqrt = math.sqrt(max_velocity)
        self._asteroids = pygame.sprite.Group()

        for _ in range(asteroids_number):
            x_pos = random.randint(0, WINDOW_SIZE_X)
            y_pos = random.randint(0, WINDOW_SIZE_Y)

            x_vel = random.uniform(-max_vel_sqrt, max_vel_sqrt)
            y_vel = random.uniform(-max_vel_sqrt, max_vel_sqrt)

            self._asteroids.add(Asteroid(Coordinates(x_pos, y_pos),
                                         Vector(x_vel, y_vel)))
