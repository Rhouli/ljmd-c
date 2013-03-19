"""IO for MyMD package

Handles reading and writing of restart files
""" 
import numpy as np
from cStringIO import StringIO

def read_restart(filename):
    """ Read a MyMD restart file.

    The MyMD restart files contains the atomic
    positions and atomic velocities.

    We would also like to read
        - cell 
        - atomic symbols/masses
    but this information is not contained in the current
    restart file format (design flaw).
    """
    from ase import Atoms, Atom

    f = open(filename)
    lines = f.readlines()

    natoms = len(lines)/2
    atomlist = Atoms()
    i = 0
    for i in range(natoms):
        x,y,z = lines[i].split()
        atomlist += Atom('Ar', position=(x,y,z))
        i = i + 1
        # TODO figure out how to do a nice parsing  

    # Reading velocities
    velocities = []
    for i in range(natoms):
        vx,vy,vz = lines[ i + natoms ].split()
        velocities.append(np.array([vx, vy, vz], dtype=float))
        i = i + 1
    atomlist.set_velocities( np.array(velocities))
    
    f.close()
   
    return atomlist

def read_trajectory(filename):
    from ase import Atoms
    from ase.io.xyz import read_xyz

    # only stores last trajectory apparently
    # need to extend it to read full traj
    atomlist = read_xyz(filename)
    return atomlist


def write_restart(filename, atoms, geometry=None):
    """Write restart info from atoms to file"""

    natoms = len(atoms)
    s = ""
    for pos in atoms.positions:
        s += "{:19.14f}      {:19.14f}      {:19.14f}\n".format(pos[0], pos[1], pos[2])

    for v in atoms.get_velocities():
        #s += "{:19.14f}      {:19.14f}      {:19.14f}\n".format(v[0], v[1], v[2])
        s += "{:19.16e} {:19.16e} {:19.16e}\n".format(v[0], v[1], v[2])

    f = open(filename, 'w')
    f.write(s)
    f.close()
