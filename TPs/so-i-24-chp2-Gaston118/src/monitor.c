/**
 * @file monitor.c
 * @brief conexion con el monitor
 */

#include "../include/monitor.h"

/**
 * @var pid
 * @brief Almacena el ID de proceso del monitor.
 *
 * Esta variable contiene el ID del proceso asociado con el monitor de métricas.
 * Se inicializa con -1 para indicar que no se ha asignado ningún proceso aún.
 */
pid_t pid = -1;

/**
 * @var metrics_to_monitor
 * @brief Lista de métricas a monitorear.
 *
 * Este array contiene las cadenas de texto con los nombres de las métricas que
 * el sistema debe monitorear. Su tamaño máximo está definido por la constante
 * MAX_METRICS.
 */
char* metrics_to_monitor[MAX_METRICS];

/**
 * @var metric_count
 * @brief Contador de métricas activas.
 *
 * Esta variable mantiene el conteo de las métricas actualmente monitoreadas
 * dentro del array `metrics_to_monitor`.
 */
int metric_count = 0;

/**
 * @var sampling_interval
 * @brief Intervalo de muestreo en segundos.
 *
 * Define el intervalo en segundos entre cada muestreo de métricas para el monitor.
 * Se inicializa con un valor predeterminado de 10 segundos.
 */
int sampling_interval = 10;

// Función para iniciar el monitoreo
void start_monitor()
{
    metric_count = 0;
    leer_configuracion("../config.json");
    // Crear un proceso hijo
    if (pid > 0)
    {
        printf("El sistema de monitoreo ya está en ejecución.\n");
        return;
    }

    // Crear un proceso hijo
    pid = fork();

    if (pid == -1)
    {
        perror("Error al crear el proceso hijo");
        return;
    }
    if (pid == 0)
    {
        // Proceso hijo
        while (1)
        {
            status_monitor();
            sleep(sampling_interval);
        }
    }
}

// Función para detener el monitoreo
void stop_monitor()
{
    if (pid > 0)
    {
        kill(pid, SIGTERM);
        waitpid(pid, NULL, 0); // Espera a que el proceso hijo termine
        printf("Sistema de monitoreo detenido.\n");
        pid = -1;
    }
    else
    {
        printf("El sistema de monitoreo no está en ejecución.\n");
    }
}

// Función para verificar el estado del monitoreo
void status_monitor()
{
    printf("\n");
    printf("================ Monitoring system in progress =================\n");
    for (int i = 0; i < metric_count; i++)
    {
        if (strcmp(metrics_to_monitor[i], "cpu") == 0)
        {
            show_cpu_usage();
        }
        else if (strcmp(metrics_to_monitor[i], "memory") == 0)
        {
            show_memory_usage();
        }
        else if (strcmp(metrics_to_monitor[i], "processes") == 0)
        {
            show_running_processes();
        }
        else if (strcmp(metrics_to_monitor[i], "context") == 0)
        {
            show_context_switches();
        }
        else if (strcmp(metrics_to_monitor[i], "disk") == 0)
        {
            show_disk_io_usage("sda");
        }
        else if (strcmp(metrics_to_monitor[i], "network") == 0)
        {
            show_network_usage("eth0");
        }
    }
    printf("===============================================================\n");
}

void show_memory_usage()
{
    double memory_usage = get_memory_usage();
    if (memory_usage >= 0.0)
    {
        printf("Uso de memoria: %.2f%%\n", memory_usage);
    }
    else
    {
        printf("Error al obtener el uso de memoria.\n");
    }
}

void show_cpu_usage()
{
    double cpu_usage = get_cpu_usage();
    if (cpu_usage >= 0.0)
    {
        printf("Uso de CPU: %.2f%%\n", cpu_usage);
    }
    else
    {
        printf("Error al obtener el uso de CPU.\n");
    }
}

void show_running_processes()
{
    int processes = get_running_processes();
    if (processes >= 0)
    {
        printf("Procesos en ejecución: %d\n", processes);
    }
    else
    {
        printf("Error al obtener el número de procesos en ejecución.\n");
    }
}

void show_context_switches()
{
    int ctxt = get_ctxt();
    if (ctxt >= 0)
    {
        printf("Cambios de contexto: %d\n", ctxt);
    }
    else
    {
        printf("Error al obtener el número de cambios de contexto.\n");
    }
}

void show_disk_io_usage(const char* disk_name)
{
    double disk_io_usage = get_disk_io_usage(disk_name);
    if (disk_io_usage >= 0.0)
    {
        printf("E/S de disco (%s): %.2f sectores\n", disk_name, disk_io_usage);
    }
    else
    {
        printf("Error al obtener la E/S del disco para %s.\n", disk_name);
    }
}

