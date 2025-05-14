#pragma once

#include "lwip/apps/mqtt.h"

#define BROKER_ADDRESS "192.168.0.40"
#define CLIENT_ID "pico_w_01"

extern volatile int moisture_threshold;
extern volatile int moisture_value;
extern volatile int photoresistor_threshold;
extern volatile int photoresistor_value;

static char current_topic[64];

static mqtt_client_t *mqtt_client;
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

err_t mqtt_connect(void);
err_t mqtt_pub_sensor_read(const char* sensor, int value);
err_t mqtt_sub(const char* topic);
static void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status);
static void mqtt_pub_cb(void *arg, err_t result);
static void mqtt_sub_cb(void *arg, err_t result);
static void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len);
static void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags);
