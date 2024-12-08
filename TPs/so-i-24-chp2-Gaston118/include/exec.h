/**
 * @file exec.h
 * @brief Declaración de funciones para la ejecución de comandos.
 */

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * @def MAX_IN
 * Número máximo de tokens que se pueden manejar en el procesamiento de comandos.
 */
#define MAX_IN 1024

/**
 * @brief Ejecuta un comando.
 * @param args Arreglo de argumentos.
 * @param bg Indica si el proceso se ejecuta en background.
 */
void exec_cmd_ext(char** args, bool bg);

/**
 * @brief Ejecuta un comando con redirección.
 * @param args Arreglo de argumentos.
 */
void exec_redirect(char** args);
