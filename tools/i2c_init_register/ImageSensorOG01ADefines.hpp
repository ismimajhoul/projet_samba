/** ************************************************************************************************
 * COMPANY : VALEO
 *
 * PROJECT  : DMSVisionsubSystem
 ***************************************************************************************************
 * \file    ImageSensorOG01ADefines.hpp
 *
 * \Module  DMSCameraSystem
 * \brief   Sensor OG01A parmeters definitions
 *
 * \author  Ivan Arevalo
 * \date    10/02/2021
 *
 * !COPYRIGHT VALEO
 * All rights reserved
 **************************************************************************************************/
#ifndef IMAGESENSOR_OG01A_Defines_HPP
#define IMAGESENSOR_OG01A_Defines_HPP

// define Sleep macro for both linux andd windows platforms
#ifdef _WIN32 /* WINDOWS PLATFORM */
   #define SLEEP(ms) Sleep(ms)
#elif defined (__linux__) || defined(__ghs__) /* POSIX PLATFORM */
   #define SLEEP(ms) usleep(ms * 1000)
#else /* Unsupported platform */

#error sleep macro not defined for this platform

#endif

//! \brief Sensor version part one
#define SENSOR_VERSION_1                            0x0000004F

//! \brief Sensor version part two
#define SENSOR_VERSION_2                            0x47303141

//! \brief MPX Camera OG01A Driver specific frame width
#define MPXCAM_OG01A_FRAME_WIDTH                   1280

//! \brief MPX Camera OG01A Driver specific frame height
#define MPXCAM_OG01A_IMAGE_HEIGHT                  1024

//! \brief MPX Camera OG01A Driver specific frame height
#define MPXCAM_OG01A_FRAME_HEIGHT                  1025U // TODO veryfy this

//! \brief Value set on dummy register when Illumination ON
#define SET_DUMMY_REG_ILLUMINATION                 0x00

//! \brief Value set on dummy register when Illumination OFF
#define SET_DUMMY_REG_NO_ILLUMINATION              0xFF

//! \brief Metadata of the sensor in byte

#define MPXCAM_OG01A_u32ESENSOR_ILLUMINATION       (SET_DUMMY_REG_ILLUMINATION >> 2)

//! \brief Metadata of the sensor in byte
#define MPXCAM_OG01A_u32ESENSOR_NO_ILLUMINATION    (SET_DUMMY_REG_NO_ILLUMINATION >> 2)

//! \brief Dummy register carrying ABAB info
#define DUMMY_REG_ABAB                             0x5610


//! \brief Default Exposure Time of the sensor
#define MPXCAM_OG01A_u32ESENSOR_DEFAULT_EXPOTIME_RGB    0x0090
#define MPXCAM_OG01A_u32ESENSOR_DEFAULT_EXPOTIME_IR     0x0010
//! \brief Default Gain of the sensor
#define MPXCAM_OG01A_u32ESENSOR_DEFAULT_GAIN_RGB    0x01
#define MPXCAM_OG01A_u32ESENSOR_DEFAULT_GAIN_IR     0x01


//! \brief Minimum Expoure time
#define MINIMUM_EXPO_TIME                             1.0f
//! \brief Maximum expoure time
//! \brief MAXIMUM_EXPO_TIME_RGB = 15.5ms , to make sure it's < (1/fps)
#define MAXIMUM_EXPO_TIME_RGB                         1500.0f
//! \brief Maximum expoure time
//! \brief MAXIMUM_EXPO_TIME_IR = Maximum limit set for the Illumination(3927,3928): 2.3ms.
#define MAXIMUM_EXPO_TIME_IR                          230.0f
//! \brief Minimum gain
#define MINIMUM_GAIN                                  1.0f
//! \brief Maximum gain
//! \brief it can be set to 0F but then its insert more distortion in an image so after testing
//! the maximum value is set  to 8
#define MAXIMUM_GAIN                                  8.0f


//! \brief MPX Camera OG01A Driver specific frame size
#define MPXCAM_OG01A_FRAME_SIZE                    MPXCAM_OG01A_FRAME_WIDTH * MPXCAM_OG01A_FRAME_HEIGHT

//! \brief MPX Camera OG01A Driver specific frame color depth
#define MPXCAM_OG01A_FRAME_COLOR_DEPTH             8U

//! \brief MPX Camera OG01A Byte Per Pixel
#define MPXCAM_OG01A_FRAME_BytePerPixel             1U

//! \brief MPX Camera OG01A default frame rate
#define MPXCAM_OG01A_u8DEFAULT_FRAMERATE           60

//! \brief Metadata of the sensor in byte
#define MPXCAM_OG01A_u32ESENSOR_METADATA           MPXCAM_OG01A_FRAME_WIDTH //(In Byte) one line TODO verify this

//! \Valeo Metadata lines before the image
#define VALEO_METADATA_LINES                        10

//! \Sensor Vertical flip value
#define SENSOR_VERT_FLIP                           0x04

//! \ Sensor Horizontal Mirror value
#define SENSOR_HORIZ_MIRROR                        0x04

//! \Sensor Start stream value
#define SENSOR_START_STREAM                        0x01

#define SENSOR_STOP_STREAM                         0x00

//! \Sensor configuration failure re-try count
#define SENSOR_CONF_FAILED_RETRY_COUNT             3

//! \Sensor Pixel Clock
#define PIXCLOCK                                   100000000

