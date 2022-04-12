/** ************************************************************************************************
 * COMPANY : VALEO
 *
 * PROJECT  : DMSVisionsubSystem
 ***************************************************************************************************
 * \file    ImageSensorOV2311Defines.hpp
 *
 * \Module  DMSCameraSystem
 * \brief   Sensor OV2311 parmeters definitions
 *
 * \author  Rene J NGONGO
 * \date    12/10/2018
 *
 * !COPYRIGHT VALEO
 * All rights reserved
 **************************************************************************************************/
#ifndef IMAGESENSOR_OV2311_Defines_HPP
#define IMAGESENSOR_OV2311_Defines_HPP

//! \brief Sensor version part one
#define SENSOR_VERSION_1                            0x00004F56U

//! \brief Sensor version part two
#define SENSOR_VERSION_2                            0x32333131U

//! \brief Video Capture Time out in milli seconds
#define VC_FRAME_TIMEOUT_MS_SECONDS                 500U

//! \brief MPX Camera OV2311 Driver specific frame width
#define MPXCAM_OV2311_FRAME_WIDTH                   1600U

//! \brief MPX Camera OV2311 Driver specific Image height
#define MPXCAM_OV2311_IMAGE_HEIGHT                  1300U

#ifndef NO_SENSOR_METADATA
//! \brief MPX Camera OV2311 Driver specific frame height
#define MPXCAM_OV2311_FRAME_HEIGHT                 1301U
//! \brief Metadata of the sensor in byte (1 line)
#define MPXCAM_OV2311_u32ESENSOR_METADATA           MPXCAM_OV2311_FRAME_WIDTH
#else
#define MPXCAM_OV2311_FRAME_HEIGHT                  1300U
#define MPXCAM_OV2311_u32ESENSOR_METADATA           0
#endif

//! \brief MPX Camera OV2311 Driver specific frame size
#define MPXCAM_OV2311_FRAME_SIZE                    MPXCAM_OV2311_FRAME_WIDTH * MPXCAM_OV2311_FRAME_HEIGHT

//! \brief MPX Camera OV2311 Driver specific frame color depth
#define MPXCAM_OV2311_FRAME_COLOR_DEPTH             8U

//! \brief Byte per pixel RAW8
#define MPXCAM_OV2311_FRAME_BYTE_PER_PIXEL          1U

//! \brief MPX Camera OV2311 default frame rate
#define MPXCAM_OV2311_u8DEFAULT_FRAMERATE           54

//! \Valeo Metadata lines before the image
#define VALEO_METADATA_LINES                        8

//! \Sensor Vertical flip value
#define SENSOR_VERT_FLIP                           0x44U

//! \ Sensor Horizontal Mirror value
#define SENSOR_HORIZ_MIRROR                        0x04U

//! \Sensor Start stream value
#define SENSOR_START_STREAM                        0x01U

#define SENSOR_STOP_STREAM                         0x00

//! \ Sensor low Power mode
#define SENSOR_LOW_POWER_MODE                      0x01U

//! \Sensor low power mode control
#define SENSOR_LOW_POWER_MODE_CTRL                 0x84U

//! \Sensor low power mode control
#define SENSOR_NORMAL_MODE_CTRL                    0x10U

//! \Sensor low power mode control
#define SENSOR_NORMAL_MODE                         0x00

//! \Sensor number of active frames
#define SENSOR_ACTIVE_FRAMES                       0x01U

//! \Sensor configuration failure re-try count
#define SENSOR_CONF_FAILED_RETRY_COUNT             3U

//! \20us delay
#define TWENTY_US_DELAY                            20U

//! \Sensor Pixel Clock
#define PIXCLOCK                                   160000000U

//! \Sensor chip ID MSB register
#define CHIP_ID_HIGH                               0x23U
//! \Sensor chip ID LSB register
#define CHIP_ID_LOW                                0x11U

//! \brief Camera sensor OV2311 i2c slave address
#define CAMERA_OV2311_I2C_SLAVE_ADDRESS            0x60U

