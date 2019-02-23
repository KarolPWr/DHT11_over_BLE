#ifndef DUMMY_BLE_SRV_H__
#define DUMMY_BLE_SRV_H__

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"

#define LBS_UUID_BASE {0x23, 0xD1, 0xBC, 0xEA, 0x5F, 0x78, 0x23, 0x15, 0xDE, 0xEF, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00}
#define LBS_UUID_SERVICE 0x1523
#define LBS_UUID_LED_CHAR 0x1525
#define LBS_UUID_BUTTON_CHAR 0x1524

// Forward declaration of the ble_dht_t type. 
typedef struct ble_dht_s ble_dht_t;

typedef void (*ble_dht_write_handler_t) (ble_dht_t * p_dht, uint8_t new_state);

typedef struct
{
    ble_dht_write_handler_t dht_write_handler;                    /**< Event handler to be called when dht characteristic is written. */
} ble_dht_init_t;

/**@brief DHT Service structure. This contains various status information for the service. */
typedef struct ble_dht_s
{
    uint16_t                    service_handle;
    ble_gatts_char_handles_t    dht_handles;
    //ble_gatts_char_handles_t    button_char_handles;
    uint8_t                     uuid_type;
    uint16_t                    conn_handle;
    ble_dht_write_handler_t dht_write_handler;
} ble_dht_t;

/**@brief Function for initializing the LED Button Service.
 *
 * @param[out]  p_dht       DHT structure. This structure will have to be supplied by
 *                          the application. It will be initialized by this function, and will later
 *                          be used to identify this particular service instance.
 * @param[in]   p_dht_init  Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
uint32_t ble_dht_init(ble_dht_t * p_dht, const ble_dht_init_t * p_dht_init);

/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the LED Button Service.
 *
 *
 * @param[in]   p_dht      LED Button Service structure.
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 */
void ble_dht_on_ble_evt(ble_dht_t * p_dht, ble_evt_t * p_ble_evt);

/**@brief Function for sending a sensor reading notification.
 */
uint32_t ble_dht_on_reading_change(ble_dht_t * p_dht, uint8_t dht_state);



#endif
