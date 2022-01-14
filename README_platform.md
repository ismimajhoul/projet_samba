Si vous utiliser un Unbuntu 20.04, veuillez modifier le fichier suivant : 
=========================================================================
cd /etc
sudo nano os-release
changer le champ Version_ID="20.04" en Version_ID="18.04" 
=========================================================================


Ouvrir dans un navigateur le tutoriel d'installation du sdk et du bsp à l'adresse : https://connecttech.com/resource-center/kdb373/
ci-dessous un exemple de mise oeuvre du tutoriel:
================================================


cliquer sur le lien:
====================
1- Open NVIDIA SDK Manager. For first time use, you must log in to your NVIDIA Developer account.

pour ouvrir "https://developer.nvidia.com/nvidia-sdk-manager"

à partir de la page "https://developer.nvidia.com/nvidia-sdk-manager"
en bas de page cliquer sur le bouton:
"Get Started: download" pour ouvrir la page: https://developer.nvidia.com/sdkmanager_deb 
et télécharger sdkmanager_1.7.1-8928_amd64.deb



à partir du navigateur ouvrir le lien https://connecttech.com/resource-center/l4t-board-support-packages/
Sélectionner "NVIDIA Jetson AGX Xavier"
télécharger le BSP à partir de la ligne:JetPack 4.4.1 - L4T r32.4.4	AGX L4T r32.4.4 BSP

=============================================================================
# Installation du SDK sur le PC ubuntu
=============================================================================
cd  ~/nvidia/nvidia_sdk/JetPack_4.4.1_Linux_JETSON_AGX_XAVIER/Linux_for_Tegra
tar -zxf CTI-L4T-AGX-32.4.4-V005.tgz 
cd CTI-L4T
sudo ./install.sh
cd ..
lsusb /* check if the board nvidia is listed */
ls

Attention avant de flasher se mettre en mode recovery sur la carte nvidia:
- mettre la carte nvidia hors tension
- appuyer sur le bouton recovery ( le bouton est etiqueté)
- booter la carte nvidia en appuyant sur le bouton
- lancer le script comme indiqué ci-dessous:

sudo ./cti-flash.sh


=============================================================================
# Mise à jour de linux
=============================================================================
Brancher le cable usb entre le pc ubuntu et la carte nvidia (port usb J3)

Attention avant de flasher se mettre en mode recovery sur la carte nvidia:
- mettre la carte nvidia hors tension
- appuyer sur le bouton recovery ( le bouton est etiqueté)
- booter la carte nvidia en appuyant sur le bouton
- lancer le script comme indiqué ci-dessous:

cd  ~/nvidia/nvidia_sdk/JetPack_4.4.1_Linux_JETSON_AGX_XAVIER/Linux_for_Tegra/kernel
rm zImage Image
cp ~/clone_linux_samba_4.4.1/build/arch/arm64/boot/Image .
cd ..
sudo ./cti-flash.sh








