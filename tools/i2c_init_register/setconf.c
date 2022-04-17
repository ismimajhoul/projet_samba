/*****************************************************************************
 * %PCMS_HEADER_SUBSTITUTION_START%
 * COMPANY : ALTRAN CDA/CIC/INTERIOR SWITCHES AND SMART CONTROLS
 *
 * PROJECT  : ISC:AP_DMS_ECU_DEV
 *
 *****************************************************************************
 * !Component       : TODO
 * !Description     : TODO
 *
 * !Module          : TODO
 * !Description     : TODO
 *
 *
 * !Author          : Contractor               !Date: 09/05/2018
 * !Coding Language : C
 *
 * !COPYRIGHT 2013 CDA/CIC/ISC
 * All rights reserved
 *****************************************************************************
 *****************************************************************************
 * EVOLUTIONS (automatic update under DIMENSIONS)
 *****************************************************************************
 * Current revision : %PR%
 *
 * %PL%
 * %PCMS_HEADER_SUBSTITUTION_END%
 * %PCMS_HEADER_SUBSTITUTION_END%
 *****************************************************************************/

/*****************************************************************************/
/* INCLUDE FILES                                                             */
/*****************************************************************************/
/****************** Sources to be used within the module *********************/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

/*****************************************************************************/
/* INCLUDE FILES                                                             */
/*****************************************************************************/
#include "setconf.h"
#ifdef OG
	#include "ImageSensorOG01ADefines.hpp"
#else
	#include "ImageSensorOV2311Defines.hpp"
#endif

#define CMD_SIZE	255
char cmdI2C[CMD_SIZE],path[5*CMD_SIZE];
int trace = 1;
int executeCmdI2C(char* cmdToExecute)
{
	FILE *fp;
	int status = 0;
	int i;
	fp = popen(cmdToExecute, "r");
	if (fp == NULL) return -1;

	while (fgets(path, 255, fp) != NULL)
	{
	   if(trace!=0) printf("%s", path);
	}

	pclose(fp);
	return 0;
}

static uint8_t gEnableTraces = ALTRAN_I2C_TRACES_ENABLED;

struct data_config
{
    char 	 device_i2c[32];
	uint16_t reg;
    uint16_t value;
    uint16_t tempo;
};

struct data_config atto_sensor_array_config[1024];
struct data_config atto_ser_array_config[1024];
struct data_config atto_deser_array_config[1024];
struct data_config device_i2c_array_config[1024];

#if 0
struct data_config atto_sensor_array_config[] =
{
		{0x0001, 0x00, 0},  /* Software Reset */
		{0x0001, 0x00, 0},  /* Software Reset */
};

//Specific Configuration for OG01A
 struct data_config atto_ser_array_config[] =
 {
		 {0x1E, 0x00, 1000},
 		 {0x04, 0x83, 1000},
		 {0x02, 0x1C, 1000},
		 {0x03, 0x00, 1000},
		 {0x04, 0x83, 1000},
		 {0x05, 0x80, 1000},
		 {0x06, 0x50, 1000},
		 {0x07, 0x06, 1000},
		 {0x08, 0x00, 1000},
		 {0x09, 0x00, 1000},
		 {0x0A, 0x00, 1000},
		 {0x0B, 0x00, 1000},
		 {0x0C, 0x00, 1000},
		 {0x0D, 0x6E, 1000},
		 {0x0E, 0x42, 1000},
		 {0x0F, 0xC2, 1000},
 };


struct data_config atto_deser_array_config[] =
{
	     {0x000D, 0x0,5},
	     {0x0320, 0x2F ,5},
	     {0x0323, 0x2F ,5},
	     {0x044A, 0xC8 ,5},
	     {0x048A, 0xC8, 5},
	     {0x0313, 0x82, 5},
	     {0x0314, 0x10, 5},
	     {0x0316, 0x5E ,5},
	     {0x0317, 0x0E ,5},
	     {0x0319, 0x10,5},
	     {0x031D, 0xEF ,5},
	     {0x0B96, 0x9B ,5},
	     {0x0C96, 0x9B ,5},
	     {0x0B06, 0xE8 ,5},
	     {0x0C06, 0xE8 ,5},
	     {0x01DA, 0x18 ,5},
	     {0x01FA, 0x18 ,5},
	     {0x0BA7, 0x45 ,5},
	     {0x0CA7, 0x45 ,5},
	     {0x040B, 0x07 ,5},
	     {0x042D, 0x15 ,5},
	     {0x040D, 0x1E ,5},
	     {0x040E, 0x1E ,5},
	     {0x040F, 0x00 ,5},
	     {0x0410, 0x00 ,5},
	     {0x0411, 0x01 ,5},
	     {0x0412, 0x01 ,5},
} ;
#endif

