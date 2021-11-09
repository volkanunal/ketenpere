#ifndef DATA_TYPE_H
#define DATA_TYPE_H

typedef struct data_type_t {

    enum {
        TOKEN_STRUCT,
        TOKEN_STRUCT_NAME,
        TOKEN_START_STRUCT_PAR,
        TOKEN_END_STRUCT_PAR,
        TOKEN_SEMICOLON,
    }token_type;

    char* type_name;

}data_type_t;

data_type_t* init_data_type(int token_type, char* name);


#endif
