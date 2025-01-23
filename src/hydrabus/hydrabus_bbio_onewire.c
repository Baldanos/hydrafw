/*
 * HydraBus/HydraNFC
 *
 * Copyright (C) 2014-2016 Benjamin VERNOUX
 * Copyright (C) 2016 Nicolas OBERLI
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "common.h"
#include "tokenline.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "bsp.h"
#include "hydrabus_bbio.h"
#include "hydrabus_bbio_onewire.h"
#include "hydrabus_mode_onewire.h"
#include "hydrabus_bbio_aux.h"


static void bbio_mode_id(t_hydra_console *con)
{
	cprint(con, BBIO_ONEWIRE_HEADER, 4);
}

void bbio_mode_onewire(t_hydra_console *con)
{
	mode_config_proto_t* proto = &con->mode->proto;
	uint32_t swio_data;
	uint8_t bbio_subcommand, i;
	uint8_t rx_data[16], tx_data[16];
	uint8_t data;
	bsp_status_t status;

	onewire_init_proto_default(con);
	onewire_pin_init(con);

	bbio_mode_id(con);

	while (!hydrabus_ubtn()) {
		if(chnRead(con->sdu, &bbio_subcommand, 1) == 1) {
			switch(bbio_subcommand) {
			case BBIO_RESET:
				onewire_cleanup(con);
				return;
			case BBIO_MODE_ID:
				bbio_mode_id(con);
				break;
			case BBIO_ONEWIRE_RESET:
				onewire_start(con);
				break;
			case BBIO_ONEWIRE_READ:
				rx_data[0] = onewire_read_u8(con);
				cprint(con, (char *)&rx_data[0], 1);
				break;
			case BBIO_ONEWIRE_SWIO_READ:
				chnRead(con->sdu, &data, 1);
				swio_data = onewire_swio_read_reg(con, data);
				cprint(con, (void *)&swio_data, 4);
				break;
			case BBIO_ONEWIRE_SWIO_WRITE:
				chnRead(con->sdu, &data, 1);
				chnRead(con->sdu, (uint8_t *)&swio_data, 4);
				onewire_swio_write_reg(con, data, swio_data);
				cprint(con, "\x01", 1);
				break;
			default:
				if ((bbio_subcommand & BBIO_AUX_MASK) == BBIO_AUX_MASK) {
					cprintf(con, "%c", bbio_aux(con, bbio_subcommand));
				} else if ((bbio_subcommand & BBIO_ONEWIRE_BULK_TRANSFER) == BBIO_ONEWIRE_BULK_TRANSFER) {
					// data contains the number of bytes to
					// write
					data = (bbio_subcommand & 0b1111) + 1;

					chnRead(con->sdu, tx_data, data);
					for(i=0; i<data; i++) {
						onewire_write_u8(con, tx_data[i]);
					}
					cprint(con, "\x01", 1);
				} else if ((bbio_subcommand & BBIO_ONEWIRE_CONFIG_PERIPH) == BBIO_ONEWIRE_CONFIG_PERIPH) {
					if(bbio_subcommand & 0b1000) {
						onewire_init_proto_swio(con);
						proto->config.onewire.dev_gpio_pull = (bbio_subcommand & 0b100)?1:0;
						status = onewire_pin_init(con);
						onewire_swio_reset(con);
					} else {
						onewire_init_proto_default(con);
						proto->config.onewire.dev_gpio_pull = (bbio_subcommand & 0b100)?1:0;
						status = onewire_pin_init(con);
					}
					//Set AUX[0] (PC4) value
					bbio_aux_write((bbio_subcommand & 0b10)>>1);

					if(status == BSP_OK) {
						cprint(con, "\x01", 1);
					} else {
						cprint(con, "\x00", 1);
					}
				}
			}
		}
	}
	onewire_cleanup(con);
}
