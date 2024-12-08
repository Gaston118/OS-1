/**
 * @file commands.h
 * @brief Declaración de funciones para el manejo de comandos.
 */

#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * @def PATH_MAX
 * Numero maximo que soporta el path.
 */
#define PATH_MAX 4096

/**
 * @def MAX_IN
 * Numero maximo de entrada.
 */
#define MAX_IN 1024

/**
 * @brief Cambia el directorio de trabajo.
 * @param ruta Ruta del directorio al que se desea cambiar.
 */
void change_directory(char* ruta);

/**
    @brief clear
*/
void clear();

/**
 * @brief Muestra la ayuda.
 */
void open_help();

/**  @brief Muestra el mensaje recibido.
 * @param mensaje Mensaje a mostrar.
 */
void echo(char* mensaje);

/** @brief Sale de la shell.
 */
void quit();

/** @brief Muestra el directorio de trabajo actual.
 */
void dir();

/**
 * @brief Maneja la ejecución de comandos.
 */
void cmdHandler(char* tokens[], int token_count, bool bg);
