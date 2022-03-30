cd DeviceTree
dtc -I dts -O dtb -f test_ar0330.dts -o tegra194-agx-cti-AGX101-JCB002-AR0330-8CAM.dtb
cp tegra194-agx-cti-AGX101-JCB002-AR0330-8CAM.dtb ../Linux_for_Tegra/kernel/dtb/
cd -