struct data_config *array_config;

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

int parseFiledata(struct data_config array_config[1024])
{
   FILE *fp1;   
   char filename[100];
   char oneword[100];
   char c;
   int i = 0;
   int j = 0;
   sprintf(filename,"%s","camera.data");
   fp1 = fopen(filename,"r");
   if(fp1==NULL)
   {
	   printf("cannot open file: %s \n",filename);
   }
   else
   {
	   printf("parsing file: %s \n",filename);
   }


   do 
   {
	  c = fscanf(fp1,"%s",oneword); /* got one word from the file */
	  strcpy(array_config[i].device_i2c,oneword);
	  printf("device i2c=%s\n",array_config[i].device_i2c);
      c = fscanf(fp1,"%s",oneword); /* got one word from the file */
      array_config[i].reg = (uint16_t) strtol(oneword,NULL,16);
      printf("register=%x\n",array_config[i].reg);
       c = fscanf(fp1,"%s",oneword); /* got one word from the file */
      array_config[i].value = (uint16_t) strtol(oneword,NULL,16);
      printf("value=%x\n",array_config[i].value);
       c = fscanf(fp1,"%s",oneword); /* got one word from the file */
      array_config[i].tempo = (uint16_t) strtol(oneword,NULL,10);   
      printf("tempo=%d\n",array_config[i].tempo);
      i++;
   }
   while (strcmp(oneword,"*"));
   fclose(fp1);

   for(j=0;j<i;j++)
   {
	printf("array_config[%d].reg=%x\n",j,array_config[j].reg);
	printf("array_config[%d].value=%x\n",j,array_config[j].value);
	printf("array_config[%d].tempo=%x\n",j,array_config[j].tempo);
   }

   return i-1;
}




/*****************************************************************************/
/* PRIVATE FUNCTIONS PROTOTYPES                                              */
/*****************************************************************************/

/******************************************************************************/
/* Description: Linux function to Read 16 bit register                        */
/*              These registers can have 8, 10 or 16 bit addresses            */
/*              The address is always provided on 16 bit, but in case of 8B   */
/*              register, we just keep the LSB                                */
/*                                                                            */
/******************************************************************************/
/* RETURN                                                                     */
/* Comment: Error code                                                        */
/* Range  : 0 if OK ; 1 else                                                  */
/******************************************************************************/
uint16_t i2cbusRead16BRegister( int device,
                                uint8_t deviceAddress,
                                enum registerLength enumRegSize,
                                uint16_t iRegisterAddress)
{
    uint8_t regAddrSize;
    uint16_t received;
    uint8_t errorSeen;
    uint16_t localRegisterAddress;

    struct i2c_rdwr_ioctl_data packets;
    struct i2c_msg messages[2];

    errorSeen = 0x00;
    received = 0x0000;

    switch(enumRegSize)
    {
        case _8B:
            regAddrSize = 1;
            printf("reg addr size: %d",regAddrSize);
            break;
        case _10B:
        case _16B:
            regAddrSize = 2;
            printf("reg addr size: %d",regAddrSize);
            break;
        default:
            regAddrSize = 1;
            printf("reg addr size: %d",regAddrSize);
            break;
    }


    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        /* Little endian : have to 8bit swap of value stored on 16 bytes */
        localRegisterAddress  = (iRegisterAddress & 0xff00) >> 8;
        localRegisterAddress |= (iRegisterAddress & 0x00ff) << 8;
    #else
        localRegisterAddress = iRegisterAddress;
    #endif



    messages[0].addr  = deviceAddress;
    messages[0].flags = 0;
    messages[0].len   = regAddrSize;
    messages[0].buf   = (void*)&localRegisterAddress;

    /* The data will get returned in this structure */
    //messages[1].addr  = deviceAddress;
    //messages[1].flags = I2C_M_RD/* | I2C_M_NOSTART*/;
    //messages[1].len   = sizeof(received);
    //messages[1].buf   = (void*)&received;

    messages[0].addr  = deviceAddress;
    printf("addr: 0x%x \n",messages[0].addr);
    messages[0].flags = 0;
    printf("flags: 0x%x \n",messages[0].flags);
    messages[0].len   = regAddrSize;
    printf("len: 0x%x \n",messages[0].len);
    messages[0].buf   = (void*)&localRegisterAddress;
    printf("localreg: 0x%x \n",localRegisterAddress);
    messages[0].len   = 2;

    /* Send the request to the kernel and get the result back */
    packets.msgs      = messages;
    packets.nmsgs     = 2;
    errorSeen |= (ioctl(device, I2C_RDWR, &packets) < 0);


    if(gEnableTraces)
    {
        fprintf(stderr, "\n[ -- ] received [0x%.04x] from [0x%.04x]",
                        received, iRegisterAddress);
    }

    if(errorSeen)
    {
        fprintf(stderr, " %s:%s:%d: WRegister err in at least one I/O op. ",
                __FILE__, __func__, __LINE__);
    }

    return received;
}

