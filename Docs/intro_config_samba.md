Les differents drivers ont été implementés dans les dossiers suivant :

fichier.c
"nvidia/drivers/media/i2c/"

fichier.h
"nvidia/include/media/"


modification du Makefile du repertoire  => "nvidia/drivers/media/i2c/"
On ajoute les lignes ci-dessous:

'''
obj-$(CONFIG_I2C_IOEXPANDER_SER_MAX9271) += max9271.o
obj-$(CONFIG_VIDEO_ATTO320) += atto320.o
obj-$(CONFIG_I2C_IOEXPANDER_DESER_MAX9296) += max9296.o
'''


modification du fichier de configuration de linux-nvidia :

"kernel-4.9/arch/arm64/configs/tegra_defconfig"

On ajoute les elements suivants :

'''
CONFIG_I2C_IOEXPANDER_SER_MAX9295=y
CONFIG_I2C_IOEXPANDER_SER_MAX9271=y
CONFIG_I2C_IOEXPANDER_DESER_MAX9296=y
'''

Nous pouvons maintenant compiler sans probleme ! 

