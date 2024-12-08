/**
 * @file signals.c
 * @brief manejo de señales
 */

#include "../include/signals.h"

/**
 * @var foreground_pid
 * @brief PID del proceso en primer plano.
 *
 * Esta variable global mantiene el PID del proceso que se ejecuta en primer
 * plano. Se inicializa en -1 y se actualiza con el PID del proceso en ejecución.
 */
pid_t foreground_pid = -1; // PID del proceso en primer plano, -1 significa que no hay ninguno

// Manejador para SIGINT (CTRL-C)
void handle_sigint(int sig)
{
    if (foreground_pid > 0)
    {
        kill(foreground_pid, SIGINT); // Enviar SIGINT al proceso en primer plano
    }
}

// Manejador para SIGTSTP (CTRL-Z)
void handle_sigtstp(int sig)
{
    if (foreground_pid > 0)
    {
        kill(foreground_pid, SIGTSTP); // Enviar SIGTSTP al proceso en primer plano
    }
}

// Manejador para SIGQUIT (CTRL-\)
void handle_sigquit(int sig)
{
    if (foreground_pid > 0)
    {
        kill(foreground_pid, SIGQUIT); // Enviar SIGQUIT al proceso en primer plano
    }
}

// Función que configura los manejadores de señal
void setup_signal_handlers()
{
    signal(SIGINT, handle_sigint);   // Captura CTRL-C
    signal(SIGTSTP, handle_sigtstp); // Captura CTRL-Z
    signal(SIGQUIT, handle_sigquit);
}