/******************************************************************************/
/* Description: Linux function to Write 16 bit register                       */
/*              These registers can have 8, 10 or 16 bit addresses            */
/*              The write is checked back by a read process                   */
/*              The write can be masked in order to change just the wanted    */
/*              part of the register                                          */
/*              The address is always provided on 16 bit, but in case of 8B   */
/*              register, we just keep the LSB                                */
/*                                                                            */
/******************************************************************************/
/* RETURN                                                                     */
/* Comment: Status of writing                                                 */
/* Range  : [0-1]                                                             */
/******************************************************************************/
int i2cbusWrite16BRegister( int device,
                            uint8_t deviceAddress,
                            enum registerLength enumRegSize,
                            uint16_t iRegisterAddress,
                            uint16_t iValue,
                            uint16_t iMask)
{
    uint8_t toWrite[4];
    uint8_t errorSeen;
    uint8_t offsetWrite;
    uint16_t localReceived;
    uint16_t localValue;
    uint16_t localRegisterAddress;
    uint16_t localMask;
    uint16_t received;

    errorSeen = 0x00;
    localValue = 0x0000;
    received = 0x0000;
    memset(toWrite, 0x00, 4);
    switch(enumRegSize)
    {
        case _8B:
            offsetWrite = 1;
            break;
        case _10B:
        case _16B:
            offsetWrite = 0;
            break;
        default:
            offsetWrite = 1;
            break;
    }

    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        /* Little endian : have to 8bit swap of value stored on 16 bytes */
        localRegisterAddress  = (iRegisterAddress & 0xff00) >> 8;
        localRegisterAddress |= (iRegisterAddress & 0x00ff) << 8;

        localValue  = (iValue & 0xff00) >> 8;
        localValue |= (iValue & 0x00ff) << 8;

        localMask  = (iMask & 0xff00) >> 8;
        localMask |= (iMask & 0x00ff) << 8;
    #else
        localRegisterAddress = iRegisterAddress;
        localValue = iValue;
        localMask = iMask;
    #endif

    if(gEnableTraces)
    {
        fprintf(stderr, "\n[    ] send %.04x at %.04x (mask %.04x) ",
                iValue, iRegisterAddress, iMask);
    }


    gEnableTraces = 0;
    received = i2cbusRead16BRegister(device,
                                     deviceAddress,
                                     enumRegSize,
                                     iRegisterAddress);
    gEnableTraces = 1;

    /* with ioctl() data is stored in big endian
     * When we printf them, we seen them reversed
     * -> 0x6700 means it is 0x67 0x00 in memory
     */
    localReceived = received;

    localReceived &=~ localMask;
    localReceived |=  localValue & localMask;

    memcpy(toWrite, &localRegisterAddress, 2);
    memcpy(toWrite + 2, &localReceived, 2);

    /** the write request */
    /* offsetWrite is to write only 1 byte addr on the two stored in toWrite */
    errorSeen |= (write(device, toWrite + offsetWrite,
                                4 - offsetWrite) != 4 - offsetWrite);
    usleep(10000);

    /* Confirmation read */
    gEnableTraces = 0;
    received = i2cbusRead16BRegister(device,
                                     deviceAddress,
                                     enumRegSize,
                                     iRegisterAddress);
    gEnableTraces = 1;

    /* with ioctl() data is stored in big endian
     * When we printf them, we seen them reversed
     * -> 0x6700 means it is 0x67 0x00 in memory
     */
    localReceived = received;


    /* Confirmation of the read value */
    if(localValue ^ localReceived)
    {
        if(gEnableTraces)
        {
            fprintf(stderr, "\r[ KO ] send %.04x at %.04x (mask %.04x) ",
                    iValue, iRegisterAddress, iMask);
        }

        fprintf(stderr, " %s:%s:%d: WRegister err Reg 0x%.04x: Expected "
                        "(print reversed) [0x%.04x] seen (print reversed) "
                        "[0x%.04x] ",
                __FILE__, __func__, __LINE__,
                iRegisterAddress, localValue, received);
    }
    else
    {
        if(gEnableTraces)
        {
            fprintf(stderr, "\r[ OK ] send %.04x at %.04x (mask %.04x) ",
                    iValue, iRegisterAddress, iMask);
        }
    }

    if(errorSeen)
    {
        fprintf(stderr, " %s:%s:%d: WRegister err in at least one I/O op ",
                __FILE__, __func__, __LINE__);
    }

    return !!errorSeen;
}




