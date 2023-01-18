#ifndef MAIN_VIEW_HPP
#define MAIN_VIEW_HPP

#include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <gui/containers/DacContainer.hpp>
 
class MainView : public MainViewBase
{
public:
	MainView(); 
	virtual ~MainView() {} 
	virtual void rdbXLRInputsSelected();
	virtual void rdbUSBInputsSelected();
	virtual void rdbHDMIInputsSelected();
	virtual void rdbRCAInputsSelected();
	virtual void rdbBNCInputsSelected();
	//Volume
	virtual void chbxMuteChanged();
	virtual void sldrVolumeValueChanged(int value);

	virtual void handleTickEvent();

	void RefreshUI();
	time_t RequestCurrentTime();

	void Refresh24Lock();
	void Refresh245Lock();
	void Refresh22Lock();
	void RefreshIntExt();

	void SetDSDPCM(int p_AudiFormat);
	void SetFreq(int p_AudiFormat);
	void SetInput(int p_DacRoute);

	void SetTemp(int p_Temp);
	void PaintDot(colortype p_Dot1, colortype p_Dot2, colortype p_Dot3);

	colortype GetOutputPressColor(bool p_State);
	colortype GetOutputReleaseColor(bool p_State);
	colortype GetLockColor(bool p_State);
	bool ToBinary(int number, int p_Position);
	void CopyBit(int input, int* output, int CopyFrom, int CopyTo);
	void SetBit(uint8_t* input, bool bit, int SetTo);
	
	void RefreshSRCInfo(uint8_t p_AudioFormat);
	void ShowDacConfigs(uint8_t p_Mode);


#ifdef SIMULATOR
	 
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

  /*** DAC ***/
  uint8_t GuiItfGetDACActualMode();
  uint8_t GuiItfGetDACActualRoute();
  void GuiItfSetDACActualRoute(uint8_t p_Route);

  void GuiItfSetVolume(uint8_t p_Volume);
  uint8_t GuiItfGetVolume();

  void GuiItfSetMute(uint8_t p_Mute);
  uint8_t GuiItfGetMute();

  uint8_t(*GuiItfGetDacFilters())[DAC_SETTINGS_SIZE_COLS];
  
  /*** SRC ***/
  uint8_t GuiItfGetSRCEnabled();
  uint8_t GuiItfGetSRCFreq();
  uint8_t GuiItfGetSRCBit();

#endif

protected:
private:
	uint8_t count;
};

#endif // MAIN_VIEW_HPP
