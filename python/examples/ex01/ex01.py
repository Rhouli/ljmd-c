""" Example 01

This example demonstrates how to set up a collection
of atoms within ASE and how to use a MyMD calculator
to run a MD simulation on these atoms.
"""

from ase.lattice.cubic import SimpleCubic
from ase.md.velocitydistribution import MaxwellBoltzmannDistribution
import ase.units as units
import ase.calculators.mymd as mymd

# Set up a cube of 125 Argon atoms in a cube of (15 Angstroms)**3.
myatoms = SimpleCubic('Ar', latticeconstant=3.0, size=(5,5,5))

# Randomize velocities
MaxwellBoltzmannDistribution(myatoms, temp= units.kB * 50)

# Set up MyMD calculator
calc  = mymd.FileIOMyMD(label='mymd',
                  nsteps=10000,
                  dt=2.0,
                  nprint=100)

# Run calculation and read results
calc.run_md(myatoms)

# Compare initial with final temperature
temp = calc.frames.collect('temp')

print "Initial temperature: {} K".format(temp[0])
print "Final temperature: {} K".format(temp[1])