/******************************************************************************/
/* Description: Linux function to Read 8 bit register                         */
/*              These registers can have 8, 10 or 16 bit addresses            */
/*              The address is always provided on 16 bit, but in case of 8B   */
/*              register, we just keep the LSB                                */
/*                                                                            */
/******************************************************************************/
/* RETURN                                                                     */
/* Comment: Error code                                                        */
/* Range  : 0 if OK ; 1 else                                                  */
/******************************************************************************/
uint8_t i2cbusReadRegister( int device,
                            enum registerLength enumRegSize,
                            uint16_t iRegisterAddress)
{
    uint8_t received[2];
    uint8_t toWrite[3];
    uint8_t errorSeen;
    uint8_t offsetWrite;
    uint16_t localRegisterAddress;

    errorSeen = 0x00;
    *received = 0x00;
    *(received+1) = 0x00;
    switch(enumRegSize)
    {
        case _8B:
            offsetWrite = 1;
            break;
        case _10B:
        case _16B:
            offsetWrite = 0;
            break;
        default:
            offsetWrite = 1;
            break;
    }

    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        /* Little endian : have to 8bit swap of value stored on 16 bytes */
        localRegisterAddress  = (iRegisterAddress & 0xff00) >> 8;
        localRegisterAddress |= (iRegisterAddress & 0x00ff) << 8;
    #endif

    printf("reg addr: %x \n",localRegisterAddress);

    /* Read request creation */
    memcpy(toWrite, &localRegisterAddress, 2);

    //printf("toWrite[0]=0x%x toWrite[1]=0x%x toWrite[2]=0x%x\n",toWrite[0],toWrite[1],toWrite[2]);
    errorSeen |= (write(device, toWrite + offsetWrite, 2 - offsetWrite)
                        != 2 - offsetWrite);
    errorSeen |= (read(device, received, 1) != 1);


    if(gEnableTraces)
    {
        fprintf(stderr, "\n[ -- ] received value [0x%.02x] from register [0x%.04x]",
                        *received, iRegisterAddress);
    }

    if(errorSeen)
    {
        fprintf(stderr, " %s:%s:%d: WRegister err in at least one I/O op",
                __FILE__, __func__, __LINE__);
    }

    return received[0];
}

