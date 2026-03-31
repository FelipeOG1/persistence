#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* buffer;
    size_t buffer_len;
    size_t input_len;

} InputBuffer;


InputBuffer* new_input_buffer() {
    InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer)); 
    input_buffer->buffer = NULL;
    input_buffer->buffer_len = 0;
    input_buffer->input_len = 0;
    
    return input_buffer;
}




void print_db() { printf("db >"); }
int main() {

    InputBuffer* input_buffer =  new_input_buffer();
    
    for ( ;; ) {
        print_db();    
        size_t bytes_read = getline(&input_buffer->buffer, &input_buffer->buffer_len, stdin);
        
    }
   
    
    return 0;
}


