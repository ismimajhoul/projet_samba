/*
 * serdes.c - GMSL driver
 * Copyright (c) 2017-2018, e-con Systems.  All rights reserved.
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

#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>
#include <linux/module.h>

#include <linux/seq_file.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <media/camera_common.h>
#include <media/serdes_atto640.h>

int atto640_serdes_write_i2c(struct i2c_client *client, u16 sladdr,  u8 * val, u32 count)
{
	int ret;

	struct i2c_msg msg = {
		.addr = sladdr,
		.flags = 0,
		.len = count,
		.buf = val,
	};

	ret = i2c_transfer(client->adapter, &msg, 1);
	if (ret < 0) {
		dev_err(&client->dev, "Failed writing register ret = %d!\n",
			ret);
		return ret;
	}
	return 0;
}

int atto640_serdes_read_i2c(struct i2c_client *client, u16 sladdr, u8 * val, u32 count)
{
	int ret;
	struct i2c_msg msg = {
		.addr = sladdr,
		.flags = 0,
		.buf = val,
	};

	msg.flags = I2C_M_RD;
	msg.len = count;
	ret = i2c_transfer(client->adapter, &msg, 1);
	if (ret < 0)
		goto err;

	return 0;

 err:
	dev_err(&client->dev, "Failed reading register ret = %d!\n", ret);
	return ret;
}

s32 atto640_serdes_read_8b_reg(struct i2c_client *client, u16 sladdr, u8 reg, u8 * val)
{
	u8 bcount = 1;
	u8 au8RegBuf[1] = { 0 };
	u8 au8RdVal[1] = { 0 };

	au8RegBuf[0] = reg;

	if (atto640_serdes_write_i2c(client, sladdr, au8RegBuf, bcount) < 0) {
		dev_err(&client->dev,"%s:write reg error:reg=0x%x\n", __func__, reg);
		return -EIO;
	}

	if (atto640_serdes_read_i2c(client,sladdr, au8RdVal, bcount) < 0) {
		dev_err(&client->dev,"%s:read reg error:reg=0x%x\n", __func__, reg);
		return -EIO;
	}

	*val = au8RdVal[0];

	return 0;
}

s32 atto640_serdes_write_8b_reg(struct i2c_client *client, u16 sladdr, u8 reg, u8 val)
{
	u8 bcount = 2;
	u8 au8Buf[2] = { 0 };

	au8Buf[0] = reg;
	au8Buf[1] = val;

	if (atto640_serdes_write_i2c(client, sladdr,au8Buf, bcount) < 0) {
		dev_err(&client->dev,
			"%s:write reg error: reg = 0x%x,val = 0x%x\n", __func__,
			reg, val);
		return -EIO;
	}

	return 0;
}

s32 atto640_serdes_read_16b_reg(struct i2c_client *client, u16 sladdr, u16 reg, u8 * val)
{
	u8 bcount;
	u8 au8RegBuf[2] = { 0 };
	u8 au8RdVal[1] = { 0 };

	au8RegBuf[0] = reg >> 8;
	au8RegBuf[1] = reg & 0xff;
	bcount = 2;

	if (atto640_serdes_write_i2c(client, sladdr, au8RegBuf, bcount) < 0) {
		dev_err(&client->dev,"%s:write reg error:reg=0x%x\n", __func__, reg);
		return -EIO;
	}

	bcount = 1;
	if (atto640_serdes_read_i2c(client,sladdr, au8RdVal, bcount) < 0) {
		dev_err(&client->dev,"%s:read reg error:reg=0x%x\n", __func__, reg);
		return -EIO;
	}

	*val = au8RdVal[0];

	return 0;
}

s32 atto640_serdes_write_16b_reg(struct i2c_client *client, u16 sladdr, u16 reg, u8 val)
{
	u8 bcount = 3;
	u8 au8Buf[3] = { 0 };

	au8Buf[0] = reg >> 8;
	au8Buf[1] = reg & 0xff;
	au8Buf[2] = val;

	if (atto640_serdes_write_i2c(client, sladdr,au8Buf, bcount) < 0) {
		dev_err(&client->dev,
			"%s:write reg error: reg = 0x%x,val = 0x%x\n", __func__,
			reg, val);
		return -EIO;
	}

	return 0;
}
