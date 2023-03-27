/*
 * GuiItf.c
 *
 *  Created on: 2022. máj. 14.
 *      Author: Margit Robert
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "Log.h"
#include "DisplayLight.h"
#include "GuiItf.h"
#include "EEPROM.h"


#define EEP_MAGICWORD_ADDR                  0x0000
#define EPP_BOOTUP_CNT_ADDR                 0x0004
#define EEP_BACKLIGHT_ADDR                  0x0008
#define EEP_SCREENSAVER_ENABLED_ADDR        0x000C
#define EEP_RTC_IS_SET_ADDR                 0x0010
#define EEP_LOG_LAST_PAGE_ADDR              0x0014
#define EEP_BACKLIGHT_OFFTIMER_ENABLED_ADDR 0x0018

#define EEP_DAC_ROUTE_ADDR                  0x001C
#define EEP_DAC_CLOCK_HEATED_TEMP_ADDR      0x0020
#define EEP_DAC_VOLUME_ADDR                 0x0024
#define EEP_DAC_SRC_ENABLED_ADDR            0x0028
#define EEP_DAC_SRC_FSOUT_ADDR              0x002C
#define EEP_DAC_SRC_BITS_ADDR               0x0030

#define MAGIC_WORD                          0x55AA5500


/* Private user code ---------------------------------------------------------*/

uint8_t GuiItfLoad(void)
{
  uint32_t value = 0;
  HAL_StatusTypeDef status = HAL_OK;
  status = EepromU32Read(EEP_MAGICWORD_ADDR, &value);

  //If EPPROM does not have Magic Word then it is the first Start...
  //We have to write default values and the Magic Word
  //The Magic Word different every devcie eg Kaurna, DAC etc
  if(status!= HAL_OK || value != MAGIC_WORD)
  {
    GuiItfSetDefault();
  }
  else
  {
    /*** Boot Up counter ***/
    EepromU32Read(EPP_BOOTUP_CNT_ADDR, &value);
    Device.Gui.BootUpCnt = value;
    Device.Gui.BootUpCnt++;
    EepromU32Write(EPP_BOOTUP_CNT_ADDR, Device.Gui.BootUpCnt);

    /*** Backlight ***/
    EepromU32Read(EEP_BACKLIGHT_ADDR, &value);
    BacklightSet(value);

    EepromU32Read(EEP_BACKLIGHT_OFFTIMER_ENABLED_ADDR, &value);
    Device.Backlight.OffTimerSec = value;

    /*** Screen Saver ***/
    EepromU32Read(EEP_SCREENSAVER_ENABLED_ADDR, &value);
    Device.Gui.ScreenSaverIsEnabled = value;

    /*** Log ***/
    EepromU32Read(EEP_LOG_LAST_PAGE_ADDR, &value);
    Device.Log.LastAddress = value;

    /*** Route ***/
    EepromU32Read(EEP_DAC_ROUTE_ADDR, &value);
    Device.DenpoDAC.Route = value;

    /*** HeatedTemp ***/
    EepromU32Read(EEP_DAC_CLOCK_HEATED_TEMP_ADDR, &value);
    Device.DenpoDAC.HeatedTemp = value;

    /*** Volume ***/
    EepromU32Read(EEP_DAC_VOLUME_ADDR, &value);
    Device.DenpoDAC.Volume = value;

    /*** SRC Enabled ***/
    EepromU32Read(EEP_DAC_SRC_ENABLED_ADDR, &value);
    Device.DenpoDAC.SRCEnabled = value;

    /*** SRC FSOUT ***/
    EepromU32Read(EEP_DAC_SRC_FSOUT_ADDR, &value);
    Device.DenpoDAC.SRCFsout = value;

    /*** SRC Bits ***/
    EepromU32Read(EEP_DAC_SRC_BITS_ADDR, &value);
    Device.DenpoDAC.SRCBits = value;

  }
  return GUIITF_OK;
}


