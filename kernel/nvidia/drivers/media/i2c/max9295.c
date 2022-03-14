/*
 * max9295.c - max9295 GMSL Serializer driver
 *
 * Copyright (c) 2018-2020, NVIDIA CORPORATION.  All rights reserved.
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

#include <media/camera_common.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <media/max9295.h>
#include <media/max9271.h>
#include <media/max9296.h>

/* register specifics */
#define MAX9295_MIPI_RX0_ADDR 0x330
#define MAX9295_MIPI_RX1_ADDR 0x331
#define MAX9295_MIPI_RX2_ADDR 0x332
#define MAX9295_MIPI_RX3_ADDR 0x333

#define MAX9295_PIPE_X_DT_ADDR 0x314
#define MAX9295_PIPE_Y_DT_ADDR 0x316
#define MAX9295_PIPE_Z_DT_ADDR 0x318
#define MAX9295_PIPE_U_DT_ADDR 0x31A

#define MAX9295_CTRL0_ADDR 0x10
#define MAX9295_SRC_CTRL_ADDR 0x2BF
#define MAX9295_SRC_PWDN_ADDR 0x02BE
#define MAX9295_SRC_OUT_RCLK_ADDR 0x3F1
#define MAX9295_START_PIPE_ADDR 0x311
#define MAX9295_PIPE_EN_ADDR 0x2
#define MAX9295_CSI_PORT_SEL_ADDR 0x308

#define MAX9295_I2C4_ADDR 0x44
#define MAX9295_I2C5_ADDR 0x45

#define MAX9295_DEV_ADDR 0x00

#define MAX9295_STREAM_PIPE_UNUSED 0x22
#define MAX9295_CSI_MODE_1X4 0x00
#define MAX9295_CSI_MODE_2X2 0x03
#define MAX9295_CSI_MODE_2X4 0x06

#define MAX9295_CSI_PORT_B(num_lanes) (((num_lanes) << 4) & 0xF0)
#define MAX9295_CSI_PORT_A(num_lanes) ((num_lanes) & 0x0F)

#define MAX9295_CSI_1X4_MODE_LANE_MAP1 0xE0
#define MAX9295_CSI_1X4_MODE_LANE_MAP2 0x04

#define MAX9295_CSI_2X4_MODE_LANE_MAP1 0xEE
#define MAX9295_CSI_2X4_MODE_LANE_MAP2 0xE4

#define MAX9295_CSI_2X2_MODE_LANE_MAP1 MAX9295_CSI_2X4_MODE_LANE_MAP1
#define MAX9295_CSI_2X2_MODE_LANE_MAP2 MAX9295_CSI_2X4_MODE_LANE_MAP2

#define MAX9295_ST_ID_0 0x0
#define MAX9295_ST_ID_1 0x1
#define MAX9295_ST_ID_2 0x2
#define MAX9295_ST_ID_3 0x3

#define MAX9295_PIPE_X_START_B 0x80
#define MAX9295_PIPE_Y_START_B 0x40
#define MAX9295_PIPE_Z_START_B 0x20
#define MAX9295_PIPE_U_START_B 0x10

#define MAX9295_PIPE_X_START_A 0x1
#define MAX9295_PIPE_Y_START_A 0x2
#define MAX9295_PIPE_Z_START_A 0x4
#define MAX9295_PIPE_U_START_A 0x8

#define MAX9295_START_PORT_A 0x10
#define MAX9295_START_PORT_B 0x20

#define MAX9295_CSI_LN2 0x1
#define MAX9295_CSI_LN4 0x3

#define MAX9295_EN_LINE_INFO 0x40

#define MAX9295_VID_TX_EN_X 0x10
#define MAX9295_VID_TX_EN_Y 0x20
#define MAX9295_VID_TX_EN_Z 0x40
#define MAX9295_VID_TX_EN_U 0x80

#define MAX9295_VID_INIT 0x3
#define MAX9295_SRC_RCLK 0x89

#define MAX9295_RESET_ALL 0x80
#define MAX9295_RESET_SRC 0x60
#define MAX9295_PWDN_GPIO 0x90

#define MAX9295_MAX_PIPES 0x4

struct max9295
{
	struct i2c_client *i2c_client;
	struct regmap *regmap;
	struct max9295_client_ctx g_client;
	struct mutex lock;
	/* primary serializer properties */
	__u32 def_addr;
	__u32 pst2_ref;
};

static struct max9295 *prim_priv__;



static struct samba_max9271 *samba_prim_priv__;



struct map_ctx {
	u8 dt;
	u16 addr;
	u8 val;
	u8 st_id;
};

int samba_max9271_write(struct i2c_client* client, u8 reg, u8 val)
{
	int ret;
	dev_dbg(&client->dev, "%s(0x%02x, 0x%02x)\n", __func__, reg, val);
	ret = i2c_smbus_write_byte_data(client, reg, val);
	if (ret < 0)
	{
		dev_err(&client->dev,"%s: register 0x%02x write KO (%d)\n",__func__, reg, ret);
	}
	else
	{
		dev_err(&client->dev,"%s: register 0x%02x write OK (%d)\n",__func__, reg, ret);
	}
	return ret;
}

