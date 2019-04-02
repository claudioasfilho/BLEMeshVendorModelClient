/***********************************************************************************************//**
 * \file   client.app.c
 * \brief  Silicon Labs BT Mesh Empty Example Project
 *
 * This example demonstrates the bare minimum needed for a Blue Gecko BT Mesh C application.
 * The application starts unprovisioned Beaconing after boot
 ***************************************************************************************************
 * <b> (C) Copyright 2017 Silicon Labs, http://www.silabs.com</b>
 ***************************************************************************************************
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 **************************************************************************************************/

/* Board headers */
#include "init_mcu.h"
#include "init_board.h"
#include "init_app.h"
#include "ble-configuration.h"
#include "board_features.h"

/* Bluetooth stack headers */
#include "bg_types.h"
#include "native_gecko.h"
#include "gatt_db.h"
#include <gecko_configuration.h>
#include <mesh_sizes.h>

/* Libraries containing default Gecko configuration values */
#include "em_emu.h"
#include "em_cmu.h"
#include <em_gpio.h>

/* Device initialization header */
#include "hal-config.h"

#if defined(HAL_CONFIG)
#include "bsphalconfig.h"
#else
#include "bspconfig.h"
#endif

#include "client_app.h"


#define BUTTON0_PIN         (2U)
#define BUTTON0_PORT        (gpioPortD)
#define BUTTON1_PIN         (3U)
#define BUTTON1_PORT        (gpioPortD)
#define LED0_PIN			(0U)
#define LED0_PORT			(gpioPortB)
#define LED1_PIN			(1U)
#define LED1_PORT			(gpioPortB)

#define PB0_PRESS_EXTSIGNAL 		(1 << 16)
#define PB1_PRESS_EXTSIGNAL       	(1 << 17)

/* The default settings of the network and the node */
#define SERVER_NODE_ADDR				0x729a
#define NET_KEY_IDX 					0
#define APP_KEY_IDX						0
#define IVI 							0
#define DEFAULT_TTL 					3
#define ELEMENT_ID						0


static uint8_t finished = 0;
static uint16_t uni_addr = 0;
static uint8_t pub_enable = 0;
static opcodes_t my_opc[] = {pub_addr_get, pub_addr_st, user_name, congrat};

static uint8_t my_name[] = "Claudio";




/* List of the opcodes client model suppports */
//static opcodes_t my_opc[] = {pub_addr_get, pub_addr_st, user_name, congrat};
/* Network key, device key and application key */
static aes_key_128 enc_key = {
	.data = "\x03\x03\x03\x03\x03\x03\x03\x03\x03\x03\x03\x03\x03\x03\x03\x03"
};

#define RESET_TIMER_ID 62
#define P_PUB_TIMER_ID					56

static void delay_reset(uint32_t ms)
{
    if(ms < 10)
        ms = 10;
gecko_cmd_hardware_set_soft_timer(328*(ms/10), RESET_TIMER_ID, 1); }

/***********************************************************************************************//**
 * @addtogroup gpio
 * @{
 **************************************************************************************************/
static void GPIO_Common_IRQHandler() {
	uint32_t flags = GPIO_IntGet();
	GPIO_IntClear(flags);

	if (flags & (1 << BUTTON0_PIN)) {
		//Send interupt event to the main loop
		gecko_external_signal(PB0_PRESS_EXTSIGNAL);
	}
	if (flags & (1 << BUTTON1_PIN)) {
		//Send interupt event to the main loop
		gecko_external_signal(PB1_PRESS_EXTSIGNAL);
	}
}

void GPIO_EVEN_IRQHandler() {
	GPIO_Common_IRQHandler();
}
void GPIO_ODD_IRQHandler() {
	GPIO_Common_IRQHandler();
}