uint8_t GuiItfSetDefault(void)
{
  uint32_t value = 0;

  /*** Boot Up counter ***/
  value = 0;
  EepromU32Write(EPP_BOOTUP_CNT_ADDR, value);
  Device.Gui.BootUpCnt = value;

  /*** Backlight ***/
  value = 50;
  EepromU32Write(EEP_BACKLIGHT_ADDR, value);
  BacklightSet((uint8_t)value);

  value = 0;
  EepromU32Write(EEP_BACKLIGHT_OFFTIMER_ENABLED_ADDR, value);
  Device.Backlight.OffTimerSec = value;

  /*** RTC ***/
  value = 0x01;
  EepromU32Write(EEP_RTC_IS_SET_ADDR, value);
  //Factory Default: 01.06.2022 02:03
  struct tm tm_info;
  tm_info.tm_year = 2022 - 1900;
  tm_info.tm_mon = 6 - 1;
  tm_info.tm_mday = 1;
  tm_info.tm_hour = 2;
  tm_info.tm_min = 3;
  tm_info.tm_sec = 4;
  tm_info.tm_isdst = 0;
  DeviceRtcSet(mktime(&tm_info));

  /*** Log ***/
  value = 0;
  EepromU32Write(EEP_LOG_LAST_PAGE_ADDR, value);
  Device.Log.LastAddress = value;

  /*** Screen Saver ***/
  value = 0;
  EepromU32Write(EEP_SCREENSAVER_ENABLED_ADDR, value);
  Device.Gui.ScreenSaverIsEnabled = value;

  /*** Magic Word ***/
  value = MAGIC_WORD;
  EepromU32Write(EEP_MAGICWORD_ADDR, value);

  value = 0;
  EepromU32Read(EEP_MAGICWORD_ADDR, &value);

  /*** Route ***/
  value = ROUTE_MUTE_DAC;
  EepromU32Write(EEP_DAC_ROUTE_ADDR, value);
  Device.DenpoDAC.Route = value;

  /*** HeatedTemp ***/
  value = 55;
  EepromU32Write(EEP_DAC_CLOCK_HEATED_TEMP_ADDR, value);
  Device.DenpoDAC.HeatedTemp = value;

  /*** Volume ***/
  value = 0;
  EepromU32Write(EEP_DAC_VOLUME_ADDR, value);
  Device.DenpoDAC.Volume = value;

  /*** SRC Enabled ***/
  value = 0;
  EepromU32Write(EEP_DAC_SRC_ENABLED_ADDR, value);
  Device.DenpoDAC.SRCEnabled = value;

  /*** SRC FSOUT ***/
  value = 0;
  EepromU32Write(EEP_DAC_SRC_FSOUT_ADDR, value);
  Device.DenpoDAC.SRCFsout = value;

  /*** SRC Bits ***/
  value = 0;
  EepromU32Write(EEP_DAC_SRC_BITS_ADDR, value);
  Device.DenpoDAC.SRCBits = value;

  LogFlashErase(); //Here we have to wait for a long time....

  return GUIITF_OK;
}

/* GUI -----------------------------------------------------------------------*/
/*
 * fw:  220510_2157               size: DEVICE_FW_SIZE
 * uid: 66DFF323530505243052936   size: DEVICE_UID_SIZE
 * pcb: V00                       size: DEVICE_PCB_SIZE
 */
uint8_t GuiItfGetVersion(char **fw, char **uid, char **pcb)
{
  *fw = Device.Gui.FW;
  *uid = Device.Gui.UID;
  *pcb = Device.Gui.PCB;
  return GUIITF_OK;
}

uint32_t GuiItfGetBootupCnt(void)
{
  return Device.Gui.BootUpCnt;
}

uint32_t GuiItfUpTimSec(void)
{
  return Device.Gui.UpTimeSec;
}

void GuiItfSoftReset(void)
{
  NVIC_SystemReset();
}

void GuiItfFacotryReset(void)
{
  GuiItfSetDefault();
  NVIC_SystemReset();
}

uint32_t GuiItfGetBusUartErrorCnt(void)
{
  return Device.Diag.RS485UartErrorCnt;
}

void GuiItfSetScreenSaverEnable(uint8_t onoff)
{
  Device.Gui.ScreenSaverIsEnabled = onoff;

  EepromU32Write(EEP_SCREENSAVER_ENABLED_ADDR, Device.Gui.ScreenSaverIsEnabled);

  if(onoff)
    LogWriteLine("GuiItfSetScreenSaverEnable: On");
  else
    LogWriteLine("GuiItfSetScreenSaverEnable: Off");
}

uint8_t GuiItfGetScreenSaverEnable(void)
{
  return Device.Gui.ScreenSaverIsEnabled;
}

