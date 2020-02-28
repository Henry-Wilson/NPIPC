/*
 * Header file to define the API of the NPIPC User Interface (iface).
 * This makes no reference to the NPIPC Core itself.
 */

#define U_STR_MAX 64
#define CODE_STR_MAX 4

int iface_exit = 0;

enum internal_codes{
    app_c = 0,

    add_c,
    sub_c,
    mul_c,
    div_c,

    kil_c,
    clr_c,
    shw_c,
    swp_c,
    
    err_c
};

typedef enum internal_codes ic;

void fetch_user_instruction();
void decode_user_instruction(char *ustr);
void execute_npipc_instruction(ic internal_code, double v, double d);
