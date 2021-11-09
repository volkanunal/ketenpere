#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "include/main.h"
#include "include/ket_lexer.h"
#include "include/data_type.h"
#include "include/visitor.h"
#include "include/from_file.h"

int main(int argc, char* argv[])
{  
    char* content = get_content(argv[1]);

    if (content)
    {        
        ketenpere_lexer_t ket_lexer = init_ketenpere_lexer(content);
        
        run_visitor(ket_lexer);

        free_lexer(ket_lexer);
    }  
}  
    
  