//! \brief Camera sensor OV2311 chip revision number
#define SENSOR_REVISION_ID                         0x300CU

//! \brief Camera sensor OV2311 chip revision number
#define SENSOR_CHIP_ID_HIGH                        0x300AU

//! \brief Camera sensor OV2311 chip revision number
#define SENSOR_I2C_ADDRS                           0x0109U

//! \brief Camera sensor OV2311 chip ID number
#define SENSOR_CHIP_ID_LOW                         0x300BU

//! \brief Camera sensor Exposure time[15:8]
#define SENSOR_EXPOSURE_TIME_2                     0x3501U

//! \brief Camera sensor Exposure time[7:0]
#define SENSOR_EXPOSURE_TIME_1                     0x3502U

//! \brief Camera sensor Fine Exposure time[15:8]
#define SENSOR_EXPOSURE_FINE_2                     0x3506U

//! \brief Camera sensor Fine Exposure time[7:0]
#define SENSOR_EXPOSURE_FINE_1                     0x3507U

//! \brief Camera sensor Timing Format 1
#define SENSOR_TIMING_FORMAT_1                     0x3820U

//! \brief Sensor Sc Ctrl 06
#define SENSOR_SC_CTRL_06                          0x3006U

//! \brief Select Pin on sensor for strobe
#define STROBE_PIN                                 0x08U

//! \brief Camera sensor Timing Format 2
#define SENSOR_TIMING_FORMAT_2                     0x3821U

//! \brief Camera sensor Gain
#define SENSOR_GAIN                                0x3508U

//! \brief Sensor Mode Select Register
#define SC_MODE_SELECT                             0x0100U

//! \brief Sensor output format
#define REG_SENSOR_FORMAT                          0x3662U

//! \brief Sensor Mipi format header
#define REG_SENSOR_FORMAT_MIPI                     0x4814U

//! \brief Sensor Total Vertical Timing Size High Byte
#define TIMMING_VTS_HIGH_BYTE                      0x380EU

//! \brief Sensor Total Vertical Timing Size Low Byte
#define TIMMING_VTS_LOW_BYTE                       0x380FU

//! \brief Sensor Total Horizontal Timing Size High Byte
#define TIMMING_HTS_HIGH_BYTE                      0x380CU

//! \brief Sensor Total Horizontal Timing Size Low Byte
#define TIMMING_HTS_LOW_BYTE                       0x380DU

//! \brief Sensor Row Global Transfer Low Byte
#define TIMMING_RGT_HIGH_BYTE                      0x382CU

//! \brief Sensor Row Global Transfer High Byte
#define TIMMING_RGT_LOW_BYTE                       0x382DU

//! \brief R Counter Reset Value High
#define R_RESET_VALUE_HIGH                         0x3826U

//! \brief R Counter Reset Value Low
#define R_RESET_VALUE_LOW                          0x3827U

//! \brief Margin to use external trigger
#define FPS_TRIGGER_MARGIN                         10U

//! \brief Sensor system Clock
#define SENSOR_SYS_CLOCK_MHZ                       80U

//! \brief Sensor strobe pattern
#define PWM_CTRL_20                                0x3920U

//! \brief Sensor strobe pattern
#define STROBE_START_PT_HIGH                       0x3929U

//! \brief Sensor strobe pattern
#define STROBE_START_PT_LOW                        0x392AU

//! \brief Target Board ISI channel used
#define BOARD_ISI_CHANNEL                          0

//! \brief Target Board CSI channel used
#define BOARD_CSI_CHANNEL                          0

//! \brief Target Board CSI mode used
#define BOARD_CSI_MODE                             1

//! \brief Minimum Expoure time
#define MINIMUM_EXPO_TIME                          3.0F

