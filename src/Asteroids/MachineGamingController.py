import pyvolution as pv


class MachineGamingController:
    def __init__(self):
        self.ea = None

    def initialize_EA(self, entries):
        p = pv.EvolutionaryAlgorithmParameters
        p.population_size = int(entries[0].get())
        p.children_bred_per_generation = int(entries[1].get())
        p.crossover_probability = float(entries[2].get())
        p.mutation_probability = float(entries[3].get())
        p.randomisation_probability = float(entries[4].get())
        p.input_size = 2
        p.hidden_layers = int(entries[5].get())
        p.output_size = 1
        self.ea = pv.EvolutionaryAlgorithm(p)

    def save(self, filename):
        if self.ea:
            self.ea.save(filename)
        else:
            print('Evolutionary Algorithm has not been created yet!')  # TODO: find better way of signalizing

    def load(self, filename):
        print('Not implemented yet.')