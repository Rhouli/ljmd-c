"""This package defines an ASE interface to MyMD

MyMD is an educational project, written during the 2013
Workshop on Computer Programming and Advanced Tools for Scientific Research Work
at ICTP Trieste, Italy.
"""

import os
import sys
import subprocess

import numpy as np

from ase.atoms import Atoms
from ase.calculators.calculator import FileIOCalculator, Parameters, ReadError

import potentials
import io

class FileIOMyMD(FileIOCalculator):
    """ ASE calculator for MyMD

    The standard class members used by FileIOCalculator are
    
        state               ase.Atoms object with current positions/velocities
        results             Results of calculation
        parameters          Input parameters
        command             Command to execute binary

    Specific for this calculator are

        parameters.potentials   Potentials used to calculate forces
        parameters.nstep        Number of MD steps to calculate
        parameters.dt           MD time step
        parameters.nprint       Stride for printing atomic positions
        parameters.task         what we are supposed to be calculating
        parameters.restart      name of restart file

     """

    # TODO: implement 'energy', 'forces'
    notimplemented = ['stress',  'dipole', 'magmom', 'magmoms']
    command = 'ljmd-serial.x < PREFIX.inp | tee PREFIX.out'

    default_parameters = dict(
        potentials=[potentials.LJPotential()],
        nstep=10000,
        dt=5.0,
        nprint=100,
        task='md',
        geometry='nocenter noautosym',
        raw='',
        restart=None,
    ) 

    def __init__(self, restart=None, ignore_bad_restart_file=False,
                 label='mymd', atoms=None, **kwargs):
        """Construct MyMD-calculator object.
        
        Parameters
            restart         STRING     
                Restart file, from which to read atomic positions and velocities
            label           STRING
                Label for files to be written by calculator. All files will be
                named <label>.<ext> where <ext> can be '.inp', '.rest', 'traj'
            atoms           ase.atoms.Atoms
                Atoms on which to perform the calculation.
        """

        # If restart is set, this method will call self.read(restart)
        # and take care of stuffing **kwarks into self.parameters
        FileIOCalculator.__init__(self, restart, ignore_bad_restart_file,
                                  label, atoms, **kwargs)

        if restart:
            self.parameters.restart = restart
        else:
            self.parameters.restart = self.label + '.rest'


    def set_atoms(self, atoms):
        """ Updates atoms with self.atoms
        
        This method is called by ase.atoms.Atoms.set_calculator,
        enabling the calculator to update atoms.
        """
        if self.state:
            atoms = self.state
    
    def set(self, **kwargs):
        changed_parameters = FileIOCalculator.set(self, **kwargs)
        if changed_parameters:
            self.reset()
    
    def calculate(self, atoms, properties=None, system_changes=None):
        """ Run MD calculation on atoms.

        atoms: ase.atoms.Atoms object
            Contains positions, unit-cell, ...
        properties: list of str
            List of what needs to be calculated.  Can be any combination
            of 'energy', 'forces', 'md'
        system_changes: list of str
            List of what has changed since last calculation.  Can be
            any combination of these five: 'positons', 'numbers', 'cell',
            'pbc' and 'magmoms'.

        """
        
        self.write_input(atoms, properties, system_changes)
        io.write_restart(self.parameters.restart, atoms)

        if self.command is None:
            raise RuntimeError('Please set $%s environment variable ' %
                               ('ASE_' + self.name.upper() + '_COMMAND') +
                               'or supply the command keyword')
        
        command = self.command.replace('PREFIX', self.prefix)
        olddir = os.getcwd()
        try:
            os.chdir(self.directory)
            print "Executing: {} ".format(command)
            errorcode = subprocess.call(command, shell=True)
            # Might choose to move to the more powerful Popen() class
            #proc = subprocess.Popen(command)
            #proc.communicate()
        finally:
            os.chdir(olddir)
        
        if errorcode:
            s  = '%s returned error %d upon executing\n' % (self.name, errorcode)
            s += command
            raise RuntimeError(s)
        
        # TODO: restart should be written by the binary
        # when this is in place, the state of the atoms can be updated here
        #self.state = io.read_restart(self.parameters.restart)
        
        self.read_results()
    

    def check_state(self, atoms):
        system_changes = FileIOCalculator.check_state(self, atoms)
        return system_changes

    def input_string(self, atoms=None, properties=None, system_changes=None):
        """Return input string readable by executable"""
        
        p = self.parameters
        # For the moment, we just have one kind of potential
        ljpot = p.potentials[0]
        
        # For the moment, we only have one kind of atom
        mlist = atoms.get_masses()
        if np.min(mlist) < 0.999 * np.max(mlist):
            s = "Different masses detected.\n"
            s+= "Currently, only a single kind of atom is supported."
            raise RuntimeError(s)

        if p.restart:
            restart = p.restart
        else:
            p.restart = self.label + '.rest'

        s  = ""
        s += "{:<18d}# number of atoms\n".format(len(atoms))
        s += "{:<18f}# atomic mass [AMU]\n".format(atoms[0].mass)
        s += "{:<18f}# LJ-epsilon [kcal/mol]\n".format(ljpot.epsilon)
        s += "{:<18f}# LJ-sigma [kcal/mol]\n".format(ljpot.sigma)
        s += "{:<18f}# LJ-cutoff radius [kcal/mol]\n".format(ljpot.rcut)
        s += "{:<18f}# box length [Angstroms]\n".format(self.get_box_length(atoms.cell))
        s += "{:<18s}# restart filename\n".format(p.restart)
        s += "{:<18s}# trajectory filename\n".format(self.label + '.xyz')
        s += "{:<18s}# energies filename\n".format(self.label + '.dat')
        s += "{:<18d}# nr of MD steps\n".format(p.nsteps)
        s += "{:<18f}# MD time step\n".format(p.dt)
        s += "{:<18d}# trajectory print stride".format(p.nprint)

        return s

    def write_input(self, atoms, properties=None, system_changes=None):
        FileIOCalculator.write_input(self, atoms, properties, system_changes)
       
        s = self.input_string(atoms, properties, system_changes) 
        f = open(self.label + '.inp', 'w')
        f.write(s)
        f.close()
       
        # writing parameters using built-in ase format
        # TODO: Cannot write objects such as LJPotential
        self.parameters.write(self.label + '.ase')


    def read_input(self,label):
        import io
        # TODO: make it take an arbitrary input filename
        # and generate the objects
        self.label = label
        
        # If the input was generated by ASE, it is simple
        if False and os.path.isfile(self.label + '.ase'):
            self.parameters = Parameters.read(self.label + '.ase')
        else:
            if not os.path.isfile(self.label + '.inp'):
                raise ReadError
            f = open(self.label + '.inp')
            s = f.readlines()

            parse = self.parse_line
           
            natoms  = int  ( parse(s[0]) )
            mass    = float( parse(s[1]) )
            epsilon = float( parse(s[2]) )
            sigma   = float( parse(s[3]) )
            rcut    = float( parse(s[4]) )
            box     =        parse(s[5])
            restfile=        parse(s[6]) 
            trajfile=        parse(s[7])
            enerfile=        parse(s[8]) 
            nsteps  = int  ( parse(s[9]) )
            dt      = float( parse(s[10]) )
            nprint  = int  ( parse(s[11]) )
            # TODO: start parsing the format...

        atoms = io.read_restart(label + '.rest')

        if len(atoms) != natoms:
            s = "natoms = {} from {} does not match with\n".\
                    format(natoms, self.label + '.inp')
            s = "natoms = {} from restart file {}".\
                    format(len(atoms), self.label + '.rest')
            raise RuntimeError(s)

        self.potentials = potentials.LJPotential(
                epsilon=epsilon,
                sigma=sigma,
                rcut=rcut)




    def read(self, label):
        """Read results and input from MyMD calculation

        The Calculator API of ASE prescribes this method and states
        that it should read both input and output.
        """
        FileIOCalculator.read(self, label)
        
        self.read_input(label)

        # Here start reading the trajectories etc.
        self.state = Atoms(symbols, positions,
                           magmoms=self.parameters.pop('magmoms'))
        self.read_results()

    def read_results(self):
        data = np.genfromtxt(self.label + '.dat', dtype=float)

        # Think about how to store the
        # full trajectory etc.

        # File format: n, T, EKIN, EPOT, ETOT
        self.niter = data[-1][0]

        self.results['kinetic energy'] = data[-1][2]
        self.results['potential energy'] = data[-1][3]
        self.results['total energy'] = data[-1][4]


    def get_box_length(self, cell):
        """Returns box length for cubic cell"""
        if len(cell) == 3:
            scp = np.dot(cell[0],cell[0])
            return np.sqrt(scp)
        else:
            raise RuntimeError("Unknown cell type")

    def parse_line(self, string):
        return (string.split(' '))[0]


    def get_potential_energy(self, atoms):
        return self.get_property('potential energy', atoms)
    
    def get_md(self, atoms):
        self.resultsenergy = self.get_property('md', atoms)



