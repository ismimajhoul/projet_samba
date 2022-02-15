/**
 * Copyright (c) 2018, NVIDIA Corporation.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __MAX9295_H__
#define __MAX9295_H__

#include <media/gmsl-link.h>
#include <linux/i2c.h>

struct max9295_client_ctx {
	struct gmsl_link_ctx *g_ctx;
	bool st_done;
};

struct samba_max9271
{
	struct i2c_client *i2c_client;
	struct regmap *regmap;
	struct max9295_client_ctx g_client;
	struct mutex lock;
	/* primary serializer properties */
	__u32 def_addr;
	__u32 pst2_ref;
};


int max9295_setup_control(struct device *dev);

int max9295_reset_control(struct device *dev);

int max9295_sdev_pair(struct device *dev, struct gmsl_link_ctx *g_ctx);

int max9295_sdev_unpair(struct device *dev, struct device *s_dev);

int max9295_setup_streaming(struct device *dev);

int samba_max9271_setup_control(struct device *dev);

int InitSerdes(struct device* dser_dev,struct device* ser_dev);

int samba_max9271_set_serial_link(struct device *ser, bool enable);

void samba_max9271_wake_up(struct device *dev,unsigned int reg,unsigned int linkid);

int samba_tstclock_max9271_init(struct device *dev);

int samba_max9271_write(struct i2c_client* client, u8 reg, u8 val);

int InitDeserLinkA(struct device *dser_dev);

int InitDeserLinkB(struct device *dser_dev);

//int max9296_read_reg(struct device *dev,unsigned int addr, unsigned int *val)

#endif  /* __MAX9295_H__ */
