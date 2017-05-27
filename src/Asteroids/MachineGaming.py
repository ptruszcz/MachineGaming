import matplotlib.pyplot as plt
from GameWindow import GameWindow
import threading

current_game = GameWindow()


def run_game():
    current_game.run()
    return


def live_plot():
    fig, ax_array = plt.subplots(2)

    curr_score = ax_array[0]
    mean_gen_score = ax_array[1]

    x = []
    y = []

    delta = 0.5
    seconds = 0
    while True:
        if seconds % 10 == 0 and seconds != 0:
            global current_game
            current_game.restart()
            curr_score.clear()
            seconds = 0
            x = []
            y = []

        x.append(seconds)
        y.append(current_game.score)
        curr_score.plot(x, y)
        plt.pause(delta)
        seconds += delta


if __name__ == '__main__':
    live_plot_thread = threading.Thread(target=live_plot)
    current_game_thread = threading.Thread(target=run_game)
    live_plot_thread.start()
    current_game_thread.start()
