/*
 * (C) Copyright 2012 - 2013 Xilinx
 * (C) Copyright 2012 Michal Simek <monstr@monstr.eu>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_ZYNQ_H
#define __CONFIG_ZYNQ_H

/* High Level Configuration Options */
#define CONFIG_ARMV7 /* CPU */
#define CONFIG_ZYNQ /* SoC */

/* Default environment */
#define CONFIG_IPADDR	10.10.70.102
#define CONFIG_SERVERIP	10.10.70.101

#define CONFIG_SYS_SDRAM_BASE	0
#define CONFIG_SYS_SDRAM_SIZE	PHYS_SDRAM_1_SIZE

/* TEXT BASE defines */
#if defined(CONFIG_CSE_QSPI) || defined(CONFIG_CSE_NOR)
# define CONFIG_SYS_TEXT_BASE		0xFFFC4800
#elif defined(CONFIG_CSE_NAND)
# define CONFIG_SYS_TEXT_BASE		0x00100000
#else
# define CONFIG_SYS_TEXT_BASE		0x04000000
#endif

/* Total Size of Environment Sector */
#define CONFIG_ENV_SIZE			(128 << 10)

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		0x400000

/* Serial drivers */
#define CONFIG_BAUDRATE			115200
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 38400, 115200 }

/* Zynq serial driver */
#ifdef CONFIG_ZYNQ_SERIAL_UART0
# define CONFIG_ZYNQ_SERIAL_BASEADDR0	0xE0000000
# define CONFIG_ZYNQ_SERIAL_BAUDRATE0	CONFIG_BAUDRATE
# define CONFIG_ZYNQ_SERIAL_CLOCK0	50000000
#endif

#ifdef CONFIG_ZYNQ_SERIAL_UART1
# define CONFIG_ZYNQ_SERIAL_BASEADDR1	0xE0001000
# define CONFIG_ZYNQ_SERIAL_BAUDRATE1	CONFIG_BAUDRATE
# define CONFIG_ZYNQ_SERIAL_CLOCK1	50000000
#endif

#if defined(CONFIG_ZYNQ_SERIAL_UART0) || defined(CONFIG_ZYNQ_SERIAL_UART1)
#define CONFIG_ZYNQ_SERIAL
#endif

/* DCC driver */
#if defined(CONFIG_ZYNQ_DCC)
# define CONFIG_ARM_DCC
# define CONFIG_CPU_V6 /* Required by CONFIG_ARM_DCC */
#endif

/* Ethernet driver */
#if defined(CONFIG_ZYNQ_GEM0) || defined(CONFIG_ZYNQ_GEM1)
# define CONFIG_NET_MULTI
# define CONFIG_ZYNQ_GEM
# define CONFIG_MII
# define CONFIG_SYS_FAULT_ECHO_LINK_DOWN
# define CONFIG_PHYLIB
# define CONFIG_PHY_MARVELL
# define CONFIG_SYS_ENET
#endif

#ifndef CONFIG_CPU_FREQ_HZ
#define CONFIG_CPU_FREQ_HZ		800000000
#endif
#define CONFIG_SYS_HZ			1000

/* Miscellaneous configurable options */
#define CONFIG_SYS_PROMPT		"zynq-uboot> "
#define CONFIG_SYS_HUSH_PARSER	/* use "hush" command parser */
#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "

#define CONFIG_CMDLINE_EDITING
#define CONFIG_AUTO_COMPLETE
#define CONFIG_SYS_LONGHELP
#define CONFIG_BOARD_LATE_INIT
#define CONFIG_SYS_MAXARGS		32
#define CONFIG_SYS_CBSIZE		2048
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + \
					sizeof(CONFIG_SYS_PROMPT) + 16)

/* Open Firmware flat tree */
#define CONFIG_OF_LIBFDT

#include <config_cmd_default.h>

#ifdef CONFIG_SYS_ENET
# define CONFIG_CMD_PING
# define CONFIG_CMD_MII
#else
# undef CONFIG_CMD_NET
# undef CONFIG_CMD_NFS
#endif

/* NOR */
#ifndef CONFIG_SYS_NO_FLASH
# define CONFIG_SYS_FLASH_BASE		0xE2000000
# define CONFIG_SYS_FLASH_SIZE		(16 * 1024 * 1024)
# define CONFIG_SYS_MAX_FLASH_BANKS	1
/* max number of sectors/blocks on one chip */
# define CONFIG_SYS_MAX_FLASH_SECT	512
# define CONFIG_SYS_FLASH_ERASE_TOUT	1000
# define CONFIG_SYS_FLASH_WRITE_TOUT	5000
# define CONFIG_FLASH_SHOW_PROGRESS	10
# define CONFIG_SYS_FLASH_CFI
# undef CONFIG_SYS_FLASH_EMPTY_INFO
# define CONFIG_FLASH_CFI_DRIVER
# undef CONFIG_SYS_FLASH_PROTECTION /* don't use hardware protection */
/* use buffered writes (20x faster) */
# define CONFIG_SYS_FLASH_USE_BUFFER_WRITE
# define CONFIG_ZYNQ_M29EW_WB_HACK
#endif

