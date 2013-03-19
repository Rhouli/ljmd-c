""" Example 02

This example demonstrates how to restart a previous
MyMD calculation.
"""
import ase.calculators.mymd as mymd
import ase.atoms as atoms

# Reading atomic positions and velocities
myatoms = mymd.io.read_restart('argon_108.rest')
# Restart does not contain cell
box = 17.158
myatoms.set_cell([box, box, box])

# Set up calculator
calc  = mymd.MyMD(label='mymd',
                  nsteps=10000,
                  dt=5.0,
                  nprint=100)
myatoms.set_calculator(calc)


# run calculator and save the total energy
# at the end of the run
etot = myatoms.get_total_energy()
print "The total energy is {} [unit] per atom".format(etot/len(myatoms))