static int samba_max9271_read(struct i2c_client* client, u8 reg)
{
	int ret;

	dev_dbg(&client->dev, "%s(0x%02x)\n", __func__, reg);

	//client->addr = 0x80;
	ret = i2c_smbus_read_byte_data(client, reg);
	if (ret < 0)
	{
		dev_dbg(&client->dev,"%s: register 0x%02x read failed KO(%d)\n",__func__, reg, ret);
	}
	else
	{
		dev_err(&client->dev,"%s: register 0x%02x write OK (%d)\n",__func__, reg, ret);
	}
	usleep_range(100, 110);

	return ret;
}



int samba_max9271_wake_up(struct device *dev, unsigned int reg,unsigned int linkid)
{
	struct samba_max9271 *priv = dev_get_drvdata(dev);
	int status;
	//priv->i2c_client->addr = addr_i2c;
	//status = i2c_smbus_read_byte_data(priv->i2c_client,priv->i2c_client->addr<< 1);
	status = i2c_smbus_read_byte_data(priv->i2c_client,reg);
	usleep_range(200000, 300000);
	if(status<0)
	{
		dev_err(dev," Samba max9271 wakeup failed KO status addr =0x%x value = 0x%x linkid: %d\n",reg,status,linkid);
	}
	else
	{
		dev_err(dev," Samba max9271 wakeup OK status addr =0x%x value = 0x%x linkid: %d\n",reg,status,linkid);
	}
	return status;
}

void samba_max9271_write_dev(struct device *dev, unsigned int reg,unsigned int value)
{
	struct samba_max9271 *priv = dev_get_drvdata(dev);
	int ret;
	ret = i2c_smbus_write_byte_data(priv->i2c_client, reg, value);
	usleep_range(1000000,2000000);
	if(ret<0)
	{
		dev_err(dev," Samba max9271 write_dev failed KO status addr =0x%x ret = 0x%x value: 0x%x\n",reg,ret,value);
	}
	else
	{
		dev_err(dev," Samba max9271 write_dev OK status addr =0x%x ret = 0x%x value: 0x%x\n",reg,ret,value);
	}
}

void samba_max9271_read_dev(struct device *dev, unsigned int reg)
{
	struct samba_max9271 *priv = dev_get_drvdata(dev);
	int ret;
	priv->i2c_client->addr = 0x60;
	ret = i2c_smbus_read_byte_data(priv->i2c_client,reg);
	usleep_range(30000, 80000);
	if(ret<0)
	{
		dev_err(dev," Samba max9271 read_dev failed KO status addr =0x%x ret = 0x%x\n",reg,ret);
	}
	else
	{
		dev_err(dev," Samba max9271 read_dev OK status addr =0x%x ret = 0x%x \n",reg,ret);
	}
}



static int max9295_write_reg(struct device *dev, u16 addr, u8 val)
{
	struct max9295 *priv = dev_get_drvdata(dev);
	int err;

	err = regmap_write(priv->regmap, addr, val);
	if (err)
		dev_err(dev, "%s:i2c write failed, 0x%x = %x\n",
			__func__, addr, val);

	/* delay before next i2c command as required for SERDES link */
	usleep_range(100, 110);

	return err;
}

/*
 * max9271_pclk_detect() - Detect valid pixel clock from image sensor
 *
 * Wait up to 10ms for a valid pixel clock.
 *
 * Returns 0 for success, < 0 for pixel clock not properly detected
 */
static int samba_max9271_pclk_detect(struct i2c_client *client)
{
	unsigned int i;
	int ret;

	for (i = 0; i < 100; i++)
	{
		ret = samba_max9271_read(client, 0x15);
		if (ret < 0)
		{
			dev_err(&client->dev, "unable to read register 15 PCLKDET KO\n");
			return ret;
		}

		if (ret & MAX9271_PCLKDET)
		{

			dev_err(&client->dev, "OK MAX9271_PCLKDET\n");
			return 0;
		}

		else
		{
			dev_err(&client->dev, "ON GOING\n");
		}
		
		usleep_range(50, 100);
	}

	dev_err(&client->dev, "Unable to detect valid pixel clock\n");

	return -EIO;
}

