"""Python interface for educational molecular dynamics code 

...
"""

import system
import integrators
import potentials


class MDSimulation:
    def __init__(self, atoms, box, restfile, trajfile, ergfile):
        self.atoms = atoms
        self.box = box
        self.io = system.IO(restfile=restfile,
                            trajfile=trajfile,
                            ergfile=ergfile)

    def run():
        """Calls binary and passes input parameters"""
        pass

