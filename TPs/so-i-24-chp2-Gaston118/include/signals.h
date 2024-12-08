/**
 * @file signals.h
 * @brief Declaración de funciones para el manejo de señales.
 */

#ifndef SIGNALS_H
#define SIGNALS_H

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * @brief Manejador de la señal SIGTSTP.
 * @param sig Número de la señal.
 */
void handle_sigtstp(int sig);

/**
 * @brief Manejador de la señal SIGINT.
 * @param sig Número de la señal.
 */
void handle_sigint(int sig);

/**
 * @brief Manejador de la señal SIGQUIT.
 * @param sig Número de la señal.
 */
void handle_sigquit(int sig);

/**
 *  @brief Configura los manejadores de señales.
 */
void setup_signal_handlers();

#endif
