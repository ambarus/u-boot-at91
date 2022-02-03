/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Chip-specific header file for the SAMA7G5 SoC
 *
 * Copyright (C) 2020 Microchip Technology, Inc. and its subsidiaries
 *		      Eugen Hristev <eugen.hristev@microchip.com>
 */

#ifndef __SAMA7G5_H__
#define __SAMA7G5_H__

/*
 * Peripheral identifiers/interrupts.
 */
#define ATMEL_ID_HSMC		21
#define ATMEL_ID_FLEXCOM0	38
#define ATMEL_ID_FLEXCOM1	39
#define ATMEL_ID_FLEXCOM2	40
#define ATMEL_ID_FLEXCOM3	41

#define ATMEL_ID_SDMMC0		80
#define ATMEL_ID_SDMMC1		81

#define ATMEL_ID_PIT64B0	70
#define ATMEL_ID_PIT64B		ATMEL_ID_PIT64B0

#define ATMEL_CHIPID_CIDR	0xe0020000
#define ATMEL_CHIPID_EXID	0xe0020004
/*
 * User Peripherals physical base addresses.
 */
#define ATMEL_BASE_PIOA		0xe0014000
#define ATMEL_BASE_PIOB		(ATMEL_BASE_PIOA + 0x40)
#define ATMEL_BASE_PIOC		(ATMEL_BASE_PIOB + 0x40)
#define ATMEL_BASE_PIOD		(ATMEL_BASE_PIOC + 0x40)
#define ATMEL_BASE_PIOE		(ATMEL_BASE_PIOD + 0x40)

#define ATMEL_PIO_PORTS		5

#define CPU_HAS_PCR

#define ATMEL_BASE_PMC		0xe0018000

#define ATMEL_BASE_WDT		0xe001c000
#define ATMEL_BASE_RSTC		0xe001d000
#define ATMEL_BASE_WDTS		0xe001d180
#define ATMEL_BASE_SCKCR	0xe001d050

#define ATMEL_BASE_HSMC		0xe0808000

#define ATMEL_BASE_SDMMC0	0xe1204000
#define ATMEL_BASE_SDMMC1	0xe1208000

#define ATMEL_BASE_PIT64B0	0xe1800000

#define ATMEL_BASE_FLEXCOM0	0xe1818000
#define ATMEL_BASE_FLEXCOM1	0xe181c000
#define ATMEL_BASE_FLEXCOM2	0xe1820000
#define ATMEL_BASE_FLEXCOM3	0xe1824000
#define ATMEL_BASE_FLEXCOM4	0xe2018000

#define ATMEL_BASE_TZC400	0xe3000000

#define ATMEL_BASE_UMCTL2	0xe3800000
#define ATMEL_BASE_UMCTL2_MP	0xe38003f8
#define ATMEL_BASE_PUBL		0xe3804000

#define ATMEL_NUM_FLEXCOM	12
#define ATMEL_PIO_PORTS		5

#define ATMEL_BASE_PIT64BC	ATMEL_BASE_PIT64B0
/*
 * Internal Memory.
 */
#define ATMEL_BASE_ROM		0x00020000

/*
 * External memory
 */
#define ATMEL_BASE_CS0		0x40000000
#define ATMEL_BASE_CS1		0x48000000
#define ATMEL_BASE_CS2		0x50000000
#define ATMEL_BASE_CS3		0x58000000

/*
 * Other misc definitions
 */
#define ATMEL_BASE_PMECC	(ATMEL_BASE_HSMC + 0x70)
#define ATMEL_BASE_PMERRLOC	(ATMEL_BASE_HSMC + 0x500)
#define ATMEL_BASE_SMC		(ATMEL_BASE_HSMC + 0x700)

/*
 * PMECC table in ROM
 */
#define ATMEL_PMECC_INDEX_OFFSET_512	0x0
#define ATMEL_PMECC_INDEX_OFFSET_1024	0x8000

#ifndef __ASSEMBLY__
char *get_cpu_name(void);
#endif

#endif /* #ifndef __SAMA7G5_H__ */