/* SPI */
#ifdef CONFIG_ZYNQ_SPI
# define CONFIG_SPI_FLASH
# define CONFIG_SPI_FLASH_SST
# define CONFIG_CMD_SPI
# define CONFIG_CMD_SF
#endif

/* QSPI */
#ifdef CONFIG_ZYNQ_QSPI
# define CONFIG_SF_DEFAULT_SPEED	30000000
# define CONFIG_SPI_FLASH
# define CONFIG_SPI_FLASH_BAR
# define CONFIG_SPI_FLASH_SPANSION
# define CONFIG_SPI_FLASH_STMICRO
# define CONFIG_SPI_FLASH_WINBOND
# define CONFIG_CMD_SPI
# define CONFIG_CMD_SF
#endif

/* MMC */
#if defined(CONFIG_ZYNQ_SDHCI0) || defined(CONFIG_ZYNQ_SDHCI1)
# define CONFIG_MMC
# define CONFIG_GENERIC_MMC
# define CONFIG_SDHCI
# define CONFIG_ZYNQ_SDHCI
# define CONFIG_CMD_MMC
# define CONFIG_CMD_FAT
# define CONFIG_SUPPORT_VFAT
# define CONFIG_CMD_EXT2
# define CONFIG_DOS_PARTITION
#endif

/* NAND */
#ifdef CONFIG_NAND_ZYNQ
# define CONFIG_CMD_NAND
# define CONFIG_CMD_NAND_LOCK_UNLOCK
# define CONFIG_SYS_MAX_NAND_DEVICE 1
# define CONFIG_SYS_NAND_SELF_INIT
# define CONFIG_SYS_NAND_ONFI_DETECTION
# define CONFIG_MTD_DEVICE
#endif

/* I2C */
#if defined(CONFIG_ZYNQ_I2C0) || defined(CONFIG_ZYNQ_I2C1)
# define CONFIG_CMD_I2C
# define CONFIG_ZYNQ_I2C
# define CONFIG_HARD_I2C
# define CONFIG_SYS_I2C_SPEED		100000
# define CONFIG_SYS_I2C_SLAVE		1
#endif

/* EEPROM */
#ifdef CONFIG_ZYNQ_EEPROM
# define CONFIG_CMD_EEPROM
# define CONFIG_SYS_I2C_EEPROM_ADDR_LEN		1
# define CONFIG_SYS_I2C_EEPROM_ADDR		0x54
# define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS	4
# define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS	5
# define CONFIG_SYS_EEPROM_SIZE			1024 /* Bytes */
#endif

#ifndef CONFIG_ENV_IS_NOWHERE
# ifndef CONFIG_SYS_NO_FLASH
/* Environment in NOR flash */
#  define CONFIG_ENV_IS_IN_FLASH
# elif defined(CONFIG_ZYNQ_QSPI)
/* Environment in Serial Flash */
#  define CONFIG_ENV_IS_IN_SPI_FLASH
# elif defined(CONFIG_NAND_ZYNQ)
/* Environment in NAND flash */
#  define CONFIG_ENV_IS_IN_NAND
# elif defined(CONFIG_SYS_NO_FLASH)
#  define CONFIG_ENV_IS_NOWHERE
# endif

# define CONFIG_ENV_SECT_SIZE		CONFIG_ENV_SIZE
# define CONFIG_ENV_OFFSET		0xE0000
# define CONFIG_CMD_SAVEENV	/* Command to save ENV to Flash */
#endif

/* For development/debugging */
#ifdef DEBUG
# define CONFIG_CMD_REGINFO
# define CONFIG_PANIC_HANG
#endif

