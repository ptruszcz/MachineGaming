import pygame
import Spaceship
from Coordinates import Coordinates
import AsteroidGenerator

WINDOW_SIZE_X = 1024
WINDOW_SIZE_Y = 768
white = (255, 255, 255)
black = (0, 0, 0)
ASTEROIDS_MAX_VELOCITY = 5
POINTS_FOR_ASTEROID = 10
ASTEROIDS_PER_SPAWN = 2
ASTEROIDS_SPAWN_INTERVAL = 1000  # no idea how much should it be
DIFFICULTY_INCREASE_INTERVAL = 10000
SPAWN_INTERVAL_DECREASE = 20
ASTEROIDS_MAX_ON_SCREEN = 15
SPAWN_MARGIN = 100


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
        self._last_asteroid_spawn = 0
        self._last_difficulty_increase = 0

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

            if pygame.time.get_ticks() - self._last_asteroid_spawn > ASTEROIDS_SPAWN_INTERVAL \
               and len(self._asteroids.sprites()) < ASTEROIDS_MAX_ON_SCREEN:
                AsteroidGenerator.spawn_asteroids(self, ASTEROIDS_PER_SPAWN)

            # time based difficulty - can easily be changed to score based
            if pygame.time.get_ticks() - self._last_difficulty_increase > DIFFICULTY_INCREASE_INTERVAL:
                self._increase_difficulty()

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

    def _increase_difficulty(self):
        global ASTEROIDS_SPAWN_INTERVAL
        global ASTEROIDS_PER_SPAWN
        global ASTEROIDS_MAX_ON_SCREEN

        if ASTEROIDS_SPAWN_INTERVAL > 0:
            ASTEROIDS_SPAWN_INTERVAL -= SPAWN_INTERVAL_DECREASE
        elif ASTEROIDS_PER_SPAWN < 10:
            ASTEROIDS_PER_SPAWN += 1
        elif ASTEROIDS_MAX_ON_SCREEN < 30:
            ASTEROIDS_MAX_ON_SCREEN += 1

        self._last_difficulty_increase = pygame.time.get_ticks()

    def _display_score(self):
        font = pygame.font.SysFont("Courier New", 30)
        label = font.render("Score: " + str(self._score), 1, white)
        self._screen.blit(label, (10, 10))
