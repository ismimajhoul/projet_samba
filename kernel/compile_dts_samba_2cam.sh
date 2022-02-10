cd DeviceTree
dtc -I dts -O dtb -f dts_atto320_2cam.dts -o tegra194-agx-cti-AGX101-JCB002-IMX390-8CAM.dtb
cp tegra194-agx-cti-AGX101-JCB002-IMX390-8CAM.dtb ../Linux_for_Tegra/kernel/dtb/
cd -
