#include "stdlib.h"
#include "include/data_type.h"

data_type_t* init_data_type(int token_type, char* type_name)
{
    data_type_t* type = calloc(1, sizeof(data_type_t));
    type -> token_type = token_type;
    type -> type_name = type_name;

    return type;
}
