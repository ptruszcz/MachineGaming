import pyvolution as pv

## @brief Class reponsible for Evolutionary Algorithm management.
#  Class that is responsible for creating, managing and calling methods on EvolutionaryAlgorithm class.
#  Contains handles for NeuralNetwork and EvolutionaryAlgorithm objects.
class MachineGamingController:

    ## @brief Constructor
    #  @params stats_window window that present statistics to the user - GUI.
    def __init__(self, stats_window):
        self.stats_window = stats_window
        self.input_size = 0
        self.neural_network = None
        self.ea = None

    ## @brief Creates new EvolutionaryAlgorithm instance
    ## Creates new EvolutionaryAlgorithm instance based on parameters passed to the method.
    def initialize_ea(self, parameters):
        p = pv.EvolutionaryAlgorithmParameters
        p.population_size = int(parameters[0])
        p.children_bred_per_generation = int(parameters[1])
        p.crossover_probability = float(parameters[2])
        p.mutation_probability = float(parameters[3])
        p.hidden_layers = int(parameters[4])
        p.input_size = 13
        p.output_size = 5
        p.weight_variance = float(parameters[5])
        self.ea = pv.EvolutionaryAlgorithm(p)
        self.input_size = p.input_size
        self.process()

    ## @brief Gets current network number.
    #  @return current network number.
    def get_current_network(self):
        return self.ea.get_current_network()

    ## @brief Gets current generation number.
    #  @return current generation number.
    def get_current_generation(self):
        return self.ea.get_current_generation()

    ## @brief Shifts to the next neural network.
    #  Shifts handle of the currently trained neural network to next network in the generation.
    def process(self):
        self.neural_network = self.ea.get_next()

    ## @brief Saves current state of the algorithm.
    #  Saves current algorithm state, parameters and current population to file.
    #  @return true operation succeeded, returns false otherwise
    def save(self, path):
        if self.ea:
            self.ea.save(path)
            return True
        else:
            return False

    ## @brief Loads algorithm from file.
    #  Loads algorithm state, parameters and current population from file.
    #  @return true if operation succeeded, parameters of the loaded algorithm
    def load(self, filename):
        self.ea = pv.EvolutionaryAlgorithm()
        self.ea.load(filename)
        parameters = [self.ea.get_population_size(), self.ea.get_children_bred_per_generation(),
                      self.ea.get_crossover_probability(), self.ea.get_mutation_probability(),
                      self.ea.get_hidden_layers(), self.ea.get_weight_variance()]
        self.process()
        return True, parameters