//! \brief Maximum Strobe Length
//CAM B02
#define MAXIMUM_STROBE_LENGTH_PLL_0_60_D_B02_RAW10   0x93 //2.708475 ms
#define MAXIMUM_STROBE_LENGTH_PLL_0_60_D_B02         0xE1 //2.7005625 ms
//CAM B01
#define MAXIMUM_STROBE_LENGTH_PLL_0_60_D_B01_RAW10   0x47 //1.308175 ms
#define MAXIMUM_STROBE_LENGTH_PLL_0_60_D_B01         0x6C //1.2987 ms
//Old Version
#define MAXIMUM_STROBE_LENGTH_PLL_0_60_OLD_RAW10     0x36U  //0.99495 ms
#define MAXIMUM_STROBE_LENGTH_PLL_0_60_OLD           0x53U  //0.998075 ms

//! \brief Minimum gain
#define MINIMUM_GAIN                               1.0F

//! \brief Maximum gain
#define MAXIMUM_GAIN                               8.0F

//! \brief 150 Frame
#define FRAME_COUNT_MODULO                         150U

//! \brief Strobe Frame Span [15:8]
#define PWM_CTRL_27                                0x3927U

//! \brief Strobe Frame Span[7:0]
#define PWM_CTRL_28                                0x3928U

//! \brief Power Control Options
#define PSV_CTRL                                   0x4F00U

//! \brief Low Power Mode Control
#define SC_LP_CTRL4                                0x3030U

//! \brief Number of active frames
#define SC_CTRL_3F                                 0x303FU

//! \brief Number of lines of sleep period [39:32]
#define SC_LP_CTRL0                                0x302CU

//! \brief Number of lines of sleep period [15:8]
#define SC_LP_CTRL1                                0x320FU

//! \brief Low power mode
#define SC_CTRL_23                                 0x3023U

//! \brief Control group mode
#define GROUP_ACCESS                               0x3208U

//! \brief TOTAL PIXEL PER LINE
#define TIMING_HTS                                 1808U

//! \brief REGISTER TO STORE AUTHENTIFICATION
#define REG_AUTHENTIFICATION                       0x7024U

//! \ brief Exposure fine Mapping Range: (0 ~ (HTS-0x10))
#define EXPO_FINE_MAP                              ((uint16_t)TIMING_HTS - 16)

//! \brief Size of OTP Memory (in Byte)
#define OTP_MEMORY_SIZE                            128U

//! \brief First Register Buffer for OTP Memory
#define REG_FIRST_ADDR_OTP_STORED                  0x7000U

//! \brief Last Register Buffer for OTP Memory
#define REG_LAST_ADDR_OTP_STORED                   0x707FU

//! \brief First Register Buffer for OTP Memory VALEO SPACE 1
#define REG_FIRST_ADDR_VALEO1_OTP_STORED           0x7010U

//! \brief Last Register Buffer for OTP Memory VALEO SPACE 1
#define REG_LAST_ADDR_VALEO1_OTP_STORED           0x7011U

//! \brief First Register Buffer for OTP Memory VALEO SPACE 2
#define REG_FIRST_ADDR_VALEO2_OTP_STORED           0x701AU

//! \brief Last Register Buffer for OTP Memory VALEO SPACE 2
#define REG_LAST_ADDR_VALEO2_OTP_STORED            0x702BU

#define OTP_LOAD_CTRL                              0x3D81U

#define OTP_PROGRAM_CTRL                           0x3D80U

#define TEMPERATURE_SEUIL                          0xC000U

#define REG_POWER_SAVE_MODE                        0x3017U
#define ENABLE_POWER_SAVE_MODE                     0xF0U
#define DISABLE_POWER_SAVE_MODE                    0xF2U


#define SC_GP_IO_IN2                               ((uint16_t)0x302A)
#define D0_BIT                                     (7U)
#define READ_D0_BIT(byte)                          uint8_t(((byte) >> D0_BIT) & (0x01U))
#define DIM(a)                                     (sizeof(a)/sizeof((a)[0]))

#define CAM_B0X_REF                                0x45598070U //ASCII + 3 x BCD = E598070
#define CAM_B02_INDEX                              0x3220U //2 x ASCII = 2.0 (0x32.0x20)
#define CAM_B01_INDEX                              0x3120U //2 x ASCII = 1.0 (0x32.0x20)

