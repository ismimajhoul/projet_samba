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
cd ..
ln -sf ~/nvidia/nvidia_sdk/JetPack_4.4.1_Linux_JETSON_AGX_XAVIER/Linux_for_Tegra 
#first remove all the old file in sdkmanager 
#rm Linux_for_Tegra/kernel/zImage
#rm Linux_for_Tegra/kernel/Image
#rm Linux_for_Tegra/kernel/dtb/tegra194-agx-cti-AGX101-JCB002-ATTO640-8CAM.dtb

#cp DeviceTree/tegra194-agx-cti-AGX101-JCB002-AR0330-8CAM.dtb Linux_for_Tegra/kernel/dtb/tegra194-agx-cti-AGX101-JCB002-AR0330-8CAM.dtb
cp build/arch/arm64/boot/Image  Linux_for_Tegra/kernel/
cp build/arch/arm64/boot/zImage Linux_for_Tegra/kernel/
#cp ../tools/webcam_capture.c ~/nvidia/nvidia_sdk/JetPack_4.4.1_Linux_JETSON_AGX_XAVIER/Linux_for_Tegra/rootfs/home/


