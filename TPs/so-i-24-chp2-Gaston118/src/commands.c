/**
 *  @file commands.c
 *  @brief manejo de todos los comandos.
 */

#include "../include/commands.h"
#include "../include/monitor.h"
#include "exec.c"

// Menu de ayuda
void open_help()
{
    puts("\n***WELCOME SHELL HELP***"
         "\nList of Commands supported:"
         "\n>cd"
         "\n>quit"
         "\n>clr"
         "\n>echo"
         "\n>dir"
         "\n>help"
         "\n>on"
         "\n>off");

    return;
}

// clr
void clear()
{
    printf("\033[H\033[J");
}

// funcion echo
void echo(char* mensaje)
{
    printf("%s\n", mensaje);
}

// salir de la shell
void quit()
{
    printf("Leaving the shell...\n");
    exit(0);
}

// manejo del cambio de directorio
/**
 * @brief directorio viejo.
 */
char oldpwd[PATH_MAX];
void change_directory(char* ruta)
{

    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd error");
        return;
    }

    // Actualizar OLDPWD
    strcpy(oldpwd, cwd);

    if (ruta == NULL)
    {
        ruta = getenv("HOME");
    }
    else if (strcmp(ruta, "-") == 0)
    {
        ruta = getenv("OLDPWD");
        if (ruta == NULL)
        {
            printf("OLDPWD not set.\n");
            return;
        }
    }

    if (chdir(ruta) != 0)
    {
        perror("cd error");
    }
    else
    {
        // Actualizar PWD
        setenv("OLDPWD", oldpwd, 1);
        getcwd(cwd, sizeof(cwd));
        if (getcwd(cwd, sizeof(cwd)) == NULL)
        {
            perror("getcwd error");
            return;
        }
        setenv("PWD", cwd, 1);
    }
}

/**
 * @brief guardamos directorio ahi.
 */

char PWD[PATH_MAX];
/**
 * puntero para argumentos.
 */
char* args[MAX_IN];

void dir(void)
{

    int archs;             /*Numero de archivos encontrados en el dir indicado*/
    struct dirent** lista; /*var que guarda la lista de archivos/dirs encontrados*/

    char ruta[PATH_MAX];
    if (getcwd(ruta, sizeof(ruta)) == NULL)
    {
        perror("getcwd error");
        return;
    }

    strcpy(PWD, ruta);

    if (args[1])
    {
        strcat(ruta, "/");
        strcat(ruta, args[1]);
    }

    archs = scandir(ruta, &lista, NULL, NULL);
    if (archs < 0)
    {
        printf("Error no existe o no se pudo leer [%s]\n", ruta);
    }
    else if (archs == 2)
    { /* Dir vacío (sólo '.' y '..') */
        printf(" El directorio [%s] está vacío\n", ruta);
    }
    else
    {
        for (int i = 0; i < archs; i++)
        {
            if (strcmp(lista[i]->d_name, ".") != 0 && strcmp(lista[i]->d_name, "..") != 0)
            {
                printf(" %s\n", lista[i]->d_name);
            }
            free(lista[i]);
        }
        free(lista);
    }
}

/**
 * @brief Maneja la ejecución de comandos.
 * @param tokens Un array de cadenas de caracteres que contienen los tokens del comando.
 * @param token_count El número de tokens en el array.
 * @param bg Un valor booleano que indica si el comando se debe ejecutar en segundo plano.
 */
void cmdHandler(char* tokens[], int token_count, bool bg)
{
    if (strcmp(tokens[0], "cd") == 0)
    {
        if (token_count > 1)
        {
            change_directory(tokens[1]);
        }
        else
        {
            change_directory(NULL);
        }
    }
    else if (strcmp(tokens[0], "clr") == 0)
    {
        clear();
    }
    else if (strcmp(tokens[0], "echo") == 0)
    {
        if (token_count > 1)
        {
            // Reconstruir el argumento después de 'echo'
            char argumentos[MAX_IN] = "";
            for (int i = 1; i < token_count; i++)
            {
                strcat(argumentos, tokens[i]);
                if (i < token_count - 1)
                {
                    strcat(argumentos, " ");
                }
            }
            echo(argumentos);
        }
        else
        {
            printf("\n");
        }
    }
    else if (strcmp(tokens[0], "quit") == 0)
    {
        quit();
    }
    else if (strcmp(tokens[0], "help") == 0)
    {
        open_help();
    }
    else if (strcmp(tokens[0], "dir") == 0)
    {
        for (int i = 1; i < token_count; i++)
        {
            args[i] = tokens[i];
        }
        dir();
    }
    else if (strcmp(tokens[0], "on") == 0)
    {
        start_monitor();
    }
    else if (strcmp(tokens[0], "off") == 0)
    {
        stop_monitor();
    }
    else if (strcmp(tokens[0], "set_config") == 0)
    {
        if (token_count == 3)
        {
            set_config(tokens[1], tokens[2]);
        }
        else
        {
            printf("Uso: set_config <clave> <valor>\n");
        }
    }
    else
    {
        // Comando externo
        exec_cmd_ext(tokens, bg);
    }
}
