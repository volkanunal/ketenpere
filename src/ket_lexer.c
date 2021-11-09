#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "include/ket_lexer.h"

struct ketenpere_lexer
{
    unsigned long size_of_ctx;
    unsigned int idx;
    char* ctx;
    char c;
};

static void ketenpere_lexer_advance(ketenpere_lexer_t self)
{
    if (self -> c != '\0' && self -> idx < self -> size_of_ctx)
    {
        self -> idx += 1;
        self -> c = self -> ctx[self -> idx];
    }
}

static data_type_t* ketenpere_catch_token_id(ketenpere_lexer_t self)
{
    char* collect = calloc(2, sizeof(char));
    collect[0] = '\0';

    while(isalnum(self -> c))
    {
        char* s  = calloc(2, sizeof(char));
        s[0] = self -> c;
        s[1] = '\0';        
        collect = realloc(collect, (strlen(collect) + strlen(s) + 1) * sizeof(char));
        strcat(collect, s);
        ketenpere_lexer_advance(self); 
    }

    if (self -> c == '*')
    {
        char* s  = calloc(2, sizeof(char));
        s[0] = self -> c;
        s[1] = '\0';        
        collect = realloc(collect, (strlen(collect) + strlen(s) + 1) * sizeof(char));
        strcat(collect, s);
    }

    ketenpere_lexer_advance(self);
 
    return init_data_type(TOKEN_STRUCT, collect);
}

static data_type_t* ketepenpere_catch_par(ketenpere_lexer_t self, int left_or_right) // 0 : left , 1 : right
{
    char* collect = calloc(2, sizeof(char));
    collect[0] = self -> c;
    collect[1] = '\0';

    ketenpere_lexer_advance(self);

    return init_data_type(left_or_right ? TOKEN_END_STRUCT_PAR : TOKEN_START_STRUCT_PAR, collect);
}

static data_type_t* ketenpere_catch_semicolon(ketenpere_lexer_t self)
{
    char* collect = calloc(2, sizeof(char));
    collect[0] = self -> c;
    collect[1] = '\0';

    ketenpere_lexer_advance(self);

    return init_data_type(TOKEN_SEMICOLON, collect);
}

static void ketenpere_eliminate_space(ketenpere_lexer_t self)
{
    while (self -> c == ' ' || self -> c == 10)
    {
        ketenpere_lexer_advance(self);
    }
}

ketenpere_lexer_t init_ketenpere_lexer(char* ctx)
{
    ketenpere_lexer_t ket_lexer = calloc(1, sizeof(struct ketenpere_lexer));
    ket_lexer -> size_of_ctx = strlen(ctx);
    ket_lexer -> ctx = ctx;
    ket_lexer -> idx = 0;
    ket_lexer -> c = ket_lexer -> ctx[ket_lexer -> idx];

    return ket_lexer;
}

data_type_t* ketenpere_token_parse(ketenpere_lexer_t self)
{
    while (self -> c != '\0' && self ->  idx < self -> size_of_ctx)
    {
        if (self -> c == ' ' || self -> c == 10) 
            ketenpere_eliminate_space(self);

        else if (isalnum(self -> c))
        {
            return ketenpere_catch_token_id(self);    
        }

        else if(self -> c == '{') 
        {
            return ketepenpere_catch_par(self, 0);
        }
        
        else if(self -> c == ';')
        {
            ketenpere_lexer_advance(self);
            //return ketenpere_catch_semicolon(self);
        }
        
        else if(self -> c == '}')
        {
            return ketepenpere_catch_par(self, 1);
        }
    }
    
    return (void*)0;
}


void free_lexer(ketenpere_lexer_t self)
{
    free(self -> ctx);
    free(self);        
}
