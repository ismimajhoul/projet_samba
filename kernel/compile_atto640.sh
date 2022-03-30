mkdir -p build
TEGRA_KERNEL_OUT=$(pwd)/build/
export CROSS_COMPILE=$HOME/l4t-gcc/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-
export LOCALVERSION=-tegra
cp configs/tegra_defconfig kernel-4.9/arch/arm64/configs/tegra_defconfig
cd kernel-4.9
echo "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
make mrproper
make ARCH=arm64 O=$TEGRA_KERNEL_OUT -j$(nproc) tegra_defconfig
#make ARCH=arm64 O=$TEGRA_KERNEL_OUT -j$(nproc) menuconfig
make ARCH=arm64 O=$TEGRA_KERNEL_OUT -j$(nproc)