int max9295_setup_streaming(struct device *dev)
{
	struct max9295 *priv = dev_get_drvdata(dev);
	int err = 0;
	u32 csi_mode;
	u32 lane_map1;
	u32 lane_map2;
	u32 port;
	u32 rx1_lanes;
	u32 st_pipe;
	u32 pipe_en;
	u32 port_sel = 0;
	struct gmsl_link_ctx *g_ctx;
	u32 i;
	u32 j;
	u32 st_en;

	struct map_ctx map_pipe_dtype[] = {
		{GMSL_CSI_DT_RAW_12, MAX9295_PIPE_Z_DT_ADDR, 0x2C,
			MAX9295_ST_ID_2},
		{GMSL_CSI_DT_UED_U1, MAX9295_PIPE_X_DT_ADDR, 0x30,
			MAX9295_ST_ID_0},
		{GMSL_CSI_DT_EMBED, MAX9295_PIPE_Y_DT_ADDR, 0x12,
			MAX9295_ST_ID_1},
	};

	mutex_lock(&priv->lock);

	if (!priv->g_client.g_ctx) {
		dev_err(dev, "%s: no sdev client found\n", __func__);
		err = -EINVAL;
		goto error;
	}

	if (priv->g_client.st_done) {
		dev_dbg(dev, "%s: stream setup is already done\n", __func__);
		goto error;
	}

	g_ctx = priv->g_client.g_ctx;

	switch (g_ctx->csi_mode) {
	case GMSL_CSI_1X4_MODE:
		csi_mode = MAX9295_CSI_MODE_1X4;
		lane_map1 = MAX9295_CSI_1X4_MODE_LANE_MAP1;
		lane_map2 = MAX9295_CSI_1X4_MODE_LANE_MAP2;
		rx1_lanes = MAX9295_CSI_LN4;
		break;
	case GMSL_CSI_2X2_MODE:
		csi_mode = MAX9295_CSI_MODE_2X2;
		lane_map1 = MAX9295_CSI_2X2_MODE_LANE_MAP1;
		lane_map2 = MAX9295_CSI_2X2_MODE_LANE_MAP2;
		rx1_lanes = MAX9295_CSI_LN2;
		break;
	case GMSL_CSI_2X4_MODE:
		csi_mode = MAX9295_CSI_MODE_2X4;
		lane_map1 = MAX9295_CSI_2X4_MODE_LANE_MAP1;
		lane_map2 = MAX9295_CSI_2X4_MODE_LANE_MAP2;
		rx1_lanes = MAX9295_CSI_LN4;
		break;
	default:
		dev_err(dev, "%s: invalid csi mode\n", __func__);
		err = -EINVAL;
		goto error;
	}

	port = (g_ctx->src_csi_port == GMSL_CSI_PORT_B) ?
			MAX9295_CSI_PORT_B(rx1_lanes) :
			MAX9295_CSI_PORT_A(rx1_lanes);

	max9295_write_reg(dev, MAX9295_MIPI_RX0_ADDR, csi_mode);
	max9295_write_reg(dev, MAX9295_MIPI_RX1_ADDR, port);
	max9295_write_reg(dev, MAX9295_MIPI_RX2_ADDR, lane_map1);
	max9295_write_reg(dev, MAX9295_MIPI_RX3_ADDR, lane_map2);

	for (i = 0; i < g_ctx->num_streams; i++) {
		struct gmsl_stream *g_stream = &g_ctx->streams[i];

		g_stream->st_id_sel = GMSL_ST_ID_UNUSED;
		for (j = 0; j < ARRAY_SIZE(map_pipe_dtype); j++) {
			if (map_pipe_dtype[j].dt == g_stream->st_data_type) {
				/*
				 * TODO:
				 * 1) Remove link specific overrides, depends
				 * on #2.
				 * 2) Add support for vc id based stream sel
				 * overrides TX_SRC_SEL. would be useful in
				 * using same mappings in all ser devs.
				 */
				if (g_ctx->serdes_csi_link ==
					GMSL_SERDES_CSI_LINK_B) {
					map_pipe_dtype[j].addr += 2;
					map_pipe_dtype[j].st_id += 1;
				}

				g_stream->st_id_sel = map_pipe_dtype[j].st_id;
				st_en = (map_pipe_dtype[j].addr ==
						MAX9295_PIPE_X_DT_ADDR) ?
							0xC0 : 0x40;

				max9295_write_reg(dev, map_pipe_dtype[j].addr,
					(st_en | map_pipe_dtype[j].val));
			}
		}
	}

	for (i = 0; i < g_ctx->num_streams; i++)
		if (g_ctx->streams[i].st_id_sel != GMSL_ST_ID_UNUSED)
			port_sel |= (1 << g_ctx->streams[i].st_id_sel);

	if (g_ctx->src_csi_port == GMSL_CSI_PORT_B) {
		st_pipe = (MAX9295_PIPE_X_START_B | MAX9295_PIPE_Y_START_B |
			MAX9295_PIPE_Z_START_B | MAX9295_PIPE_U_START_B);
		port_sel |= (MAX9295_EN_LINE_INFO | MAX9295_START_PORT_B);
	} else {
		st_pipe = MAX9295_PIPE_X_START_A | MAX9295_PIPE_Y_START_A |
			MAX9295_PIPE_Z_START_A | MAX9295_PIPE_U_START_A;
		port_sel |= (MAX9295_EN_LINE_INFO | MAX9295_START_PORT_A);
	}

	pipe_en = (MAX9295_VID_TX_EN_X | MAX9295_VID_TX_EN_Y |
		MAX9295_VID_TX_EN_Z | MAX9295_VID_TX_EN_U | MAX9295_VID_INIT);

	max9295_write_reg(dev, MAX9295_START_PIPE_ADDR, st_pipe);
	max9295_write_reg(dev, MAX9295_CSI_PORT_SEL_ADDR, port_sel);
	max9295_write_reg(dev, MAX9295_PIPE_EN_ADDR, pipe_en);

	priv->g_client.st_done = true;

error:
	mutex_unlock(&priv->lock);
	return err;
}
EXPORT_SYMBOL(max9295_setup_streaming);




//int max9271_configure_gmsl_link_samba_project(struct i2c_client* client)