float GuiItfGetTempCh0(void)
{
  return Device.Gui.Temps[AI_CH0];
}

float GuiItfGetTempCh1(void)
{
  return Device.Gui.Temps[AI_CH1];
}

float GuiItfGetTempCh2(void)
{
  return Device.Gui.Temps[AI_CH2];
}

float GuiItfGetTempCh3(void)
{
  return Device.Gui.Temps[AI_CH3];
}

void GuiItfSetDo0(uint8_t onoff)
{
  if(onoff)
    Device.Gui.DO |= DO_0;
  else
    Device.Gui.DO &= ~DO_0;
}

void GuiItfSetDo1(uint8_t onoff)
{
  if(onoff)
    Device.Gui.DO |= DO_1;
  else
    Device.Gui.DO &= ~DO_1;
}

void GuiItfSetDo2(uint8_t onoff)
{
  if(onoff)
    Device.Gui.DO |= DO_2;
  else
    Device.Gui.DO &= ~DO_2;
}

void GuiItfSetDo3(uint8_t onoff)
{
  if(onoff)
    Device.Gui.DO |= DO_3;
  else
    Device.Gui.DO &= ~DO_3;
}

void GuiItfSetDo4(uint8_t onoff)
{
  if(onoff)
    Device.Gui.DO |= DO_4;
  else
    Device.Gui.DO &= ~DO_4;
}

void GuiItfSetDo5(uint8_t onoff)
{
  if(onoff)
    Device.Gui.DO |= DO_5;
  else
    Device.Gui.DO &= ~DO_5;
}

void GuiItfSetDo6(uint8_t onoff)
{
  if(onoff)
    Device.Gui.DO |= DO_6;
  else
    Device.Gui.DO &= ~DO_6;
}

void GuiItfSetDo7(uint8_t onoff)
{
  if(onoff)
    Device.Gui.DO |= DO_7;
  else
    Device.Gui.DO &= ~DO_7;
}

uint8_t GuiItfGetDo0(void)
{
  return (Device.Gui.DO & DO_0) == DO_0;
}

uint8_t GuiItfGetDo1(void)
{
  return (Device.Gui.DO & DO_1) == DO_1;
}

uint8_t GuiItfGetDo2(void)
{
  return (Device.Gui.DO & DO_2) == DO_2;
}

uint8_t GuiItfGetDo3(void)
{
  return (Device.Gui.DO & DO_3) == DO_3;
}

uint8_t GuiItfGetDo4(void)
{
  return (Device.Gui.DO & DO_4) == DO_4;
}

uint8_t GuiItfGetDo5(void)
{
  return (Device.Gui.DO & DO_5) == DO_5;
}

uint8_t GuiItfGetDo6(void)
{
  return (Device.Gui.DO & DO_6) == DO_6;
}

uint8_t GuiItfGetDo7(void)
{
  return (Device.Gui.DO & DO_7) == DO_7;
}

uint8_t GuiItfGetDi0(void)
{
  return (Device.Gui.DI & DI_0) == DI_0;
}

uint8_t GuiItfGetDi1(void)
{
  return (Device.Gui.DI & DI_1) == DI_1;
}

uint8_t GuiItfGetDi2(void)
{
  return (Device.Gui.DI & DI_2) == DI_2;
}

uint8_t GuiItfGetDi3(void)
{
  return (Device.Gui.DI & DI_3) == DI_3;
}

uint8_t GuiItfGetDi4(void)
{
  return (Device.Gui.DI & DI_4) == DI_4;
}

uint8_t GuiItfGetDi5(void)
{
  return (Device.Gui.DI & DI_5) == DI_5;
}

uint8_t GuiItfGetDi6(void)
{
  return (Device.Gui.DI & DI_6) == DI_6;
}

uint8_t GuiItfGetDi7(void)
{
  return (Device.Gui.DI & DI_7) == DI_7;
}

uint8_t GuiItfGetDi8(void)
{
  return (Device.Gui.DI & DI_8) == DI_8;
}

uint8_t GuiItfGetDi9(void)
{
  return (Device.Gui.DI & DI_9) == DI_9;
}

uint8_t GuiItfGetDi10(void)
{
  return (Device.Gui.DI & DI_10) == DI_10;
}