/******************************************************************************/
/* Description: Linux function to Write 8 bit register                        */
/*              These registers can have 8, 10 or 16 bit addresses            */
/*              The write is checked back by a read process                   */
/*              The write can be masked in order to change just the wanted    */
/*              part of the register                                          */
/*              The address is always provided on 16 bit, but in case of 8B   */
/*              register, we just keep the LSB                                */
/*                                                                            */
/******************************************************************************/
/* RETURN                                                                     */
/* Comment: Error status of writing                                           */
/* Range  : [0-1]                                                             */
/******************************************************************************/
int i2cbusWriteRegister(int device,
                        enum registerLength enumRegSize,
                        uint16_t iRegisterAddress,
                        uint8_t iValue,
                        uint8_t iMask)
{
    uint8_t received[2];
    uint8_t toWrite[3];
    uint8_t errorSeen;
    uint8_t offsetWrite;
    uint16_t localRegisterAddress;

    errorSeen = 0x00;
    memset(toWrite, 0x00, 3);
    memset(received, 0x00, 2);
    switch(enumRegSize)
    {
        case _8B:
            offsetWrite = 1;
            break;
        case _10B:
        case _16B:
            offsetWrite = 0;
            break;
        default:
            offsetWrite = 1;
            break;
    }

    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        /* Little endian : have to 8bit swap of value stored on 16 bytes */
        localRegisterAddress  = (iRegisterAddress & 0xff00) >> 8;
        localRegisterAddress |= (iRegisterAddress & 0x00ff) << 8;
    #endif

    if(gEnableTraces)
    {
        fprintf(stderr, "\n[    ] send %.02x at %.04x (mask %.02x)",
                iValue, iRegisterAddress, iMask);
    }

    memcpy(toWrite, &localRegisterAddress, 2);

    /* read initial value only if a mask is to apply */
    if(iMask != 0xff)
    {
        errorSeen |= (write(device, toWrite + offsetWrite, 2 - offsetWrite)
                             != 2 - offsetWrite);
        errorSeen |= (read(device, received, 1) != 1);
    }

    /* create value from retrieved and mask */
    iValue &= iMask;
    *(toWrite + 2) = *received &~ iMask;
    *(toWrite + 2) |= iValue;


    /** the write request */
    /* offsetWrite is to write only 1 byte addr on the two stored in toWrite */
    errorSeen |= (write(device, toWrite + offsetWrite, 3 - offsetWrite)
                        != 3 - offsetWrite);
    usleep(10000);

    /* Read confirmation */
    errorSeen |= (write(device, toWrite + offsetWrite, 2 - offsetWrite)
                        != 2 - offsetWrite);
    errorSeen |= (read(device, received, 1) != 1);

    /* Confirmation of the read value */
    if(*(toWrite + 2) ^ *(received))
    {
        if(gEnableTraces)
        {
            fprintf(stderr, "\r[ KO ] send %.02x at %.04x (mask %.02x)",
                    iValue, iRegisterAddress, iMask);
        }

        fprintf(stderr, " %s:%s:%d: WRegister err Reg 0x%.04x: "
                        "Expected [0x%.02x] seen [0x%.02x]",
                __FILE__, __func__, __LINE__,
                iRegisterAddress, *(toWrite + 2), *received);
    }
    else
    {
        if(gEnableTraces)
        {
            fprintf(stderr, "\r[ OK ] send %.02x at %.04x (mask %.02x)",
                    iValue, iRegisterAddress, iMask);
        }
    }
    if(errorSeen)
    {
        fprintf(stderr, " %s:%s:%d: WRegister err in at least one I/O op",
                __FILE__, __func__, __LINE__);
    }

    return !!errorSeen;
}





/******************************************************************************/
/* Description: Physically open the device                                    */
/*              Integrity system call                                         */
/*                                                                            */
/******************************************************************************/
/* RETURN                                                                     */
/* Comment: Nothing                                                           */
/* Range  : Nothing                                                           */
/******************************************************************************/
/*
*/
uint8_t initI2CDevice(void)
{
    return 0;
}

/******************************************************************************/
/* Description: Function to close physically the device                       */
/*              Integrity system call                                         */
/*                                                                            */
/******************************************************************************/
/* RETURN                                                                     */
/* Comment: Nothing                                                           */
/* Range  : Nothing                                                           */
/******************************************************************************/
uint8_t uninitI2CDevice(void)
{
    return 0;
}

/******************************************************************************/
/* Description: Logically open the device                                     */
/*              On linux it is a UNIX call (open) to the device               */
/*              On integrity it is a call the an abstraction layer. We just   */
/*              require the access to a device.                               */
/*                                                                            */
/******************************************************************************/
/* RETURN                                                                     */
/* Comment: Error code                                                        */
/* Range  : 0 if OK ; 1 else                                                  */
/******************************************************************************/
uint8_t openI2Cdevice(int* fd,int bus)
{
    char filename[80];
    // ouvre le device associe au bus I2C
    sprintf( filename,"/dev/i2c-%d", bus);
    printf("\n openI2Cdevice filename: %s\n",filename);

    //*fd = open("/dev/i2c-0", O_RDWR);
    *fd = open(filename, O_FSYNC|O_RDWR);

    if (*fd < 0)
    {
        printf("Error opening file: %s\n", strerror(errno));
        return 1;
    }
}


/******************************************************************************/
/* Description: Function to close logically the device                        */
/*              System call                                                   */
/*                                                                            */
/******************************************************************************/
/* RETURN                                                                     */
/* Comment: Nothing                                                           */
/* Range  : Nothing                                                           */
/******************************************************************************/
void closeI2Cdevice(int fd)
{
    close(fd);
}



/******************************************************************************/
/* Description: Change the destination device                                 */
/*              On linux we have to make a system call to change the device   */
/*              before an i2c request.                                        */
/*                                                                            */
/******************************************************************************/
/* RETURN                                                                     */
/* Comment: Error code. Error is seen when a device isn't reachable           */
/* Range  : 0 if OK ; 1 else                                                  */
/******************************************************************************/
uint8_t linuxChangePeripheralSelector(int fd, uint8_t deviceID)
{
    int errorSeen;
    static uint8_t oldDeviceID = 0x00;

    errorSeen = 0x00;

    if(oldDeviceID != deviceID)
    {
        printf("device I2C address: 0x[%x] \n", deviceID);
        errorSeen = (ioctl(fd, I2C_SLAVE, deviceID) < 0) ? 1 : 0;
        if(gEnableTraces)
        {
            //fprintf(stderr, "\n       %.02x -> %.02x", oldDeviceID, deviceID);
        }
        if(!errorSeen)
        {
            oldDeviceID = deviceID;
        }
    }

    return errorSeen;
}




