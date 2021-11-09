 #include "include/visitor.h"
 #include <stdlib.h>
 #include <string.h>
 #include <stdio.h>

typedef struct visitor_t {

    data_type_t* inner_node;
    int element_count;
    char* inner_node_name[5];
    int inner_node_count;
    char* node_name;
    data_type_t* node_self_elements[20];

}visitor_t;

static visitor_t* visitor_container[10] = { 0 }; 

static void free_all(visitor_t** self)
{
    for (int i = 0; visitor_container[i] != NULL; ++i)
    {      
        for (int elements = 0; elements < self[i] -> element_count; ++elements)
        {
            free(self[i] -> node_self_elements[elements] -> type_name);
            free(self[i] -> node_self_elements[elements]);
        }

        free(self[i]);
    } 
}

static visitor_t* init_visitor(void)
{
    visitor_t* visitor = calloc(1, sizeof(struct visitor_t));
    visitor -> inner_node = (void*)0;
    visitor -> element_count = 0;
    visitor -> node_name = (void*)0;
    visitor -> inner_node_count = 0;

    return visitor;
}

static void test_verbose_visitor(visitor_t** self)
{
    #define RED(string) "\x1b[31m" string "\x1b[0m"
    #define BLUE(string) "\x1b[34m" string "\x1b[0m"

    for (int container_idx = 0; visitor_container[container_idx] != NULL; ++container_idx)
    {   
        
        printf(RED("%s")"(struct) has following member or members ", self[container_idx] -> node_name);
        
        const int container_element_start_idx = 1;

        for (int containter_elements = container_element_start_idx; self[container_idx] -> node_self_elements[containter_elements] != (void*)0; containter_elements++)
        {
            if (self[container_idx] -> node_self_elements[containter_elements] -> token_type == TOKEN_START_STRUCT_PAR ||  
                    //self[container_idx] -> node_self_elements[containter_elements] -> token_type == TOKEN_SEMICOLON || 
                    self[container_idx] -> node_self_elements[containter_elements] -> token_type == TOKEN_END_STRUCT_PAR) {
                        containter_elements++;
                    }

            if (self[container_idx] -> node_self_elements[containter_elements] -> type_name) 
            {                
                printf(BLUE("(%s)") , self[container_idx] -> node_self_elements[containter_elements++] -> type_name);                
            }

            if (self[container_idx] -> node_self_elements[containter_elements] -> type_name)
            {
                printf("%s ", self[container_idx] -> node_self_elements[containter_elements] -> type_name);
            }
            
        }

        if(self[container_idx] -> inner_node)
        {   
            for (int in_node_cnt = 0; in_node_cnt < self[container_idx] -> inner_node_count; ++in_node_cnt)
            {
                printf(BLUE("(struct)") "%s" , self[container_idx] -> inner_node_name[in_node_cnt]);
            }            
        }

        printf("\r\n"); 
       
        if (!self[container_idx] -> inner_node) 
        {
            printf("\n********************************************************\n");
        }
        
    } 

    free_all(self);
}

void run_visitor(ketenpere_lexer_t ket_lexer)
{
    data_type_t* data = (void*)0;
    
    //Hold new structs
    visitor_t* visit = (void*)0; 

    int i = 0;
    int begin_struct = 0;

    while ((data = ketenpere_token_parse(ket_lexer)) != (void*)0)
    {     
        if (begin_struct && !strcmp(data -> type_name, "}"))
        {
            begin_struct = 0;
        }  

        if (!strcmp(data -> type_name, "struct"))
        {    
            // is there any nested struct ? To do : Think twice.
            if (i > 0 && begin_struct) 
            {                
                visit -> inner_node = data;
                visit -> node_self_elements[visit -> element_count] = (void*)0;
                //We no longer need to keep the token named "struct"
                free(data -> type_name);
                free(data);

                data = ketenpere_token_parse(ket_lexer);                
                visit -> inner_node_name[visit -> inner_node_count++] = data -> type_name;
                                
            }

            visit = init_visitor();

            if (!begin_struct) 
            {
                //We no longer need to keep the token named "struct"
                free(data -> type_name);
                free(data);

                data = ketenpere_token_parse(ket_lexer);
            }  

            visit -> node_name = data -> type_name;     
            visitor_container[i++] = visit;
        }

        if (!strcmp(data -> type_name, "{"))
        {
            begin_struct = 1;
        }

        //We no longer need to keep the token named "{ or }"
        if (!strcmp(data -> type_name, "{") || !strcmp(data -> type_name, "}"))
        {
            free(data -> type_name);
            free(data);
        }

        else
        {
            visit -> node_self_elements[visit -> element_count++] = data;
        }
    }

    //Check open struct is left!
    if (begin_struct)
    {
        printf("Error open struct");
    }

    visit -> node_self_elements[visit -> element_count] = (void*)0;
    visitor_container[i] = (void*)0;

    test_verbose_visitor(visitor_container);
}
