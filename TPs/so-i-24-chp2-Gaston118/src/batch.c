/**
 * @file batch.c
 * @brief Manejo de la funcion batch.
 */

#include "../include/batch.h"

/* @brief funcion para activar batch mode.
 */
void batch_mode(FILE* file, char* tokens[], bool bg)
{
    char input[MAX_IN];

    // Leer y ejecutar cada línea del archivo
    while (fgets(input, sizeof(input), file) != NULL)
    {
        // Remover el salto de línea
        input[strcspn(input, "\n")] = '\0';

        // Tokenizar la entrada
        int token_count = 0;
        char* token = strtok(input, " ");
        while (token != NULL && token_count < MAX_TOKENS - 1)
        {
            tokens[token_count++] = token;
            token = strtok(NULL, " ");
        }
        tokens[token_count] = NULL;

        if (token_count == 0)
        {
            continue; // Entrada vacía
        }
        // Comandos internos
        cmdHandler(tokens, token_count, bg);
    }
}
