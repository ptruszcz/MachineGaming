import math
import matplotlib
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
from matplotlib import style
from MachineGamingController import MachineGamingController
from GameController import GameController
import GUILabels
import sys
if sys.version_info[0] < 3:
    import Tkinter as tk
else:
    import tkinter as tk

matplotlib.rcParams.update({'font.size': 8})
matplotlib.use('TkAgg')
style.use('dark_background')


class MachineGaming(tk.Tk):
    def __init__(self):
        tk.Tk.__init__(self)
        self.machine_gaming_controller = MachineGamingController(stats_window=self)
        self.game_controller = GameController(stats_window=self)

        self.fig = Figure(figsize=(5, 5), dpi=100, tight_layout={'h_pad': 3})
        self.overall_best = self.fig.add_subplot(3, 1, 1, title='Najlepszy', xlabel='czas [s]')
        self.overall_best_x = []
        self

        self.curr_gen_best = self.fig.add_subplot(3, 1, 2, title='Najlepszy w obecnej generacji', xlabel='czas [t]')
        self.mean_gen_score = self.fig.add_subplot(3, 1, 3, title='Średni wynik generacji', xlabel='generacja')
        self.mean_gen_score_x = []
        self.mean_gen_score_y = []
        self.eap_label_vars = []
        self.stat_label_vars = []

        frame = tk.Frame(self)
        frame.pack(side=tk.TOP, anchor='w')

        self.controls_frame = tk.Frame(frame)
        self.controls_frame.pack(side=tk.LEFT)
        self.infos_frame = tk.Frame(frame)
        self.infos_frame.pack(side=tk.TOP, anchor='e')
        self.sliders_frame = tk.Frame(frame)
        self.sliders_frame.pack(side=tk.BOTTOM)

        self.add_controls()
        self.add_infos()
        self.add_sliders()
        self.add_plot()

    def add_controls(self):
        buttons_callbacks = [self.game_controller.start, self.game_controller.stop,
                             self.game_controller.change_lines,
                             self.enter_parameters, self.set_filename_and_save,
                             None, self._quit]

        for i in range(len(GUILabels.buttons_texts)):
            button = tk.Button(self.controls_frame, text=GUILabels.buttons_texts[i],
                               padx=8, pady=8, width=6, height=1, command=buttons_callbacks[i])
            button.pack(side=tk.TOP)

    def add_infos(self):
        stats_frame = tk.LabelFrame(self.infos_frame, text='Statystyki')
        stats_frame.pack(side=tk.TOP, anchor='e')
        stats_labels = []

        for i in range(len(GUILabels.stats_texts)):
            self.stat_label_vars.append(tk.StringVar())
            self.stat_label_vars[i].set(GUILabels.stats_texts[i])

        for i in range(len(GUILabels.stats_texts)):
            stats_labels.append(tk.Label(stats_frame, textvariable=self.stat_label_vars[i],
                                         width=50, anchor="w"))
            stats_labels[i].pack(side=tk.TOP, anchor='w')

        params_frame = tk.LabelFrame(self.infos_frame, text='Parametry')
        params_frame.pack(side=tk.TOP, anchor='e')

        for i in range(len(GUILabels.params_texts)):
            self.eap_label_vars.append(tk.StringVar())
            self.eap_label_vars[i].set(GUILabels.params_texts[i])

        param_labels = []
        for i in range(len(GUILabels.params_texts)):
            param_labels.append(tk.Label(params_frame, textvariable=self.eap_label_vars[i],
                                         width=50, anchor="w"))
            param_labels[i].pack(anchor='nw')

    def add_sliders(self):
        speed_slider_frame = tk.Frame(self.sliders_frame)
        speed_slider_frame.pack(side=tk.LEFT)
        speed_label = tk.Label(speed_slider_frame, text="Prędkość symulacji")
        speed_label.pack(side=tk.BOTTOM)
        speed = tk.Scale(speed_slider_frame, orient='horizontal', length=200,
                         from_=1, to=10, resolution=0.1, command=self.game_controller.change_speed)
        speed.pack(side=tk.BOTTOM)

    def add_plot(self):
        canvas = FigureCanvasTkAgg(self.fig, self)
        canvas.show()
        canvas.get_tk_widget().pack(side=tk.BOTTOM)

    def enter_parameters(self):
        param_frame = tk.Toplevel()
        default_values = [10, 4,
                          1, 0.5,
                          3, 10.0]
        entries = []

        for i in range(len(GUILabels.params_texts)):
            label = tk.Label(param_frame, text=GUILabels.params_texts[i])
            entries.append(tk.Entry(param_frame))
            label.grid(row=i, column=0)
            entries[i].insert(0, default_values[i])
            entries[i].grid(row=i, column=1)

        create_button = tk.Button(param_frame,
                                  text="UTWÓRZ",
                                  command=lambda: [self.machine_gaming_controller.initialize_ea(entries),
                                                   self.update_ea_parameters(entries),
                                                   param_frame.destroy()])
        create_button.grid(row=10, column=0, columnspan=2)

    def update_ea_parameters(self, entries):
        for i in range(len(entries)):
            self.eap_label_vars[i].set(GUILabels.params_texts[i] + entries[i].get())

    def update_stats(self, current_gen_num, current_nn_num, current_score):
        current_stats = [current_gen_num,
                         current_nn_num,
                         current_score]

        for i in range(len(self.stat_label_vars)):
            self.stat_label_vars[i].set(GUILabels.stats_texts[i] + str(current_stats[i]))

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
        self.machine_gaming_controller.neural_network.fitness = self.game_controller.current_game.score
        self.machine_gaming_controller.process()

    def on_screen_update(self, player, obstacles):
        neural_network = self.machine_gaming_controller.neural_network
        if neural_network is None:
            return

        screen_state = [player.direction]

        for obstacle in obstacles:
            delta_x = obstacle.coordinates.x - player.coordinates.x
            delta_y = - (obstacle.coordinates.y - player.coordinates.y)  # because cartesian but upside down

            obstacle_direction = self._direction_degrees(delta_y, delta_x)
            delta_direction = obstacle_direction - player.direction

            screen_state.append(delta_x)
            screen_state.append(delta_y)
            screen_state.append(delta_direction)

        screen_state_size = len(screen_state)
        if screen_state_size < 16:
            screen_state += [0] * (16 - screen_state_size)

        self.update_stats(self.machine_gaming_controller.current_generation(),
                          self.machine_gaming_controller.current_network(),
                          self.game_controller.current_game.score)

        return self.game_controller.calculate_buttons(neural_network=neural_network,
                                                      input_vector=screen_state)

    @staticmethod
    def _direction_degrees(y, x):
        direction_rad = math.atan2(y, x)
        if direction_rad >= 0:
            return math.degrees(direction_rad)
        else:
            return math.degrees(2*math.pi + direction_rad)


machine_gaming = MachineGaming()


if __name__ == '__main__':
    machine_gaming.run()
