/**
 * @file prompt.h
 * @brief Declaración de funciones para mostrar el prompt y la inicialización de la shell.
 */

#include <limits.h>
#include <linux/limits.h>
#include <pwd.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**
 * @def PATH_MAX
 * Número máximo de tokens que se pueden manejar en el procesamiento de comandos.
 */
#define PATH_MAX 4096

/**
 * @def HOST_MAX
 * Número máximo de hosts.
 */
#define HOST_MAX 64

/**
 * @brief Muestra el prompt de la shell.
 */
void mostrar_prompt();

/**
 * @brief Inicializa la shell.
 */
void init_shell();
