import pyvolution as pv


class MachineGamingController:
    def __init__(self, stats_window):
        self.stats_window = stats_window
        self.neural_network = None
        self.ea = None

    def initialize_ea(self, entries):
        p = pv.EvolutionaryAlgorithmParameters
        p.population_size = int(entries[0].get())
        p.children_bred_per_generation = int(entries[1].get())
        p.crossover_probability = float(entries[2].get())
        p.mutation_probability = float(entries[3].get())
        p.hidden_layers = int(entries[4].get())
        p.input_size = 16
        p.output_size = 5
        p.weight_variance = float(entries[5].get())
        self.ea = pv.EvolutionaryAlgorithm(p)
        self.process()

    def current_network(self):
        return self.ea.current_network()

    def current_generation(self):
        return self.ea.current_generation()

    def process(self):
        self.neural_network = self.ea.get_next()

    def save(self, filename):
        if self.ea:
            self.ea.save(filename)
        else:
            print('Evolutionary Algorithm has not been created yet!')  # TODO: find better way of signalizing

    def load(self, filename):
        print('Not implemented yet.')
