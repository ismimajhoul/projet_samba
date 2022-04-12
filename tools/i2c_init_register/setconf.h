/*****************************************************************************
 * %PCMS_HEADER_SUBSTITUTION_START%
 * COMPANY : ALTRAN CDA/CIC/INTERIOR SWITCHES AND SMART CONTROLS
 *
 * PROJECT  : ISC:AP_DMS_ECU_DEV
 *
 *****************************************************************************
 * !File            : i2c_init_sequence.h
 *
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


/******************************************************************************/
/* Description: Provide data and orders to send or retrieve                   */
/*              Reserve and initialize memory - fills provided pointers with  */
/*              address of the memory reserved                                */
/*                                                                            */
/******************************************************************************/
/* RETURN                                                                     */
/* Comment: Values returned are stored in the provided pointers               */
/* Range  : Memory addresses                                                  */
/******************************************************************************/

#ifndef _I2C_MAX_TI_MLX_CONFIGURATION_H_
#define _I2C_MAX_TI_MLX_CONFIGURATION_H_

/*****************************************************************************/
/* CONSTANTS, MACROS                                                         */
/*****************************************************************************/

/*****************************************************************************/
/* Description: Enable /Disable Debug messages                               */
/*****************************************************************************/
#define ALTRAN_I2C_TRACES_ENABLED    (0x01)
#define ALTRAN_I2C_TRACES_DISABLED   (0x00)
#define _ALTRAN_I2C_DRIVER_TARGET_LINUX (0x01)
/*#define _TARGET_UNITY              (0x01)*/

/*****************************************************************************/
/* Description: ID of each device of the bus                                 */
/* Value: 0x00 to 0x7F                                                       */
/*****************************************************************************/
#define I2CDESER                    (0x48)
#define I2CD2                       (0x2c)
#define I2CS2                       (0x0c)
#define I2CSER                      (0x50)
#define I2CPLL                      (0x69)
#define I2CMLX                      (0x67)
#define I2CSEN                      (0x12)


/*****************************************************************************/
/* Description: ID of each device of the bus                                 */
/* Value: Number of commands to execute                                      */
/*****************************************************************************/
#define I2C_MAX_WRITE_RETRIES       ( 3 )


/******************************************************************************/
/* TYPES                                                                      */
/******************************************************************************/
/******************************************************************************/
/* Description: size of data got or register addresses                        */
/******************************************************************************/



enum registerLength
{
    _8B = 0,
    _10B = 1,
    _16B = 2,
};



void registerSequenceInit(  uint16_t** listOfRegister,
                            enum registerLength** dataLength,
                            enum registerLength** addressLength,
                            uint8_t** listOfDev,
                            uint8_t** listOfOps,
                            uint16_t** listOfMask,
                            uint16_t** listOfNewValues,
                            uint16_t** listOfTimerMS,
                            size_t* howManyCommands)
{
    /* 270 requests
     * This is the reference sequence provided by Melexis
     * We keep it here just for the record and to have a reference sequence for
     * further tests */


    /* We don't use 80 columns here to improve visual
     * management of the list of the commands. Under vim, you can add a new
     * command by making a visual selection of a block, under a GUI tool
     * you can use sublime text to do the same. Commands are easier to read
     * like this */
    //static uint16_t _listOfRegister[] =             { 0x0010,0x02b0,0x0005,0x02b0,0x02b2,0x2cb,0x2cc,0x2bc,0x2bd,0x2be,0x51,0x112,0x330,0x333,0x44a,0x320,0x332,0x2,0x10 };
    static uint16_t _listOfRegister[2048];
    //static enum registerLength _addressLength[] =   { _16B,_16B,_16B,_16B,_16B,_16B,_16B,_16B,_16B,_16B,_16B,_16B,_16B,_16B,_16B,_16B,_16B,_16B,_16B };
    static enum registerLength _addressLength[2048]   ;
    //static enum registerLength _dataLength[] =      { _8B,_8B,_8B,_8B,_8B,_8B,_8B,_8B,_8B,_8B,_8B,_8B,_8B,_8B,_8B,_8B,_8B,_8B,_8B };
    static enum registerLength _dataLength[2048] ;
    //static uint8_t _listOfDev[] =                   { I2CDES,I2CDES,I2CDES,I2CDES,I2CDES,I2CDES,I2CDES,I2CDES,I2CDES,I2CDES,I2CDES,I2CDES,I2CDES,I2CDES,I2CDES,I2CDES,I2CDES,I2CDES,I2CDES};
    static uint8_t _listOfDev[2048] ;
    //static uint8_t _listOfOps[] =                   { 0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01};
    static uint8_t _listOfOps[2048];
    //static uint16_t _listOfMask[] =                 { 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
    static uint16_t _listOfMask[2048] ;
    //static uint16_t _listOfNewValues[] =          { 0x51,0x81,0x81,0x60,0x03,0x43,0x11,0x04,0x20,0x05,0x81,0x32,0x04,0x4e,0x40,0x2c,0x20,0x23,0x11};
    static uint16_t _listOfNewValues[2048];
    //static uint16_t _listOfTimerMS[] =              { 0x50, 0x50, 0x50, 0x50, 0x50,0x50,0x50,0x50,0x50,0x50,0x50,0x50,0x50,0x50,0x50,0x50,0x50,0x50,0x0};
    static uint16_t _listOfTimerMS[2048] ;


     /* Makes the redirection -> reserved and filled memory
      * have to be pointed by provided pointers */
    *listOfRegister     = _listOfRegister;
    *addressLength      = _addressLength;
    *dataLength         = _dataLength;
    *listOfDev          = _listOfDev;
    *listOfOps          = _listOfOps;
    *listOfMask         = _listOfMask;
    *listOfNewValues    = _listOfNewValues;
    *listOfTimerMS      = _listOfTimerMS;

    *howManyCommands = sizeof(_listOfRegister) / sizeof(_listOfRegister[0]);
}


#endif