void gpio_init() {
	// Enable GPIO clock.
	CMU_ClockEnable(cmuClock_GPIO, true);

	// Configure PB0 as input and enable interrupt.
	GPIO_PinModeSet(BUTTON0_PORT, BUTTON0_PIN, gpioModeInputPullFilter, 1);
	GPIO_IntConfig(BUTTON0_PORT, BUTTON0_PIN, false, true, true);

	// Configure PB1 as input and enable interrupt.
	GPIO_PinModeSet(BUTTON1_PORT, BUTTON1_PIN, gpioModeInputPullFilter, 1);
	GPIO_IntConfig(BUTTON1_PORT, BUTTON1_PIN, false, true, true);

	NVIC_ClearPendingIRQ(GPIO_EVEN_IRQn);
	NVIC_EnableIRQ(GPIO_EVEN_IRQn);

	NVIC_ClearPendingIRQ(GPIO_ODD_IRQn);
	NVIC_EnableIRQ(GPIO_ODD_IRQn);

	// Turn off by defaut
	GPIO_PinModeSet(LED0_PORT, LED0_PIN, gpioModePushPull, 0);
	GPIO_PinModeSet(LED1_PORT, LED1_PIN, gpioModePushPull, 0);
}

static void handle_gecko_generic(struct gecko_cmd_packet *evt)
{
	switch(BGLIB_MSG_ID(evt->header))
	{
		case gecko_evt_system_external_signal_id:
			{
				if (evt->data.evt_system_external_signal.extsignals & PB0_PRESS_EXTSIGNAL)
				{
					/* Handle PB0 press event here */
					printf("Send unicast once.\n");

					/* Send unicast to server to get the addresses */
					gecko_cmd_mesh_vendor_model_send(ELEMENT_ID, VENDOR_ID, CLIENT_MODEL_ID, SERVER_NODE_ADDR, 0, APP_KEY_IDX, 0, my_opc[0], 1, 0, NULL);

				}
				if (evt->data.evt_system_external_signal.extsignals & PB1_PRESS_EXTSIGNAL)
				{
					/* Handle PB0 press event here */
					gecko_cmd_flash_ps_erase_all();
				}
				break;
			}
	}
}

static void handle_gecko_event(uint32_t evt_id, struct gecko_cmd_packet *evt);
bool mesh_bgapi_listener(struct gecko_cmd_packet *evt);

void AppHandler(void)
{
	gecko_bgapi_class_mesh_vendor_model_init();
	gpio_init();

	while (1) {
		struct gecko_cmd_packet *evt = gecko_wait_event();
		bool pass = mesh_bgapi_listener(evt);
		handle_gecko_generic(evt);
		if (pass) {
			handle_gecko_event(BGLIB_MSG_ID(evt->header), evt);
		}

	}
}

