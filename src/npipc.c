/*
 * NPIPC Implementation
 * Complies with API in npipc.h
 */

#include <math.h> //sqrt
#include <stdlib.h> //malloc, free
#include <string.h> //strcpy, strcat
#include <stdio.h> //snprintf

//#define TESTER

#ifdef TESTER
#include <time.h> //Runtime measurement
#endif /* TESTER */

#include "npipc.h" //NPIPC API

int stack_top = -1;

/*
 * Put a new entry on the top of the stack
 */
void append_entry(double v, double d){
    //create
    entry e;
    e.value = v;
    e.delta = d;
    //append
    stack[stack_top+1] = e;
    stack_top = stack_top + 1;
}

/*
 * Add the top two entries and put the result on the stack
 */
void add(){
    //retrieve
    entry e1;
    e1.value = stack[stack_top].value;
    e1.delta = stack[stack_top].delta;
    stack_top = stack_top - 1;
    entry e2;
    e2.value = stack[stack_top].value;
    e2.delta = stack[stack_top].delta;
    stack_top = stack_top - 1;
    //create
    double e3value = e2.value + e1.value; //e2 comes first. ALWAYS.
    double e3delta = sqrt(e2.delta * e2.delta + e1.delta * e1.delta); //sqrt sum sqr
    //append
    append_entry(e3value, e3delta);
}

/*
 * Subtract the top two entries and put the result on the stack
 */
void sub(){
    //retrieve
    entry e1;
    e1.value = stack[stack_top].value;
    e1.delta = stack[stack_top].delta;
    stack_top = stack_top - 1;
    entry e2;
    e2.value = stack[stack_top].value;
    e2.delta = stack[stack_top].delta;
    stack_top = stack_top - 1;
    //create
    double e3value = e2.value - e1.value; //e2 comes first. ALWAYS.
    double e3delta = sqrt( (e2.delta * e2.delta) + (e1.delta * e1.delta) ); //sqrt sum sqr
    //append
    append_entry(e3value, e3delta);
}

/*
 * Multiply the top two entries and put the result on the stack
 */
void mul(){
    //retrieve
    entry e1;
    e1.value = stack[stack_top].value;
    e1.delta = stack[stack_top].delta;
    stack_top = stack_top - 1;
    entry e2;
    e2.value = stack[stack_top].value;
    e2.delta = stack[stack_top].delta;
    stack_top = stack_top - 1;
    //create
    double e3value = e2.value * e1.value;
    double e3delta = sqrt( ((e2.delta * e2.delta) / (e2.value * e2.value)) +
                           ((e1.delta * e1.delta) / (e1.value * e1.value)) )
                           * e3value;
    //append
    append_entry(e3value, e3delta);
}

/*
 * Divide the top two entries and put the result on the stack
 */
void quo(){
    //retrieve
    entry e1;
    e1.value = stack[stack_top].value;
    e1.delta = stack[stack_top].delta;
    stack_top = stack_top - 1;
    entry e2;
    e2.value = stack[stack_top].value;
    e2.delta = stack[stack_top].delta;
    stack_top = stack_top - 1;
    //create
    double e3value = e2.value / e1.value;
    double e3delta = sqrt( ((e2.delta * e2.delta) / (e2.value * e2.value)) +
                           ((e1.delta * e1.delta) / (e1.value * e1.value)) )
                           * e3value;
    //append
    append_entry(e3value, e3delta);
}

/*
 * Destroy the top entry of the stack
 */
void kill(){
    stack_top = stack_top - 1;
}

/*
 * Empty the stack completely
 */
void clear(){
    stack_top = -1;
}

void swap(){
    //retrieve
    entry e1;
    e1.value = stack[stack_top].value;
    e1.delta = stack[stack_top].delta;
    entry e2;
    e2.value = stack[stack_top-1].value;
    e2.delta = stack[stack_top-1].delta;
    stack_top = stack_top - 2;
    append_entry(e1.value, e1.delta);
    append_entry(e2.value, e2.delta);
}

/*
 * Return a char array (string) representation of the top of the stack
 */
void show_two(char* str){
    //setup
    str[0] = '\0'; //reset str
    char* estr = malloc(STR_MAX/4 * sizeof(char)); //entry string
    //retrieve
    entry e1;
    e1.value = stack[stack_top].value;
    e1.delta = stack[stack_top].delta;
    entry e2;
    e2.value = stack[stack_top-1].value;
    e2.delta = stack[stack_top-1].delta;
    //build
    //e2
    strcat(str, "E2: [");
    ent_to_str(estr,e2);
    strcat(str, estr);
    strcat(str, "]");
    //newline
    strcat(str, "\n");
    //e1
    strcat(str, "E1: [");
    ent_to_str(estr,e1);
    strcat(str, estr);
    strcat(str, "]");
    //return
    free(estr);
    return;
}

/*
 * return a string representation of a particular entry
 */
void ent_to_str(char* str, entry e1){
    //setup
    str[0] = '\0'; //reset str
    char *fstr = malloc(STR_MAX/4 * sizeof(char)); //float string
    //build
    snprintf(fstr, STR_MAX/4, "%lf", e1.value); // copy double in
    strcat(str, fstr);
    strcat(str, ", ");
    snprintf(fstr, STR_MAX/4, "%lf", e1.delta);
    strcat(str, fstr);
    //return
    free(fstr);
    return;
}

#ifdef TESTER
/*
 * Testing function
 */
int tester(){
    //setup
    char *string_1 = malloc(STR_MAX * sizeof(char));
    int time = clock(); //start clock cycle
    //test addition
    append_entry(3,0.05);
    append_entry(4,0.05);
    show_two(string_1);
    printf("Before Addition:\n%s\n",string_1);
    add();
    show_two(string_1);
    printf("After Addition:\n%s\n",string_1);
    //test multipilication
    append_entry(3,0.05);
    append_entry(4,0.05);
    show_two(string_1);
    printf("Before Multiplication:\n%s\n",string_1);
    mul();
    show_two(string_1);
    printf("After Multiplication:\n%s\n",string_1);
    //test clear
    clear();
    show_two(string_1);
    printf("After Stack Clear:\n%s\n",string_1);
    //cleanup / return
    free(string_1);
    int end = clock(); //end clock cycle
    printf("RUN TIME: %d CLOCK CYCLES\n", end - time);
    return 0;
}

int main(){
    return tester();
}
#endif /*TESTER*/
