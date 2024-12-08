/**
 * @file main.c
 * @brief Entry point of the system
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "batch.c"
#include "commands.c"
#include "monitor.c"
#include "pipes.c"
#include "prompt.c"
#include "signals.c"

/**
 * @def MAX_TOKENS
 * Número máximo de tokens que se pueden manejar en el procesamiento de comandos.
 */
#define MAX_TOKENS 100 // max number of commands to be supported

/**
 * @def MAX_IN
 * Número máximo de letras que se pueden manejar en el procesamiento de comandos.
 */
#define MAX_IN 1024 // max number of letters to be supported

/**
 * @brief Punto de entrada del programa
 * @param argc Cantidad de argumentos
 * @param argv Argumentos del programa
 * @return Código de salida
 */
int main(int argc, char* argv[])
{
    char input[MAX_IN];
    char* tokens[MAX_TOKENS];
    bool bg = false;
    bool redirect = false;

    init_shell();

    if (argc > 1)
    {
        FILE* file = fopen(argv[1], "r");
        if (file == NULL)
        {
            perror("Error opening file");
            return 1;
        }
        batch_mode(file, tokens, bg);
        fclose(file);
        return 0;
    }

    setup_signal_handlers();

    while (1)
    {
        mostrar_prompt();

        // Leer la línea de entrada
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            break; // EOF
        }

        // Remover el salto de línea
        input[strcspn(input, "\n")] = '\0';

        if (strstr(input, "|") != NULL)
        {
            execute_external_command(input);
            continue;
        }

        int token_count = 0;
        char* token = strtok(input, " ");
        bg = false;
        redirect = false;

        // Tokenizar la entrada

        while (token != NULL && token_count < MAX_TOKENS - 1)
        {
            tokens[token_count++] = token;
            token = strtok(NULL, " ");

            if (strcmp(tokens[token_count - 1], "&") == 0)
            {
                bg = true;
                tokens[token_count - 1] = NULL; // Eliminar '&' de los argumentos
                continue;
            }

            if (strcmp(tokens[token_count - 1], ">") == 0 || strcmp(tokens[token_count - 1], "<") == 0)
            {
                redirect = true;
                break;
            }
        }

        if (redirect)
        {
            exec_redirect(tokens);
            continue;
        }

        tokens[token_count] = NULL;

        if (token_count == 0)
        {
            continue; // Entrada vacía
        }

        // Comandos internos
        cmdHandler(tokens, token_count, bg);
    }

    return 0;
}
