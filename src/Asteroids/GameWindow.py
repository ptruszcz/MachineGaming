import pygame


class GameWindow:
    def __init__(self):
        self._running = True
        self._screen = None
        self._clock = None

    def execute(self):
        if not self._init():
            self._running = False

        #while running
            #event
            #loop
            #render

    def _init(self):
        pygame.init()
        self._screen = pygame.display.set_mode((1024, 768), pygame.HWSURFACE | pygame.DOUBLEBUF)
        self._clock = pygame.time.Clock()
        self._running = True

