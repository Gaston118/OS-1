#include "../include/expose_metrics.h"

/** Mutex para sincronización de hilos */
pthread_mutex_t lock;

static prom_gauge_t* cpu_usage_metric;

static prom_gauge_t* memory_usage_metric;

static prom_gauge_t* disk_io_usage_metric;

static prom_gauge_t* process_metric;

static prom_gauge_t* network_usage_metric;

static prom_gauge_t* ctxt_metric;

void update_cpu_gauge()
{
    double usage = get_cpu_usage();
    if (usage >= 0)
    {
        pthread_mutex_lock(&lock);
        prom_gauge_set(cpu_usage_metric, usage, NULL);
        pthread_mutex_unlock(&lock);
    }
    else
    {
        fprintf(stderr, "Error al obtener el uso de CPU\n");
    }
}

void update_memory_gauge()
{
    double usage = get_memory_usage();
    if (usage >= 0)
    {
        pthread_mutex_lock(&lock);
        prom_gauge_set(memory_usage_metric, usage, NULL);
        pthread_mutex_unlock(&lock);
    }
    else
    {
        fprintf(stderr, "Error al obtener el uso de memoria\n");
    }
}

void update_disk_io_gauge()
{
    double usage = get_disk_io_usage("sda");
    if (usage >= 0)
    {
        pthread_mutex_lock(&lock);
        prom_gauge_set(disk_io_usage_metric, usage, NULL);
        pthread_mutex_unlock(&lock);
    }
    else
    {
        fprintf(stderr, "Error al obtener el uso de disco\n");
    }
}

void update_process_gauge()
{
    double usage = get_running_processes();
    if (usage >= 0)
    {
        pthread_mutex_lock(&lock);
        prom_gauge_set(process_metric, usage, NULL);
        pthread_mutex_unlock(&lock);
    }
    else
    {
        fprintf(stderr, "Error al obtener el uso de procesos\n");
    }
}

void update_network_gauge()
{
    double usage = get_network_usage("lo");
    if (usage >= 0)
    {
        pthread_mutex_lock(&lock);
        prom_gauge_set(network_usage_metric, usage, NULL);
        pthread_mutex_unlock(&lock);
    }
    else
    {
        fprintf(stderr, "Error al obtener el uso de red\n");
    }
}

void update_ctxt_gauge()
{
    double usage = get_ctxt();
    if (usage >= 0)
    {
        pthread_mutex_lock(&lock);
        prom_gauge_set(ctxt_metric, usage, NULL);
        pthread_mutex_unlock(&lock);
    }
    else
    {
        fprintf(stderr, "Error al obtener el uso de red\n");
    }
}

void* expose_metrics(void* arg)
{
    (void)arg; // Argumento no utilizado

    // Aseguramos que el manejador HTTP esté adjunto al registro por defecto
    promhttp_set_active_collector_registry(NULL);

    // Iniciamos el servidor HTTP en el puerto 8000
    struct MHD_Daemon* daemon = promhttp_start_daemon(MHD_USE_SELECT_INTERNALLY, 8000, NULL, NULL);
    if (daemon == NULL)
    {
        fprintf(stderr, "Error al iniciar el servidor HTTP\n");
        return NULL;
    }

    // Mantenemos el servidor en ejecución
    while (1)
    {
        sleep(1);
    }

    // Nunca debería llegar aquí
    MHD_stop_daemon(daemon);
    return NULL;
}

void init_metrics()
{
    // Inicializamos el mutex
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        fprintf(stderr, "Error al inicializar el mutex\n");
    }

    // Inicializamos el registro de coleccionistas de Prometheus
    if (prom_collector_registry_default_init() != 0)
    {
        fprintf(stderr, "Error al inicializar el registro de Prometheus\n");
    }

    // Creamos la métrica para el uso de CPU
    cpu_usage_metric = prom_gauge_new("cpu_usage_percentage", "Porcentaje de uso de CPU", 0, NULL);
    if (cpu_usage_metric == NULL)
    {
        fprintf(stderr, "Error al crear la métrica de uso de CPU\n");
    }

    // Creamos la métrica para el uso de memoria
    memory_usage_metric = prom_gauge_new("memory_usage_percentage", "Porcentaje de uso de memoria", 0, NULL);
    if (memory_usage_metric == NULL)
    {
        fprintf(stderr, "Error al crear la métrica de uso de memoria\n");
    }

    disk_io_usage_metric = prom_gauge_new("disk_io_usage_percentage", "Porcentaje de uso de disco", 0, NULL);
    if (disk_io_usage_metric == NULL)
    {
        fprintf(stderr, "Error al crear la métrica de uso de disco\n");
    }

    process_metric = prom_gauge_new("process_count", "Cantidad de procesos", 0, NULL);
    if (process_metric == NULL)
    {
        fprintf(stderr, "Error al crear la métrica de cantidad de procesos\n");
    }

    network_usage_metric = prom_gauge_new("network_usage_percentage", "Porcentaje de uso de red", 0, NULL);
    if (network_usage_metric == NULL)
    {
        fprintf(stderr, "Error al crear la métrica de uso de red\n");
    }

    ctxt_metric = prom_gauge_new("ctxt_count", "Cantidad de context switches", 0, NULL);
    if (ctxt_metric == NULL)
    {
        fprintf(stderr, "Error al crear la métrica de cantidad de context switches\n");
    }

    // Registramos las métricas en el registro por defecto
    if (prom_collector_registry_must_register_metric(cpu_usage_metric) == NULL)
    {
        fprintf(stderr, "Error al registrar la métrica CPU USAGE\n");
    }
    if (prom_collector_registry_must_register_metric(memory_usage_metric) == NULL)
    {
        fprintf(stderr, "Error al registrar la métrica MEMORY USAGE\n");
    }
    if (prom_collector_registry_must_register_metric(disk_io_usage_metric) == NULL)
    {
        fprintf(stderr, "Error al registrar la métrica DISK IO USAGE\n");
    }
    if (prom_collector_registry_must_register_metric(process_metric) == NULL)
    {
        fprintf(stderr, "Error al registrar la métrica PROCESS COUNT\n");
    }
    if (prom_collector_registry_must_register_metric(network_usage_metric) == NULL)
    {
        fprintf(stderr, "Error al registrar la métrica NETWORK USAGE\n");
    }
    if (prom_collector_registry_must_register_metric(ctxt_metric) == NULL)
    {
        fprintf(stderr, "Error al registrar la métrica CTXT COUNT\n");
    }
}

void destroy_mutex()
{
    pthread_mutex_destroy(&lock);
}
