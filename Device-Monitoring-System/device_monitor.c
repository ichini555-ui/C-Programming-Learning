#include <stdio.h>

enum SensorStatus {
    NORMAL,
    WARNING,
    CRITICAL
};

const int CRITICAL_THRESHOLD = 60;
const int WARNING_THRESHOLD = 40;

struct Sensor {
    int id;
    int temperature;
    enum SensorStatus status;
};


enum SensorStatus check_temperature(int temperature)
{
    if (temperature >= CRITICAL_THRESHOLD) {
        return CRITICAL;
    } else if (temperature >= WARNING_THRESHOLD) {
        return WARNING;
    } else {
        return NORMAL;
    }
}


const char *status_to_string(enum SensorStatus status)
{
    if (status == NORMAL) {
        return "NORMAL";
    } else if (status == WARNING) {
        return "WARNING";
    } else if (status == CRITICAL) {
        return "CRITICAL";
    }

    return "UNKNOWN";
}


void print_status(int sensor_id, enum SensorStatus status)
{
    printf("Sensor %d: %s\n\n",
           sensor_id,
           status_to_string(status));
}


int find_max_sensor_temperature(struct Sensor *sensors, int size)
{
    int max = sensors[0].temperature;

    for (int i = 1; i < size; i++) {
        if (sensors[i].temperature > max) {
            max = sensors[i].temperature;
        }
    }

    return max;
}


void normalize_sensors(struct Sensor *sensors, int size)
{
    for (int i = 0; i < size; i++) {
        if (sensors[i].temperature < 0) {
            sensors[i].temperature = 0;
        }
    }
}


void monitor_sensors(struct Sensor *sensors, int size)
{
    for (int i = 0; i < size; i++) {
        int current_temperature = sensors[i].temperature;

        printf("Temperature: %d\n", current_temperature);

        sensors[i].status = check_temperature(current_temperature);

        print_status(sensors[i].id, sensors[i].status);
    }
}


void count_sensor_statuses(
    int *normal_count,
    int *warning_count,
    int *critical_count,
    struct Sensor *sensors,
    int size
)
{
    for (int i = 0; i < size; i++) {

        if (sensors[i].status == NORMAL) {
            (*normal_count)++;
        } else if (sensors[i].status == WARNING) {
            (*warning_count)++;
        } else if (sensors[i].status == CRITICAL) {
            (*critical_count)++;
        }
    }
}


void print_summary(
    int max_temperature,
    int normal_count,
    int warning_count,
    int critical_count
)
{
    printf("=== DEVICE MONITOR SUMMARY ===\n\n");

    printf("Max temperature: %d\n", max_temperature);
    printf("Normal sensors: %d\n", normal_count);
    printf("Warning sensors: %d\n", warning_count);
    printf("Critical sensors: %d\n", critical_count);

    printf("===============================\n\n");
}


int main(void)
{
    struct Sensor sensors[] = {
        {1, -2, NORMAL},
        {2, 50, NORMAL},
        {3, 65, NORMAL},
        {4, 33, NORMAL},
        {5, 15, NORMAL}
    };

    int sensor_count = sizeof(sensors) / sizeof(sensors[0]);

    normalize_sensors(sensors, sensor_count);

    int max_temperature =
        find_max_sensor_temperature(sensors, sensor_count);

    printf("Max temperature: %d\n", max_temperature);

    monitor_sensors(sensors, sensor_count);

    int normal_count = 0;
    int warning_count = 0;
    int critical_count = 0;

    count_sensor_statuses(
        &normal_count,
        &warning_count,
        &critical_count,
        sensors,
        sensor_count
    );

    print_summary(
        max_temperature,
        normal_count,
        warning_count,
        critical_count
    );

    for (int i = 0; i < sensor_count; i++) {
        printf(
            "Sensor %d: Temperature %d, Status %s\n",
            sensors[i].id,
            sensors[i].temperature,
            status_to_string(sensors[i].status)
        );
    }

    return 0;
}
    
