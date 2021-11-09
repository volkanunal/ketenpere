#ifndef KET_LEXER_H
#define KET_LEXER_H

#include "data_type.h"

struct ketenpere_lexer;
typedef struct ketenpere_lexer* ketenpere_lexer_t;

ketenpere_lexer_t init_ketenpere_lexer(char* ctx);

data_type_t* ketenpere_token_parse(ketenpere_lexer_t self);

void free_lexer(ketenpere_lexer_t self);



#endif