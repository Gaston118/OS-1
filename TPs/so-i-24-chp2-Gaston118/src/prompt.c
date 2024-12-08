/**
 * @file prompt.c
 * @brief prompt de la shell
 */

#include "../include/prompt.h"

void mostrar_prompt()
{
    char hostname[HOST_MAX];
    char cwd[PATH_MAX];

    // Obtener el nombre del usuario
    char* username = getenv("USER");

    // Obtener el nombre del host
    gethostname(hostname, sizeof(hostname));

    // Obtener el directorio actual
    getcwd(cwd, sizeof(cwd));

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd error");
        return;
    }

    // Reemplazar el directorio home por ~
    char* home = getenv("HOME");
    if (home != NULL && strstr(cwd, home) == cwd)
    {
        char display_cwd[PATH_MAX];
        snprintf(display_cwd, sizeof(display_cwd), "~%s", cwd + strlen(home));
        printf("%s@%s:%s$ ", username, hostname, display_cwd);
    }
    else
    {
        printf("%s@%s:%s$ ", username, hostname, cwd);
    }
}

void init_shell()
{
    printf("\n*******************************************");
    printf("\n\n\tVault-Tec Corporation Shell");
    printf("\n\n*******************************************");

    char* username = getenv("USER");

    printf("\n\nUSER is: @%s", username);
    printf("\n\n");
    sleep(1);
}
