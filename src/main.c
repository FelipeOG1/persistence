#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char* buffer;
    size_t buffer_len;
    size_t input_len;

} InputBuffer;


typedef enum {
    META_COMMNAD_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND,
} MetaCommandResult;

typedef enum { PREPARE_SUCCESS, PREPARE_UNRECOGNIZED_STATEMENT } PrepareResult;


typedef enum { STATEMENT_INSERT, STATEMENT_SELECT } StatementType;

typedef struct {
  StatementType type;
} Statement;

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
void print_buffer(InputBuffer* buffer) { printf("contentd: %s, size: %zu\n", buffer->buffer, buffer->input_len); }
void close_input_buffer(InputBuffer* buffer) {
    free(buffer->buffer);
    free(buffer);
}

MetaCommandResult handle_meta_command(InputBuffer* buffer) {
    if (strcmp(buffer->buffer, ".exit") == 0) {
        exit(EXIT_SUCCESS);
        
    } else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
    
}

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement) {
    if (strcmp(input_buffer->buffer, "insert") == 0) {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;  
    }
    if (strcmp(input_buffer->buffer, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;

}

void start_repl() {
    for (;;) {
        
        InputBuffer* input_buffer = new_input_buffer();
        print_db();
        read_input(input_buffer);

        if (input_buffer->buffer[0] == '.') {
            switch(handle_meta_command(input_buffer)) {
                case (META_COMMNAD_SUCCESS):
                    continue;
                case (META_COMMAND_UNRECOGNIZED_COMMAND):
                    printf("Unrecognized command: %s\n", input_buffer->buffer);
                    continue;

            }
        
        }

        Statement statement;
        switch (prepare_statement(input_buffer, &statement)) {
            case PREPARE_SUCCESS:
                break;
            case PREPARE_UNRECOGNIZED_STATEMENT:
                printf("Unrecognized statement: %s\n", input_buffer->buffer);
                continue;
                
        }

    }

}
int main() {

      
    start_repl();
    return 0;
}


