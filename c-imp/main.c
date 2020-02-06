#include <stdio.h>

#include "element.h"
#include "operators.h"

void main(){
    element_t e1 = {};
    element_t e2 = {};
    double v1, v2, d1, d2;
    v1 = 1.0;
    v2 = 2.0;
    d1 = 0.03;
    d2 = 0.04;
    e1 = eset(e1, v1, d1);
    e2 = eset(e2, v2, d2);

    element_t e3 = {};
    e3 = add(e1, e2);
    printf("Value and delta of e3 are: %lf, %lf.\n", e3.value, e3.delta);
}