int InitSerdes(struct device *dser_dev,struct device *ser_dev)
{
	int ret = 0;
	//int val_deser = 0;
	struct samba_max9271 *priv = dev_get_drvdata(ser_dev);
// For lock priv->dser_dev
	//max9296_write_reg(dser_dev, 0x07, 0x0C); // retrouve le lock quand le M1-mini est eteint
	// //9272 reg 0x7 <= 0x0C
	// max9296_write_reg(dser_dev, MAX9296_GMSL1_B07_ADDR, 0x0); /*DBL DRS DWL HVEN EVC*/
	// max9296_write_reg(dser_dev, MAX9296_GMSL1_C07_ADDR, 0x0); /*DBL DRS DWL HVEN EVC*/
	// max9296_write_reg(dser_dev, MAX9296_GMSL1_VIDEO_RX_103_ADDR, 0x043);/* HS VS TRACKING*/

    //usleep_range(200000,300000);
    //// verifications
    //ok, val = max.read (i2cport,0x48,0x1e,1);
    //assert ((ok ==1) and (val == 10), "0x48 is not MAX9272")
    //ok, val = max.read (i2cport,0x40,0x1e,1);
    //assert ((ok == 1) and (val == 9), "0x40 is not MAX9271")

// inits distantes sur max9271
// INTTYPE=00 Local control channel uses i2c when i2csel=0
    ret = samba_max9271_write(priv->i2c_client,4,0x83); // distant
    //max9296_write_reg(dser_dev,4,0x03); // local

	// Reg 0x2:
	//- PRNG=11 => Automatically detect the pixel clock range.
	//- SRNG=00=>Automatically detect the pixel clock range.
	ret = samba_max9271_write(priv->i2c_client,0x02,0x1C);

	// Reg 0x3
	//- AUTOFM=00=> Calibrate spread-modulation rate only once after locking.
	//- SDIV=00000=>Autocalibrate sawtooth divider.
	ret = samba_max9271_write(priv->i2c_client,0x03,0x00);

	// Reg 0x4
	//- SEREN=1=>Disable serial link. Reverse control-channel communication remains
	//unavailable for 350Fs after the serializer starts/stops the serial link.
	//- CLINKEN=0
	//- PRBSEN=0
	//- SLEEP=0
	//- INTTYPE=00
	//- REVCCEN=1=>Enable reverse control channel from deserializer (receiving)
	//- FWDCCEN=1=>Enable forward control channel to deserializer (sending)
	//ret = samba_max9271_write(priv->i2c_client,0x04, 0x83);
	samba_max9271_set_serial_link(ser_dev,true);
	/* proceed even if ser setup failed, to setup deser correctly */


	// Reg 0x5
	//- I2CMETHOD=1 =>Disable sending of I2C register address when converting
	//UART to I2C (command-byte-only mode).
	//- ENJITFILT=0
	//- PRBSLEN=00
	//- ENWAKEN=0
	//- ENWAKEP=0
	ret = samba_max9271_write(priv->i2c_client,0x05, 0x80);

	// Reg 0x6
	//- CMLLVL=0101 =>250mV output level.
	//- PREEMP=0000=>Preemphasis off.
	ret = samba_max9271_write(priv->i2c_client,0x06,0x50);

	// Reg 0x7
	//- DBL=0
	//- DRS=0
	//- BWS=0
	//- ES=0
	//- HVEN=1=>HS/VS encoding enabled. Power-up default when LCCEN = low and
	//MS/HVEN = high.
	//- EDC=10=>6-bit hamming code (single-bit error correct, double-bit error detect)
	//and 16 word interleaving. Power-up default when LCCEN = low and
	//RX/SDA/EDC = high.

	////PROBLEMMMM////ret = samba_max9271_write(priv->i2c_client,0x07, 0x06); // perd le lock, car Hamming code enable

	//sleep(0.020); // DS : tLock 2ms (link start time), serializer delay ~ 17ms

	// DESER
	//=> mwrite (i2cport, 0x48, 0x07, 0x0E); // retrouve le lock !!!!! atention ceci \E9crit dans le max 9272 DESER
	// max9296_write_reg(dser_dev, MAX9296_GMSL1_B07_ADDR, 0x4); /*DBL DRS DWL HVEN EVC*/
	// max9296_write_reg(dser_dev, MAX9296_GMSL1_C07_ADDR, 0x4); /*DBL DRS DWL HVEN EVC*/
	// max9296_write_reg(dser_dev, MAX9296_GMSL1_VIDEO_RX_103_ADDR, 0x043);/* HS VS TRACKING*/
	//usleep_range(200000,300000);

	// Reg 0x8
	//- INVVS =0=>No VS or DIN0 inversion.
	//- INVHS=0 =>No HS or DIN1 inversion.
	//ret = max9271_write(client,0x08,0x00);

	ret = samba_max9271_write(priv->i2c_client, 0x08, 0x00);
	ret = samba_max9271_write(priv->i2c_client, 0x09, 0x00);
	ret = samba_max9271_write(priv->i2c_client, 0x0A, 0x00);
	ret = samba_max9271_write(priv->i2c_client, 0x0B, 0x00);
	ret = samba_max9271_write(priv->i2c_client, 0x0C, 0x00);
	ret = samba_max9271_write(priv->i2c_client, 0x0D, 0x6E); // Lien I2C serialiseur \E0 105KHz
	ret = samba_max9271_write(priv->i2c_client, 0x0E, 0x42);
	ret = samba_max9271_write(priv->i2c_client, 0x0F, 0xC2);


	// Finalisation INIT Max9296
	// max9296_write_reg(dser_dev, MAX9296_GMSL1_B02_ADDR, 0x00);
	// max9296_write_reg(dser_dev,MAX9296_GMSL1_B04_ADDR,0x3);
	// max9296_write_reg(dser_dev,MAX9296_GMSL1_42_ADDR,0x00);
	// max9296_write_reg(dser_dev,MAX9296_GMSL1_43_ADDR,0x00);
	// max9296_write_reg(dser_dev,MAX9296_GMSL1_44_ADDR,0x00);
	// max9296_write_reg(dser_dev,MAX9296_GMSL1_45_ADDR,0x00);


	// Faire ici l'init du deser max 9296 \E0 la place de l'inits du max9272

	//mwrite (i2cport, 0x48, 0x02, 0x1C);
	//mwrite (i2cport, 0x48, 0x03, 0x00);
	//mwrite (i2cport, 0x48, 0x04, 0x03);
	//mwrite (i2cport, 0x48, 0x05, 0xA9);
	//mwrite (i2cport, 0x48, 0x08, 0x00);
	//mwrite (i2cport, 0x48, 0x09, 0x00);
	//mwrite (i2cport, 0x48, 0x0A, 0x00);
	//mwrite (i2cport, 0x48, 0x0B, 0x00);
	//mwrite (i2cport, 0x48, 0x0C, 0x00);
	//mwrite (i2cport, 0x48, 0x0D, 0x36); //
	//mwrite (i2cport, 0x48, 0x0E, 0x60);
	//mwrite (i2cport, 0x48, 0x0F, 0x00);
	return ret;
}
EXPORT_SYMBOL_GPL(InitSerdes);

