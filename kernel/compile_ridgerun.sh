mkdir -p build
mkdir -p modules

TEGRA_KERNEL_OUT=$(pwd)/build/
KERNEL_MODULES_OUT=$(pwd)/modules/
export CROSS_COMPILE=$HOME/l4t-gcc/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-
export LOCALVERSION=-tegra
cd kernel-4.9
echo "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
make ARCH=arm64 O=$TEGRA_KERNEL_OUT tegra_defconfig
make ARCH=arm64 O=$TEGRA_KERNEL_OUT -j$(nproc) Image
#make ARCH=arm64 O=$TEGRA_KERNEL_OUT -j$(nproc) dtbs
make ARCH=arm64 O=$TEGRA_KERNEL_OUT -j$(nproc) modules
make ARCH=arm64 O=$TEGRA_KERNEL_OUT -j$(nproc) INSTALL_MOD_PATH=$KERNEL_MODULES_OUT modules_install
cd ..
ln -sf ~/nvidia/nvidia_sdk/JetPack_4.4.1_Linux_JETSON_AGX_XAVIER/Linux_for_Tegra 
#first remove all the old file in sdkmanager 
rm Linux_for_Tegra/kernel/zImage
rm Linux_for_Tegra/kernel/Image
rm Linux_for_Tegra/kernel/dtb/tegra194-agx-cti-AGX101-JCB002-IMX390-8CAM.dtb

cp DeviceTree/tegra194-agx-cti-AGX101-JCB002-IMX390-8CAM.dtb Linux_for_Tegra/kernel/dtb/
cp build/arch/arm64/boot/Image  Linux_for_Tegra/kernel/
cp build/arch/arm64/boot/zImage Linux_for_Tegra/kernel/