// for legacy with previous version (to be removed after version 2.18)
#define DAIMLER_B0X_REF                            CAM_B0X_REF
#define DAIMLER_B02_INDEX                          CAM_B02_INDEX
#define DAIMLER_B01_INDEX                          CAM_B01_INDEX


#define CAM_C0X_TYPE                               0x43U //ASCII = C (0x43) = C for Camera
#define CAM_C01_INDEX                              0x4312U //1xASCII + Proto Number + Board Variant = C01 (0x43 0x1 0x2)
#define CAM_C02_INDEX                              0x4322U //1xASCII + Proto Number + Board Variant = C02 (0x43 0x2 0x2)

//OTP access offset for B0X Sample
#define OFFSET_VALEODATA1                          16U
#define OFFSET_VALEODATA2                          26U
#define OFFSET_FINAL_PRODUCT_B0X_REF               26U
#define OFFSET_FINAL_PRODUCT_B0X_INDEX             30U
#define OFFSET_FINAL_PRODUCT_B0X_PLANT             32U
#define OFFSET_FINAL_PRODUCT_B0X_LINE              36U
#define OFFSET_FINAL_PRODUCT_B0X_MANUFACT          37U
#define OFFSET_FINAL_PRODUCT_B0X_DAILY_CPT         40U
#define OFFSET_FINAL_PRODUCT_B0X_DEVIAT_NBR        42U

#define FINAL_PRODUCT_B0X_REF_SIZE                 4U
#define FINAL_PRODUCT_B0X_INDEX_SIZE               2U
#define FINAL_PRODUCT_B0X_PLANT_SIZE               4U
#define FINAL_PRODUCT_B0X_MANUFACT_SIZE            3U
#define FINAL_PRODUCT_B0X_DAILY_COUNTER_SIZE       2U


//OTP access offset for C0X Sample
#define OFFSET_C0X_SERIAL_TYPE                     16U
#define OFFSET_C0X_VCAFT_DAY                       17U
#define OFFSET_C0X_VCAFT_MONTH                     26U
#define OFFSET_C0X_VCAFT_YEAR                      27U
#define OFFSET_C0X_DATE_STAMP                      28U
#define OFFSET_C0X_SERIAL_NBR_COUNT                31U
#define OFFSET_C0X_PRODUCT_MAJOR_MINOR             34U
#define OFFSET_C0X_SITE                            36U
#define OFFSET_C0X_CAM_PRODUCT_CODE                37U
#define OFFSET_C0X_RELEASE_YEAR_WEEK               42U

#define C0X_DATE_STAMP_SIZE                        3U
#define C0X_SERIAL_NUMBER_COUNTER_SIZE             3U
#define C0X_PRODUCT_MAJOR_MINOR_SIZE               2U
#define C0X_CAM_PRODUCT_CODE_SIZE                  5U
#define C0X_RELEASE_WEEK_YEAR_SIZE                 2U

//! \brief Serial Camera Control Bus (SCCB) clock switch register
#define SB_SWITCH                                  0x31FFU

//! \brief SCCB with clock
#define SCCB_WITH_CLOCK                            0x01U

//! \brief SCCB without clock
#define SCCB_WO_CLOCK                              0x00U

//! \brief R_CORE_4 (analog control) register
#define R_CORE_4                                   0x3664U

//! \brief mask to enable ADC for sensor temperature in standby mode
#define EN_ADC_TEMP_MASK                           0x40U

//! \brief TPM2_INTEGER register (temperature integer part)
#define TPM2_INTEGER                               0x4417U
//! \brief TPM2_DECIMAL register (temperature decimal part)
#define TPM2_DECIMAL                               0x4418U

//Contains the number of usefull variable in the struct tstrSensorMapMetadata 
#define NBR_DATA_STRUCT_SENSOR_METADATA            13U


//namespace valeo
//{
//namespace camerasystem
//{

//! \brief Sensor strobe pattern
enum
{
  enuSTROBE_PATTERN_EXT_TRIG = 0xA5,
  enuSTROBE_PATTERN_NORMAL_MODE = 0xFF
};

