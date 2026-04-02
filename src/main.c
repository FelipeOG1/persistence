#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>




#define USERNAME_SIZE 32
#define EMAIL_SIZE 255

typedef struct {
    char* buffer;
    size_t buffer_len;
    size_t input_len;

} InputBuffer;

typedef struct {
	int id;
	char username[USERNAME_SIZE];
	char* email[EMAIL_SIZE];
} Row;

typedef enum {
    META_COMMNAD_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND,
} MetaCommandResult;

typedef enum { PREPARE_SUCCESS, PREPARE_UNRECOGNIZED_STATEMENT } PrepareResult;


typedef enum { STATEMENT_INSERT, STATEMENT_SELECT, STATEMENT_DELETE } StatementType;

typedef struct {
  StatementType type;
  Row row_to_insert;

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
    if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
		int args_count = sscanf(input_buffer->buffer, "insert %d %255s %32s", &(statement->row_to_insert.id), 
								statement->row_to_insert.email, statement->row_to_insert.username);

		printf("args count: %d", args_count);
		

		if (args_count < 0) { exit(EXIT_FAILURE);}
		
		
        return PREPARE_SUCCESS;  
    }
    if (strcmp(input_buffer->buffer, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }
	if (strcmp(input_buffer->buffer, "delete") == 0) {
		statement->type = STATEMENT_DELETE;
		return PREPARE_SUCCESS;
	}

    return PREPARE_UNRECOGNIZED_STATEMENT;

}

void execute_statement(Statement* statement) { switch(statement->type) {
		case (STATEMENT_INSERT):
			break;
		case(STATEMENT_SELECT):
			printf("handle select\n");
			break;
			
	}
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
				execute_statement(&statement);
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


