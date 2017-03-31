import pygame
from Spaceship import Spaceship
from Coordinates import Coordinates


WINDOW_SIZE_X = 1024
WINDOW_SIZE_Y = 768
white = (255, 255, 255)
black = (0, 0, 0)


class GameWindow:
    def __init__(self):
        self._running = False
        self._screen = None
        self._clock = None
        self._pressed_buttons = set()
        self._spaceship = Spaceship(Coordinates(WINDOW_SIZE_X/2, WINDOW_SIZE_Y/2))

    def run(self):
        self._init()

        while self._running:
            self._clock.tick(15)

            for event in pygame.event.get():
                self._handle_event(event)
            for key in self._pressed_buttons:
                self._spaceship.steer(key)

            self._spaceship.move()
            self._render()

        pygame.quit()

    def _init(self):
        pygame.init()
        self._screen = pygame.display.set_mode((WINDOW_SIZE_X, WINDOW_SIZE_Y), pygame.HWSURFACE | pygame.DOUBLEBUF)
        self._clock = pygame.time.Clock()
        self._running = True

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
        self._spaceship.draw(self._screen, white)
        pygame.display.update()
