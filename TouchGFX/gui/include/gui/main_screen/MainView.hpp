#ifndef MAIN_VIEW_HPP
#define MAIN_VIEW_HPP

#include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/main_screen/MainPresenter.hpp>

class MainView : public MainViewBase
{
public:
	MainView(); 
	virtual ~MainView() {} 
	virtual void ToggleHDMI();
	virtual void ToggleRCA();
	virtual void ToggleBNC();
	virtual void ToggleXLR();

	virtual void handleTickEvent();

	void RefreshKarunaAndClockInfo();
	time_t RequestCurrentTime();

	void RefreshBNCOutput();
	void RefreshRCAOutput();
	void RefreshHDMIOutput();
	void RefreshXLROutput();

	void Refresh24Lock();
	void Refresh245Lock();
	void Refresh22Lock();
	void RefreshIntExt();

	void SetDSDPCM(int p_AudiFormat);
	void SetBitDepth(int p_AudiFormat);
	void SetFreq(int p_AudiFormat);

	void SetTemp(int p_Temp);
	void PaintDot(colortype p_Dot1, colortype p_Dot2, colortype p_Dot3);

	colortype GetOutputPressColor(bool p_State);
	colortype GetOutputReleaseColor(bool p_State);
	colortype GetLockColor(bool p_State);
	bool ToBinary(int number, int p_Position);
	void CopyBit(int input, int* output, int CopyFrom, int CopyTo);
	void SetBit(uint8_t* input, bool bit, int SetTo);


#ifdef SIMULATOR

  /*** Karuna ****/
  uint8_t GuiItfGetKarunaStatus();
  void GuiItfSetKarunaHdmi(uint8_t onfoff);
  uint8_t GuitIfGetKarunaIsHdmiSet(void);
  void GuiItfSetKarunaRca(uint8_t onfoff);
  uint8_t GuitIfGetKarunaIsRcaSet(void);
  void GuiItfSetKarunaBnc(uint8_t onfoff);
  uint8_t GuitIfGetKarunaIsBncSet(void);
  void GuiItfSetKarunaXlr(uint8_t onfoff);
  uint8_t GuitIfGetKarunaIsXlrSet(void);
  uint8_t GuiItfGetKarunaMclkOutIsEanbled(void);

  /*** Time ***/
  void GuiItfGetRtc(time_t* dt);

  /*** Display ***/
  uint8_t GuiItfGetScreenSaverEnable();

#ifdef KARUNA_7i
  /*** DAS Clock ***/
  float GuiItfGetDasClockMV341Temp();
  uint8_t GuiItfGetDasClockStatusLock1();
  uint8_t GuiItfGetDasClockStatusLock2();
  uint8_t GuiItfGetDasClockIsExt();
#endif 

#ifdef KARUNA_43i
  /*** Tri Clock ***/
  float GuiItfGetTempCh1(void);
  uint8_t GuiItfGetDi1(void);
  uint8_t GuiItfGetDi11(void);
  uint8_t GuiItfGetDi13(void);
  uint8_t GuiItfGetDi15(void);
#endif

  /*** Clock Temp ***/
  uint32_t GuiItfGetDasClockHeatedTemperature();
  void GuiItfSetDasClockHeatedTemperature(uint32_t temp);

#endif


protected:


private:
	uint8_t count;
};

#endif // MAIN_VIEW_HPP
