import math
import matplotlib
import Config as c
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
from matplotlib import style
from MachineGamingController import MachineGamingController
from GameController import GameController
import Labels
import sys
if sys.version_info[0] < 3:
    import Tkinter as tk
    from Tkinter import filedialog
    from Tkinter import messagebox
else:
    import tkinter as tk
    from tkinter import filedialog
    from tkinter import messagebox

matplotlib.rcParams.update({'font.size': 8})
matplotlib.use('TkAgg')
style.use('dark_background')


class MachineGaming(tk.Tk):
    def __init__(self):
        tk.Tk.__init__(self)
        self.wm_title(Labels.title)
        self.resizable(0, 0)
        self.machine_gaming_controller = MachineGamingController(stats_window=self)
        self.game_controller = GameController(stats_window=self)

        self.canvas = None
        self.fig = Figure(figsize=(5, 4), dpi=100, tight_layout={'h_pad': 3})
        self.best_gen_score = self.fig.add_subplot(2, 1, 1, title=Labels.plot_title[0], xlabel=Labels.plot_xlabel)
        self.mean_gen_score = self.fig.add_subplot(2, 1, 2, title=Labels.plot_title[1], xlabel=Labels.plot_xlabel)

        self.mean_gen_score_x = []
        self.mean_gen_score_y = []
        self.best_gen_score_x = []
        self.best_gen_score_y = []
        self.best_score_overall = 0
        self.curr_gen_best = 0
        self.curr_gen_total_score = 0
        self._previous_population = 0  # population size
        self._previous_generation = 1  # generation number

        self.eap_label_vars = []
        self.stat_label_vars = []

        frame = tk.Frame(self)
        frame.pack(side=tk.TOP, anchor='w')

        self.controls_frame = tk.Frame(frame)
        self.controls_frame.pack(side=tk.LEFT)
        self.infos_frame = tk.Frame(frame)
        self.infos_frame.pack(side=tk.TOP, anchor='e')
        self.speed_slider = None
        self.sliders_frame = tk.Frame(frame)
        self.sliders_frame.pack(side=tk.BOTTOM)

        self.add_controls()
        self.add_infos()
        self.add_sliders()
        self.add_plot()

    def add_controls(self):
        buttons_callbacks = [lambda: self.start(headless=True),
                             lambda: self.start(headless=False),
                             self.stop, self.game_controller.change_lines,
                             self.enter_parameters, self._set_path_and_save,
                             self._set_path_and_load, self._quit]

        for i in range(len(Labels.buttons)):
            button = tk.Button(self.controls_frame, text=Labels.buttons[i],
                               padx=8, pady=6, width=6, height=1, command=buttons_callbacks[i])
            button.pack(side=tk.TOP)

    def add_infos(self):
        stats_frame = tk.LabelFrame(self.infos_frame, text=Labels.frames[0])
        stats_frame.pack(side=tk.TOP, anchor='e')
        stats_labels = []

        for i in range(len(Labels.stats)):
            self.stat_label_vars.append(tk.StringVar())
            self.stat_label_vars[i].set(Labels.stats[i])

        for i in range(len(Labels.stats)):
            stats_labels.append(tk.Label(stats_frame, textvariable=self.stat_label_vars[i],
                                         width=50, anchor="w"))
            stats_labels[i].pack(side=tk.TOP, anchor='w')

        params_frame = tk.LabelFrame(self.infos_frame, text=Labels.frames[1])
        params_frame.pack(side=tk.TOP, anchor='e')

        for i in range(len(Labels.params)):
            self.eap_label_vars.append(tk.StringVar())
            self.eap_label_vars[i].set(Labels.params[i])

        param_labels = []
        for i in range(len(Labels.params)):
            param_labels.append(tk.Label(params_frame, textvariable=self.eap_label_vars[i],
                                         width=50, anchor="w"))
            param_labels[i].pack(anchor='nw')

    def add_sliders(self):
        speed_slider_frame = tk.Frame(self.sliders_frame)
        speed_slider_frame.pack(side=tk.LEFT)
        speed_label = tk.Label(speed_slider_frame, text=Labels.slider)
        speed_label.pack(side=tk.BOTTOM)
        self.speed_slider = tk.Scale(speed_slider_frame, orient='horizontal', length=350, width=10,
                                     from_=1, to=10, resolution=0.1, command=self.game_controller.change_speed)
        self.speed_slider.pack(side=tk.BOTTOM)

    def add_plot(self):
        self.canvas = FigureCanvasTkAgg(self.fig, self)
        self.canvas.show()
        self.canvas.get_tk_widget().pack(side=tk.BOTTOM)

    def enter_parameters(self):
        param_frame = tk.Toplevel()
        default_values = [10, 4,
                          1, 0.5,
                          3, 10.0]
        entries = []

        for i in range(len(Labels.params)):
            label = tk.Label(param_frame, text=Labels.params[i])
            entries.append(tk.Entry(param_frame))
            label.grid(row=i, column=0)
            entries[i].insert(0, default_values[i])
            entries[i].grid(row=i, column=1)

        create_button = tk.Button(
            param_frame, text=Labels.create_button,
            command=lambda: [self.machine_gaming_controller.initialize_ea(self.extract_str_from_entries(entries)),
                             self.update_ea_parameters(self.extract_str_from_entries(entries)),
                             param_frame.destroy()])
        create_button.grid(row=10, column=0, columnspan=2)

    def extract_str_from_entries(self, entries):
        return [e.get() for e in entries]

    def update_ea_parameters(self, parameters):
        for i in range(len(parameters)):
            self.eap_label_vars[i].set(Labels.params[i] + str(parameters[i]))
        self._previous_population = len(self.machine_gaming_controller.ea.get_population())
        self._previous_generation = self.machine_gaming_controller.get_current_generation()

    def update_stats(self, current_gen_num, current_nn_num, current_score):
        current_stats = [current_gen_num,
                         current_nn_num,
                         current_score,
                         self.best_score_overall]

        for i in range(len(self.stat_label_vars)):
            self.stat_label_vars[i].set(Labels.stats[i] + str(current_stats[i]))

    def start(self, headless):
        if self.machine_gaming_controller.ea is not None:
            if self.game_controller.current_game is not None:
                self.stop()

            self.game_controller.start(headless=headless)
        else:
            messagebox.showwarning(Labels.msgbox_title[0], Labels.msgbox_msg[0])

    def run(self):
        self.protocol("WM_DELETE_WINDOW", self._quit)
        self.mainloop()

    def stop(self):
        self.speed_slider.set(1)
        if self.game_controller.current_game is not None:
            self.game_controller.stop()
            self.game_controller.current_game_thread.join(5)

    def _quit(self):
        self.stop()
        self.quit()     # stops mainloop
        self.destroy()  # this is necessary on Windows to prevent Fatal Python Error

    def _set_path_and_save(self):
        path = filedialog.asksaveasfilename(filetypes=Labels.mg_filetype, initialfile=Labels.initialfilename)
        if len(path) is 0:  # dialog closed with "cancel".
            return
        if self.machine_gaming_controller.save(path):
            messagebox.showinfo(Labels.msgbox_title[1], Labels.msgbox_msg[1])
        else:
            messagebox.showwarning(Labels.msgbox_title[1], Labels.msgbox_msg[2])

    def _set_path_and_load(self):
        path = filedialog.askopenfilename(filetypes=Labels.mg_filetype)
        if len(path) is 0:  # dialog closed with "cancel".
            return
        success, parameters = self.machine_gaming_controller.load(path)
        if success:
            self.update_ea_parameters(parameters)
            messagebox.showinfo(Labels.msgbox_title[2], Labels.msgbox_msg[3])
        else:
            messagebox.showwarning(Labels.msgbox_title[2], Labels.msgbox_msg[4])

    def on_game_over(self):  # listener for spaceship crashes
        current_game_score = self.game_controller.current_game.score
        self.update_scores(current_game_score)
        self.machine_gaming_controller.neural_network.fitness = current_game_score
        self.machine_gaming_controller.process()

    def on_screen_update(self, player, obstacles):
        neural_network = self.machine_gaming_controller.neural_network
        if neural_network is None:
            return

        screen_state = [player.direction,
                        player.coordinates.calculate_distance(c.CENTER_POINT)]

        for obstacle in obstacles:
            delta_x = obstacle.coordinates.x - player.coordinates.x
            delta_y = - (obstacle.coordinates.y - player.coordinates.y)  # because cartesian but upside down

            delta_v_x = obstacle.velocity.x - player.velocity.x
            delta_v_y = - (obstacle.velocity.y - player.velocity.y)

            obstacle_direction = self._direction_degrees(delta_y, delta_x)
            delta_direction = self._direction_delta(obstacle_direction, player.direction)

            screen_state.append(player.coordinates.calculate_distance(obstacle.coordinates))
            screen_state.append(delta_v_x)
            screen_state.append(delta_v_y)
            screen_state.append(delta_direction)

        screen_state_size = len(screen_state)
        if screen_state_size < self.machine_gaming_controller.input_size:
            screen_state += [0] * (self.machine_gaming_controller.input_size - screen_state_size)

        if self.game_controller.current_game is not None:
            self.update_stats(self.machine_gaming_controller.get_current_generation(),
                              self.machine_gaming_controller.get_current_network(),
                              self.game_controller.current_game.score)

        return self.game_controller.calculate_buttons(neural_network=neural_network, input_vector=screen_state)

    def update_scores(self, score):
        if self._previous_generation == self.machine_gaming_controller.get_current_generation():
            if score > self.curr_gen_best:
                self.curr_gen_best = score
            if score > self.best_score_overall:
                self.best_score_overall = score
            self.curr_gen_total_score += score
        else:
            self.update_plots(generation=self._previous_generation,
                              gen_best=self.curr_gen_best,
                              gen_avg=self.curr_gen_total_score/self._previous_population)
            self._previous_population = len(self.machine_gaming_controller.ea.get_population())
            self.curr_gen_total_score = 0
            self.curr_gen_best = 0
            self._previous_generation = self.machine_gaming_controller.get_current_generation()

    def update_plots(self, generation, gen_best, gen_avg):
        self.best_gen_score_y.append(gen_best)
        self.best_gen_score_x.append(generation)
        self.mean_gen_score_y.append(gen_avg)
        self.mean_gen_score_x.append(generation)

        self.mean_gen_score.clear()
        self.best_gen_score.clear()
        self.best_gen_score.plot(self.best_gen_score_x, self.best_gen_score_y)
        self.mean_gen_score.plot(self.mean_gen_score_x, self.mean_gen_score_y)
        self.best_gen_score.set_title(Labels.plot_title[0])
        self.best_gen_score.set_xlabel(Labels.plot_xlabel)
        self.mean_gen_score.set_title(Labels.plot_title[1])
        self.mean_gen_score.set_xlabel(Labels.plot_xlabel)
        self.canvas.draw()

    @staticmethod
    def _direction_degrees(y, x):
        direction_rad = math.atan2(y, x)
        if direction_rad >= 0:
            return math.degrees(direction_rad)
        else:
            return math.degrees(2*math.pi + direction_rad)

    @staticmethod
    def _direction_delta(x, y):
        return ((x-y) % 360 + 180) % 360 - 180


machine_gaming = MachineGaming()


if __name__ == '__main__':
    machine_gaming.run()
