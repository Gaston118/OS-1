/**
 * @file monitor.h
 * @brief Declaración de funciones para el monitoreo de recursos del sistema.
 */

#ifndef MONITOR_H
#define MONITOR_H

#include "../TPs/so-i-24-Gaston118/TPs/so-i-24-Gaston118/include/metrics.h"
#include "../TPs/so-i-24-Gaston118/TPs/so-i-24-Gaston118/src/metrics.c"
#include <cjson/cJSON.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * @def MAX_METRICS
 * Número máximo de metrics soportadas.
 */
#define MAX_METRICS 10

/**
 * @brief Estructura para almacenar las métricas a monitorear.
 */
void start_monitor();

/**
 * @brief Detiene el monitoreo de recursos.
 */
void stop_monitor();

/**
 * @brief Muestra el estado actual del monitoreo.
 */
void status_monitor();

/**
 * @brief Muestra el uso de recursos del sistema.
 */
void show_cpu_usage();

/**
 * @brief Muestra el uso de memoria del sistema.
 */
void show_memory_usage();

/**
 * @brief Muestra la cantidad de procesos en ejecución.
 */
void show_running_processes();

/**
 * @brief Muestra los cambios de contexto.
 */
void show_context_switches();

/**
 * @brief Muestra el uso de red para una interfaz específica.
 * @param interface Nombre de la interfaz de red.
 */
void show_network_usage(const char* interface);

/**
 * @brief Muestra el uso de disco para un dispositivo específico.
 * @param disk_name Nombre del dispositivo de disco.
 */
void show_disk_io_usage(const char* disk_name);

/**
 * @brief Lee el Cjson.
 */
void leer_configuracion(const char* archivo);

/**
 * @brief Configura el Cjson.
 */
void set_config(char* clave, char* valor);

#endif // MONITOR_H