int InitDeserLinkA(struct device *dser_dev)
{
	int val_deser = 0;
	//struct samba_max9271 *priv = dev_get_drvdata(dser_dev);
	///////////////////////init deser MAX9296 ////////////////////////////
	max9296_read_reg(dser_dev,0xBCA, &val_deser);
	max9296_write_reg(dser_dev, 0x01, 0xC1);

	//11 CTRL1 Lecture du registre pour vérifier que les bits 2 (CXTP_B)
	//et 0  (CXTP_A) sont positionnés à 1 (Coax drive)
	max9296_read_reg(dser_dev,0x11, &val_deser);
	max9296_read_reg(dser_dev,0x330, &val_deser);

	//330 MIPI_PHY0 A évaluer pour activer le mode test rebouclé du MIPI

	//B04 GMSL1_4 03 ou 0B
	max9296_write_reg(dser_dev, MAX9296_GMSL1_B04_ADDR, 0x03);

	//B05 GMSL1_5 29
	max9296_write_reg(dser_dev, MAX9296_GMSL1_B05_ADDR, 0x29);

	//B06 GMSL1_6 69
	max9296_write_reg(dser_dev, 0xB06, 0x69);

	//B07 GMSL1_7 4
	max9296_write_reg(dser_dev, MAX9296_GMSL1_B07_ADDR, 0x04);

	//B08 GMSL1_8 31
	max9296_write_reg(dser_dev, 0xB08, 0x31);

	//B0D GMSL1_D 84
	max9296_write_reg(dser_dev, 0xB0D, 0x4);

	//B0E GMSL1_E Reset value

	//B0F GMSL1_F 1
	max9296_write_reg(dser_dev, 0xB0F, 0x01);

	//B10 GMSL1_10 Reset value

	//B12 GMSL1_12 Reset value

	//B13 GMSL1_13 Reset value

	//B14 GMSL1_14 0
	max9296_write_reg(dser_dev, 0xB14, 0x00);

	//B15 GMSL1_15 Reset value


	//B16 GMSL1_16 Reset value

	//B17 GMSL1_17 20
	max9296_write_reg(dser_dev, 0xB17, 0x20);

	//B18 GMSL1_18 Reset value

	//B19 GMSL1_19 Reset value

	//B1A GMSL1_1A Reset value

	//B1B GMSL1_1B Reset value

	//B1C GMSL1_1C Reset value

	//B1D GMSL1_1D Reset value

	//B20 GMSL1_20 Reset value

	//B21 GMSL1_21 Reset value

	//B22 GMSL1_22 Reset value

	//B23 GMSL1_23 Reset value

	//B96 GMSL1_96 2A
	max9296_write_reg(dser_dev, 0xB96, 0x2A);

	max9296_read_reg(dser_dev,0x11, &val_deser);
	max9296_read_reg(dser_dev,0x330, &val_deser);
	//msleep(20);
	max9296_read_reg(dser_dev,0xBCA, &val_deser);

////////////////////////////////////////////////////////////////
	return 0;
}


