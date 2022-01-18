création du dts du projet SAMBA à partir d'un dts nvidia
========================================================

un fichier .dts a été créé à partir d'un fichier .dtb avec la commande ci-dessous:

dtc -I dtb -O dts -f devicetree_file_name.dtb -o devicetree_file_name.dts

devicetree_file_name.dtb: 
~/nvidia/nvidia_sdk/JetPack_4.4.1_Linux_JETSON_AGX_XAVIER/Linux_for_Tegra/kernel/dtb/tegra194-agx-cti-AGX101-JCB002-IMX390-8CAM.dtb

devicetree_file_name.dts:
/home/altran-brahim/clone_linux_samba_4.4.1/DeviceTree/devicetree_second_version.dts



modification du dts:
===================
modifier le fichier 
dtc -I dts -O dtb -f devicetree_second_version.dts -o tegra194-agx-cti-AGX101-JCB002-IMX390-8CAM.dtb
cp tegra194-agx-cti-AGX101-JCB002-IMX390-8CAM.dtb ~/nvidia/nvidia_sdk/JetPack_4.4.1_Linux_JETSON_AGX_XAVIER/Linux_for_Tegra/kernel/dtb/



implémentation dans le dts de l'atto320 à la place de imx390_a@1b
============================================================

La caméra atto320 est implémentée dans le dts à la place de l'imx390_a@1b
dans cette phase on ne modifie pas les propriétés existantes de la caméra




création du driver atto320.c à partir du driver imx_390.c
=========================================================

le driver atto320.c est un copy/paste de l'imx_390.c dans lequel on a:

- changé les symboles contenant imx_390 par atto320, ceci pour les fonctions, ctes, variables,...

adaptation du driver max9296.c au projet SAMBA
==============================================

- porter l'initialisation du deserializer max9272 dans le driver max9296.c, afin que le deserializer du projet SAMBA (max9296) effectue une
  initialisation similaire à celle qui était faite pour le deserializer max9272 du projet antérieur à SAMBA.
- porter l'initialisation du serializer max9271 dans le driver du max9295.c



adaptation du driver max9295.c au projet SAMBA
==============================================
Afin de minimiser les modifications dans le dts et dans linux on a conservé le fichier
max9295.c
On a également conservé les nodes propres au max9295 dans le dts. 
Par la suite on a rajouté dans le fichier max9295.c les fonctions propres au serializer max9271
permettant le wakeup, la lecture et l'écriture sur le bus i2c, etc...







