"""Classes defining the properties of the integrator

...
"""

class Integrator:
    def __init__(self, nsteps, dt, nprint):
        self.nsteps = nsteps
        self.dt = dt
        self.nprint = nprint


#class VelocityVerlet:
