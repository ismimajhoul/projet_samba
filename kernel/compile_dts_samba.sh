cd DeviceTree
dtc -O dtb -o tegra194-agx-cti-AGX101-JCB002-IMX390-8CAM.dtb devicetree_second_version.dts
cp tegra194-agx-cti-AGX101-JCB002-IMX390-8CAM.dtb ~/nvidia/nvidia_sdk/JetPack_4.4.1_Linux_JETSON_AGX_XAVIER/Linux_for_Tegra/kernel/dtb/
cd -