//! \Sensor chip ID MSB register
#define CHIP_ID_HIGH                               0x47
//! \Sensor chip ID LSB register
#define CHIP_ID_LOW                                0x01
//! \brief Camera sensor OV9284 i2c slave address
#define CAMERA_OG01A_I2C_SLAVE_ADDRESS             0x60U

//! \brief Camera sensor OG01A chip revision number
#define SENSOR_REVISION_ID                         0x300CU

//! \brief Camera sensor OG01A chip revision number
#define SENSOR_CHIP_ID_HIGH                        0x300AU

//! \brief Camera sensor OG01A chip ID number
#define SENSOR_CHIP_ID_LOW                         0x300BU

//! \brief Camera sensor Exposure time[15:8]
#define SENSOR_EXPOSURE_TIME_2                     0x3501U

//! \brief Camera sensor Exposure time[7:0]
#define SENSOR_EXPOSURE_TIME_1                     0x3502U

//! \brief Camera sensor Timing Format 1
#define SENSOR_TIMING_FORMAT_1                     0x3820U

//! \brief Camera sensor Timing Format 2
#define SENSOR_TIMING_FORMAT_2                     0x3821U

//! \brief Camera sensor Fine Exposure time[15:8]
#define SENSOR_EXPOSURE_FINE_2                     0x3506U

//! \brief Camera sensor Fine Exposure time[7:0]
#define SENSOR_EXPOSURE_FINE_1                     0x3507U

//! \brief Sensor Mode Select Register
#define SC_MODE_SELECT                             0x0100U

//! \brief Sensor Group Access
#define SENSOR_GROUP_ACCESS                       0x3208U

//! \brief Sensor Gain Coarse
#define SENSOR_GAIN_COARSE                        0x3508U

//! \brief Sensor Gain Fine
#define SENSOR_GAIN_FINE                          0x3509U

//! \brief Sensor Digigain Fine: hacked to store illumination instead
#define SENSOR_DIGIGAIN_FINE                      0x350CU

//! \brief Sensor Sc Ctrl 06
#define SENSOR_SC_CTRL_06                         0x3006

//! \brief Sensor Pwm Ctrl 20
#define SENSOR_PWM_CTRL_20                        0x3920U

//! \brief Sensor Pwm Ctrl 27
#define SENSOR_PWM_CTRL_27                        0x3927U

//! \brief Sensor Pwm Ctrl 28
#define SENSOR_PWM_CTRL_28                        0x3928U

//! \brief Sensor Pwm Ctrl 29
#define SENSOR_PWM_CTRL_29                        0x3929U

//! \brief Sensor Strobe Ctrl 2D
#define STROBE_CTRL_2D                            0x392DU

//! \brief Sensor Strobe Ctrl 2E
#define STROBE_CTRL_2E                            0x392EU

//! \brief Sensor Total Vertical Timing Size High Byte
#define TIMMING_VTS_HIGH_BYTE                      0x380EU

//! \brief Sensor Total Vertical Timing Size Low Byte
#define TIMMING_VTS_LOW_BYTE                       0x380FU

//! \brief Sensor Total Horizontal Timing Size High Byte
#define TIMMING_HTS_HIGH_BYTE                      0x380CU

//! \brief Sensor Total Horizontal Timing Size Low Byte
#define TIMMING_HTS_LOW_BYTE                       0x380DU

//! \brief Sensor system Clock
#define SENSOR_SYS_CLOCK_MHZ                       120U

//! \brief Sensor Strobe duration msb
#define STROBE_DURATION_MSB                        0x00U

//! \brief Select Pin on sensor for strobe
#define STROBE_PIN                                 0x08U

//! \brief Select Pin on sensor for strobe
#define GAIN_CONST_IR                              0x03U

//! \brief Target Board ISI channel used
#define BOARD_ISI_CHANNEL                          0

//! \brief Target Board CSI channel used
#define BOARD_CSI_CHANNEL                          0

//! \brief Target Board CSI mode used
#define BOARD_CSI_MODE                             1

//! \brief TOTAL PIXEL PER LINE
#define TIMING_HTS                                 1808

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

#define REG_POWER_SAVE_MODE                        0x3017U
#define ENABLE_POWER_SAVE_MODE                     0xF0U
#define DISABLE_POWER_SAVE_MODE                    0xF2U

#define SC_GP_IO_IN2                               ((uint16_t)0x302A)
#define D0_BIT                                     (7)
#define READ_D0_BIT(byte)                          ((uint8_t)(((byte) >> D0_BIT) & (0x01)))
#define DIM(a)                                     (sizeof(a)/sizeof((a)[0]))

// Put enums and structures in the block below if necessary
//namespace valeo
//{
//namespace camerasystem
//{
#if 0
typedef struct
{
    uint8_t u8Seq15;             // This byte should be "0x15"
    uint8_t u8Byte2;             // Not used
    uint8_t u8Seq04;             // This byte should be "0x04"
    uint8_t u8Byte4;             // Not used
    uint8_t u8Illumination;      // R5610<<2
} tstrSensorMapMetadata;
#endif

#if 0
/* !Comment: Structure to represent OTP Memory (128 Bytes) */
typedef struct
{
  uint8_t au8OmnivisionData1[16];
  uint8_t au8ValeoData1[2];
  uint8_t au8OmnivisionData2[8];
  uint8_t au8ValeoData2[18];
  uint8_t au8OmnivisionData3[84];
}tstrSensorMapOTP;
#endif

//}} //namespace

#endif /* IMAGESENSOR_OG01A_HPP */

