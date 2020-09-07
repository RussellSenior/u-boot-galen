// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2020 Galen Seitz <galens@seitzassoc.com>
 *
 */
#include <init.h>
#include <net.h>

#define FACTORY_DATA_OFFS	0x40000
#define FACTORY_BASE		(CONFIG_SPL_TEXT_BASE + FACTORY_DATA_OFFS)

struct factory_data_values {
	u8 pad_1[4];
	u8 wifi_mac[6];		/* offs: 0x004: binary value */
	u8 pad_2[30];
	u8 copy_wifi_mac[6];	/* offs: 0x028: binary value */
	u8 eth_mac[6];		/* offs: 0x02e: binary value */
};

int misc_init_r(void)
{
	struct factory_data_values *pfactory;

	/* Load ethaddr with MAC from factory data. */
	pfactory = (struct factory_data_values *)FACTORY_BASE;
	if (is_valid_ethaddr(pfactory->eth_mac))
		eth_env_set_enetaddr("ethaddr", pfactory->eth_mac);

	/* Always return success.  u-boot will generate a random MAC
	   if ethaddr is not set. */
	return 0;
}