int InitDeserLinkB(struct device *dser_dev)
{
	//struct samba_max9271 *priv = dev_get_drvdata(dser_dev);
	///////////////////////init deser MAX9296 ////////////////////////////
	int val_deser = 0;
	max9296_read_reg(dser_dev,0xCCA, &val_deser);
	//1 REG1 C1
	max9296_write_reg(dser_dev, 0x01, 0xC1);

	//11 CTRL1 Lecture du registre pour vérifier que les bits 2 (CXTP_B)
	//et 0  (CXTP_A) sont positionnés à 1 (Coax drive)
	max9296_read_reg(dser_dev,0x11, &val_deser);
	max9296_read_reg(dser_dev,0x330, &val_deser);

	//330 MIPI_PHY0 A évaluer pour activer le mode test rebouclé du MIPI

	//B04 GMSL1_4 03 ou 0B
	max9296_write_reg(dser_dev, MAX9296_GMSL1_C04_ADDR, 0x03);

	//B05 GMSL1_5 29
	max9296_write_reg(dser_dev, 0xC05, 0x29);

	//B06 GMSL1_6 69
	max9296_write_reg(dser_dev, 0xC06, 0x69);

	//B07 GMSL1_7 4
	max9296_write_reg(dser_dev, MAX9296_GMSL1_C07_ADDR, 0x04);

	//B08 GMSL1_8 31
	max9296_write_reg(dser_dev, 0xC08, 0x31);

	//B0D GMSL1_D 84
	max9296_write_reg(dser_dev, 0xC0D, 0x4);

	//B0E GMSL1_E Reset value

	//B0F GMSL1_F 1
	max9296_write_reg(dser_dev, 0xC0F, 0x01);

	//B10 GMSL1_10 Reset value

	//B12 GMSL1_12 Reset value

	//B13 GMSL1_13 Reset value

	//B14 GMSL1_14 0
	max9296_write_reg(dser_dev, 0xC14, 0x00);

	//B15 GMSL1_15 Reset value


	//B16 GMSL1_16 Reset value

	//B17 GMSL1_17 20
	max9296_write_reg(dser_dev, 0xC17, 0x20);

	//B18 GMSL1_18 Reset value

	//B19 GMSL1_19 Reset value

	//B1A GMSL1_1A Reset value

	//B1B GMSL1_1B Reset value

	//B1C GMSL1_1C Reset value

	//B1D GMSL1_1D Reset value

	//B20 GMSL1_20 Reset value

	//B21 GMSL1_21 Reset value

	//B22 GMSL1_22 Reset value

	//B23 GMSL1_23 Reset value

	//B96 GMSL1_96 2A
	max9296_write_reg(dser_dev, 0xC96, 0x2A);

	max9296_read_reg(dser_dev,0x11, &val_deser);
	max9296_read_reg(dser_dev,0x330, &val_deser);
	msleep(20);
	max9296_read_reg(dser_dev,0xCCA, &val_deser);
////////////////////////////////////////////////////////////////
	return 0;
}






int samba_max9271_set_serial_link(struct device *ser, bool enable)
{


	int ret;
	struct samba_max9271 *priv = dev_get_drvdata(ser); 
	u8 val = MAX9271_REVCCEN | MAX9271_FWDCCEN;

	dev_err(ser, "samba Set serial link max9271 \n");

	if (enable)
	{
		ret = samba_max9271_pclk_detect(priv->i2c_client);
		if (ret)
			return ret;

		val |= MAX9271_SEREN;
		dev_err(ser, "samba Set serial link max9271 set SEREN\n");
	}
	else
	{
		val |= MAX9271_CLINKEN;
		dev_err(ser, "Set serial link max9271 set CLKINKEN\n");
	}

	/*
	 * The serializer temporarily disables the reverse control channel for
	 * 350µs after starting/stopping the forward serial link, but the
	 * deserializer synchronization time isn't clearly documented.
	 *
	 * According to the serializer datasheet we should wait 3ms, while
	 * according to the deserializer datasheet we should wait 5ms.
	 *
	 * Short delays here appear to show bit-errors in the writes following.
	 * Therefore a conservative delay seems best here.
	 */
	ret = samba_max9271_write(priv->i2c_client, 0x04, val);
	if (ret < 0)
	{
		dev_err(ser, "samba Set serial link max9271 error\n");
		return ret;
	}

	usleep_range(5000, 8000);

	return 0;
}
EXPORT_SYMBOL_GPL(samba_max9271_set_serial_link);

static int samba_max9271_verify_id(struct i2c_client* client)
{
	int ret;

	ret = samba_max9271_read(client, 0x1e);
	if (ret < 0) {
		dev_err(&client->dev, "MAX9271 ID read failed (%d)\n",
			ret);
		return ret;
	}

	if (ret != MAX9271_ID) {
		dev_err(&client->dev, "MAX9271 ID mismatch (0x%02x)\n",
			ret);
		return -ENXIO;
	}

	return 0;
}
EXPORT_SYMBOL_GPL(samba_max9271_verify_id);

static int samba_std_max9271_init(struct device *dev)
{
	int ret = 0;
	struct samba_max9271 *priv = dev_get_drvdata(dev);

	/* Serial link disabled during config as it needs a valid pixel clock. */
	ret = samba_max9271_set_serial_link(dev, false);


	ret = samba_max9271_verify_id(priv->i2c_client);
	return ret;
}
EXPORT_SYMBOL_GPL(samba_std_max9271_init);

