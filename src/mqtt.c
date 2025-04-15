#include "pico/stdlib.h"
#include "lwip/apps/mqtt.h"
#include "mqtt.h"

#include <string.h>

int mqtt_init(void)
{
    mqtt_client = mqtt_client_new();
    ip4addr_aton(BROKER_ADDRESS, &broker_ip);

    return 0;
}

err_t mqtt_connect(void)
{
    err_t err = mqtt_client_connect(mqtt_client, &broker_ip, 1883, mqtt_connection_cb, NULL, &client_info);
    return err;
}

static void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status)
{
    if (status == MQTT_CONNECT_ACCEPTED)
    {
        printf("Connection to broker success: %d\n", status);
    }
    else
    {
        printf("Connection to broker failed: %d\n", status);
    }
}

static void mqtt_pub_request_cb(void *arg, err_t result)
{
    if (result == ERR_OK)
    {
        printf("Publish success: %d\n", result);
    }
    else
    {
        printf("Publish failed: %d\n", result);
    }
}

err_t publish_read(const char* sensor, int value)
{
    char topic[32];
    snprintf(topic, sizeof(topic), "edge/%s/sensor/%s", CLIENT_ID, sensor);

    char payload[32];
    snprintf(payload, sizeof(payload), "{\"value\": %d}", value);

    err_t err = mqtt_publish(mqtt_client, topic, payload, strlen(payload), 0, 0, mqtt_pub_request_cb, NULL);

    return err;
}
