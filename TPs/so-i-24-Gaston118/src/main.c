/**
 * @file main.c
 * @brief Entry point of the system
 */

#include "../include/expose_metrics.h"
#include "../include/metrics.h"
#include <stdbool.h>

/**
 * @brief Tiempo de espera entre actualizaciones de métricas (en segundos)
 */
#define SLEEP_TIME 1

/**
 * @brief Punto de entrada del programa
 * @param argc Cantidad de argumentos
 * @param argv Argumentos del programa
 * @return Código de salida
 */
int main(int argc, char* argv[]) // NOLINT
{
    init_metrics();

    // Creamos un hilo para exponer las métricas vía HTTP
    pthread_t tid;
    if (pthread_create(&tid, NULL, expose_metrics, NULL) != 0)
    {
        fprintf(stderr, "Error al crear el hilo del servidor HTTP\n");
        return -1;
    }

    // Bucle principal para actualizar las métricas cada segundo
    while (true)
    {
        update_cpu_gauge();
        update_memory_gauge();
        update_disk_io_gauge();
        update_process_gauge();
        update_network_gauge();
        update_ctxt_gauge();
        sleep(SLEEP_TIME);
    }

    return EXIT_SUCCESS;
}