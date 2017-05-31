import math
import matplotlib
matplotlib.use('TkAgg')
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
from matplotlib.figure import Figure
import matplotlib.animation as animation
from matplotlib import style

from GameWindow import GameWindow
import threading
import sys
if sys.version_info[0] < 3:
    import Tkinter as tk
else:
    import tkinter as tk

from MachineGamingController import MachineGamingController

style.use('dark_background')


def run_game():
    global current_game
    global current_game_thread
    current_game = GameWindow()
    current_game_thread = threading.Thread(target=current_game.run)
    current_game_thread.start()
    return


class MachineGaming(tk.Tk):
    def __init__(self):
        tk.Tk.__init__(self)
        self.root = tk.Frame(self)
        self.current_game_time = 0.0
        self.mgc = MachineGamingController()

        self.fig = Figure(figsize=(5, 5), dpi=100, tight_layout={'h_pad': 3})
        self.curr_score = self.fig.add_subplot(2, 1, 1, title='Current score', xlabel='time [s]')
        self.mean_gen_score = self.fig.add_subplot(2, 1, 2, title='Mean generation score', xlabel='generation')
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
        button_texts = ['START', 'PAUSE', 'SAVE', 'LOAD', 'NEW', 'EXIT']
        button_callbacks = [run_game, None, self.set_filename_and_save, None, self.enter_parameters, self._quit]
        buttons = []

        for i in range(len(button_texts)):
            buttons.append(tk.Button(button_frame, text=button_texts[i], padx=10, pady=10, width=10,
                                     command=button_callbacks[i]))
            buttons[i].grid(row=(math.floor(i/2)), column=(i % 2), sticky='nw')

    def add_stats(self):
        label_frame = tk.LabelFrame(self, text='Statistics')
        label_frame.grid(row=0, column=0, rowspan=3, columnspan=3, sticky='nwe')

        label_texts = ['Current generation: ', 'Current network: ', 'Current fitness: ',
                       'Neuron layers: ', 'Input: ', 'Output button: ']
        labels = []

        for i in range(len(label_texts)):
            labels.append(tk.Label(label_frame, text=label_texts[i]))
            labels[i].pack(anchor='nw')

    def add_plot(self):
        canvas = FigureCanvasTkAgg(self.fig, self)
        canvas.show()
        canvas.get_tk_widget().grid(row=3, column=0, columnspan=4)

    def animate_plot(self, i):
        if current_game.running:
            self.curr_score_x.append(self.current_game_time)
            self.curr_score_y.append(current_game.score)
            self.curr_score.clear()
            self.curr_score.plot(self.curr_score_x, self.curr_score_y)
            self.current_game_time += 1.0
        else:
            self.current_game_time = 0.0
            self.curr_score_x.clear()
            self.curr_score_y.clear()

    def enter_parameters(self):
        param_frame = tk.Toplevel()

        label_texts = ["Population size", "Children bred per generation", "Crossover probability",
                       "Mutation probability", "Randomisation probability", "Hidden layers"]  # add output size?
        default_values = [10, 4, 1, 0.5, 0.1, 3]
        entries = []

        for i in range(len(label_texts)):
            label = tk.Label(param_frame, text=label_texts[i])
            entries.append(tk.Entry(param_frame))
            label.grid(row=i, column=0)
            entries[i].insert(0, default_values[i])
            entries[i].grid(row=i, column=1)

        create_button = tk.Button(param_frame, text="CREATE",
                                  command=lambda: [self.mgc.initialize_EA(entries), param_frame.destroy()])
        create_button.grid(row=10, column=0, columnspan=2)

    def set_filename_and_save(self):
        save_frame = tk.Toplevel()
        label = tk.Label(save_frame, text="Save as: ")
        entry = tk.Entry(save_frame)
        entry.insert(0, 'generation.mg')
        label.grid(row=0, column=0)
        entry.grid(row=0, column=1)
        create_button = tk.Button(save_frame, text="SAVE",
                                  command=lambda: [self.mgc.save(entry.get()), save_frame.destroy()])
        create_button.grid(row=1, column=0, columnspan=2)

    def run(self):
        self.mainloop()

    def _quit(self):
        self.quit()     # stops mainloop
        self.destroy()  # this is necessary on Windows to prevent Fatal Python Error

current_game = GameWindow()
machine_gaming = MachineGaming()
current_game_thread = threading.Thread(target=current_game.run)
animFunc = animation.FuncAnimation(fig=machine_gaming.fig, func=machine_gaming.animate_plot, interval=1000, blit=False)

if __name__ == '__main__':
    machine_gaming.run()
