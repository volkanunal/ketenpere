#include "include/from_file.h"
#include "stdlib.h"

char* get_content(const char* file_path)
{
    char* buffer = (void*)0;
    uint32_t size = 0;
    FILE* f = fopen(file_path, "rb");

    if (f)
    {
        fseek(f, 0, SEEK_END);
        size = ftell(f);
        fseek(f, 0, SEEK_SET);

        buffer = calloc(size, size);
        
        if (buffer)
        {
            fread(buffer, 1, size, f);
        }

        fclose(f);

        return buffer;
    }

    return (void*)0;
}