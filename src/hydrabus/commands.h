/*
 * HydraBus/HydraNFC
 *
 * Copyright (C) 2014 Bert Vermeulen <bert@biot.com>
 * Copyright (C) 2014-2017 Benjamin VERNOUX
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
/* Developer warning keep this list synchronized with same number of items and same items order as commands.c => t_token_dict tl_dict */
enum {
	T_HELP = 1,
	T_HISTORY,
	T_EXIT,
	T_CLEAR,
	T_DEBUG,
	T_SHOW,
	T_SYSTEM,
	T_MEMORY,
	T_THREADS,
	T_SD,
	T_MOUNT,
	T_UMOUNT,
	T_CD,
	T_PWD,
	T_LS,
	T_CAT,
	T_HD,
	T_ERASE,
	T_REALLY,
	T_TESTPERF,
	T_MODE,
	T_SPI,
	T_I2C,
	T_DEVICE,
	T_MASTER,
	T_SLAVE,
	T_FREQUENCY,
	T_POLARITY,
	T_PHASE,
	T_MSB_FIRST,
	T_LSB_FIRST,
	T_PULL,
	T_UP,
	T_DOWN,
	T_FLOATING,
	T_ON,
	T_OFF,
	T_CS_ON,
	T_CS_OFF,
	T_PINS,
	T_READ,
	T_WRITE,
	T_START,
	T_STOP,
	T_UART,
	T_SPEED,
	T_PARITY,
	T_NONE,
	T_EVEN,
	T_ODD,
	T_STOP_BITS,
	T_ADC,
	T_ADC1,
	T_TEMPSENSOR,
	T_VREFINT,
	T_VBAT,
	T_SAMPLES,
	T_PERIOD,
	T_CONTINUOUS,
	T_SCAN,
#ifdef HYDRANFC
	T_NFC,
	T_TYPEA,
	T_VICINITY,
	T_EMUL_MIFARE,
	T_EMUL_ISO14443A,
	T_REGISTERS,
	T_READ_MF_ULTRALIGHT,
	T_EMUL_MF_ULTRALIGHT,
	T_CLONE_MF_ULTRALIGHT,
	T_TRACE_UART1,
	T_FRAME_TIME,
	T_PCAP,
	T_BIN,
	T_DIRECT_MODE_0,
	T_DIRECT_MODE_1,
#endif
	T_SNIFF,
	T_GPIO,
	T_IN,
	T_OUT,
	T_OPEN_DRAIN,
	T_TOKENLINE,
	T_TIMING,
	T_DEBUG_TEST_RX,
	T_RM,
	T_MKDIR,
	T_LOGGING,
	T_DAC,
	T_DAC1,
	T_DAC2,
	T_RAW,
	T_VOLT,
	T_TRIANGLE,
	T_NOISE,
	T_PWM,
	T_DUTY_CYCLE,
	T_BRIDGE,
	T_SUMP,
	T_JTAG,
	T_TCK,
	T_TMS,
	T_TDI,
	T_TDO,
	T_TRST,
	T_QUERY,
	T_BRUTE,
	T_BYPASS,
	T_IDCODE,
	T_OOCD,
	T_RNG,
	T_TWOWIRE,
	T_CAN,
	T_ID,
	T_MASK,
	T_FILTER,
	T_LOW,
	T_HIGH,
	T_THREEWIRE,
	T_SCRIPT,
	T_FILE,
	T_ONEWIRE,
	T_FLASH,
	T_TRIGGER,
	T_SLCAN,
	T_TS1,
	T_TS2,
	T_SJW,
	T_WIEGAND,
	T_LIN,
	T_SMARTCARD,
	T_ATR,
	T_GUARDTIME,
	T_PRESCALER,
	T_CONVENTION,
	T_DELAY,
	T_CLOCK_STRETCH,
	T_TIMEOUT,
	T_PEEK,
	T_POKE,
	T_SWIO,
	T_CONTINUITY,
	/* Developer warning add new command(s) here */

	/* BP-compatible commands */
	T_LEFT_SQ,
	T_RIGHT_SQ,
	T_LEFT_CURLY,
	T_RIGHT_CURLY,
	T_SLASH,
	T_BACKSLASH,
	T_MINUS,
	T_UNDERSCORE,
	T_EXCLAMATION,
	T_CARET,
	T_DOT,
	T_AMPERSAND,
	T_PERCENT,
	T_TILDE,
	T_AUX_OFF,
	T_AUX_ON,
	T_AUX_READ,
};

