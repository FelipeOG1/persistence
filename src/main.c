#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

//commands handlers
bool is_command(InputBuffer* input_buffer) {
    return input_buffer->buffer[0] == '.';
}

void print_db() { printf("db >"); }
void print_buffer(InputBuffer* buffer) { printf("contentd: %s, size: %zu\n", buffer->buffer, buffer->input_len); }
void close_input_buffer(InputBuffer* buffer) {
    free(buffer->buffer);
    free(buffer);
}


void start_repl() {
    for (;;) {
        
        InputBuffer* input_buffer = new_input_buffer();
        print_db();
        read_input(input_buffer);

        if (is_command(input_buffer)) {
            if (strcmp(input_buffer->buffer, ".exit") == 0) {
                close_input_buffer(input_buffer);
                break;
            } else {
               printf("NOT VALID COMMAND\n");
            }
   
        }
            
    }
}
int main() {

      
    start_repl();
    return 0;
}


