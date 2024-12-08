/**
 * @file batch.h
 * @brief Declaración de funciones para el manejo de archivos batch.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @def MAX_TOKENS
 * Número máximo de tokens que se pueden manejar en el procesamiento de comandos.
 */
#define MAX_TOKENS 100

/**
 * @def MAX_IN
 * Número máximo de entrada.
 */
#define MAX_IN 1024

/**
 * @brief Ejecuta un archivo batch.
 * @param file Archivo a ejecutar.
 * @param tokens Arreglo de tokens.
 * @param bg Indica si el proceso se ejecuta en background.
 */
void batch_mode(FILE* file, char* tokens[], bool bg);
