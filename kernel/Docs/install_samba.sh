git clone https://github.com/Xperience94/linux_samba_4.4.1.git
cd $(pwd)/linux_samba_4.4.1/
mkdir -p build
TEGRA_KERNEL_OUT=$(pwd)/build/
export CROSS_COMPILE=$HOME/l4t-gcc/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-
export LOCALVERSION=-tegra
cd kernel-4.9
make ARCH=arm64 O=$TEGRA_KERNEL_OUT tegra_defconfig
make ARCH=arm64 O=$TEGRA_KERNEL_OUT Image