uint8_t GuiItfGetDi11(void)
{
  return (Device.Gui.DI & DI_11) == DI_11;
}

uint8_t GuiItfGetDi12(void)
{
  return (Device.Gui.DI & DI_12) == DI_12;
}

uint8_t GuiItfGetDi13(void)
{
  return (Device.Gui.DI & DI_13) == DI_13;
}

uint8_t GuiItfGetDi14(void)
{
  return (Device.Gui.DI & DI_14) == DI_14;
}

uint8_t GuiItfGetDi15(void)
{
  return (Device.Gui.DI & DI_15) == DI_15;
}


/* Backlight -----------------------------------------------------------------*/
uint8_t GuiItfSetBacklight(uint8_t percent)
{
  if(percent > 100)
    return GUIITF_OUT_OF_RANGE;
  BacklightSet(percent);
  EepromU32Write(EEP_BACKLIGHT_ADDR, percent);
  return GUIITF_OK;
}

uint8_t GuiItfGetBacklight(void)
{
  return BacklightGet();
}

void GuiItfSetBacklightEn(uint8_t onoff)
{
  BacklightEn(onoff);
}

/*
 * 0  -> Off
 * 60 -> 1min
 */
void GuiItfSetBackLightAutoOff(uint32_t sec)
{
  Device.Backlight.OffTimerSec = sec;
  EepromU32Write(EEP_BACKLIGHT_OFFTIMER_ENABLED_ADDR, sec);
  if(sec!= 0)
    DeviceBacklightOffTimerReset();
}

uint32_t GuiItfGetBacklightAutoOff(void)
{
  return Device.Backlight.OffTimerSec;
}

uint32_t GuiItfGetRemainingTimeToOff(void)
{
  return Device.Backlight.RemainingTimeToOff;
}

/* RTC -----------------------------------------------------------------------*/
/*
 * Example Set RTC:
 * struct tm tm_info;
 * tm_info.tm_year = 2022 - 1900; // 2022
 * tm_info.tm_mon = 6 - 1; //Juni
 * tm_info.tm_mday = 1;
 * tm_info.tm_hour = 2;
 * tm_info.tm_min = 3;
 * tm_info.tm_sec = 4;
 * tm_info.tm_isdst = 0;
 *
 * DeviceRtcSet(mktime(&tm_info));
 */
void GuiItfSetRtc(time_t dt)
{
  DeviceRtcSet(dt);
  LogWriteLine("GuiItfSetRtc.......");
}

/*
 * Example Get RTC:
 * time_t dt;
 * GuiItfGetRtc(&dt);
 * struct tm *tm_info = gmtime(&dt);
 *
 * uint16_t year = tm_info->tm_year + 1900;
 * uint8_t mon = tm_info->tm_mon + 1;
 * uint8_t day = tm_info->tm_mday;
 *
 * uint8_t hour = tm_info->tm_hour;
 * uint8_t min = tm_info->tm_min;
 * uint8_t sec = tm_info->tm_sec;
 */
void GuiItfGetRtc(time_t *dt)
{
  *dt = Device.DateTime.PosixTime;
}

/* Log -----------------------------------------------------------------------*/
/* A log egy sorát 0 és GuiItfLogGetLastAddress() között lehet lekérni
 * GuitItfLogGetLine() segitségével..,.
 *
 *
 * *** Example - Read Log ***
 * char buf[256];
 * for(uint32_t i = 0; i < GuiItfLogGetLastAddress(); i++)
 * {
 *  GuitItfLogGetLine(i, buf, sizeof(buf));
 *   printf( "%s\n", buf);
 * }
 *
 * *** Example 2 - Write to Log ***
 *
 * LogWriteLine("Hello, World!");
 *
 */
uint32_t GuiItfLogGetLastAddress(void)
{
  return Device.Log.LastAddress;
}

void GuitItfLogGetLine(uint32_t address, char *line, uint32_t size)
{
  LogFlashRead(address, (uint8_t*)line, size);
}

/*
 * Only for backend...
 */
void GuiItfLogIncPage(void)
{
  Device.Log.LastAddress++;
  if(Device.Log.LastAddress > LOG_FLASH_MAX_LINE)
    Device.Log.LastAddress = 0;
  EepromU32Write(EEP_LOG_LAST_PAGE_ADDR, Device.Log.LastAddress);
}

