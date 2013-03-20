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
calc  = mymd.MyMD(label='mymd',
                  nsteps=10000,
                  dt=2.0,
                  nprint=100)
myatoms.set_calculator(calc)

# Get the total energy at the end of the run
etot = myatoms.get_total_energy()
print "The total energy is {} [unit] per atom".format(etot/len(myatoms))

# If the pygtk module is available, you can use the
# built-in ASE viewer to visualize the atoms

#from ase.visualize import view
#view(myatoms)
