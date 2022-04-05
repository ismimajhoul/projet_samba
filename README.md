# Contexte: linux_samba_4.4.1 version bsp utilisé Jetpack 4.4.1
==============================================================

#Pour récupérer le dépot git:
============================

git clone https://github.com/ismimajhoul/projet_samba.git

les drivers se trouve dans les repertoires suivants: 

nvidia/drivers/media/i2c/
nvidia/include/media

#Executer les commandes suivantes pour installer le compilateur:
===============================================================

mkdir $HOME/l4t-gcc
cd $HOME/l4t-gcc
wget https://releases.linaro.org/components/toolchain/binaries/7.3-2018.05/aarch64-linux-gnu/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu.tar.xz
tar xf gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu.tar.xz


Afin de compiler le kernel et generer l'image et les modules associer suivre le tutoriel suivant:

- cd <my_depot_git>
- mkdir build
- TEGRA_KERNEL_OUT=$(pwd)/build/
- export CROSS_COMPILE=$HOME/l4t-gcc/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-
- export LOCALVERSION=-tegra
- cd kernel-4.9
- make ARCH=arm64 O=$TEGRA_KERNEL_OUT tegra_defconfig
- make ARCH=arm64 O=$TEGRA_KERNEL_OUT -j<n>


Ou bien exécuter le script compile_samba.sh 







