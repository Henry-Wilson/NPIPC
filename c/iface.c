/*
 * NPIPC User Interface (iface) definition
 */

#include <stdlib.h> //malloc, free
#include <stdio.h> //fgets, printf, sscanf

#include "iface.h"
#include "npipc.h"

void fetch_user_instruction(){
    char *ustr = malloc(U_STR_MAX * sizeof(char));
    fgets(ustr, U_STR_MAX, stdin);
    decode_user_instruction(ustr);
    free(ustr);
}

void decode_user_instruction(char *ustr){
    /*
     * The plan:
     * first FOUR characters of the user command must be a correctly formatted
     * command string as defined by our header.
     * strcpy those chars into a little buffer,
     * determine which command they correspond to,
     * pass that to executor.
     *
     * If we are appending, there will be extra work: find the value, delta vars.
     */
    printf("DECODE: DEBUG: USTR: %s",ustr);
    ic internal_code = app_c;
    execute_npipc_instruction(internal_code, 0.0, 0.0);
}

void execute_npipc_instruction(ic internal_code , double v, double d){
    switch(internal_code){
        case app_c:
            printf("WOOH! APPEND!\n");
            append_entry(v, d);
            break;
        default:
            printf("Aww...\n");
            break;
    }
}

void main(){
    while( 1 ){
        fetch_user_instruction();
    }
}
