Les differents drivers on été implementé dans les dossier suivant :

fichier.c
"nvidia/drivers/media/i2c/"

fichier.h
"nvidia/include/media/"


le Makefile dans le repertoir  => "nvidia/drivers/media/i2c/"
On ajoute les lignes ci-dessous:

'''
obj-$(CONFIG_I2C_IOEXPANDER_SER_MAX9271) += max9271.o
obj-$(CONFIG_VIDEO_ATTO320) += atto320.o
obj-$(CONFIG_I2C_IOEXPANDER_DESER_MAX9296) += max9296.o
'''


Il a falut egalement rajouter dans le fichier suivant :

"kernel-4.9/arch/arm64/configs/tegra_defconfig"

les elements suivants :

'''
CONFIG_I2C_IOEXPANDER_SER_MAX9295=y
CONFIG_I2C_IOEXPANDER_SER_MAX9271=y
CONFIG_I2C_IOEXPANDER_DESER_MAX9296=y
'''

Nous pouvons maintenant compiler sans probleme ! 

