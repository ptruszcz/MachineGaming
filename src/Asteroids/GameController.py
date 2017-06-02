import threading
from GameWindow import GameWindow


class GameController:
    def __init__(self, stats_window, key_threshold=0.75):
        self.stats_window = stats_window
        self.current_game = None
        self._current_game_thread = None
        self._key_threshold = key_threshold
        self._key_mappings = []

    def start(self):
        self.current_game = GameWindow(game_over_listener=self.stats_window)
        self._current_game_thread = threading.Thread(target=self.current_game.run)
        self._current_game_thread.start()
        return        

    def stop(self):
        self.current_game.running = False
        return

    def calculate_buttons(self, neural_network, input_vector):
        neural_network.feed_forward(input_vector)
        output = neural_network.get_output()
        return [self._key_mappings[i]
                for i in output
                if i > self._key_threshold]

    def add_key_mapping(self, key):
        self._key_mappings.append(key)