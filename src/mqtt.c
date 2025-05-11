#include "pico/stdlib.h"
#include "lwip/apps/mqtt.h"
#include "mqtt.h"

#include <string.h>

err_t mqtt_connect(void)
{
    mqtt_client = mqtt_client_new();
    ip4addr_aton(BROKER_ADDRESS, &broker_ip);
    err_t err = mqtt_client_connect(mqtt_client, &broker_ip,
                                    MQTT_PORT, mqtt_connection_cb,
                                    NULL, &client_info);

    return err;
}

static void mqtt_connection_cb(mqtt_client_t *client, void *arg,
                               mqtt_connection_status_t status)
{
    if (status == MQTT_CONNECT_ACCEPTED)
    {
        printf("Connection to broker success: %d\n", status);
        mqtt_set_inpub_callback(mqtt_client, NULL, mqtt_incoming_data_cb, NULL);
    }
    else
    {
        printf("Connection to broker failed: %d\n", status);
    }
}

static void mqtt_pub_cb(void *arg, err_t result)
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

err_t mqtt_pub_sensor_read(const char* sensor_type, int value)
{
    char topic[32];
    snprintf(topic, sizeof(topic), "edge/%s/sensor/%s", CLIENT_ID, sensor_type);

    char payload[20];
    snprintf(payload, sizeof(payload), "{\"value\": %d}", value);

    err_t err = mqtt_publish(mqtt_client, topic,
                             payload, strlen(payload),
                             0, 0, mqtt_pub_cb, NULL);

    return err;
}

static void mqtt_sub_cb(void *arg, err_t result)
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

err_t mqtt_sub(const char* topic)
{
    err_t err = mqtt_sub_unsub(mqtt_client, topic, 0, mqtt_sub_cb, 0, 1);

    return err;
}

static void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags)
{
}