/******************************************************************************/
/* Description: Make a read or write of a register                            */
/*              Call the appropriate function if we are on linux or integrity */
/*              and if we try to reach a 8B or 16B data register. This        */
/*              function also make read and/or write as asked by the calling  */
/*              function                                                      */
/*                                                                            */
/******************************************************************************/
/* RETURN                                                                     */
/* Comment: The success state of the device change operation -on linux-       */
/* Range  : 0 if OK ; 1 else. On integrity, value have to be discarded        */
/******************************************************************************/
uint8_t doReadOrWrite(  int fd,
                        uint16_t listOfRegister,
                        enum registerLength dataLength,
                        enum registerLength addressLength,
                        uint8_t listOfDev,
                        uint8_t listOfOps,
                        uint16_t listOfMask,
                        uint16_t listOfNewValues,
                        uint16_t listOfTimerMS)
{
    static uint8_t currentDevice = 0x00;
    uint8_t errorSeen = 0x00;
    int writeError = 0x00;

//#ifdef _ALTRAN_I2C_DRIVER_TARGET_LINUX

    /* Linux specific */
    errorSeen = linuxChangePeripheralSelector( fd, listOfDev );

    if(!errorSeen)
    {
        do
        {
            currentDevice =  listOfDev;

            /* read or write on register with 8,10,16 bit addr are done
             * by the same function */
            if(dataLength == _8B)
            {
		printf("\n8 bits operations\n");
                if(!listOfOps)    i2cbusReadRegister(   fd,
                                                        addressLength,
                                                        listOfRegister);

                if( listOfOps)    
                {
                    writeError =
                                  i2cbusWriteRegister( fd,
                                                        addressLength,
                                                        listOfRegister,
                                                        (listOfNewValues & 0xff),
                                                        (listOfMask & 0xff))
                                  ?
                                  (writeError + 1) : 0;}
                }
            /* Data size of 16B is handled by another function */
            else if(dataLength == _16B)
            {
		printf("\n16 bits operations\n");
                if(!listOfOps)    i2cbusRead16BRegister(    fd,
                                                            listOfDev,
                                                            addressLength,
                                                            listOfRegister);

                if( listOfOps)    {writeError =
                                  i2cbusWrite16BRegister(   fd,
                                                            listOfDev,
                                                            addressLength,
                                                            listOfRegister,
                                                            listOfNewValues,
                                                            listOfMask)
                                  ?
                                  (writeError + 1) : 0;}
            }

            /* Some request needs time to be executed
             * because some hardware reconfiguration is needed */
            usleep(1000 * listOfTimerMS);
        }while(writeError < I2C_MAX_WRITE_RETRIES && writeError != 0);

        writeError = 0;
    }
    else
    {
        fprintf(stderr, "%s:%s:%d: Error, unknown data register size\n",
                __FILE__, __func__, __LINE__);
        /*  This error is to notify the device switch error. So,
            we cannot use it in this case */
        /* errorSeen |= 1; */
    }

//#endif
    //printf("\n end of doReadOrWrite \n");

    return errorSeen;
}



/******************************************************************************/
/* Description: Debug function : dump all registers                           */
/*              Do it without error check, just dump as many as possible      */
/*                                                                            */
/******************************************************************************/
/* RETURN                                                                     */
/* Comment: Error code                                                        */
/* Range  : 0 if OK ; 1 else                                                  */
/******************************************************************************/
uint8_t dumpAllReg(int fd)
{
    uint8_t errorSeen;
    uint8_t currentDevice;
    int i;

    errorSeen = 0x00;



    for(i=0; i<0xff; i++)
    {
        /* Serializer Dump */
        errorSeen |= doReadOrWrite   ( fd,
                                       i,
                                       _8B,
                                       _8B,
                                       I2CSER,
                                       0x00,
                                       0x0000,
                                       0x0000,
                                       0x000f);

    }

    for(i=0; i<0xffff; i++)
    {
        /* Deser dump */
        errorSeen |= doReadOrWrite   ( fd,
                                       i,
                                       _8B,
                                       _16B,
                                       I2CDESER,
                                       0x00,
                                       0x0000,
                                       0x0000,
                                       0x000f);

    }

    return errorSeen;
}