static void handle_gecko_event(uint32_t evt_id, struct gecko_cmd_packet *evt)
{
	switch (evt_id) {
		case gecko_evt_system_boot_id:


			printf("I am alive\n\r");
			// Initialize Mesh stack in Node operation mode, wait for initialized event
			gecko_cmd_mesh_node_init();
			break;

		case gecko_evt_hardware_soft_timer_id:
			switch(evt->data.evt_hardware_soft_timer.handle)
			{
				/* Handler soft timer here when it expires */
				case RESET_TIMER_ID:
					gecko_cmd_system_reset(0);
				break;
				default:
					break;
			}
			break;
		case gecko_evt_mesh_node_initialized_id:
			{
				struct gecko_msg_mesh_node_initialized_evt_t *ret = (struct gecko_msg_mesh_node_initialized_evt_t *)&evt->data;
				
				/* Unicast address will be used in the following code, so get it here */
				
				/* Derive the unicast address from the LSB 2 bytes from the BD_ADDR */
				struct gecko_msg_system_get_bt_address_rsp_t *bd_ret = gecko_cmd_system_get_bt_address();
				uni_addr =((bd_ret->address.addr[1] << 8) | bd_ret->address.addr[0]) & 0x7FFF;
				printf("Unicast Address = 0x%04X\n", uni_addr);

				/* Provision itself if not provisioned yet */
				if(ret->provisioned)
				{
					/* Node is provisioned already */
					struct gecko_msg_mesh_node_initialized_evt_t *ret = (struct gecko_msg_mesh_node_initialized_evt_t *)&evt->data;
					printf("Node Initialized...\n");

					/* Derive the unicast address from the LSB 2 bytes from the BD_ADDR */
					struct gecko_msg_system_get_bt_address_rsp_t *bd_ret = gecko_cmd_system_get_bt_address();
					uni_addr =((bd_ret->address.addr[1] << 8) | bd_ret->address.addr[0]) & 0x7FFF;
					printf("Unicast Address = 0x%04X\n", uni_addr);
				}else
				{
					/* Node is not provisioned yet */
					/* Provision the node locally */
					gecko_cmd_mesh_node_set_provisioning_data(enc_key, enc_key, NET_KEY_IDX, IVI, uni_addr, 0);
					delay_reset(100);
					break;
				}

				/* Initialize the vendor model */

				gecko_cmd_mesh_vendor_model_init(ELEMENT_ID, VENDOR_ID, CLIENT_MODEL_ID, true, sizeof(my_opc), my_opc);
				/* Add an application key locally */
				gecko_cmd_mesh_test_add_local_key(1, enc_key, APP_KEY_IDX, NET_KEY_IDX);
				/* Bind the application key to the vendor client model */
				gecko_cmd_mesh_test_bind_local_model_app(ELEMENT_ID, APP_KEY_IDX, VENDOR_ID, CLIENT_MODEL_ID);



				/* Enable relay by default */
				gecko_cmd_mesh_test_set_relay(1, 0, 0);
				break;
			}
		case gecko_evt_mesh_vendor_model_receive_id:
			{
				struct gecko_msg_mesh_vendor_model_receive_evt_t *re_evt = (struct gecko_msg_mesh_vendor_model_receive_evt_t *)&evt->data;
				/* Get publication address && Use unicast (Destination address is not group address) */
				if(re_evt->opcode == pub_addr_st)
				{
					/* Got the addresses, parse the data */
					uint16_t pub_addr = 0, sub_addr = 0;
					memcpy((uint8_t *)&pub_addr, re_evt->payload.data, 2);
					memcpy((uint8_t *)&sub_addr, re_evt->payload.data+2, 2);

					/* Set the publication and subscription, then may try publishing User Name to the server node */
					struct gecko_msg_mesh_test_get_local_model_pub_rsp_t *pub_setting = gecko_cmd_mesh_test_get_local_model_pub(ELEMENT_ID, VENDOR_ID, CLIENT_MODEL_ID);

					if(!pub_setting->result && pub_setting->pub_address == pub_addr)
					{
						printf("Configuration done already.\n");
						/* Node it already configured, no need to configure again */
					}else
					{
						printf("***Received the addresses from the server side.*** Pub = 0x%04X, Sub = 0x%04X\n", pub_addr, sub_addr);
						printf("Set local model pub...\n");
						/* Set the publication address locally */
						gecko_cmd_mesh_test_set_local_model_pub(ELEMENT_ID, APP_KEY_IDX, VENDOR_ID, CLIENT_MODEL_ID, pub_addr, DEFAULT_TTL, 0, 0, 0);
						printf("Add local model sub...\n");
						/* Add a subscription address locally */
						gecko_cmd_mesh_test_add_local_model_sub(ELEMENT_ID, VENDOR_ID, CLIENT_MODEL_ID, sub_addr);
						/* Set up the publication data with User Name */
						gecko_cmd_mesh_vendor_model_set_publication(ELEMENT_ID, VENDOR_ID, CLIENT_MODEL_ID, user_name, 1, sizeof(my_name)-1, my_name);
						pub_enable = 1;
						printf("Publish once.\n");
						/* Publish once, the data was set before */
						gecko_cmd_mesh_vendor_model_publish(ELEMENT_ID, VENDOR_ID, CLIENT_MODEL_ID);
					}
					
				}
				/* Trainees send the user name from the subscribed group */
				else if(re_evt->opcode == congrat)
				{
									/* Congratulation message received, you have done the hands-on, parse the list if you want */
									printf("name list = ");
									if(!finished)
									{
										for(uint8_t i = 0; i < re_evt->payload.len; i++)
										{
											if(!memcmp(re_evt->payload.data + i, (uint8_t *)&uni_addr, sizeof(uint16_t)))
											{
												/* Stop the publication of user name if it exists in the congrat list already */
												finished = 1;
												gecko_cmd_hardware_set_soft_timer(0, P_PUB_TIMER_ID, 0);
												break;
											}
										}
									}
				}
			}
			break;

		case gecko_evt_le_connection_closed_id:
			/* Check if need to boot to dfu mode */
			break;
		default:
			break;
	}
}
