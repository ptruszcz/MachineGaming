import pyvolution as pv
import unittest

# before start copy latest pyvolution.so to the test directory
class pyvolutionTest(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        pv.Neuron.reset_counter()
        pv.Connection.reset_counter()

    def testEvolutionaryAlgorithmParameters(self):
        eap = pv.EvolutionaryAlgorithmParameters
        eap.population_size = 5
        eap.crossover_probability = 0.05
        self.assertEqual(0.05, eap.crossover_probability)
        self.assertEqual(5, eap.population_size)

    def testGetSetFitness(self):
        nn = pv.NeuralNetwork(5, 5, 5)
        nn.fitness = 2.2
        self.assertEqual(2.2, nn.fitness)

    def testFeedForward(self):
        nn = pv.NeuralNetwork(5, 5, 5)
        inp = [1, 2, 3, 4, 5]
        nn.feed_forward(inp)
        self.assertEqual(5, len(nn.get_output()), 'Your NeuralNetwork is bad and you should feel bad!')

    def testGenerationSize(self):
        p = pv.EvolutionaryAlgorithmParameters

        p.population_size = 10
        p.children_bred_per_generation = 2
        p.crossover_probability = 1
        p.mutation_probability = 0.5
        p.randomisation_probability = 0.1
        p.input_size = 2
        p.hidden_layers = 2
        p.output_size = 1

        ea = pv.EvolutionaryAlgorithm(p)
        self.assertEqual(p.population_size, len(ea.get_current_generation()))

        ea.breed()
        self.assertEqual(p.population_size + p.children_bred_per_generation,
                         len(ea.get_current_generation()))

        ea.remove_weakest_individuals()
        self.assertEqual(p.population_size, len(ea.get_current_generation()))

    def testImproveResults(self):
        p = pv.EvolutionaryAlgorithmParameters
        p.population_size = 10
        p.children_bred_per_generation = 5
        p.crossover_probability = 1
        p.mutation_probability = 0.5
        p.randomisation_probability = 0.1
        p.input_size = 2
        p.hidden_layers = 3
        p.output_size = 1

        ea = pv.EvolutionaryAlgorithm(p)
        self.trainXOR(ea.get_current_generation())

        while ea.get_current_generation()[0].fitness < 3.50:
            ea.breed()
            self.trainXOR(ea.get_current_generation())
            ea.remove_weakest_individuals()

            print('Best fit: ' + str(ea.get_current_generation()[0].fitness))

    def trainXOR(self, neural_networks):
        for network in neural_networks:
            if network.fitness == 0:
                fitness = 0

                network.feed_forward([0, 0])
                fitness += 1 - abs(network.get_output()[0])
                print('0 XOR 0 ~' + str(network.get_output()[0]))

                network.feed_forward([0, 1])
                fitness += network.get_output()[0]
                print('0 XOR 1 ~' + str(network.get_output()[0]))

                network.feed_forward([1, 0])
                fitness += network.get_output()[0]
                print('1 XOR 0 ~' + str(network.get_output()[0]))

                network.feed_forward([1, 1])
                fitness += 1 - (abs(network.get_output()[0]))
                print('1 XOR 1 ~' + str(network.get_output()[0]))

                print('Fitness: ' + str(fitness))
                print('--------------')

                network.fitness = fitness

    def testSerialization(self):
        p = pv.EvolutionaryAlgorithmParameters
        p.population_size = 10
        p.children_bred_per_generation = 5
        p.crossover_probability = 1
        p.mutation_probability = 0.5
        p.randomisation_probability = 0.1
        p.input_size = 5
        p.hidden_layers = 5
        p.output_size = 5

        serialized_ea = pv.EvolutionaryAlgorithm(p)
        serialized_ea.save("EvolutionaryAlgorithmPythonTest.mg")

        deserialized_ea = pv.EvolutionaryAlgorithm()
        deserialized_ea.load("EvolutionaryAlgorithmPythonTest.mg")

        serialized_nn = serialized_ea.get_current_generation()
        deserialized_nn = deserialized_ea.get_current_generation()

        input = [1, 1, 1, 1, 1]
        for i in range(p.population_size):
            serialized_nn[i].feed_forward(input)
            deserialized_nn[i].feed_forward(input)

            expected = serialized_nn[i].get_output()
            actual = deserialized_nn[i].get_output()

            self.assertEqual(expected, actual)


if __name__ == '__main__':
    unittest.main()