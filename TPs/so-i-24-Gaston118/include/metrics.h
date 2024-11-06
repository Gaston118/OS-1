/**
 * @file metrics.h
 * @brief Funciones para obtener el uso de CPU y memoria desde el sistema de archivos /proc.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * @brief Tamaño del buffer para leer archivos.
 */
#define BUFFER_SIZE 256

/**
 * @brief Tamaño del buffer.
 */
#define BUFF 32

/**
 * @brief Obtiene el porcentaje de uso de memoria desde /proc/meminfo.
 *
 * Lee los valores de memoria total y disponible desde /proc/meminfo y calcula
 * el porcentaje de uso de memoria.
 *
 * @return Uso de memoria como porcentaje (0.0 a 100.0), o -1.0 en caso de error.
 */
double get_memory_usage();

/**
 * @brief Obtiene el porcentaje de uso de CPU desde /proc/stat.
 *
 * Lee los tiempos de CPU desde /proc/stat y calcula el porcentaje de uso de CPU
 * en un intervalo de tiempo.
 *
 * @return Uso de CPU como porcentaje (0.0 a 100.0), o -1.0 en caso de error.
 */
double get_cpu_usage();

/**
 * @brief Obtiene el porcentaje de uso de disco para un dispositivo específico.
 *
 * Lee las estadísticas de E/S de disco desde /proc/diskstats y calcula el
 * porcentaje de uso de disco para un dispositivo específico.
 *
 * @param disk_name Nombre del dispositivo de disco (ej. "sda").
 * @return Uso de disco como porcentaje (0.0 a 100.0), o -1.0 en caso de error.
 */
double get_disk_io_usage(const char* disk_name);

/**
 * @brief Obtiene la cantidad de procesos en ejecución desde /proc/stat.
 *
 * Lee las estadísticas de procesos desde /proc/stat y obtiene la cantidad de
 * procesos en ejecución.
 *
 * @return Cantidad de procesos en ejecución, o -1 en caso de error.
 */
int get_running_processes();

/**
 * @brief Obtiene el uso de red para una interfaz de red específica.
 *
 * Lee las estadísticas de red desde /proc/net/dev y obtiene el uso de red
 * para una interfaz de red específica.
 *
 * @param interface Nombre de la interfaz de red (ej. "eth0").
 * @return Uso de red en bytes, o -1.0 en caso de error.
 */
double get_network_usage(const char* interface);

/**
 * @brief Obtiene la cantidad de cambios de contexto desde /proc/stat.
 *
 * Lee las estadísticas de cambios de contexto desde /proc/stat y obtiene la
 * cantidad de cambios de contexto.
 *
 * @return Cantidad de cambios de contexto, o -1 en caso de error.
 */
int get_ctxt();
