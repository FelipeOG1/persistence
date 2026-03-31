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

void read_input(InputBuffer* buffer) {
    size_t bytes_read = getline(&buffer->buffer, &buffer->buffer_len, stdin);
    if (bytes_read < 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }
    buffer->input_len = bytes_read - 1;
    buffer->buffer[bytes_read - 1] = 0;//eliminate /n character
   
}


void print_db() { printf("db >"); }
int main() {

    InputBuffer* input_buffer =  new_input_buffer();
    
    for ( ;; ) {
        print_db();
        read_input(input_buffer);
        printf("%s\n", input_buffer->buffer);

    }
   
    
    return 0;
}


