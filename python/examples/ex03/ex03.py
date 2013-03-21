""" Example 03

This example shows how to use the built-in atom viewer
of ASE as well as data visualization with matplotlib.
"""
from ase.lattice.cubic import SimpleCubic
from ase.md.velocitydistribution import MaxwellBoltzmannDistribution
import ase.units as units
import ase.calculators.mymd as mymd

# Set up a cube of 125 Argon atoms in a cube of (15 Angstroms)**3.
myatoms = SimpleCubic('Ar', latticeconstant=3.0, size=(5,5,5))
MaxwellBoltzmannDistribution(myatoms, temp= units.kB * 50)

from ase.visualize import view
view(myatoms)


# Set up MyMD calculator and run
calc  = mymd.FileIOMyMD(label='mymd',
                  nsteps=10000,
                  dt=2.0,
                  nprint=100)
calc.run_md(myatoms)

# View final state of the atoms
view(calc.state)

# View trajectory of the atoms
trajectory = calc.frames.collect('atoms')
view(trajectory)

# Visualize data using matplotlib
import matplotlib.pyplot as plt

n    = calc.frames.collect('index')
ekin = calc.frames.collect('ekin')
epot = calc.frames.collect('epot')
etot = calc.frames.collect('etot')

plt.plot(n,epot, label='Potential Energy []')
plt.plot(n,ekin, label='Kinetic Energy []')
plt.plot(n,etot, label='Total Energy []')
plt.legend()

plt.show()
