/**
 * @file exec.c
 * @brief manejador de comandos
 */

#include "../include/exec.h"

/**
 * @brief Contador de trabajos activos.
 */
int job_count = 0;

void exec_cmd_ext(char** args, bool bg)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        // Error al crear el proceso
        perror("fork error");
    }
    else if (pid == 0)
    {
        // Proceso Hijo
        if (execvp(args[0], args) == -1)
        {
            perror("execvp error");
        }
        exit(-1);
    }
    else
    {
        if (bg)
        {
            // Procces in bakcground
            printf("[%d] %d\n", job_count++, pid);
            wait(NULL);
        }
        else
        {
            // Proceso Padre espera
            int status;
            waitpid(pid, &status, 0);
        }
    }
}

// ./myshell.o < ../comandos.txt > salida.txt
void exec_redirect(char** args)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork error");
    }
    else if (pid == 0)
    {
        // Proceso Hijo
        for (int i = 0; args[i] != NULL; i++)
        {
            if (strcmp(args[i], "<") == 0)
            {
                int fd = open(args[i + 1], O_RDONLY);
                if (fd < 0)
                {
                    perror("open error");
                    exit(-1);
                }
                dup2(fd, STDIN_FILENO);
                close(fd);
                args[i] = NULL;
            }
            else if (strcmp(args[i], ">") == 0)
            {
                int fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd < 0)
                {
                    perror("open error");
                    exit(-1);
                }
                dup2(fd, STDOUT_FILENO);
                close(fd);
                args[i] = NULL;
            }
        }

        if (execvp(args[0], args) == -1)
        {
            perror("execvp error");
            exit(-1);
        }
    }
    else
    {
        // Proceso Padre
        int status;
        waitpid(pid, &status, 0);
    }
}
