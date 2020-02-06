#include "element.h"

element_t eset(element_t elt, double v, double d){
    elt.value = v;
    elt.delta = d;
    return elt;
}

/*
element_t eget(element_t elt, double v, double d){
    v = elt.value;
    d = elt.delta;
    return elt;
}
*/
