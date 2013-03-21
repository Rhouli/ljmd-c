/**
 * Pair_LJ: calculation of forces based on Lennard-Jones pair interaction potential
 *
 * @short This function provides forces, based on the Lennard-Jones interaction potential, acting on atoms
 * @authors Aris Marcolongo <XXX@gmail.com>
 */

#include "Pair_LJ.h"
#include "Helper.h"
#include <math.h>
#if defined(_OPENMP)
#include <omp.h>
#endif

void Pair_LJ::ComputeForce(Atoms *atom) 
{
    double epot;
    
#if defined(_OPENMP)
#pragma omp parallel reduction(+:epot)
#endif
    {
        double c12,c6,boxby2,rcsq;
        double *fx, *fy, *fz;
        double *rx, *ry, *rz;
        int i, tid, fromidx, toidx, natoms, nthreads;

        /* precompute some constants */
        c12 = 4.0*epsilon*pow(sigma,12.0);
        c6  = 4.0*epsilon*pow(sigma, 6.0);
        rcsq= atom->GetRadCut() * atom->GetRadCut();
        boxby2 = 0.5*atom->GetBoxSize();
        natoms = atom->GetNAtoms();
        epot = 0.0;
        
        /* let each thread operate on a different
           part of the enlarged force array */
#if defined(_OPENMP)
	nthreads=omp_get_num_threads();
        tid=omp_get_thread_num();
#else
	nthreads=1;
        tid=0;
#endif
        fx=atom->GetForce() + (3*tid*natoms);
        azzero(fx,3*natoms);
        fy=atom->GetForce() + ((3*tid+1)*natoms);
        fz=atom->GetForce() + ((3*tid+2)*natoms);
        rx=atom->GetPosition();
        ry=atom->GetPosition() + natoms;
        rz=atom->GetPosition() + 2*natoms;
	int x;
        /* self interaction of atoms in cell */
        for(i=0; i < atom->GetNCells(); i += nthreads) {
            int j;
	    //            cell_t *c1;
            
            x = i + tid;
            if (j >= (atom->GetNCells())) break;
//            c1=atom->clist + j;
//            afc=getlist(j) 
            for (j=0; j < atom->GetCellIndexSize(x)-1; ++j) {
//	    for (j=0; j < GetCellData()-1; ++j) {  
                int ii,k;
                double rx1, ry1, rz1;		
 //               ii=c1->idxlist[j];
		ii=atom->GetCellIndex(x,j);
		
                rx1=rx[ii];
                ry1=ry[ii];
                rz1=rz[ii];
        
                for(k=j+1; k < atom->GetCellIndexSize(x); ++k) {
                    int jj;
                    double rx2,ry2,rz2,rsq;

		    jj=atom->GetCellIndex(x,k); 
                    /* get distance between particle i and j */
                    rx2=pbc(rx1 - rx[jj], boxby2, atom->GetBoxSize());
                    ry2=pbc(ry1 - ry[jj], boxby2, atom->GetBoxSize());
                    rz2=pbc(rz1 - rz[jj], boxby2, atom->GetBoxSize());
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
        for(i=0; i < atom->GetNPairs(); i += nthreads) {
            int j;
	    //            const cell_t *c1, *c2;

            x = i + tid;
            if (x >= (atom->GetNPairs())) break;
	  
        //    c1=atom->clist + atom->plist[2*x];
        //    c2=atom->clist + atom->plist[2*x+1];
        
            for (j=0; j < atom->GetCellIndexSize(atom->GetPairItem(2*x)); ++j) {
                int ii, k;
                double rx1, ry1, rz1;

                ii=atom->GetCellIndex(atom->GetPairItem(2*x),j);
                rx1=rx[ii];
                ry1=ry[ii];
                rz1=rz[ii];
        
                for(k=0; k < atom->GetCellIndexSize(atom->GetPairItem(2*x+1)); ++k) {
                    int jj;
                    double rx2,ry2,rz2,rsq;
                
                   // jj=c2->idxlist[k];
		    
		    jj = atom->GetCellIndex(atom->GetPairItem(2*x+1),k);
                    /* get distance between particle i and j */
                    rx2=pbc(rx1 - rx[jj], boxby2, atom->GetBoxSize());
                    ry2=pbc(ry1 - ry[jj], boxby2, atom->GetBoxSize());
                    rz2=pbc(rz1 - rz[jj], boxby2, atom->GetBoxSize());
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
        i = 1 + (3*natoms / nthreads);
        fromidx = tid * i;
        toidx = fromidx + i;
        if (toidx > 3*natoms) toidx = 3*natoms;

        /* reduce forces from threads with tid != 0 into
           the storage of the first thread. since we have
           threads already spawned, we do this in parallel. */
        for (i=1; i < nthreads; ++i) {
            int offs, j;

            offs = 3*i*natoms;

            for (j=fromidx; j < toidx; ++j) {
  //              atom->frc[j] += atom->frc[offs+j];
		atom->SetForce(j,atom->GetForce(j)+atom->GetForce(offs+j)); 
            }
        }
    }
    atom->SetPotEnergy(epot);
}


