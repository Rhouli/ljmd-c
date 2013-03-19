/**
 * Header of the Helper 
 *
 * @short This class provides a variety of helper functions
 * @authors Ryan Houlihan <ryan.houliha90@gmail.com>
 */


/**
 * read a line and then return
 *  the first string with whitespace stripped off
 * @param Pointer to a FILE
 * @param Pointer to a char buffer
 * @return void
 */
static int get_a_line(FILE *fp, char *buf)
{
    char tmp[BLEN], *ptr;

    /* read a line and cut of comments and blanks */
    if (fgets(tmp,BLEN,fp)) {
        int i;

        ptr=strchr(tmp,'#');
        if (ptr) *ptr= '\0';
        i=strlen(tmp); --i;
        while(isspace(tmp[i])) {
            tmp[i]='\0';
            --i;
        }
        ptr=tmp;
        while(isspace(*ptr)) {++ptr;}
        i=strlen(ptr);
        strcpy(buf,tmp);
        return 0;
    } else {
        perror("problem reading input");
        return -1;
    }
    return 0;
}

/**
 * Zero out an array
 * @param Pointer to an array
 * @param size of an array
 * @return void
 */
__attribute__((always_inline))
static void azzero(double *d, const int n)
{
    int i;
    for (i=0; i<n; ++i) {
        d[i]=0.0;
    }
}

/**
 * Apply minimum image convention
 * @param Double value
 * @param double matrix of box X 2
 * @param double value of box
 * @return The modified double which was given as the first parameter
 */
__attribute__((always_inline,pure))
static double pbc(double x, const double boxby2, const double box)
{
    while (x >  boxby2) x -= box;
    while (x < -boxby2) x += box;
    return x;
}