/******************************************************************************/
/* Description: Entry point.                                                  */
/*              Call mains functions (as the main steps of the program)       */
/*                                                                            */
/******************************************************************************/
/* RETURN                                                                     */
/* Comment: Error code                                                        */
/* Range  : 0 if OK ; 1 else                                                  */
/******************************************************************************/
uint8_t doAllReadWriteOperations (  int fd,
                                    uint16_t* listOfRegister,
                                    enum registerLength* dataLength,
                                    enum registerLength* addressLength,
                                    uint8_t* listOfDev,
                                    uint8_t* listOfOps,
                                    uint16_t* listOfMask,
                                    uint16_t* listOfNewValues,
                                    uint16_t* listOfTimerMS,
                                    size_t howManyCommands)
{
    uint8_t errorSeen;
    uint8_t currentDevice;
    int i;

    errorSeen = 0x00;



    /* Send all commands to devices. One by one */
    for(i=0; i<howManyCommands; i++)
    {
        /* this function can be executed on both OS */
        //printf("debug: 0x%x \n",listOfDev[i]);
        errorSeen = doReadOrWrite    ( fd,
                                       listOfRegister[i],
                                       dataLength[i],
                                       addressLength[i],
                                       listOfDev[i],
                                       listOfOps[i],
                                       listOfMask[i],
                                       listOfNewValues[i],
                                       listOfTimerMS[i]);

        /* An error seen equals to an issue to change
         * the destination device. Meaning, in many cases
         * that the destination device is impossible to reach
         * (no started or invalid device ID */
        if(!errorSeen)
        {
            currentDevice = listOfDev[i];
        }
        else
        {
            fprintf(stderr, "\n%s:%s:%d: Dev id switch impossible from %.02x "
                            "to %.02x\n",
                __FILE__, __func__, __LINE__, currentDevice,  listOfDev[i]);
            close(fd);
            return 1;
        }
    /* Execute command per command and wait return key pressed */
    /* getchar(); */
    }


    return errorSeen;
}


int getChannel()
{
	int c;
	c = getchar();
	//while (c != EOF)
	//{
		//printf("%c ", c);
		//c = getchar();
	//}
	return c-0x30;
}

int selectchannel()
{
	int channel;
	printf("select multiplexer channel\n");
	printf("enter channel number\n");
	printf("0 => channel 0\n");
	printf("1 => channel 1\n");
	printf("2 => channel 2\n");
	printf("3 => channel 3\n");
	channel= getChannel() + 4;
	sprintf(cmdI2C,"i2cset -y -f 7 0x72 0 %d\n",channel);
	printf("%s\n",cmdI2C);
	executeCmdI2C(cmdI2C);
	executeCmdI2C("i2cdetect -y -r 7");
	printf("channel:%d\n",channel);
	return channel;
}



