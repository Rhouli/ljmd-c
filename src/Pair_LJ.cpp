/**
 * Pair_LJ: calculation of forces based on Lennard-Jones pair interaction potential
 *
 * @short This function provides forces, based on the Lennard-Jones interaction potential, acting on atoms
 * @authors Aris Marcolongo <XXX@gmail.com>
 */

#include "Pair_LJ.h"

#if defined(_OPENMP)
#include <omp.h>
#endif

/* construction */
Pair_LJ::Pair_LJ(){
	Pair_LJ(double e, double s) {
		epsilon=e;
		sigma=s;
	}

static void Pair_LJ::ComputeForce(Atom *sys) 
{
    double epot;

    epot = 0.0;
    
#if defined(_OPENMP)
#pragma omp parallel reduction(+:epot)
#endif
    {
        double c12,c6,boxby2,rcsq;
        double *fx, *fy, *fz;
        const double *rx, *ry, *rz;
        int i, tid, fromidx, toidx, natoms;

        /* precompute some constants */
        c12 = 4.0*epsilon*pow(sigma,12.0);
        c6  = 4.0*epsilon*pow(sigma, 6.0);
        rcsq= sys->rcut * sys->rcut;
        boxby2 = 0.5*sys->box;
        natoms = sys->natoms;
        epot = 0.0;
        
        /* let each thread operate on a different
           part of the enlarged force array */
#if defined(_OPENMP)
        tid=omp_get_thread_num();
#else
        tid=0;
#endif
        fx=sys->frc + (3*tid*natoms);
        azzero(fx,3*natoms);
        fy=sys->frc + ((3*tid+1)*natoms);
        fz=sys->frc + ((3*tid+2)*natoms);
        rx=sys->pos;
        ry=sys->pos + natoms;
        rz=sys->pos + 2*natoms;

        /* self interaction of atoms in cell */
        for(i=0; i < sys->ncell; i += sys->nthreads) {
            int j;
            const cell_t *c1;

            j = i + tid;
            if (j >= (sys->ncell)) break;
            c1=sys->clist + j;

            for (j=0; j < c1->natoms-1; ++j) {
                int ii,k;
                double rx1, ry1, rz1;

                ii=c1->idxlist[j];
                rx1=rx[ii];
                ry1=ry[ii];
                rz1=rz[ii];
        
                for(k=j+1; k < c1->natoms; ++k) {
                    int jj;
                    double rx2,ry2,rz2,rsq;

                    jj=c1->idxlist[k];

                    /* get distance between particle i and j */
                    rx2=pbc(rx1 - rx[jj], boxby2, sys->box);
                    ry2=pbc(ry1 - ry[jj], boxby2, sys->box);
                    rz2=pbc(rz1 - rz[jj], boxby2, sys->box);
                    rsq = rx2*rx2 + ry2*ry2 + rz2*rz2;

                    /* compute force and energy if within cutoff */
                    if (rsq < rcsq) {
                        double r6,rinv,ffac;

                        rinv=1.0/rsq;
                        r6=rinv*rinv*rinv;
                    
                        ffac = (12.0*c12*r6 - 6.0*c6)*r6*rinv;
                        epot += r6*(c12*r6 - c6);

                        fx[ii] += rx2*ffac;
                        fy[ii] += ry2*ffac;
                        fz[ii] += rz2*ffac;
                        fx[jj] -= rx2*ffac;
                        fy[jj] -= ry2*ffac;
                        fz[jj] -= rz2*ffac;
                    }
                }
            }
        }    

        /* interaction of atoms in different cells */
        for(i=0; i < sys->npair; i += sys->nthreads) {
            int j;
            const cell_t *c1, *c2;

            j = i + tid;
            if (j >= (sys->npair)) break;
            c1=sys->clist + sys->plist[2*j];
            c2=sys->clist + sys->plist[2*j+1];
        
            for (j=0; j < c1->natoms; ++j) {
                int ii, k;
                double rx1, ry1, rz1;

                ii=c1->idxlist[j];
                rx1=rx[ii];
                ry1=ry[ii];
                rz1=rz[ii];
        
                for(k=0; k < c2->natoms; ++k) {
                    int jj;
                    double rx2,ry2,rz2,rsq;
                
                    jj=c2->idxlist[k];
                
                    /* get distance between particle i and j */
                    rx2=pbc(rx1 - rx[jj], boxby2, sys->box);
                    ry2=pbc(ry1 - ry[jj], boxby2, sys->box);
                    rz2=pbc(rz1 - rz[jj], boxby2, sys->box);
                    rsq = rx2*rx2 + ry2*ry2 + rz2*rz2;
                
                    /* compute force and energy if within cutoff */
                    if (rsq < rcsq) {
                        double r6,rinv,ffac;

                        rinv=1.0/rsq;
                        r6=rinv*rinv*rinv;
                    
                        ffac = (12.0*c12*r6 - 6.0*c6)*r6*rinv;
                        epot += r6*(c12*r6 - c6);

                        fx[ii] += rx2*ffac;
                        fy[ii] += ry2*ffac;
                        fz[ii] += rz2*ffac;
                        fx[jj] -= rx2*ffac;
                        fy[jj] -= ry2*ffac;
                        fz[jj] -= rz2*ffac;
                    }
                }
            }
        }

        /* before reducing the forces, we have to make sure 
           that all threads are done adding to them. */
#if defined (_OPENMP)
#pragma omp barrier
#endif
        /* set equal chunks of index ranges */
        i = 1 + (3*natoms / sys->nthreads);
        fromidx = tid * i;
        toidx = fromidx + i;
        if (toidx > 3*natoms) toidx = 3*natoms;

        /* reduce forces from threads with tid != 0 into
           the storage of the first thread. since we have
           threads already spawned, we do this in parallel. */
        for (i=1; i < sys->nthreads; ++i) {
            int offs, j;

            offs = 3*i*natoms;

            for (j=fromidx; j < toidx; ++j) {
                sys->frc[j] += sys->frc[offs+j];
            }
        }
    }
    sys->epot = epot;
}

}
