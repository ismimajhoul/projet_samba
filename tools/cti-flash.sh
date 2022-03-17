#!/bin/bash

NOCOLOR='\033[0m'
GREEN='\033[0;32m'
RED='\033[0;41m'
STD='\033[0;0;39m'

flash(){   
    echo cti/$1/$2 
    ./flash.sh cti/$1/$2 mmcblk0p1
    exit 0
}

menu() {
    clear
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~"  
    echo "         CTI FLASH         "
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    echo "1. Rogue"
    echo "2. RogueX"
    echo "3. Mimic"
    echo "4. Xavier devkit with JCB004"
    echo "x. Exit"
}

xavierMenu() {
    clear
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~"  
    echo "      Xavier Modules       "
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    echo "1. Xavier"
    echo "2. Xavier8GB"
    echo "3. Cancel (back to main)"
    
}

rogueMenu() {
    clear
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~"  
    echo "          Rogue            "
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    echo "1. Base"
    echo "2. Base + 2 IMX274 Cam"
    echo "3. Base + 8 IMX390 Cam (on jcb002 adapter)"
    echo "4. Base + 8 AR0330 Cam (on jcb002 adapter)"
    echo "5. Cancel (back to main menu)"
}

rogueXMenu() {
    clear
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~"  
    echo "          RogueX           "
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    echo "1. Base"
    echo "2. Base + 2 IMX274 Cam"
    echo "3. Base + 8 IMX390 Cam (on jcb002 adapter)"
    echo "4. Base + 8 AR0330 Cam (on jcb002 adapter)"
    echo "5. Cancel (back to main menu)"
}

mimicMenu() {
    clear
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~"  
    echo "           Mimic           "
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    echo "1. Elroy RevF+"
    echo "2. Elroy mPCIe"
    echo "3. Elroy USB3"
    echo "4. Spacely"
    echo "5. Cancel (back to main menu)"
}

devkitMenu() {
    clear
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~"  
    echo "          JCB004           "
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    echo "Note: jcb004 cameras are not currently supported"
    echo "      on Xavier8GB"
    echo "1. Devkit + 8 AR0330 (E-CON) Cam (on jcb004 adapter)"
    echo "2. Devkit + 8 IMX390 (Leopard) Cam (on jcb004 adapter)"
    echo "3. Cancel (back to main menu)"
}

xavierOptions() {
    xavierMenu
    local choice
    read -p "Enter choice:  " choice

    case $choice in
        1) flash xavier $1;;
        2)  if [ $1 == "rogue-JCB002-IMX390" ] || [ $1 == "rogueX-JCB002-IMX390" ] 
            then
                echo -e "IMX390(8 Camera) not supported for Xavier 8GB" && sleep 2
	        elif [ $1 == "rogue-JCB002-AR0330" ] || [ $1 == "rogueX-JCB002-AR0330" ]
	        then
                echo -e "AR0330(8 Camera) not supported for Xavier 8GB" && sleep 2
            elif [ $1 == "mimic-elroy-revF+" ] || [ $1 == "mimic-elroy-mPCIe" ] || [ $1 == "mimic-elroy-USB3" ]
            then
                echo -e "Mimic not supported for Xavier 8GB" && sleep 2
		    else
                flash xavier-8G $1
            fi;; 
        3) ;;
        *) echo -e "${RED}Invalid Choice...${STD}" && sleep 1
    esac

}

rogueOptions(){
    rogueMenu
    local choice
    read -p "Enter choice:  " choice
    case $choice in
        1) xavierOptions rogue;;
        2) xavierOptions rogue-IMX274;;
        3) xavierOptions rogue-JCB002-IMX390;;
        4) xavierOptions rogue-JCB002-AR0330;;
        5) ;;
        *) echo -e "${RED}Invalid Choice...${STD}" && sleep 1
    esac
}

rogueXOptions(){
    rogueXMenu
    local choice
    read -p "Enter choice:  " choice
    case $choice in
        1) xavierOptions rogueX;;
        2) xavierOptions rogueX-IMX274;;
		3) xavierOptions rogueX-JCB002-IMX390;;
        4) xavierOptions rogueX-JCB002-AR0330;;
        5) ;;
        *) echo -e "${RED}Invalid Choice...${STD}" && sleep 1
    esac
}

devkitOptions(){
	devkitMenu
	local choice
	read -p "Enter choice:  " choice
	case $choice in
		1) flash xavier jcb004-ar0330;;
		2) flash xavier jcb004-imx390;;
		3) ;;
		*) echo -e "${RED}Invalid Choice...${STD}" && sleep 1
	esac
}

mimicOptions(){
    mimicMenu
    local choice
    read -p "Enter choice:  " choice
    case $choice in
        1) xavierOptions mimic-elroy-revF+;;
        2) xavierOptions mimic-elroy-mPCIe;;
        3) xavierOptions mimic-elroy-USB3;;
        4) xavierOptions mimic-spacely;;
        5) ;;
        *) echo -e "${RED}Invalid Choice...${STD}" && sleep 1
    esac
}

boardOptions(){
    local choice
    read -p "Enter choice:  " choice
    case $choice in
        1) rogueOptions;;
        2) rogueXOptions;;
        3) mimicOptions;;
	4) devkitOptions;;
        x) exit 0;;
        *) echo -e "${RED}Invalid Choice...${STD}" && sleep 1
    esac
}
 
trap ''
dmesg -D
 
while true
do
    menu
    boardOptions
done
