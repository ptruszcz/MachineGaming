import math
import matplotlib
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
import matplotlib.animation as animation
from matplotlib import style

import sys
if sys.version_info[0] < 3:
    import Tkinter as tk
else:
    import tkinter as tk

from MachineGamingController import MachineGamingController
from GameController import GameController

matplotlib.use('TkAgg')
style.use('dark_background')


class MachineGaming(tk.Tk):
    def __init__(self):
        tk.Tk.__init__(self)
        self.root = tk.Frame(self)
        self.current_game_time = 0.0
        self.machine_gaming_controller = MachineGamingController(stats_window=self)
        self.game_controller = GameController(stats_window=self)

        self.fig = Figure(figsize=(5, 5), dpi=100, tight_layout={'h_pad': 3})
        self.curr_score = self.fig.add_subplot(2, 1, 1, title='Wynik sieci', xlabel='czas [s]')
        self.mean_gen_score = self.fig.add_subplot(2, 1, 2, title='Średni wynik generacji', xlabel='generacja')
        # TODO: find out why titles and labels disappear after plot update
        self.curr_score_x = []
        self.curr_score_y = []
        self.mean_gen_score_x = []
        self.mean_gen_score_y = []

        self.root.grid_rowconfigure(0, weight=1)
        self.root.grid_columnconfigure(0, weight=1)
        self.add_buttons()
        self.add_stats()
        self.add_plot()

    def add_buttons(self):
        button_frame = tk.Frame(self)
        button_frame.grid(row=0, column=3, rowspan=3, columnspan=2, sticky='swe')
        button_texts = ['START', 'STOP', 'ZAPISZ', 'WCZYTAJ', 'NOWY', 'WYJŚCIE']
        button_callbacks = [self.game_controller.start, self.game_controller.stop, self.set_filename_and_save, None, self.enter_parameters, self._quit]
        buttons = []

        for i in range(len(button_texts)):
            buttons.append(tk.Button(button_frame, text=button_texts[i], padx=10, pady=10, width=10,
                                     command=button_callbacks[i]))
            buttons[i].grid(row=(math.floor(i/2)), column=(i % 2), sticky='nw')

    def add_stats(self):
        label_frame = tk.LabelFrame(self, text='Statystyki')
        label_frame.grid(row=0, column=0, rowspan=3, columnspan=3, sticky='nwe')

        label_texts = ['Generacja: ', 'Sieć: ', 'Wynik sieci: ',
                       'Liczba warstw neuronów: ', 'Wektor wejściowy: ', 'Przycisk: ']
        labels = []

        for i in range(len(label_texts)):
            labels.append(tk.Label(label_frame, text=label_texts[i]))
            labels[i].pack(anchor='nw')

    def add_plot(self):
        canvas = FigureCanvasTkAgg(self.fig, self)
        canvas.show()
        canvas.get_tk_widget().grid(row=3, column=0, columnspan=4)

    def animate_plot(self, i):
        if self.game_controller.current_game is not None:
            self.curr_score_x.append(self.current_game_time)
            self.curr_score_y.append(self.game_controller.current_game.score)
            self.curr_score.clear()
            self.curr_score.plot(self.curr_score_x, self.curr_score_y)
            self.current_game_time += 1.0

    def enter_parameters(self):
        param_frame = tk.Toplevel()

        label_texts = ["Rozmiar populacji", "Liczba dzieci na generację", "Prawdopodobieństwo skrzyżowania",
                       "Prawdopodobieństwo mutacji", "Liczba ukrytych warstw", "Wariancja wag połączeń"]  # add output size?
        default_values = [10, 4, 1, 0.5, 3, 10.0]
        entries = []

        for i in range(len(label_texts)):
            label = tk.Label(param_frame, text=label_texts[i])
            entries.append(tk.Entry(param_frame))
            label.grid(row=i, column=0)
            entries[i].insert(0, default_values[i])
            entries[i].grid(row=i, column=1)

        create_button = tk.Button(param_frame,
                                  text="UTWÓRZ",
                                  command=lambda: [self.machine_gaming_controller.initialize_ea(entries),
                                                   param_frame.destroy()])
        create_button.grid(row=10, column=0, columnspan=2)

    def set_filename_and_save(self):
        save_frame = tk.Toplevel()
        label = tk.Label(save_frame, text="Zapisz jako: ")
        entry = tk.Entry(save_frame)
        entry.insert(0, 'generation.mg')
        label.grid(row=0, column=0)
        entry.grid(row=0, column=1)
        create_button = tk.Button(save_frame,
                                  text="ZAPISZ",
                                  command=lambda: [self.machine_gaming_controller.save(entry.get()),
                                                   save_frame.destroy()])
        create_button.grid(row=1, column=0, columnspan=2)

    def run(self):
        self.mainloop()

    def _quit(self):
        self.quit()     # stops mainloop
        self.destroy()  # this is necessary on Windows to prevent Fatal Python Error

    def on_game_over(self): # listener for spaceship crashes
        self.current_game_time = 0.0
        self.curr_score_x.clear()
        self.curr_score_y.clear()
        self.machine_gaming_controller.neural_network.fitness = self.game_controller.current_game.score
        self.machine_gaming_controller.process()

    def on_screen_update(self, player, obstacles):
        neural_network = self.machine_gaming_controller.neural_network
        if neural_network is None:
            return

        screen_state = [player.direction]

        for obstacle in obstacles:
            screen_state.append(obstacle.coordinates.x - player.coordinates.x)
            screen_state.append(obstacle.coordinates.y - player.coordinates.y)
            screen_state.append(obstacle.velocity.x - player.velocity.x)
            screen_state.append(obstacle.velocity.y - player.velocity.y)

        screen_state_size = len(screen_state)
        if screen_state_size < 21:
            screen_state += [0] * (21 - screen_state_size)

        return self.game_controller.calculate_buttons(neural_network=neural_network,
                                                      input_vector=screen_state)

machine_gaming = MachineGaming()
animation_func = animation.FuncAnimation(fig=machine_gaming.fig,
                                         func=machine_gaming.animate_plot,
                                         interval=1000,
                                         blit=False)


if __name__ == '__main__':
    machine_gaming.run()
