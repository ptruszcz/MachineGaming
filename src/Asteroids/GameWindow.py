import pygame
import random
import math
import Spaceship
from Coordinates import Coordinates
from Vector import Vector
from Asteroid import Asteroid

WINDOW_SIZE_X = 1024
WINDOW_SIZE_Y = 768
white = (255, 255, 255)
black = (0, 0, 0)
INITIAL_ASTEROIDS_NUMBER = 10
ASTEROIDS_MAX_VELOCITY = 5
POINTS_FOR_ASTEROID = 10
ASTEROIDS_PER_SPAWN = 2
ASTEROID_SPAWN_INTERVAL = 1000 # no idea how much should it be
SPAWN_RECT = 100


class GameWindow:
    def __init__(self):
        self._running = False
        self._screen = None
        self._clock = None
        self._score = 0
        self._pressed_buttons = set()
        self._asteroids = pygame.sprite.Group()
        self._missiles = pygame.sprite.Group()
        self._spaceship = Spaceship.Spaceship(Coordinates(WINDOW_SIZE_X/2, WINDOW_SIZE_Y/2))
        self._spawn_asteroids_off_screen(INITIAL_ASTEROIDS_NUMBER, ASTEROIDS_MAX_VELOCITY)
        self._last_asteroid_spawn = 0

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
            if destroyed_asteroids:
                self._score += POINTS_FOR_ASTEROID

            if pygame.time.get_ticks() - self._last_asteroid_spawn > ASTEROID_SPAWN_INTERVAL:
                self._spawn_asteroids_off_screen(ASTEROIDS_PER_SPAWN, ASTEROIDS_MAX_VELOCITY)
                self._last_asteroid_spawn = pygame.time.get_ticks()

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
        self._display_score()
        pygame.display.update()

    def _spawn_asteroids_off_screen(self, asteroids_number, max_velocity):
        """spawn asteroids outside the screen, with velocity vector pointed towards the screen"""
        max_vel_sqrt = math.sqrt(max_velocity)

        for _ in range(asteroids_number):
            option = random.randint(1, 4)
            # get random point on outer rectangle (bigger by SPAWN_RECT in every direction than screen)
            if option == 1:
                position = (-SPAWN_RECT, random.randint(-SPAWN_RECT, WINDOW_SIZE_Y + SPAWN_RECT))
            elif option == 2:
                position = (WINDOW_SIZE_X + SPAWN_RECT, random.randint(-SPAWN_RECT, WINDOW_SIZE_Y + SPAWN_RECT))
            elif option == 3:
                position = (random.randint(-SPAWN_RECT, WINDOW_SIZE_X+SPAWN_RECT), -SPAWN_RECT)
            elif option == 4:
                position = (random.randint(-SPAWN_RECT, WINDOW_SIZE_X+SPAWN_RECT), WINDOW_SIZE_Y+SPAWN_RECT)

            # random point on screen towards which asteroid will be flying
            point = (random.randint(0, WINDOW_SIZE_X), random.randint(0, WINDOW_SIZE_Y))
            # distance between spawn point and random point on screen
            distance = (point[0]-position[0], point[1]-position[1])
            norm = math.sqrt(distance[0] ** 2 + distance[1] ** 2)
            # unit vector of direction
            direction = (distance[0]/norm, distance[1]/norm)

            velocity = (direction[0]*max_vel_sqrt, direction[1]*max_vel_sqrt)
            self._asteroids.add(Asteroid(Coordinates(position[0], position[1]),
                                         Vector(velocity[0], velocity[1])))

    def _display_score(self):
        font = pygame.font.SysFont("Courier New", 30)
        label = font.render("Score: " + str(self._score), 1, white)
        self._screen.blit(label, (10, 10))
