/*//
 * GuiItf.h
 *
 *  Created on: 2023. feb. 02.
 *      Author: Margit Robert
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _GUIITF_H_
#define _GUIITF_H_

#include <time.h>

typedef enum _Route
{
  ROUTE_NONE_DAC = 0,
  ROUTE_MUTE_DAC,
  ROUTE_USB_DAC,
  ROUTE_USB_SRC_DAC,
  ROUTE_HDMI_DAC,
  ROUTE_HDMI_SRC_DAC,
  ROUTE_BNC_DAC,
  ROUTE_BNC_SRC_DAC,
  ROUTE_RCA_DAC,
  ROUTE_RCA_SRC_DAC,
  ROUTE_XLR_DAC,
  ROUTE_XLR_SRC_DAC
}Route_t;

enum DacConfig
{
  DAC_PCM_32_0KHZ = 0,
  DAC_PCM_44_1KHZ,
  DAC_PCM_48_0KHZ,
  DAC_PCM_88_2KHZ,
  DAC_PCM_96_0KHZ,
  DAC_PCM_176_4KHZ,
  DAC_PCM_192_KHZ,
  DAC_PCM_362_8KHZ,
  DAC_PCM_384_0KHZ,
  DAC_PCM_705_6KHZ,
  DAC_PCM_768_0KHZ,
  DAC_DSD_64,
  DAC_DSD_128,
  DAC_DSD_256,
  DAC_DSD_512
};

#define GUIITF_OK             0x00
#define GUIITF_FAIL           0x01
#define GUIITF_OUT_OF_RANGE   0x02



#define DENPO_DAC_DI_A0             ((uint32_t)1<<0)
#define DENPO_DAC_DI_A1             ((uint32_t)1<<1)
#define DENPO_DAC_DI_A2             ((uint32_t)1<<2)
#define DENPO_DAC_DI_A3             ((uint32_t)1<<3)
#define DENPO_DAC_DI_UNUSED1        ((uint32_t)1<<4)
#define DENPO_DAC_DI_UNUSED2        ((uint32_t)1<<5)
#define DENPO_DAC_DI_UNUSED3        ((uint32_t)1<<6)
#define DENPO_DAC_DI_UNUSED4        ((uint32_t)1<<7)
#define DENPO_DAC_DI_UNUSED5        ((uint32_t)1<<8)
#define DENPO_DAC_DI_UNUSED6        ((uint32_t)1<<9)
#define DENPO_DAC_DI_UNUSED7        ((uint32_t)1<<10)
#define DENPO_DAC_DI_UNUSED8        ((uint32_t)1<<11)
#define DENPO_DAC_DI_UNUSED9        ((uint32_t)1<<12)


/* Exported functions prototypes ---------------------------------------------*/
/* GUI -----------------------------------------------------------------------*/
uint8_t GuiItfLoad(void);
uint8_t GuiItfSetDefault(void);
uint8_t GuiItfGetVersion(char **fw, char **uid, char **pcb);
uint32_t GuiItfGetBootupCnt(void);
uint32_t GuiItfUpTimSec(void);
void GuiItfFacotryReset(void);
void GuiItfSoftReset(void);
uint32_t GuiItfGetBusUartErrorCnt(void);
float GuiItfGetTempCh0(void);
float GuiItfGetTempCh1(void);
float GuiItfGetTempCh2(void);
float GuiItfGetTempCh3(void);
void GuiItfSetDo0(uint8_t onoff);
void GuiItfSetDo1(uint8_t onoff);
void GuiItfSetDo2(uint8_t onoff);
void GuiItfSetDo3(uint8_t onoff);
void GuiItfSetDo4(uint8_t onoff);
void GuiItfSetDo5(uint8_t onoff);
void GuiItfSetDo6(uint8_t onoff);
void GuiItfSetDo7(uint8_t onoff);
uint8_t GuiItfGetDo0(void);
uint8_t GuiItfGetDo1(void);
uint8_t GuiItfGetDo2(void);
uint8_t GuiItfGetDo3(void);
uint8_t GuiItfGetDo4(void);
uint8_t GuiItfGetDo5(void);
uint8_t GuiItfGetDo6(void);
uint8_t GuiItfGetDo7(void);
uint8_t GuiItfGetDi0(void);
uint8_t GuiItfGetDi1(void);
uint8_t GuiItfGetDi2(void);
uint8_t GuiItfGetDi3(void);
uint8_t GuiItfGetDi4(void);
uint8_t GuiItfGetDi5(void);
uint8_t GuiItfGetDi6(void);
uint8_t GuiItfGetDi7(void);
uint8_t GuiItfGetDi8(void);
uint8_t GuiItfGetDi9(void);
uint8_t GuiItfGetDi10(void);
uint8_t GuiItfGetDi11(void);
uint8_t GuiItfGetDi12(void);
uint8_t GuiItfGetDi13(void);
uint8_t GuiItfGetDi14(void);
uint8_t GuiItfGetDi15(void);

/* Backlight -----------------------------------------------------------------*/
uint8_t GuiItfSetBacklight(uint8_t percent);
uint8_t GuiItfGetBacklight(void);
void GuiItfSetBacklightEn(uint8_t onoff);
void GuiItfSetBackLightAutoOff(uint32_t sec);
uint32_t GuiItfGetBacklightAutoOff(void);
uint32_t GuiItfGetRemainingTimeToOff(void);
uint8_t GuiItfGetBacklightIsEnabled(void);
uint32_t GuiItfGetClockHeatedTemperature();
void GuiItfSetClockHeatedTemperature(uint32_t temp);

/* RTC -----------------------------------------------------------------------*/
void GuiItfSetRtc(time_t dt);
void GuiItfGetRtc(time_t *dt);
/* Log -----------------------------------------------------------------------*/
uint32_t GuiItfLogGetLastAddress(void);
void GuitItfLogGetLine(uint32_t address, char *line, uint32_t size);
void GuiItfLogIncPage(void);

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/







#endif /* _GUIITF_H_ */
