#cd DeviceTree
cpp -DLINUX_VERSION=409 -nostdinc -undef -x assembler-with-cpp -I ~/Téléchargements/83725_cti-l4t-src-agx-32.6.1-v006/sources/hardware/nvidia/platform/t19x/galen/kernel-dts -I ~/Téléchargements/83725_cti-l4t-src-agx-32.6.1-v006/sources/hardware/nvidia/soc/tegra/kernel-include -I ~/Téléchargements/83725_cti-l4t-src-agx-32.6.1-v006/sources/hardware/nvidia/soc/t19x/kernel-include -I Téléchargements/83725_cti-l4t-src-agx-32.6.1-v006/sources/hardware/nvidia/platform/t19x/common/kernel-dts -I ~/Téléchargements/83725_cti-l4t-src-agx-32.6.1-v006/sources/hardware/nvidia/platform/t19x/common/kernel-dts -I /home/lopes/Téléchargements/83725_cti-l4t-src-agx-32.6.1-v006/sources/hardware/nvidia/soc/t19x/kernel-dts tegra194-agx-cti-AGX101-JCB002-AR0330-8CAM.dts |grep -v '^# ' > my.dts

dtc -I dts -O dtb -f my.dts -o my.dtb
#cp tegra194-agx-cti-AGX101-JCB002-AR0330-8CAM.dtb ../Linux_for_Tegra/kernel/dtb/
#cd -
