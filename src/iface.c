/*
 * NPIPC User Interface (iface) definition
 */

#include <stdlib.h> //malloc, free
#include <stdio.h> //fgets, printf, sscanf
#include <string.h> //strcpy, memset

#include "iface.h"
#include "npipc.h"

void fetch_user_instruction(){
    printf("NPIPC >>");
    char *ustr = malloc(U_STR_MAX * sizeof(char));
    char *result;
    result = fgets(ustr, U_STR_MAX, stdin);
    if(result == 0){ // null check
        printf("\n%s\n", "EOF REACHED. EXIT.");
        iface_exit = 1;
        free(ustr);
        return;
    }
    decode_user_instruction(ustr);
    free(ustr);
    return;
}

void decode_user_instruction(char *ustr){
    /*
     * The plan:
     * first 3 characters of the user command must be a correctly formatted
     * command string as defined by our header.
     * strcpy those chars into a little buffer,
     * determine which command they correspond to,
     * pass that to executor.
     *
     * If we are appending, there will be extra work: find the value, delta vars.
     */

    //Define and fill code string.
    char code[CODE_STR_MAX];
    for (int i = 0; i < CODE_STR_MAX-1; i = i + 1){
        code[i] = ustr[i];
    }
    code[CODE_STR_MAX-1] = '\0';

    //Some debug prints
    /*
    printf("DECODE: DEBUG: USTR: %s",ustr);
    printf("DECODE: DEBUG: CODE: %s\n",code);
    */

    //declare ic var, if statements to assign
    //declare value and delta in case of append
    ic internal_code;
    double value = 0.0;
    double delta = 0.0;
    if(strcmp(code, "app") == 0 || strcmp(code, "APP") == 0){ //append special
        internal_code = app_c;
        sscanf(ustr, "%*s %lf %lf", &value, &delta);
        //printf("DEBUG: VAL/DEL: %lf, %lf\n", value, delta);
        //find value and delta from string
        //separated by comma, one assumes.
    }

    else if(strcmp(code, "add") == 0 || strcmp(code, "ADD") == 0){ //arithmetic
        internal_code = add_c;
    }
    else if(strcmp(code, "sub") == 0 || strcmp(code, "SUB") == 0){
        internal_code = sub_c;
    }
    else if(strcmp(code, "mul") == 0 || strcmp(code, "MUL") == 0){
        internal_code = mul_c;
    }
    else if(strcmp(code, "div") == 0 || strcmp(code, "DIV") == 0
            || strcmp(code, "quo") == 0 || strcmp(code, "QUO") == 0){
        internal_code = div_c;
    }

    else if(strcmp(code, "kil") == 0 || strcmp(code, "KIL") == 0){ //stack handling
        internal_code = kil_c;
    }
    else if(strcmp(code, "cle") == 0 || strcmp(code, "CLE") == 0
            || strcmp(code, "clr") == 0 || strcmp(code, "CLR") == 0){
        internal_code = clr_c;
    }
    else if(strcmp(code, "sho") == 0 || strcmp(code, "SHO") == 0
            || strcmp(code, "shw") == 0 || strcmp(code, "SHW") == 0){
        internal_code = shw_c;
    }
    else if(strcmp(code, "swa") == 0 || strcmp(code, "SWA") == 0
            || strcmp(code, "swp") == 0 || strcmp(code, "SHW") == 0){
        internal_code = swp_c;
    }

    else { // error
        internal_code = err_c;
    }

    //call EXEC
    execute_npipc_instruction(internal_code, value, delta);
}

void execute_npipc_instruction(ic internal_code , double v, double d){
    if(internal_code != app_c && internal_code != err_c){
        if(stack_top <= 0){
            printf("%s %d %s\n", "Impossible: stack size", stack_top+1, "too small.");
            return;
        }
    }
    
    switch(internal_code){
        case app_c: //Append
            printf("Append...\n");
            append_entry(v, d);
            break;

        case add_c: //Arithmetic
            printf("Sum...\n");
            add();
            break;
        case sub_c:
            printf("Difference...\n");
            sub();
            break;
        case mul_c:
            printf("Product...\n");
            mul();
            break;
        case div_c:
            printf("Quotient...\n");
            quo();
            break;

        case kil_c: //Stack manip
            printf("Kill...\n");
            kill();
            break;
        case clr_c:
            printf("Clear...\n");
            clear();
            break;
        case shw_c:
            printf("Show stack...\n");
            char* ps = malloc(STR_MAX * sizeof(char));
            show_two(ps);
            printf("%s\n",ps);
            free(ps);
            break;
        case swp_c:
            printf("Swap top two...\n");
            swap();
            break;

        default: // Error
            printf("Malformed command!\n");
            break;
    }
}

void main(){
    ic inst;
    while( !iface_exit ){
        fetch_user_instruction();
    }
    return;
}
