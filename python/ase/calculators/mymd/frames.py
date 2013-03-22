""" Provides classes Frame and Frames
"""

from ase.atoms import Atoms

class Frame(object):
    """ A single frame of a molecular dynamics calculation 
    
    A frame can have any combination of the properties
        atoms       positions/velocities of atoms
        temp        temperature
        ekin        kinetic energy
        epot        potential energy
        etot        total energy

    """
    def __init__(self, index=None, atoms=None, temp=None,
             ekin=None, epot=None, etot=None):
        self.index = index
        if atoms is None:
            self.atoms = None
        else:
            self.atoms = atoms.copy()
        self.temp = temp
        self.ekin = ekin
        self.epot = epot
        self.etot = etot

    def has_atoms(self):
        if self.atoms is None:
            return False
        else:
            return True

    def add_atoms(self, atoms):
        """ Add atoms to this frame """
        if self.has_atoms():
            s = "Frame already has atoms."
            raise RuntimeError(s)
        else:
            self.atoms = atoms



class Frames(object):
    """ A collection of frames of a molecular dynamics calculation """
    def __init__(self):
        self.frames = []
        pass
  
    def add(self, frame):
        self.frames.append(frame)
    
    def get(self, index):
        return self.frames[index]


    def __getitem__(self, index):
        return self.frames[index]

    def __len__(self):
        return len(self.frames)

    def collect(self, prop):
        """ Collect properties from frames.

        Properties can be
            'atoms'
            'temp'
            'ekin'
            'epot'
            'etot'
        """
        l = []
        for f in self.frames:
            val = eval('f.' + prop)
            if val is not None:
                l.append(val)
        return l

