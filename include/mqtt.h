#ifndef MQTT_H
#define MQTT_H

#include "lwip/apps/mqtt.h"

#define BROKER_ADDRESS "192.168.1.220"
#define CLIENT_ID "pico_w_01"

static mqtt_client_t *mqtt_client;
static mqtt_client = mqtt_client_new();
static struct mqtt_connect_client_info_t client_info = {
    .client_id = CLIENT_ID,
    .client_user = NULL,
    .client_pass = NULL,
    .keep_alive = 60,
    .will_topic = NULL,
    .will_msg = NULL,
    .will_qos = 0,
    .will_retain = 0,
};

static ip_addr_t broker_ip;
static ip4addr_aton(BROKER_ADDRESS, &broker_ip);

int mqtt_init();
static void mqtt_connection_cb(mqtt_client, &broker_ip, 1883, mqtt_connection_cb, NULL, &client_info);
static void mqtt_pub_request(void *arg, err_t result);

#endif
