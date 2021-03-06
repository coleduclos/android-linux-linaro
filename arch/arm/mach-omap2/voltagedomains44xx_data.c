/*
 * OMAP3/OMAP4 Voltage Management Routines
 *
 * Author: Thara Gopinath	<thara@ti.com>
 *
 * Copyright (C) 2007 Texas Instruments, Inc.
 * Rajendra Nayak <rnayak@ti.com>
 * Lesly A M <x0080970@ti.com>
 *
 * Copyright (C) 2008 Nokia Corporation
 * Kalle Jokiniemi
 *
 * Copyright (C) 2010 Texas Instruments, Inc.
 * Thara Gopinath <thara@ti.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/kernel.h>
#include <linux/err.h>
#include <linux/init.h>

#include "common.h"

#include "prm-regbits-44xx.h"
#include "prm44xx.h"
#include "scrm44xx.h"
#include "prcm44xx.h"
#include "prminst44xx.h"
#include "voltage.h"
#include "omap_opp_data.h"
#include "vc.h"
#include "vp.h"
#include "abb.h"

static const struct omap_vfsm_instance omap4_vdd_mpu_vfsm = {
	.voltsetup_reg = OMAP4_PRM_VOLTSETUP_MPU_RET_SLEEP_OFFSET,
	.voltsetup_off_reg = OMAP4_PRM_VOLTSETUP_MPU_OFF_OFFSET,
};
static struct omap_vdd_info omap4_vdd_mpu_info;


static const struct omap_vfsm_instance omap4_vdd_iva_vfsm = {
	.voltsetup_reg = OMAP4_PRM_VOLTSETUP_IVA_RET_SLEEP_OFFSET,
	.voltsetup_off_reg = OMAP4_PRM_VOLTSETUP_IVA_OFF_OFFSET,
};
static struct omap_vdd_info omap4_vdd_iva_info;

static const struct omap_vfsm_instance omap4_vdd_core_vfsm = {
	.voltsetup_reg = OMAP4_PRM_VOLTSETUP_CORE_RET_SLEEP_OFFSET,
	.voltsetup_off_reg = OMAP4_PRM_VOLTSETUP_CORE_OFF_OFFSET,
};
static struct omap_vdd_info omap4_vdd_core_info;

static struct voltagedomain omap4_voltdm_mpu = {
	.name = "mpu",
	.scalable = true,
	.read = omap4_prm_vcvp_read,
	.write = omap4_prm_vcvp_write,
	.rmw = omap4_prm_vcvp_rmw,
	.scrm_write = omap4_scrm_write,
	.vc = &omap4_vc_mpu,
	.vfsm = &omap4_vdd_mpu_vfsm,
	.vp = &omap4_vp_mpu,
	.vdd = &omap4_vdd_mpu_info,
	.abb = &omap4_abb_mpu,
};

static struct voltagedomain omap4_voltdm_iva = {
	.name = "iva",
	.scalable = true,
	.read = omap4_prm_vcvp_read,
	.write = omap4_prm_vcvp_write,
	.rmw = omap4_prm_vcvp_rmw,
	.scrm_write = omap4_scrm_write,
	.vc = &omap4_vc_iva,
	.vfsm = &omap4_vdd_iva_vfsm,
	.vp = &omap4_vp_iva,
	.vdd = &omap4_vdd_iva_info,
	.abb = &omap4_abb_iva,
};

static struct voltagedomain omap4_voltdm_core = {
	.name = "core",
	.scalable = true,
	.read = omap4_prm_vcvp_read,
	.write = omap4_prm_vcvp_write,
	.rmw = omap4_prm_vcvp_rmw,
	.scrm_write = omap4_scrm_write,
	.vc = &omap4_vc_core,
	.vfsm = &omap4_vdd_core_vfsm,
	.vp = &omap4_vp_core,
	.vdd = &omap4_vdd_core_info,
};

static struct voltagedomain omap4_voltdm_wkup = {
	.name = "wakeup",
};

static struct voltagedomain *voltagedomains_omap4[] __initdata = {
	&omap4_voltdm_mpu,
	&omap4_voltdm_iva,
	&omap4_voltdm_core,
	&omap4_voltdm_wkup,
	NULL,
};

static const char *sys_clk_name __initdata = "sys_clkin_ck";

void __init omap44xx_voltagedomains_init(void)
{
	struct voltagedomain *voltdm;
	int i;

	/*
	 * XXX Will depend on the process, validation, and binning
	 * for the currently-running IC
	 */
	if (cpu_is_omap443x()) {
		omap4_voltdm_mpu.volt_data = omap443x_vdd_mpu_volt_data;
		omap4_vdd_mpu_info.dep_vdd_info = omap443x_vddmpu_dep_info;

		omap4_voltdm_iva.volt_data = omap443x_vdd_iva_volt_data;
		omap4_vdd_iva_info.dep_vdd_info = omap443x_vddiva_dep_info;

		omap4_voltdm_core.volt_data = omap443x_vdd_core_volt_data;

		omap4_voltdm_mpu.vp_param = &omap443x_mpu_vp_data;
		omap4_voltdm_iva.vp_param = &omap443x_iva_vp_data;
		omap4_voltdm_core.vp_param = &omap443x_core_vp_data;

		omap4_voltdm_mpu.vc_param = &omap44xx_mpu_vc_data;
		omap4_voltdm_iva.vc_param = &omap44xx_iva_vc_data;
		omap4_voltdm_core.vc_param = &omap44xx_core_vc_data;
	} else if (cpu_is_omap446x()) {
		omap4_voltdm_mpu.volt_data = omap446x_vdd_mpu_volt_data;
		omap4_vdd_mpu_info.dep_vdd_info = omap446x_vddmpu_dep_info;

		omap4_voltdm_iva.volt_data = omap446x_vdd_iva_volt_data;
		omap4_vdd_iva_info.dep_vdd_info = omap446x_vddiva_dep_info;

		omap4_voltdm_core.volt_data = omap446x_vdd_core_volt_data;

		omap4_voltdm_mpu.vp_param = &omap446x_mpu_vp_data;
		omap4_voltdm_iva.vp_param = &omap446x_iva_vp_data;
		omap4_voltdm_core.vp_param = &omap446x_core_vp_data;

		omap4_voltdm_mpu.vc_param = &omap44xx_mpu_vc_data;
		omap4_voltdm_iva.vc_param = &omap44xx_iva_vc_data;
		omap4_voltdm_core.vc_param = &omap446x_core_vc_data;
	} else
		return;

	for (i = 0; voltdm = voltagedomains_omap4[i], voltdm; i++)
		voltdm->sys_clk.name = sys_clk_name;

	voltdm_init(voltagedomains_omap4);
}

static int __init init_volt_domain_notifier_list(void)
{
	return __init_volt_domain_notifier_list(voltagedomains_omap4);
}
pure_initcall(init_volt_domain_notifier_list);
