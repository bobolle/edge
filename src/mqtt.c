#include "pico/stdlib.h"
#include "lwip/apps/mqtt.h"

int mqtt_init()
{
    err_t err = mqtt_client_connect(mqtt_client, &broker_ip, 1883, mqtt_connection_cb, NULL, &client_info);

    if (err != ERR_OK)
    {
        printf("Error connection to broker\n");
    }
}

static void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status)
{
    printf("Connection status: %d\n", status);
}

static void mqtt_pub_request_cb(void *arg, err_t result)
{
    if (result != ERR_OK)
    {
        printf("Publish failed with result: %d\n", result);
    }
    else
    {
        printf("Publish succes with result: %d\n", result);
    }
}