#if 0
/* !Comment: Structure to represent OTP Memory for B0X Sample (128 Bytes) */
typedef struct
{
  uint8_t au8OmnivisionData1[16];    //Reserved OVT data                  //Offset 0
  uint8_t au8ValeoData1[2];       //Empty Valeo Space                     //Offset 16
  uint8_t au8OmnivisionData2[8];     //Reserved OVT data                  //Offset 18
  uint8_t au8FinalProductRef[FINAL_PRODUCT_B0X_REF_SIZE];                 //Offset 26
  uint8_t au8FinalProductIndex[FINAL_PRODUCT_B0X_INDEX_SIZE];             //Offset 30
  uint8_t au8FinalProductPlant[FINAL_PRODUCT_B0X_PLANT_SIZE];             //Offset 32
  uint8_t u8FinalProductLine;                                             //Offset 36
  uint8_t au8FinalProductManufact[FINAL_PRODUCT_B0X_MANUFACT_SIZE];       //Offset 37
  uint8_t au8FinalProductDailyCounter[FINAL_PRODUCT_B0X_DAILY_COUNTER_SIZE];  //Offset 40
  uint8_t u8DeviationNumber;                                              //Offset 42
  uint8_t u8ValeoData2;                    //Empty Valeo Space            //Offset 43
  uint8_t au8OmnivisionData3[84];          //Reserved OVT data            //Offset 44
}tstrSensorMapOTP;
#endif


/* !Comment: Structure to represent OTP Memory for C0x sample (128 Bytes) */
typedef struct
{
  uint8_t au8OmnivisionData1[16];           //Reserved OVT data  //Offset 0
  uint8_t u8SerialNumberType;                                    //Offset 16
  uint8_t u8VcaftDay;                                            //Offset 17
  uint8_t au8OmnivisionData2[8];            //Reserved OVT data  //Offset 18
  uint8_t u8VcaftMonth;                                          //Offset 26
  uint8_t u8VcaftYear;                                           //Offset 27
  uint8_t au8VcasDateStamp[C0X_DATE_STAMP_SIZE];                 //Offset 28
  uint8_t au8VcasCounter[C0X_SERIAL_NUMBER_COUNTER_SIZE];        //Offset 31
  uint8_t au8ProductMajorMinorIndex[C0X_PRODUCT_MAJOR_MINOR_SIZE];  //Offset 34
  uint8_t u8Site;                                                //Offset 36
  uint8_t au8CamProductCode[C0X_CAM_PRODUCT_CODE_SIZE];          //Offset 37
  uint8_t au16ReleaseYearWeek[C0X_RELEASE_WEEK_YEAR_SIZE];       //Offset 42
  uint8_t au8OmnivisionData3[84];          //Reserved OVT data   //Offset 44
}tstrSensorMapOTP_C0X;

//Contains Sensor metadata struct, update the Macro NBR_DATA_STRUCT_SENSOR_METADATA if the var is added
#if 0
typedef struct
{
    uint8_t au8Unused1[5];
    uint8_t u8TempInteger;
    uint8_t au8Unused2[5];
    uint8_t u8TempDecimal;
    uint8_t au8Unused3[5];
    uint8_t u8FrameCounter31_24;
    uint8_t au8Unused4[5];
    uint8_t u8FrameCounter23_16;
    uint8_t au8Unused5[5];
    uint8_t u8FrameCounter15_8;
    uint8_t au8Unused6[5];
    uint8_t u8FrameCounter7_0;
    uint8_t au8Unused7[5];
    uint8_t u8CoarseExposureHigh;
    uint8_t au8Unused8[5];
    uint8_t u8CoarseExposureLow;
    uint8_t au8Unused9[5];
    uint8_t u8FineExposureHigh;
    uint8_t au8Unused10[5];
    uint8_t u8FineExposureLow;
    uint8_t au8Unused11[5];
    uint8_t u8CoarseGain;
    uint8_t au8Unused12[5];
    uint8_t u8FineGain;
    uint8_t au8Unused13[5];
    uint8_t u8Authentification;
} tstrSensorMapMetadata;
#endif



//}} //namespace

#endif /* IMAGESENSOR_OV928x_HPP */