/******************************************************************************/
/* Description: Entry point.                                                  */
/*              Call mains functions (as the main steps of the program)       */
/*                                                                            */
/******************************************************************************/
/* RETURN                                                                     */
/* Comment: Error code                                                        */
/* Range  : 0 if OK ; 1 else                                                  */
/******************************************************************************/
int main(int argc,char* argv[])
{
    int fd;
    int i;
    uint8_t currentDevice;
    uint8_t errorSeen;


    uint16_t*            listOfRegister;
    enum registerLength* addressLength;
    enum registerLength* dataLength;
    uint8_t*             listOfDev;
    uint8_t*             listOfOps;
    uint16_t*            listOfMask;
    uint16_t*            listOfNewValues;
    uint16_t*            listOfTimerMS;
    size_t               howManyCommands;
    uint8_t 		device_conf;
    int 		channel;

    int nb_elem;
    if(argc < 2)
    {
    	printf("nb parameter issue\n");
    	return 0;
    }
    else
    {
	printf("nb parameter: %d\n",argc);
    }

    channel = selectchannel();

    currentDevice = 0x00;
    errorSeen = 0x00;
    howManyCommands = 0x00;

    // chargement data register
    /* Fill memory buffers pointed by parameters */
    registerSequenceInit(&listOfRegister, &dataLength, &addressLength, &listOfDev,
                         &listOfOps, &listOfMask, &listOfNewValues,
                         &listOfTimerMS, &howManyCommands);;

    //array_config = device_i2c_array_config;
    nb_elem = parseFiledata(device_i2c_array_config);

/*
    if(strcmp(argv[1],"deser")==0)
    {
    	array_config = &atto_deser_array_config[0];
    	nb_elem= ARRAY_SIZE(atto_deser_array_config);
    	device_conf = I2CDESER;
    	nb_elem = parseFiledata("deser",atto_deser_array_config);
        printf("nombre d'elements extraits du fichier deser.data\n");
    	//printf("sizeof array: %ld\n",sizeof(atto_deser_array_config));
    	//printf("sizeof((x)[0]: %ld\n",sizeof((atto_deser_array_config[0])));
    }
    else if (strcmp(argv[1],"ser")==0)
    {
    	array_config = &atto_ser_array_config[0];
    	nb_elem= ARRAY_SIZE(atto_ser_array_config);
    	device_conf = I2CSER;
    	nb_elem = parseFiledata("ser",atto_ser_array_config);
    	printf("sizeof array: %ld\n",sizeof(atto_ser_array_config));
    	printf("sizeof((x)[0]: %ld\n",sizeof((atto_ser_array_config[0])));
    }
    else if (strcmp(argv[1],"sensor")==0)
    {
    	array_config = &atto_sensor_array_config[0];
    	nb_elem= ARRAY_SIZE(atto_sensor_array_config);
    	printf("I2CSENSOR : 0x%x \n",I2CSENSOR);
    	device_conf = I2CSENSOR;
    	nb_elem = parseFiledata("sensor",atto_sensor_array_config);
    	printf("debug : 0x%x \n",device_conf);
    	printf("sizeof array: %ld\n",sizeof(atto_sensor_array_config));
    	printf("sizeof((x)[0]: %ld\n",sizeof((atto_sensor_array_config[0])));
    }
    else
    {
    	printf("*** %s unknown config *** \n",argv[1]);
    	return 0;
    }
*/

    
    howManyCommands = nb_elem;
    printf("nb register: %d\n",nb_elem);
    
    printf("\n register list\n");
    for(int i = 0;i<nb_elem;i++)
    {
    	 listOfRegister[i] 	= device_i2c_array_config[i].reg;
    	 listOfOps[i] 		= 0x0;
         listOfDev[i] 		= device_conf; 
         if (strcmp(device_i2c_array_config[i].device_i2c,"ser")==0)
        	 addressLength[i] 	= _8B;
         else
        	 addressLength[i] 	= _16B;

         dataLength[i] 	= _8B;
         listOfTimerMS[i] 	= 0x50;
         listOfMask[i] 		= 0xffff;
    	 //printf("listOfRegister[%d]= 0x%x\n",i,listOfRegister[i]);
         
    }
    
    printf("\n register list\n");
    for(int i = 0;i<nb_elem;i++)
    {
    	 listOfRegister[i] = device_i2c_array_config[i].reg;
    	 printf("listOfRegister[%d]= 0x%x\n",i,listOfRegister[i]);
    	 listOfNewValues[i] = device_i2c_array_config[i].value;
    	 printf("listOfNewValues[%d]= 0x%x\n",i,listOfNewValues[i]);
         printf("addressLength[%d]= %d\n",i,addressLength[i]);
    }

    for(int i = 0;i<nb_elem;i++)                                    
    {                                                               
         if(argc > 2)
        	 listOfOps[i] = (unsigned char) atoi(argv[2]);
         else
        	 listOfOps[i] = 0;
         printf("listOfOps[%d]= %d\n",i,listOfOps[i]);
    }  
    
    /* For integrity, call physical init */
    errorSeen |= initI2CDevice();

    /* Open devices - In linux it is a open() call
     * and in integrity it is a HWI call to have an
     * abstraction number */
    printf("channel:%d\n",channel);
    //errorSeen |= openI2Cdevice(&fd,30 + channel - 4);
    errorSeen |= openI2Cdevice(&fd,0);

    for(;;)
    {
    /* Do all operation listed in the .h file */
    	errorSeen |= doAllReadWriteOperations(fd, listOfRegister, dataLength,
                                          addressLength, listOfDev,
                                          listOfOps, listOfMask, listOfNewValues,
                                          listOfTimerMS, howManyCommands);
	if(argc==3)
        {
    	    if (strcmp(argv[2],"surv")!=0) break;
	}
	else if(argc==2)
        {
    	    if (strcmp(argv[1],"surv")!=0) break;
	}
	else if(argc==1)
	{
	    break;
	}
    }
    /* Dump all registers for debug purposes */
    /* errorSeen |= dumpAllReg(fd); */

    /* Logically close the device */
    closeI2Cdevice(fd);

    /* Physically close the device - for integrity */
    errorSeen |= uninitI2CDevice();

    fprintf(stderr, "\n");

    return 0;
}



