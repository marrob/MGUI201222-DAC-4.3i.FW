#ifndef DACCONTAINER_HPP
#define DACCONTAINER_HPP

#include <gui_generated/containers/DacContainerBase.hpp>

#define DAC_SETTINGS_SIZE_COLS	8 //DoDo: ezt valahol GuiItf.h-ban kell deklarálni mert a c fájlbol ennek az értékét nem érem el...
#define DAC_SETTINSG_ITEMS_ROWS	15 //DoDo: ezt valahol egy GuiItf.h-ban kell deklarálni mert a c fájlbol ennek az értékét nem érem el...

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

enum DacRoute
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
};

enum DacConfigBytes {

	Clock2,
	AudioIF3,
	DSDFilter,
	FIR1,
	FIR2,
	DeEmp1,
	DeEmp2,
	DeltaSigma
};


enum SRCFreq
{
	SRCF_Low = 0,
	SRCF_Mid,
	SRCF_High,
};

enum SRCBit
{
	SRC_Bit_16 = 0,
	SRC_Bit_24,
};
 
class DacContainer : public DacContainerBase
{
public:
	DacContainer();
	virtual ~DacContainer() {}

	virtual void initialize();

	virtual void btnUserProfileClicked();
	virtual void btnFactoryProfileClicked();

	void SetDacConfig(uint8_t DacMode, uint8_t DacConfig, uint8_t Settings);
	void SetDacConfigWithMask(uint8_t DacMode, uint8_t DacConfig, uint8_t Settings, uint8_t Mask);
	uint8_t GetDacConfig(uint8_t DacMode, uint8_t DacConfigEnum);

	virtual void OnDSDCutOffValueChanged(uint32_t value);
	virtual void OnFirValueChanged(uint32_t value);	
	virtual void OnDeEmpValueChanged(uint32_t value);
	virtual void OnDeltaSigmaValueChanged(uint32_t value);

	virtual void chbxSwapChanged();
	virtual void chbxPhaseChanged();
	virtual void chbxHighPrecChanged();
	virtual void chbxMuteChanged();
	virtual void sldrVolumeValueChanged(int value);

	virtual void chbxEnableSRCChecked();
	virtual void rdbSRCFreqLowSelected();
	virtual void rdbSRCFreqMidSelected();
	virtual void rdbSRCFreqHighSelected();
	virtual void rdbSRCBit16Selected();
	virtual void rdbSRCBit24Selected();

	void ShowDacConfigs();


#ifdef SIMULATOR


	 
	static uint8_t DacConfigArray[15][8];

	static uint8_t simVolume;
	static uint8_t simSRCEn;
	static uint8_t simSRCFreq;
	static uint8_t simSrcBit;
	static uint8_t simMute;
	static uint8_t simDACRoute;


	void GuiItfSetVolume(uint8_t p_Volume);
	uint8_t  GuiItfGetVolume();

	void GuiItfSetMute(uint8_t p_Mute);
	uint8_t GuiItfGetMute();

	void GuiItfSaveDacFilters();
	uint8_t(*GuiItfGetDacFilters())[DAC_SETTINGS_SIZE_COLS];

	void GuiItfSetSRCEnabled(uint8_t p_Enabled);
	uint8_t GuiItfGetSRCEnabled();

	void GuiItfSetSRCFreq(uint8_t p_Freq);
	uint8_t GuiItfGetSRCFreq();

	void GuiItfSetSRCBit(uint8_t p_Bit);
	uint8_t GuiItfGetSRCBit();

	uint8_t GuiItfGetDACActualRoute();
	void GuiItfSetDACActualRoute(uint8_t p_Route);	 

#endif
	
protected:
};

#endif // DACCONTAINER_HPP