void show_network_usage(const char* interface)
{
    double network_usage = get_network_usage(interface);
    if (network_usage >= 0.0)
    {
        printf("Uso de red (%s): %.2f bytes\n", interface, network_usage);
    }
    else
    {
        printf("Error al obtener el uso de red para %s.\n", interface);
    }
}

void leer_configuracion(const char* archivo)
{
    FILE* f = fopen(archivo, "r");
    if (!f)
    {
        perror("fopen error");
        exit(EXIT_FAILURE);
    }

    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek(f, 0, SEEK_SET);
    char* data = malloc(length + 1);
    size_t result = fread(data, 1, length, f);
    if (result != length)
    {
        perror("fread error");
        free(data);
        exit(EXIT_FAILURE);
    }
    data[length] = '\0';
    fclose(f);

    cJSON* json = cJSON_Parse(data);
    if (!json)
    {
        fprintf(stderr, "Error parseando JSON: %s\n", cJSON_GetErrorPtr());
        free(data);
        exit(EXIT_FAILURE);
    }

    cJSON* intervalo = cJSON_GetObjectItemCaseSensitive(json, "interval");
    if (cJSON_IsNumber(intervalo))
    {
        sampling_interval = intervalo->valueint; // Ya no es un puntero
        printf("Intervalo de muestreo: %d segundos\n", sampling_interval);
    }

    // Leer métricas y almacenarlas
    cJSON* metrics = cJSON_GetObjectItemCaseSensitive(json, "metrics");
    if (cJSON_IsArray(metrics))
    {
        printf("Métricas a recolectar:\n");
        cJSON* metric;
        cJSON_ArrayForEach(metric, metrics)
        {
            if (cJSON_IsString(metric) && (metric->valuestring != NULL))
            {
                if (metric_count < MAX_METRICS)
                {
                    metrics_to_monitor[metric_count] = strdup(metric->valuestring);
                    printf("- %s\n", metrics_to_monitor[metric_count]);
                    metric_count++;
                }
            }
        }
    }

    cJSON_Delete(json);
    free(data);
}

void set_config(char* clave, char* valor)
{
    FILE* f = fopen("../config.json", "r+");
    if (!f)
    {
        perror("fopen error");
        return;
    }

    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek(f, 0, SEEK_SET);
    char* data = malloc(length + 1);
    size_t result2 = fread(data, 1, length, f);
    if (result2 != length)
    {
        perror("fread error");
        free(data);
        return;
    }
    data[length] = '\0';
    fclose(f);

    cJSON* json = cJSON_Parse(data);
    if (!json)
    {
        fprintf(stderr, "Error parseando JSON: %s\n", cJSON_GetErrorPtr());
        free(data);
        return;
    }

    // Actualizar la clave "interval"
    if (strcmp(clave, "interval") == 0)
    {
        cJSON* item = cJSON_GetObjectItemCaseSensitive(json, "interval");
        if (cJSON_IsNumber(item))
        {
            int nuevo_valor = atoi(valor);
            cJSON_SetNumberValue(item, nuevo_valor);
        }
        else
        {
            // Si "interval" no existe, añadirlo
            cJSON_AddNumberToObject(json, "interval", atoi(valor));
        }
    }
    // Actualizar la clave "metrics"
    else if (strcmp(clave, "metrics") == 0)
    {
        cJSON* metrics = cJSON_GetObjectItemCaseSensitive(json, "metrics");
        if (cJSON_IsArray(metrics))
        {
            // Convertir el nuevo valor en un objeto JSON
            cJSON* nuevo_metric = cJSON_CreateString(valor);
            cJSON_AddItemToArray(metrics, nuevo_metric);
        }
        else
        {
            // Si "metrics" no es un array, crearlo
            metrics = cJSON_CreateArray();
            cJSON_AddItemToArray(metrics, cJSON_CreateString(valor));
            cJSON_AddItemToObject(json, "metrics", metrics);
        }
    }
    else
    {
        // Manejo de otros casos
        // Añadir la clave si no existe
        if (cJSON_IsNumber(cJSON_CreateNumber(0)))
        {
            cJSON_AddNumberToObject(json, clave, atoi(valor));
        }
        else
        {
            cJSON_AddStringToObject(json, clave, valor);
        }
    }

    // Escribir de vuelta al archivo
    f = fopen("../config.json", "w"); // Abre de nuevo para escritura
    if (!f)
    {
        perror("fopen error");
        cJSON_Delete(json);
        free(data);
        return;
    }

    char* out = cJSON_Print(json);
    fprintf(f, "%s", out);
    fclose(f);

    cJSON_Delete(json);
    free(data);
    free(out);
}