/* Default environment */
#define CONFIG_EXTRA_ENV_SETTINGS	\
	"ethaddr=00:0a:35:00:01:22\0"	\
	"kernel_image=uImage\0"	\
	"ramdisk_image=uramdisk.image.gz\0"	\
	"devicetree_image=devicetree.dtb\0"	\
	"bitstream_image=system.bit.bin\0"	\
	"loadbit_addr=0x100000\0"	\
	"loadbootenv_addr=0x2000000\0" \
	"kernel_size=0x500000\0"	\
	"devicetree_size=0x20000\0"	\
	"ramdisk_size=0x5E0000\0"	\
	"fdt_high=0x20000000\0"	\
	"initrd_high=0x20000000\0"	\
	"bootenv=uEnv.txt\0" \
	"loadbootenv=fatload mmc 0 ${loadbootenv_addr} ${bootenv}\0" \
	"importbootenv=echo Importing environment from SD ...; " \
		"env import -t ${loadbootenv_addr} $filesize\0" \
	"mmc_loadbit_fat=echo Loading bitstream from SD/MMC/eMMC to RAM.. && " \
		"mmcinfo && " \
		"fatload mmc 0 ${loadbit_addr} ${bitstream_image} && " \
		"fpga load 0 ${loadbit_addr} ${filesize}\0" \
	"norboot=echo Copying Linux from NOR flash to RAM... && " \
		"cp.b 0xE2100000 0x3000000 ${kernel_size} && " \
		"cp.b 0xE2600000 0x2A00000 ${devicetree_size} && " \
		"echo Copying ramdisk... && " \
		"cp.b 0xE2620000 0x2000000 ${ramdisk_size} && " \
		"bootm 0x3000000 0x2000000 0x2A00000\0" \
	"qspiboot=echo Copying Linux from QSPI flash to RAM... && " \
		"sf probe 0 0 0 && " \
		"sf read 0x3000000 0x100000 ${kernel_size} && " \
		"sf read 0x2A00000 0x600000 ${devicetree_size} && " \
		"echo Copying ramdisk... && " \
		"sf read 0x2000000 0x620000 ${ramdisk_size} && " \
		"bootm 0x3000000 0x2000000 0x2A00000\0" \
	"uenvboot=" \
		"if run loadbootenv; then " \
			"echo Loaded environment from ${bootenv}; " \
			"run importbootenv; " \
		"fi; " \
		"if test -n $uenvcmd; then " \
			"echo Running uenvcmd ...; " \
			"run uenvcmd; " \
		"fi\0" \
	"sdboot=if mmcinfo; then " \
			"run uenvboot; " \
			"echo Copying Linux from SD to RAM... && " \
			"fatload mmc 0 0x3000000 ${kernel_image} && " \
			"fatload mmc 0 0x2A00000 ${devicetree_image} && " \
			"fatload mmc 0 0x2000000 ${ramdisk_image} && " \
			"bootm 0x3000000 0x2000000 0x2A00000; " \
		"fi\0" \
	"nandboot=echo Copying Linux from NAND flash to RAM... && " \
		"nand read 0x3000000 0x100000 ${kernel_size} && " \
		"nand read 0x2A00000 0x600000 ${devicetree_size} && " \
		"echo Copying ramdisk... && " \
		"nand read 0x2000000 0x620000 ${ramdisk_size} && " \
		"bootm 0x3000000 0x2000000 0x2A00000\0" \
	"jtagboot=echo TFTPing Linux to RAM... && " \
		"tftp 0x3000000 ${kernel_image} && " \
		"tftp 0x2A00000 ${devicetree_image} && " \
		"tftp 0x2000000 ${ramdisk_image} && " \
		"bootm 0x3000000 0x2000000 0x2A00000\0"

/* default boot is according to the bootmode switch settings */
#define CONFIG_BOOTCOMMAND		"run $modeboot"
#define CONFIG_BOOTDELAY		3 /* -1 to Disable autoboot */
#define CONFIG_SYS_LOAD_ADDR		0 /* default? */

#define CONFIG_CMD_CACHE

/* Keep L2 Cache Disabled */
#define CONFIG_SYS_L2CACHE_OFF
#define CONFIG_SYS_CACHELINE_SIZE	32

#ifndef CONFIG_SYS_L2CACHE_OFF
#define CONFIG_SYS_L2_PL310
#define CONFIG_SYS_PL310_BASE	0xf8f02000
#endif

/* Physical Memory map */
#define CONFIG_NR_DRAM_BANKS		1
#define PHYS_SDRAM_1			0

#define CONFIG_SYS_MEMTEST_START	PHYS_SDRAM_1
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START + \
					PHYS_SDRAM_1_SIZE - (16 * 1024 * 1024))

#define CONFIG_SYS_INIT_RAM_ADDR	0xFFFF0000
#define CONFIG_SYS_INIT_RAM_SIZE	0x1000
#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_INIT_RAM_ADDR + \
					CONFIG_SYS_INIT_RAM_SIZE - \
					GENERATED_GBL_DATA_SIZE)

/* Enable the PL to be downloaded */
#define CONFIG_FPGA
#define CONFIG_FPGA_XILINX
#define CONFIG_FPGA_ZYNQPL
#define CONFIG_CMD_FPGA

/* FIT support */
#define CONFIG_FIT		1
#define CONFIG_FIT_VERBOSE	1 /* enable fit_format_{error,warning}() */

/* Boot FreeBSD/vxWorks from an ELF image */
#if defined(CONFIG_ZYNQ_BOOT_FREEBSD)
# define CONFIG_API
# define CONFIG_CMD_ELF
# define CONFIG_SYS_MMC_MAX_DEVICE	1
#endif

#define CONFIG_CMD_BOOTZ
#undef CONFIG_BOOTM_NETBSD

#endif /* __CONFIG_ZYNQ_H */
