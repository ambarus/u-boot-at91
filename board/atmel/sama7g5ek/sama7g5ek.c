// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2020 Microchip Technology, Inc.
 *		      Eugen Hristev <eugen.hristev@microchip.com>
 */

#include <common.h>
#include <debug_uart.h>
#include <init.h>
#include <clk.h>
#include <asm/global_data.h>
#include <asm/io.h>
#include <asm/arch/at91_common.h>
#include <asm/arch/atmel_pio4.h>
#include <asm/arch/clk.h>
#include <asm/arch/gpio.h>
#include <asm/arch/sama7g5.h>
#include <asm/arch/sama5d2_smc.h>
#include <dm/uclass.h>

DECLARE_GLOBAL_DATA_PTR;

static void board_leds_init(void)
{
	atmel_pio4_set_pio_output(AT91_PIO_PORTB, 8, 0);	/* LED RED */
	atmel_pio4_set_pio_output(AT91_PIO_PORTA, 13, 0);	/* LED GREEN */
	atmel_pio4_set_pio_output(AT91_PIO_PORTD, 20, 1);	/* LED BLUE */
}

int board_late_init(void)
{
	return 0;
}

#if (IS_ENABLED(CONFIG_DEBUG_UART_BOARD_INIT))
static void board_uart0_hw_init(void)
{
	/* FLEXCOM3 IO0 */
	atmel_pio4_set_f_periph(AT91_PIO_PORTD, 17, ATMEL_PIO_PUEN_MASK);
	/* FLEXCOM3 IO1 */
	atmel_pio4_set_f_periph(AT91_PIO_PORTD, 16, 0);

	at91_periph_clk_enable(ATMEL_ID_FLEXCOM3);
}

void board_debug_uart_init(void)
{
	board_uart0_hw_init();
}
#endif

int board_early_init_f(void)
{
#if (IS_ENABLED(CONFIG_DEBUG_UART))
	debug_uart_init();
#endif
	return 0;
}

#define MAC24AA_MAC_OFFSET     0xfa

#if (IS_ENABLED(CONFIG_MISC_INIT_R))
int misc_init_r(void)
{
#if (IS_ENABLED(CONFIG_I2C_EEPROM))
	at91_set_ethaddr(MAC24AA_MAC_OFFSET);
	at91_set_eth1addr(MAC24AA_MAC_OFFSET);
#endif
	return 0;
}
#endif

#ifdef CONFIG_NAND_ATMEL
static void sama7g5ek_nand_hw_init(void)
{
	struct at91_smc *smc = (struct at91_smc *)ATMEL_BASE_SMC;

	at91_periph_clk_enable(ATMEL_ID_HSMC);

	writel(AT91_SMC_SETUP_NWE(4), &smc->cs[3].setup);
	writel(AT91_SMC_PULSE_NWE(10) | AT91_SMC_PULSE_NCS_WR(20) |
	       AT91_SMC_PULSE_NRD(10) | AT91_SMC_PULSE_NCS_RD(20),
	       &smc->cs[3].pulse);
	writel(AT91_SMC_CYCLE_NWE(20) | AT91_SMC_CYCLE_NRD(20),
	       &smc->cs[3].cycle);
	writel(AT91_SMC_TIMINGS_TCLR(4) | AT91_SMC_TIMINGS_TADL(15) |
	       AT91_SMC_TIMINGS_TAR(5)  | AT91_SMC_TIMINGS_TRR(8)   |
	       AT91_SMC_TIMINGS_TWB(8)  | AT91_SMC_TIMINGS_NFSEL(1),
	       &smc->cs[3].timings);
	writel(AT91_SMC_MODE_RM_NRD | AT91_SMC_MODE_WM_NWE |
	       AT91_SMC_MODE_TDF | AT91_SMC_MODE_TDF_CYCLE(15),
	       &smc->cs[3].mode);

	atmel_pio4_set_d_periph(AT91_PIO_PORTD, 9, 0);	/* NAND_D0 */
	atmel_pio4_set_d_periph(AT91_PIO_PORTD, 10, 0);	/* NAND_D1 */
	atmel_pio4_set_d_periph(AT91_PIO_PORTD, 11, 0);	/* NAND_D2 */
	atmel_pio4_set_d_periph(AT91_PIO_PORTC, 21, 0);	/* NAND_D3 */
	atmel_pio4_set_d_periph(AT91_PIO_PORTC, 22, 0);	/* NAND_D4 */
	atmel_pio4_set_d_periph(AT91_PIO_PORTC, 23, 0);	/* NAND_D5 */
	atmel_pio4_set_d_periph(AT91_PIO_PORTC, 24, 0);	/* NAND_D6 */
	atmel_pio4_set_d_periph(AT91_PIO_PORTD, 2, 0);	/* NAND_D7 */
	atmel_pio4_set_d_periph(AT91_PIO_PORTD, 5, 0);	/* NAND_WE */
	atmel_pio4_set_d_periph(AT91_PIO_PORTD, 6, 0);	/* NAND_OE */
	atmel_pio4_set_d_periph(AT91_PIO_PORTD, 7, 0);	/* NAND_ALE */
	atmel_pio4_set_d_periph(AT91_PIO_PORTD, 8, 0);	/* NAND_CLE */
	atmel_pio4_set_d_periph(AT91_PIO_PORTD, 3, 0);	/* NAND_RDY */
	atmel_pio4_set_d_periph(AT91_PIO_PORTD, 4, 0);	/* NAND_CS */
}
#endif

int board_init(void)
{
	/* address of boot parameters */
	gd->bd->bi_boot_params = CONFIG_SYS_SDRAM_BASE + 0x100;

#ifdef CONFIG_NAND_ATMEL
	sama7g5ek_nand_hw_init();
#endif

	board_leds_init();

	return 0;
}

int dram_init(void)
{
	gd->ram_size = get_ram_size((void *)CONFIG_SYS_SDRAM_BASE,
				    CONFIG_SYS_SDRAM_SIZE);
	return 0;
}

