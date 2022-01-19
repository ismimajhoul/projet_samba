mkdir -p build
TEGRA_KERNEL_OUT=$(pwd)/build/
export CROSS_COMPILE=$HOME/l4t-gcc/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-
export LOCALVERSION=-tegra
cd kernel-4.9
make ARCH=arm64 O=$TEGRA_KERNEL_OUT -j 6
ln -s ~/nvidia/nvidia_sdk/JetPack_4.4.1_Linux_JETSON_AGX_XAVIER/Linux_for_Tegra Linux_for_Tegra
#first remove all the old file in sdkmanager 
rm Linux_for_tegra/kernel/zImage
rm Linux_for_tegra/kernel/Image
rm Linux_for_tegra/kernel/dtb/tegra194-agx-cti-AGX101-JCB002-IMX390-8CAM.dtb

cp DeviceTree/tegra194-agx-cti-AGX101-JCB002-IMX390-8CAM.dtb Linux_for_tegra/kernel/dtb/
cp build/arch/arm64/boot/Image  Linux_for_tegra/kernel/
cp build/arch/arm64/boot/zImage Linux_for_tegra/kernel/



