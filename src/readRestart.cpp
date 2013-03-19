void MyMD::readRestart() {

/* read restart */
    fp=fopen(restfile,"r");
    if(fp) {
        int natoms;
        natoms=sys.natoms;

        for (i=0; i<natoms; ++i) {
            fscanf(fp,"%lf%lf%lf",sys.pos+i, sys.pos+natoms+i, sys.pos+2*natoms+i);
        }
        for (i=0; i<natoms; ++i) {
            fscanf(fp,"%lf%lf%lf",sys.vel+i, sys.vel+natoms+i, sys.vel+2*natoms+i);
        }
        fclose(fp);
        azzero(sys.frc, 3*sys.nthreads*sys.natoms);
    } else {
        perror("cannot read restart file");
        return 3;
    }

}
