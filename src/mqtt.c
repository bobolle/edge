#include "mqtt.h"
#include "pico/stdlib.h"
#include "lwip/apps/mqtt.h"

#include <string.h>

volatile int moisture_threshold = 2000;
volatile int moisture_value = 0;
volatile int photoresistor_threshold = 2000;
volatile int photoresistor_value = 0;

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
        mqtt_set_inpub_callback(mqtt_client, mqtt_incoming_publish_cb, mqtt_incoming_data_cb, NULL);
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
        printf("Subscribe success: %d\n", result);
    }
    else
    {
        printf("Subscribe failed: %d\n", result);
    }
}

err_t mqtt_sub(const char* topic)
{
    err_t err = mqtt_sub_unsub(mqtt_client, topic, 0, mqtt_sub_cb, 0, 1);

    return err;
}

static void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len)
{
    strncpy(current_topic, topic, sizeof(current_topic) - 1);
    current_topic[sizeof(current_topic) - 1] = '\0';
}

static void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags)
{
    char temp_buffer[5];
    if (len < sizeof(temp_buffer))
    {
        memcpy (temp_buffer, data, len);
        temp_buffer[len] = '\0';
    }

    int part = 0;
    char *token = strtok(current_topic, "/");
    char *control = NULL;
    char *sensor_type = NULL;

    // example topic: 
    //     edge/+/incoming/moisture
    while (token != NULL)
    {
        if (part == 2)
        {
            control = token;
        }
        else if (part == 3)
        {
            sensor_type = token;
        }

        token = strtok(NULL, "/");
        part++;
    }

    if (strcmp(control, "set") == 0)
    {
        if (strcmp(sensor_type, "moisture") == 0)
        {
            moisture_threshold = atoi(temp_buffer);
            printf("New moisture threshold set to: %d\n", moisture_threshold);
        }
        else if (strcmp(sensor_type, "photoresistor") == 0)
        {
            photoresistor_threshold = atoi(temp_buffer);
            printf("New photoresistor threshold set to: %d\n", photoresistor_threshold);
        }
    } else
    {
        if (strcmp(sensor_type, "moisture") == 0)
        {
            moisture_value = atoi(temp_buffer);
            printf("New moisture value: %d\n", photoresistor_value);
        }
        else if (strcmp(sensor_type, "photoresistor") == 0)
        {
            photoresistor_value = atoi(temp_buffer);
            printf("New photoresistor value: %d\n", photoresistor_value);
        }
    }

}
