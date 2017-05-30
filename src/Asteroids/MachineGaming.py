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

style.use('ggplot')


def run_game():
    current_game_thread.start()
    return


class MachineGaming(tk.Tk):
    def __init__(self):
        tk.Tk.__init__(self)
        self.root = tk.Frame(self)
        self.current_game_time = 0.0
        self.x = []
        self.y = []
        self.fig = Figure(figsize=(5, 5), dpi=100)
        self.curr_score = self.fig.add_subplot(2, 1, 1)
        self.mean_gen_score = self.fig.add_subplot(2, 1, 2)

        self.root.grid_rowconfigure(0, weight=1)
        self.root.grid_columnconfigure(0, weight=1)
        self.add_buttons()
        self.add_stats()
        self.add_plot()

    def add_buttons(self):
        start_button = tk.Button(self, text='START', command=run_game)
        start_button.grid(row=0, column=0, sticky='nw')

        pause_button = tk.Button(self, text='PAUSE')
        pause_button.grid(row=0, column=1, sticky='nw')

        save_button = tk.Button(self, text='SAVE')
        save_button.grid(row=1, column=0, sticky='nw')

        load_button = tk.Button(self, text='LOAD')
        load_button.grid(row=1, column=1, sticky='nw')

        new_button = tk.Button(self, text='NEW')
        new_button.grid(row=2, column=0, sticky='nw')

        exit_button = tk.Button(self, text='EXIT', command=self._quit)
        exit_button.grid(row=2, column=1, sticky='nw')

    def add_stats(self):
        label_frame = tk.LabelFrame(self, text='Statistics')
        label_frame.grid(row=0, column=3, rowspan=3, columnspan=2)

        current_generation_label = tk.Label(label_frame, text='Current generation: ')
        current_generation_label.pack(anchor='nw')

        current_fitness_label = tk.Label(label_frame, text='Current fitness: ')
        current_fitness_label.pack(anchor='nw')

        neuron_layers_label = tk.Label(label_frame, text='Neuron layers: ')
        neuron_layers_label.pack(anchor='nw')

        input_label = tk.Label(label_frame, text='Input: ')
        input_label.pack(anchor='nw')

        output_label = tk.Label(label_frame, text='Output button: ')
        output_label.pack(anchor='nw')

    def add_plot(self):
        canvas = FigureCanvasTkAgg(self.fig, self)
        canvas.show()
        canvas.get_tk_widget().grid(row=3, column=0, columnspan=4)

    def animate_plot(self, i):
        if current_game.running:
            self.x.append(self.current_game_time)
            self.y.append(current_game.score)
            self.curr_score.clear()
            self.curr_score.plot(self.x, self.y)
            self.current_game_time += 1.0
        else:
            self.current_game_time = 0.0

    def run(self):
        self.mainloop()

    def _quit(self):
        self.quit()     # stops mainloop
        self.destroy()  # this is necessary on Windows to prevent Fatal Python Error

current_game = GameWindow()
machine_gaming = MachineGaming()
current_game_thread = threading.Thread(target=current_game.run)
animFunc = animation.FuncAnimation(fig=machine_gaming.fig, func=machine_gaming.animate_plot, interval=1000)

if __name__ == '__main__':
    machine_gaming.run()
