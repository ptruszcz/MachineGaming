import pygame


class GameWindow:
    def __init__(self):
        self._screen = None
        self._clock = None

    def run(self):
        self._init()

        while True:
            for event in pygame.event.get():
                self._handle_event(event)
                self._render()



    def _init(self):
        pygame.init()
        self._screen = pygame.display.set_mode((1024, 768), pygame.HWSURFACE | pygame.DOUBLEBUF)
        self._clock = pygame.time.Clock()

    def _handle_event(self, event):
        if event.type == pygame.QUIT:
            pygame.quit()

        # do sth

    def _render(self):
        # render sth
        # switch buffers as pygame uses double buffering
        pygame.display.flip()
