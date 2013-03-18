"""Different pair potentials

"""



class PairPotential:
    def __init__(self):
        pass

    def __str__(self):
        print("Abstract pair potential class.")

class LJPot(PairPotential):
    def __init__(self, epsilon, sigma, rcut):
        self.epsilon = epsilon
        self.sigma = sigma
        self.rcut = rcut
    
    def __str__(self):
        print("Lennard-Jones potential.")
