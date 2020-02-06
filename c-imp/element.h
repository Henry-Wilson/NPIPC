typedef struct element element_t;

struct element{
    double value;
    double delta;
};

//Sets the members of elt
element_t eset(element_t elt, double v, double d);
//Fills v and d with the members of elt
/*
 * element_t eget(element_t elt, double v, double* d);
 */
