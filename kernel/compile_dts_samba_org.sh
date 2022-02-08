cd DeviceTree
dtc -I dts -O dtb -f devicetree_file_name_origine.dts -o tegra194-agx-cti-AGX101-JCB002-IMX390-8CAM.dtb
cp tegra194-agx-cti-AGX101-JCB002-IMX390-8CAM.dtb ../Linux_for_Tegra/kernel/dtb/
cd -
