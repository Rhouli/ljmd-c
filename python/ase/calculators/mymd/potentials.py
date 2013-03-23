"""Input parameters for potentials

Defines the required input parameters for
different kinds of potentials.
"""


class PairPotential:
    def __init__(self):
        pass

    def __str__(self):
        return "Abstract pair potential class."


class LJPotential(PairPotential):
    def __init__(self, epsilon=0.2379, sigma=3.405, rcut=8.5):
        self.epsilon = epsilon
        self.sigma = sigma
        self.rcut = rcut

    def __str__(self):
        s = "Lennard-Jones potential with \
             epsilon={}, sigma={} and rcut={}".format(
            self.epsilon,
            self.sigma,
            self.rcut,
        )
        return s
