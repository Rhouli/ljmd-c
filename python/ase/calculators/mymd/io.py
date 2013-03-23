"""IO for MyMD package

Handles reading and writing of restart files
"""
import numpy as np
from cStringIO import StringIO
from ase.atoms import Atoms
from ase.parallel import paropen


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

    natoms = len(lines) / 2
    atomlist = Atoms()
    i = 0
    for i in range(natoms):
        x, y, z = lines[i].split()
        atomlist += Atom('Ar', position=(x, y, z))
        i = i + 1
        # TODO figure out how to do a nice parsing

    # Reading velocities
    velocities = []
    for i in range(natoms):
        vx, vy, vz = lines[i + natoms].split()
        velocities.append(np.array([vx, vy, vz], dtype=float))
        i = i + 1
    atomlist.set_velocities(np.array(velocities))

    f.close()

    return atomlist


def write_restart(filename, atoms, geometry=None):
    """Write restart info from atoms to file"""

    natoms = len(atoms)
    s = ""
    for pos in atoms.positions:
        s += "{:19.14f}      {:19.14f}      {:19.14f}\n".format(
            pos[0], pos[1], pos[2])

    for v in atoms.get_velocities():
        # s += "{:19.14f}      {:19.14f}      {:19.14f}\n".format(v[0], v[1],
        # v[2])
        s += "{:19.16e} {:19.16e} {:19.16e}\n".format(v[0], v[1], v[2])

    f = open(filename, 'w')
    f.write(s)
    f.close()


def read_xyz(fileobj, index=None):
    """ Reads a trajectory from an xyz file.

    This function returns a list of ase.atoms.Atoms objects.
    The original ase.io.xyz.read_xyz function was only capable
    of returning a single Atoms object.
    """
    if isinstance(fileobj, str):
        fileobj = open(fileobj)

    lines = fileobj.readlines()
    L1 = lines[0].split()
    if len(L1) == 1:
        del lines[:2]
        natoms = int(L1[0])
    else:
        natoms = len(lines)

    images = []
    while len(lines) >= natoms:
        positions = []
        symbols = []
        for line in lines[:natoms]:
            symbol, x, y, z = line.split()[:4]
            symbol = symbol.lower().capitalize()
            symbols.append(symbol)
            positions.append([float(x), float(y), float(z)])
        images.append(Atoms(symbols=symbols, positions=positions))
        del lines[:natoms + 2]

    if index is None:
        return images
    else:
        return images[index]


def read_trajectory(filename):
    return read_xyz(filename)
