#include <stdlib.h>
#include <gaussian.h>

int main(void){
    double v[5] = {1, 2, 3, 4, 5};
    double* gf = gaussian_filter1d(v, 5, 1);
    printd(gf, 5);
    free(gf);

    return 0;
}