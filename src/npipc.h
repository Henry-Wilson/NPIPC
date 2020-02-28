/*
 * Header file to define the interface of the Naive Propagation in Illusory
 * Parallel Calculator (NPIPC). This will not include the user interface, but
 * rather serves as the NPIPC API.
 */
#ifndef NPIPC_H
#define NPIPC_H

struct ent{
    double value;
    double delta;
};

typedef struct ent entry;

#define STR_MAX 512
#define STACK_MAX 16

entry stack[STACK_MAX];
extern int stack_top; //defined in the npipc implementation

void append_entry(double v, double d); //Add a new entry to the stack

void add(); //sum the top two entries
void sub(); //difference the top two entries
void mul(); //product the top two entries
void quo(); //quotient the top two entries

void kill(); //destroy the top entry
void clear(); //clear the stack completely
void swap(); //swap the top two entries

void ent_to_str(char* str, entry e1); //convert entry to string
void show_two(char* str); //convert top of stack to string

#endif /* NPIPC_H */
