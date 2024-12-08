/**
 * @file pipes.c
 * @brief manejo de pipes
 */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * @def BUFF_INPUT
 * Número máximo de tokens que se pueden manejar en el procesamiento de comandos.
 */
#define BUFF_INPUT 1024

/**
 * @brief Divide un string en dos partes según el carácter pipe '|'.
 *
 * @param str Cadena de caracteres a dividir.
 * @param strpiped Array de dos punteros para almacenar las partes de la cadena.
 * @return int Retorna 1 si se encuentra un pipe '|' en el string, de lo contrario retorna 0.
 */
int parsePipe(char* str, char** strpiped)
{
    int i;
    for (i = 0; i < 2; i++)
    {
        strpiped[i] = strsep(&str, "|");
        if (strpiped[i] == NULL)
            break;
    }

    if (strpiped[1] == NULL)
        return 0; // returns zero if no pipe is found.
    else
    {
        return 1;
    }
}

/**
 * @var foreground_pid2
 * @brief PID del proceso en primer plano.
 *
 * Esta variable global mantiene el PID del proceso que se ejecuta en primer
 * plano. Se inicializa en -1 y se actualiza con el PID del proceso en ejecución.
 */
volatile pid_t foreground_pid2 = -1;

/**
 * @brief Ejecuta una serie de comandos encadenados por pipes.
 *
 * @param input Cadena de caracteres que contiene los comandos a ejecutar.
 *
 * Esta función toma una cadena `input` que contiene comandos separados por '|',
 * los divide y crea un proceso hijo para cada comando, permitiendo la
 * comunicación entre ellos mediante pipes. Cada comando se ejecuta en un
 * proceso separado, y la función espera hasta que todos los procesos terminen.
 */
void execute_external_command(char* input)
{
    char* commands[BUFF_INPUT / 2 + 1]; // Array to hold commands
    int num_commands = 0;

    // Split input by pipe
    char* token = strtok(input, "|");
    while (token != NULL && num_commands < BUFF_INPUT / 2)
    {
        commands[num_commands++] = token;
        token = strtok(NULL, "|");
    }
    commands[num_commands] = NULL;

    int pipe_fds[2 * (num_commands - 1)]; // Pipes for inter-process communication

    // Create pipes
    for (int i = 0; i < num_commands - 1; i++)
    {
        if (pipe(pipe_fds + i * 2) == -1)
        {
            perror("pipe");
            return;
        }
    }

    for (int i = 0; i < num_commands; i++)
    {
        // Create a child process
        pid_t pid = fork();
        if (pid < 0)
        {
            perror("Error to create a child process");
            return;
        }
        else if (pid == 0)
        {
            // Child process
            if (i > 0)
            {
                // If not the first command, get input from the previous pipe
                dup2(pipe_fds[(i - 1) * 2], 0);
            }
            if (i < num_commands - 1)
            {
                // If not the last command, output to the next pipe
                dup2(pipe_fds[i * 2 + 1], 1);
            }
            // Close all pipe fds in the child process
            for (int j = 0; j < 2 * (num_commands - 1); j++)
            {
                close(pipe_fds[j]);
            }

            // Tokenize the command for execution
            char* args[BUFF_INPUT / 2 + 1];
            char* cmd = commands[i];
            int arg_index = 0;

            char* arg_token = strtok(cmd, " ");
            while (arg_token != NULL && arg_index < BUFF_INPUT / 2)
            {
                args[arg_index++] = arg_token;
                arg_token = strtok(NULL, " ");
            }
            args[arg_index] = NULL;

            // Execute the command
            if (execvp(args[0], args) == -1)
            {
                perror("Error trying to execute command");
            }
            exit(EXIT_FAILURE);
        }
        else
        {
            foreground_pid2 = pid;
            // If it's the last command, close the pipe for the output
            if (i < num_commands - 1)
            {
                close(pipe_fds[i * 2 + 1]); // Close write end of the pipe
            }
            // If it's the first command, close the read end of the pipe
            if (i > 0)
            {
                close(pipe_fds[(i - 1) * 2]); // Close read end of the previous pipe
            }
        }
    }

    // Close all pipe fds in the parent process
    for (int i = 0; i < 2 * (num_commands - 1); i++)
    {
        close(pipe_fds[i]);
    }

    // Wait for all child processes
    for (int i = 0; i < num_commands; i++)
    {
        int status;
        waitpid(-1, &status, 0); // Wait for any child
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        {
            printf("Command failed with exit code %d\n", WEXITSTATUS(status));
        }
    }

    foreground_pid2 = -1; // Reset foreground PID
}
