/**
 * Copyright (c) 2018-2020, NVIDIA Corporation.  All rights reserved.
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

#ifndef __MAX9296_H__
#define __MAX9296_H__

#include <media/gmsl-link.h>

/* Dual GMSL MAX9296A/B */
#define MAX9296_MAX_SOURCES 2
#define MAX9296_MAX_PIPES 4

struct pipe_ctx {
	u32 id;
	u32 dt_type;
	u32 dst_csi_ctrl;
	u32 st_count;
	u32 st_id_sel;
};

struct max9296_source_ctx {
	struct gmsl_link_ctx *g_ctx;
	bool st_enabled;
};

struct max9296 {
	struct i2c_client *i2c_client;
	struct regmap *regmap;
	u32 num_src;
	u32 max_src;
	u32 num_src_found;
	u32 src_link;
	bool splitter_enabled;
	struct max9296_source_ctx sources[MAX9296_MAX_SOURCES];
	struct mutex lock;
	u32 sdev_ref;
	bool lane_setup;
	bool link_setup;
	struct pipe_ctx pipe[MAX9296_MAX_PIPES];
	u8 csi_mode;
	u8 lane_mp1;
	u8 lane_mp2;
	int reset_gpio;
	int pw_ref;
	struct regulator *vdd_cam_1v2;
};


int max9296_samba_portage_9272(struct device *dev);

int max9296_setup_link(struct device *dev, struct device *s_dev);

int max9296_setup_control(struct device *dev, struct device *s_dev);

int max9296_reset_control(struct device *dev, struct device *s_dev);

int max9296_sdev_register(struct device *dev, struct gmsl_link_ctx *g_ctx);

int max9296_sdev_unregister(struct device *dev, struct device *s_dev);

int max9296_setup_streaming(struct device *dev, struct device *s_dev);

int max9296_start_streaming(struct device *dev, struct device *s_dev);

int max9296_stop_streaming(struct device *dev, struct device *s_dev);

int max9296_power_on(struct device *dev);

void max9296_power_off(struct device *dev);

int max9296_write_reg(struct device *dev,
	u16 addr, u8 val);
int max9296_read_reg(struct device *dev,unsigned int addr, unsigned int *val);

#endif  /* __MAX9296_H__ */