int samba_tstclock_max9271_init(struct device *dev)
{
	int ret = 0;
	int i=0;
	struct samba_max9271 *priv = dev_get_drvdata(dev);
	while(1)
	{
		for(i=0;i<255;i++){
			priv->i2c_client->addr = i;
			ret = samba_max9271_read(priv->i2c_client, 0);
			dev_err(dev,"%s: test lecture addr ser = 0x%x",__func__, ret);
			usleep_range(100, 110);
			// regmap_read(priv->regmap, 0x1e, &ret);
			// dev_err(dev,"%s: test lecture addr ser = 0x%x",__func__, ret);
			// usleep_range(100, 110);
		}
	}
	return ret;
}
EXPORT_SYMBOL_GPL(samba_tstclock_max9271_init);




int samba_max9271_setup_control(struct device *dev)
{
	struct samba_max9271 *priv = dev_get_drvdata(dev);
	int err = 0, ret = 0;
	struct gmsl_link_ctx *g_ctx;



		mutex_lock(&priv->lock);

		if (!priv->g_client.g_ctx)
		{
			dev_err(dev, "%s: no sensor dev client found\n", __func__);
			err = -EINVAL;
			goto error;
		}

		g_ctx = priv->g_client.g_ctx;

		/* Serial link disabled during config as it needs a valid pixel clock. */
		ret = samba_max9271_set_serial_link(dev, false);
		if (ret)
			return ret;

error:
			mutex_unlock(&priv->lock);
			return err;

}



int max9295_setup_control(struct device *dev)
{
	struct max9295 *priv = dev_get_drvdata(dev);
	int err = 0;
	struct gmsl_link_ctx *g_ctx;
	u32 offset1 = 0;
	u32 offset2 = 0;
	u32 i;

	u8 i2c_ovrd[] = {
		0x6B, 0x10,
		0x73, 0x11,
		0x7B, 0x30,
		0x83, 0x30,
		0x93, 0x30,
		0x9B, 0x30,
		0xA3, 0x30,
		0xAB, 0x30,
		0x8B, 0x30,
	};

	u8 addr_offset[] = {
		0x80, 0x00, 0x00,
		0x84, 0x00, 0x01,
		0xC0, 0x02, 0x02,
		0xC4, 0x02, 0x03,
	};

	mutex_lock(&priv->lock);

	if (!priv->g_client.g_ctx) {
		dev_err(dev, "%s: no sensor dev client found\n", __func__);
		err = -EINVAL;
		goto error;
	}

	g_ctx = priv->g_client.g_ctx;

	if (prim_priv__)
	{
		/* update address reassingment */
		max9295_write_reg(&prim_priv__->i2c_client->dev,
				MAX9295_DEV_ADDR, (g_ctx->ser_reg << 1));
	}

	if (g_ctx->serdes_csi_link == GMSL_SERDES_CSI_LINK_A)
		err = max9295_write_reg(dev, MAX9295_CTRL0_ADDR, 0x21);
	else
		err = max9295_write_reg(dev, MAX9295_CTRL0_ADDR, 0x22);

	/* check if serializer device exists */
	if (err)
	{
		dev_err(dev, "%s: ERROR: ser device not found\n", __func__);
		goto error;
	}

	/* delay to settle link */
	msleep(100);

	for (i = 0; i < ARRAY_SIZE(addr_offset); i += 3) {
		if ((g_ctx->ser_reg << 1) == addr_offset[i]) {
			offset1 = addr_offset[i+1];
			offset2 = addr_offset[i+2];
			break;
		}
	}

	if (i == ARRAY_SIZE(addr_offset)) {
		dev_err(dev, "%s: invalid ser slave address\n", __func__);
		err = -EINVAL;
		goto error;
	}

	for (i = 0; i < ARRAY_SIZE(i2c_ovrd); i += 2)
	{
		/* update address overrides */
		i2c_ovrd[i+1] += (i < 4) ? offset1 : offset2;

		/* i2c passthrough2 must be configured once for all devices */
		if ((i2c_ovrd[i] == 0x8B) && prim_priv__ && prim_priv__->pst2_ref)
			continue;

		max9295_write_reg(dev, i2c_ovrd[i], i2c_ovrd[i+1]);
	}

	/* dev addr pass-through2 ref */
	if (prim_priv__)
		prim_priv__->pst2_ref++;

	max9295_write_reg(dev, MAX9295_I2C4_ADDR, (g_ctx->sdev_reg << 1));
	max9295_write_reg(dev, MAX9295_I2C5_ADDR, (g_ctx->sdev_def << 1));

	max9295_write_reg(dev, MAX9295_SRC_PWDN_ADDR, MAX9295_PWDN_GPIO);
	max9295_write_reg(dev, MAX9295_SRC_CTRL_ADDR, MAX9295_RESET_SRC);
	max9295_write_reg(dev, MAX9295_SRC_OUT_RCLK_ADDR, MAX9295_SRC_RCLK);

	g_ctx->serdev_found = true;

error:
	mutex_unlock(&priv->lock);
	return err;
}

EXPORT_SYMBOL(max9295_setup_control);

