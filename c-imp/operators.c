#include <math.h>
#include "element.h"

/*
 * Each of these functions takes two elements as input
 * and returns one element. This is the standard interface.
 */

element_t add(element_t e1, element_t e2){
    double v1, v2, v3, d1, d2, d3;
    v1 = e1.value;
    v2 = e2.value;
    d1 = e1.delta;
    d2 = e2.delta;

    v3 = v2 + v1;

    //square root of sum of squares
    d3 = pow( (pow(d1,2.0) + pow(d2,2.0)), 0.5);

    element_t e3 = {};
    e3 = eset(e3, v3, d3);
    return e3;
}

element_t sub(element_t e1, element_t e2){
    double v1, v2, v3, d1, d2, d3;
    v1 = e1.value;
    v2 = e2.value;
    d1 = e1.delta;
    d2 = e2.delta;

    v3 = v2 - v1;

    //square root of sum of squares
    d3 = pow( (pow(d1,2.0) + pow(d2,2.0)), 0.5);

    element_t e3 = {};
    e3 = eset(e3, v3, d3);
    return e3;
}