/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/*Filters --------------------------------------------------------------------*/
#define DAC_SETTINGS_SIZE_COLS  8
#define DAC_SETTINSG_ITEMS_ROWS 15

uint8_t(*GuiItfGetDacFilters())[DAC_SETTINGS_SIZE_COLS]
{
  return NULL;
}
void GuiItfSaveDacFilters(void){

}

/*Volume ---------------------------------------------------------------------*/
void GuiItfSetVolume(uint8_t value){
  Device.DenpoDAC.Volume = value;
  EepromU32Write(EEP_DAC_VOLUME_ADDR, Device.DenpoDAC.Volume);
}

uint8_t GuiItfGetVolume(void){
  return Device.DenpoDAC.StatusOfVolume;
}

/*SRC ------------------------------------------------------------------------*/
uint8_t GuiItfGetSRCEnable(void){
  return Device.DenpoDAC.SRCEnabled;
}

void GuiItfSetSRCEnable(uint8_t value){
  Device.DenpoDAC.SRCEnabled = value;
  EepromU32Write(EEP_DAC_SRC_ENABLED_ADDR, Device.DenpoDAC.SRCEnabled);
}

int GuiItfGetSRCFsout(void){
  return Device.DenpoDAC.StatusOfSRCFsout;
}

void GuiItfSetSRCFsout(uint8_t value){
  Device.DenpoDAC.SRCFsout = value;
  EepromU32Write(EEP_DAC_SRC_FSOUT_ADDR, Device.DenpoDAC.SRCFsout);
}

int GuiItfGetSRCBits(void){
  return Device.DenpoDAC.StatusOfSRCBits;
}

void GuiItfSetSRCBits(uint8_t value){
  Device.DenpoDAC.SRCBits = value;
  EepromU32Write(EEP_DAC_SRC_BITS_ADDR, Device.DenpoDAC.SRCBits);
}

/*Mute -----------------------------------------------------------------------*/
void GuiItfSetMute(int value){
  static Route_t lastRoute = ROUTE_MUTE_DAC;
  if(value != 0){
    lastRoute = Device.DenpoDAC.StatusOfRoute;
    Device.DenpoDAC.Route = ROUTE_MUTE_DAC;
  }
  else {
    if(lastRoute != ROUTE_MUTE_DAC)
      Device.DenpoDAC.Route = lastRoute;
  }
}

uint8_t GuiItfGetMute(void){
  return (ROUTE_MUTE_DAC == Device.DenpoDAC.StatusOfRoute);
}

/*Route ----------------------------------------------------------------------*/
uint8_t GuiItfGetRoute(void){
  return Device.DenpoDAC.StatusOfRoute;
}

void GuiItfSetRoute(int value){
  EepromU32Write(EEP_DAC_ROUTE_ADDR, value);
  Device.DenpoDAC.Route = value;
}

/*Route ----------------------------------------------------------------------*/
uint8_t GuiItfGetConfig(void){
  return Device.DenpoDAC.StatusOfConfig;
}

/*Heated Temperature ---------------------------------------------------------*/
uint32_t GuiItfGetClockHeatedTemperature(){
  return Device.DenpoDAC.HeatedTemp;
}

void GuiItfSetClockHeatedTemperature(uint32_t temp){
  Device.DenpoDAC.HeatedTemp = temp;
  EepromU32Write(EEP_DAC_CLOCK_HEATED_TEMP_ADDR, Device.DenpoDAC.HeatedTemp);
}

/*DAC Tools -------- ---------------------------------------------------------*/
/*
 * fw:  220510_2157               size: DEVICE_FW_SIZE
 * uid: 66DFF323530505243052936   size: DEVICE_UID_SIZE
 * pcb: V00                       size: DEVICE_PCB_SIZE
 */
uint8_t GuiItfGetDacVersion(char **fw, char **uid, char **pcb)
{
  *fw = Device.DenpoDAC.FW;
  *uid = Device.DenpoDAC.UID;
  *pcb = Device.DenpoDAC.PCB;
  return GUIITF_OK;
}

uint32_t GuiItfGetDacUpTimeSec()
{
  return Device.DenpoDAC.UpTimeSec;
}

uint32_t GuiItfGetDacBusErrorCnt()
{
  return Device.DenpoDAC.UartErrorCnt;
}