int max9295_reset_control(struct device *dev)
{
	struct max9295 *priv = dev_get_drvdata(dev);
	int err = 0;

	mutex_lock(&priv->lock);
	if (!priv->g_client.g_ctx) {
		dev_err(dev, "%s: no sdev client found\n", __func__);
		err = -EINVAL;
		goto error;
	}

	priv->g_client.st_done = false;

	if (prim_priv__) {
		prim_priv__->pst2_ref--;

		max9295_write_reg(dev, MAX9295_DEV_ADDR, (prim_priv__->def_addr << 1));

		max9295_write_reg(&prim_priv__->i2c_client->dev,
					MAX9295_CTRL0_ADDR, MAX9295_RESET_ALL);
	}

error:
	mutex_unlock(&priv->lock);
	return err;
}
EXPORT_SYMBOL(max9295_reset_control);





int max9295_sdev_pair(struct device *dev, struct gmsl_link_ctx *g_ctx)
{
	struct max9295 *priv;
	int err = 0;

	if (!dev || !g_ctx || !g_ctx->s_dev)
	{
		dev_err(dev, "%s: invalid input params\n", __func__);
		return -EINVAL;
	}

	priv = dev_get_drvdata(dev);
	mutex_lock(&priv->lock);
	if (priv->g_client.g_ctx)
	{
		dev_err(dev, "%s: device already paired\n", __func__);
		err = -EINVAL;
		goto error;
	}
	else
	{
		dev_err(dev, "%s: device paired\n", __func__);
	}

	priv->g_client.st_done = false;

	priv->g_client.g_ctx = g_ctx;

error:
	mutex_unlock(&priv->lock);
	return 0;
}
EXPORT_SYMBOL(max9295_sdev_pair);

int max9295_sdev_unpair(struct device *dev, struct device *s_dev)
{
	struct max9295 *priv = NULL;
	int err = 0;

	if (!dev || !s_dev) {
		dev_err(dev, "%s: invalid input params\n", __func__);
		return -EINVAL;
	}

	priv = dev_get_drvdata(dev);

	mutex_lock(&priv->lock);

	if (!priv->g_client.g_ctx) {
		dev_err(dev, "%s: device is not paired\n", __func__);
		err = -ENOMEM;
		goto error;
	}

	if (priv->g_client.g_ctx->s_dev != s_dev) {
		dev_err(dev, "%s: invalid device\n", __func__);
		err = -EINVAL;
		goto error;
	}

	priv->g_client.g_ctx = NULL;
	priv->g_client.st_done = false;

error:
	mutex_unlock(&priv->lock);
	return err;
}
EXPORT_SYMBOL(max9295_sdev_unpair);

static  struct regmap_config max9295_regmap_config = {
	.reg_bits = 16,
	.val_bits = 8,
	.cache_type = REGCACHE_RBTREE,
};

static int max9295_probe(struct i2c_client *client,
				const struct i2c_device_id *id)
{
	struct samba_max9271 *priv;
	int err = 0;
	struct device_node *node = client->dev.of_node;

	dev_info(&client->dev, "[MAX9295]: probing GMSL Serializer\n");
	priv = devm_kzalloc(&client->dev, sizeof(*priv), GFP_KERNEL);
	priv->i2c_client = client;
	priv->regmap = devm_regmap_init_i2c(priv->i2c_client,
				&max9295_regmap_config);
	if (IS_ERR(priv->regmap))
	{
		dev_err(&client->dev,
			"regmap init failed: %ld\n", PTR_ERR(priv->regmap));
		return -ENODEV;
	}

	mutex_init(&priv->lock);

	if (of_get_property(node, "is-prim-ser", NULL))
	{
		if (samba_prim_priv__) {
			dev_err(&client->dev,
				"prim-ser already exists\n");
				return -EEXIST;
		}

		err = of_property_read_u32(node, "reg", &priv->def_addr);
		if (err < 0) {
			dev_err(&client->dev, "reg not found\n");
			return -EINVAL;
		}

		samba_prim_priv__ = priv;
	}

	dev_set_drvdata(&client->dev, priv);
	//client->addr = priv->def_addr;
	//max9295_wake_up(client);

	/* dev communication gets validated when GMSL link setup is done */
	dev_info(&client->dev, "%s:  success\n", __func__);



	return err;
}

static int max9295_remove(struct i2c_client *client)
{
	struct max9295 *priv;

	if (client != NULL) {
		priv = dev_get_drvdata(&client->dev);
		mutex_destroy(&priv->lock);
		i2c_unregister_device(client);
		client = NULL;
	}

	return 0;
}

static const struct i2c_device_id max9295_id[] = {
	{ "max9295", 0 },
	{ },
};

const struct of_device_id max9295_of_match[] = {
	{ .compatible = "nvidia,max9295", },
	{ },
};
MODULE_DEVICE_TABLE(of, max9295_of_match);
MODULE_DEVICE_TABLE(i2c, max9295_id);

static struct i2c_driver max9295_i2c_driver = {
	.driver = {
		.name = "max9295",
		.owner = THIS_MODULE,
	},
	.probe = max9295_probe,
	.remove = max9295_remove,
	.id_table = max9295_id,
};

static int __init max9295_init(void)
{
	return i2c_add_driver(&max9295_i2c_driver);
}

static void __exit max9295_exit(void)
{
	i2c_del_driver(&max9295_i2c_driver);
}

module_init(max9295_init);
module_exit(max9295_exit);

MODULE_DESCRIPTION("GMSL Serializer driver max9295");
MODULE_AUTHOR("Sudhir Vyas <svyas@nvidia.com>");
MODULE_LICENSE("GPL v2");
