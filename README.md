# linux_samba_4.4.1

version bsp utilisé Jetpack 4.4.1



les drivers ce trouve dans le repertoire suivant : 

nvidia/drivers/media/i2c/




le compilateur  ce trouve dans le dossier compilator executer les commander suivante :

tar xf gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu.tar.xz
mkdir $HOME/l4t-gcc
cp gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu $HOME/l4t-gcc


afin de compiler le kernel et de genrer l'image et les modules associer suivre le lien suivant:

a la racine du depot executer les commande suivante :

- mkdir build
- TEGRA_KERNEL_OUT=$(pwd)/build/
- export CROSS_COMPILE=$HOME/l4t-gcc/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-
- export LOCALVERSION=-tegra
- cd kernel-4.9
- make ARCH=arm64 O=$TEGRA_KERNEL_OUT tegra_defconfig
- make ARCH=arm64 O=$TEGRA_KERNEL_OUT -j<n>








------------------------------ BSP SDKManager -----------------------------------------

ensuite il faut installer le BSP voici le lien pour l'installer:

https://developer.nvidia.com/embedded/jetpack-archive

ensuite afin de flasher la carte il faut suivre ce lien apartir du step 8https://connecttech.com/resource-center/kdb373/

 :





