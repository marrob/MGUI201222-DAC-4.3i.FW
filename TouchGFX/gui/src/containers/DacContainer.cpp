#include <gui/containers/DacContainer.hpp>
#include <stdio.h>

//To set deafault settings
static uint8_t RohmDefaultConfigArray[15][8] = {
	//| Clock2 | AudioIf3 | DsdFilter | FirFilter1 | FirFilter2 | DeEmph1 | DeEmph2 | DeltaSigma 
   {      0x00,      0x00,        0x00,       0x01,      0x80,       0x00,     0x00,       0x02,   }, //DAC_PCM_32_0KHZ
   {      0x00,      0x00,        0x00,       0x01,      0x80,       0x00,     0x00,       0x02,   }, //DAC_PCM_44_1KHZ
   {      0x00,      0x00,        0x00,       0x01,      0x80,       0x00,     0x00,       0x02,   }, //DAC_PCM_48_0KHZ
   {      0x00,      0x00,        0x00,       0x02,      0x01,       0x00,     0x00,       0x11,   }, //DAC_PCM_88_2KHZ
   {      0x00,      0x00,        0x00,       0x02,      0x01,       0x00,     0x00,       0x11,   }, //DAC_PCM_96_0KHZ
   {      0x00,      0x00,        0x00,       0x04,      0x02,       0x00,     0x00,       0x11,   }, //DAC_PCM_176_4KHZ
   {      0x00,      0x00,        0x00,       0x04,      0x02,       0x00,     0x00,       0x11,   }, //DAC_PCM_192_KHZ
   {      0x00,      0x00,        0x00,       0x08,      0x80,       0x00,     0x00,       0x11,   }, //DAC_PCM_362_8KHZ
   {      0x00,      0x00,        0x00,       0x08,      0x80,       0x00,     0x00,       0x11,   }, //DAC_PCM_384_0KHZ
   {      0x00,      0x00,        0x00,       0x08,      0x80,       0x00,     0x00,       0x01,   }, //DAC_PCM_705_6KHZ
   {      0x00,      0x00,        0x00,       0x08,      0x80,       0x00,     0x00,       0x01,   }, //DAC_PCM_768_0KHZ
   {      0x00,      0x00,        0x02,       0x00,      0x00,       0x00,     0x00,       0x02,   }, //DAC_DSD_64
   {      0x00,      0x00,        0x01,       0x00,      0x00,       0x00,     0x00,       0x02,   }, //DAC_DSD_128
   {      0x00,      0x00,        0x00,       0x00,      0x00,       0x00,     0x00,       0x02,   }, //DAC_DSD_256
   {      0x00,      0x00,        0x00,       0x00,      0x00,       0x00,     0x00,       0x02,   }, //DAC_DSD_512
};


uint8_t(*CurrentDacConfigArray)[DAC_SETTINGS_SIZE_COLS];
bool m_ShowInfo = false;


// Debug Console
//char str[256];
//
//const char* DacModes_name[] =
//{ "DAC_PCM_32_0KHZ",
//	"DAC_PCM_44_1KHZ",
//	"DAC_PCM_48_0KHZ",
//	"DAC_PCM_88_2KHZ",
//	"DAC_PCM_96_0KHZ",
//	"DAC_PCM_176_4KHZ",
//	"DAC_PCM_192_KHZ",
//	"DAC_PCM_362_8KHZ",
//	"DAC_PCM_384_0KHZ",
//	"DAC_PCM_705_6KHZ",
//	"DAC_PCM_768_0KHZ",
//	"DAC_DSD_64",
//	"DAC_DSD_128",
//	"DAC_DSD_256",
//	"DAC_DSD_512"
//};
//
//const char* DacConfigBytes_name[] =
//{
//	"Clock2",
//	"AudioIF3",
//	"DSDFilter",
//	"FIR1",
//	"FIR2",
//	"DeEmp1",
//	"DeEmp2",
//	"DeltaSigma"
//};



#ifdef SIMULATOR

uint8_t DacContainer::DacConfigArray[15][8];

uint8_t DacContainer::simVolume = 80;
uint8_t DacContainer::simSRCEn;
uint8_t DacContainer::simSRCFreq;
uint8_t DacContainer::simSrcBit;
uint8_t DacContainer::simMute;
uint8_t DacContainer::simDACRoute = DACRoute::ROUTE_HDMI_DAC;

void DacContainer::GuiItfSetVolume(uint8_t p_Volume)
{
	simVolume = p_Volume;
}

uint8_t DacContainer::GuiItfGetVolume()
{
	return simVolume;
}

void DacContainer::GuiItfSetMute(uint8_t p_Mute)
{
	simMute = p_Mute;
}
uint8_t DacContainer::GuiItfGetMute()
{
	return simMute;
}

void DacContainer::GuiItfSaveDacFilters()
{

}

uint8_t(*DacContainer::GuiItfGetDacFilters())[DAC_SETTINGS_SIZE_COLS]
{
	return DacConfigArray;
}


void DacContainer::GuiItfSetSRCEnabled(uint8_t p_Enabled)
{
	simSRCEn = p_Enabled;
}
uint8_t DacContainer::GuiItfGetSRCEnabled()
{
	return simSRCEn;
}

void DacContainer::GuiItfSetSRCFreq(uint8_t p_Freq)
{
	simSRCFreq = p_Freq;
}
uint8_t DacContainer::GuiItfGetSRCFreq() {
	return simSRCFreq;
}

void DacContainer::GuiItfSetSRCBit(uint8_t p_Bit)
{
	simSrcBit = p_Bit;
}
uint8_t DacContainer::GuiItfGetSRCBit()
{
	return simSrcBit;
}



uint8_t DacContainer::GuiItfGetRoute()
{
	return simDACRoute;
}

void DacContainer::GuiItfSetRoute(uint8_t p_Route)
{
	simDACRoute = p_Route;
}

#else
extern "C"
{
	void GuiItfSetVolume(uint8_t p_Volume);
	uint8_t  GuiItfGetVolume();

	void  GuiItfSetMute(uint8_t p_Mute);
	uint8_t  GuiItfGetMute();

	void  GuiItfSaveDacFilters();
	uint8_t(*GuiItfGetDacFilters())[DAC_SETTINGS_SIZE_COLS];

	void  GuiItfSetSRCEnabled(uint8_t p_Enabled);
	uint8_t  GuiItfGetSRCEnabled();

	void  GuiItfSetSRCFreq(uint8_t p_Freq);
	uint8_t  GuiItfGetSRCFreq();

	void  GuiItfSetSRCBit(uint8_t p_Bit);
	uint8_t  GuiItfGetSRCBit();

	uint8_t GuiItfGetRoute();
	void GuiItfSetRoute(uint8_t p_Route);

}
#endif

DacContainer::DacContainer()
{
	nudDeEnp.MinValue = 0;
	nudDeEnp.MaxValue = 3;

	nudDeltaSigma.MinValue = 0;
	nudDeltaSigma.MaxValue = 2;

	nudDSDCutOff.MinValue = 0;
	nudDSDCutOff.MaxValue = 2;

	nudFIR.MinValue = 0;
	nudFIR.MaxValue = 2;

	ShowDacConfigs();
}

void DacContainer::ShowDacConfigs()
{
	m_ShowInfo = true;
	//DAC FILTERS
	CurrentDacConfigArray = GuiItfGetDacFilters();

	//LrSwap: Audio Data Swap Control
	uint8_t	swap = CurrentDacConfigArray[DacConfig::DAC_PCM_96_0KHZ][DacConfigBytes::AudioIF3];
	chbxSwap.forceState(swap == 1);

	//PhaseAdj: Phase Adjustment Control for Internal Clock
	uint8_t	phaseAdj = CurrentDacConfigArray[DacConfig::DAC_PCM_96_0KHZ][DacConfigBytes::Clock2];
	chbxPhase.forceState(phaseAdj == 1);

	//Sampling Frequency  for De-Emphasis (For PCM mode)
	uint8_t	deemp1 = CurrentDacConfigArray[DacConfig::DAC_PCM_96_0KHZ][DacConfigBytes::DeEmp1];
	uint8_t	deempEnabled = CurrentDacConfigArray[DacConfig::DAC_PCM_96_0KHZ][DacConfigBytes::DeEmp2];
	if (deempEnabled == 0)
	{
		nudDeEnp.SetValue(0);
	}
	else
	{
		nudDeEnp.SetValue(deemp1);
	}

	// Oversampling Rate Selection for delta-sigma Modulator
	uint8_t	deltaSigma = CurrentDacConfigArray[DacConfig::DAC_PCM_96_0KHZ][DacConfigBytes::DeltaSigma];
	if (deltaSigma == 0)
	{
		nudDeltaSigma.SetValue(0);
	}
	else
	{
		deltaSigma &= 0x0F;
		nudDeltaSigma.SetValue(deltaSigma + 1);
	}

	//FIR Filters - Sharp Roll-Off/Slow Roll-Off
	uint8_t	fir1 = CurrentDacConfigArray[DacConfig::DAC_PCM_96_0KHZ][DacConfigBytes::FIR1];
	uint8_t	fir2 = CurrentDacConfigArray[DacConfig::DAC_PCM_96_0KHZ][DacConfigBytes::FIR2] & 0x0F;
	if (fir1 == 0 || fir1 == 8)
	{
		nudFIR.SetValue(0);
	}
	else
	{
		if (fir2 == 0 || fir2 == 1 || fir2 == 2)
		{
			nudFIR.SetValue(1);
		}
		else
		{
			nudFIR.SetValue(2);
		}
	}

	// High Precision Calculation Mode Control (For PCM mode)
	uint8_t	HPCM = CurrentDacConfigArray[DacConfig::DAC_PCM_96_0KHZ][DacConfigBytes::FIR2] & 0x80;
	chbxHighPrec.forceState(HPCM == 0);

	//Cut Off Frequency of DSD Filter
	uint8_t	DSDFilter = CurrentDacConfigArray[DacConfig::DAC_DSD_64][DacConfigBytes::DSDFilter];
	nudDSDCutOff.SetValue(DSDFilter);

	//VOLUME
	sldrVolume.setValue(GuiItfGetVolume());
	chbxMute.forceState(GuiItfGetMute());

	//SRC ENABLED
	chbxEnableSRC.forceState(GuiItfGetSRCEnabled());

	// SRC FREQUENCY
	switch (GuiItfGetSRCFreq())
	{
	case SRCF_Low:
	{
		rdbSRCFreqLow.setSelected(true);
	}
	break;
	case SRCF_Mid:
	{
		rdbSRCFreqMid.setSelected(true);
	}
	break;
	case SRCF_High:
	{
		rdbSRCFreqHigh.setSelected(true);
	}
	break;
	default:
		break;
	}

	//SRC BIT DEPTH
	switch (GuiItfGetSRCBit())
	{
	case SRC_Bit_16:
	{
		rdbSRCBit16.setSelected(true);
	}
	break;
	case SRC_Bit_24:
	{
		rdbSRCBit24.setSelected(true);
	}
	break;
	default:
		break;
	}

	m_ShowInfo = false;
}

void DacContainer::initialize()
{
	DacContainerBase::initialize();
}


// ======================== Profile ========================

void DacContainer::btnUserProfileClicked()
{
	// Override and implement this function in DacContainer
}

void DacContainer::btnFactoryProfileClicked()
{
	for (size_t config = DacConfigBytes::Clock2; config < DacConfigBytes::DeltaSigma; config++)
	{
		for (size_t mode = DacConfig::DAC_PCM_32_0KHZ; mode < DacConfig::DAC_DSD_512; mode++)
		{
			SetDacConfig(mode, config, RohmDefaultConfigArray[mode][config]);
		}
	}

	GuiItfSaveDacFilters();
	ShowDacConfigs();
}

// ======================== CONFIG ========================

void DacContainer::SetDacConfig(uint8_t DacMode, uint8_t DacConfigEnum, uint8_t Settings)
{
	CurrentDacConfigArray[DacMode][DacConfigEnum] = Settings;

	////Debug console
	//sprintf_s(str, sizeof(str), "DacMode: %s - DacConfig: %s  Value: %d\n",
	//	DacModes_name[DacMode], DacConfigBytes_name[DacConfigEnum], Settings);
	//OutputDebugStringA(str); 
}

void DacContainer::SetDacConfigWithMask(uint8_t DacMode, uint8_t DacConfig, uint8_t Settings, uint8_t Mask)
{
	uint8_t maskedSettings = Settings & Mask;
	uint8_t maskedResult = CurrentDacConfigArray[DacMode][DacConfig] & ~Mask;
	CurrentDacConfigArray[DacMode][DacConfig] = maskedSettings | maskedResult;

	////Debug console
	//sprintf_s(str, sizeof(str), "DacMode: %s - DacConfig: %s  Value: %d Result: %d \n",
	//	DacModes_name[DacMode], DacConfigBytes_name[DacConfig], Settings, CurrentDacConfigArray[DacMode][DacConfig]);
	//OutputDebugStringA(str);
}

uint8_t DacContainer::GetDacConfig(uint8_t DacMode, uint8_t DacConfigEnum)
{
	return CurrentDacConfigArray[DacMode][DacConfigEnum];
}

void DacContainer::OnDSDCutOffValueChanged(uint32_t value)
{
	// Clock2,AudioIF3,	[DSDFilter]	,FIR1,FIR2,DeEmp1,DeEmp2,DeltaSigma

	//address Register Name R/W Initial D7 D6 D5 D4 D3 D2    D1 D0
	//16h		DSD	Filter R/W	  00h    0  0  0  0  0  0 DsdFilter[1:0]
	/*DsdFilter
		[1:0]
							   Cut Off Frequency
		DSD 2.8 MHz		DSD 5.6 MHz		DSD 11.2 MHz	DSD 22.4 MHz
		00	13 kHz		26 kHz			52 kHz			104 kHz
		01	26 kHz		52 kHz			104 kHz			208 kHz
		10	52 kHz		104 kHz			208 kHz			416 kHz
		11 Prohibition
	*/

	for (int y = DacConfig::DAC_DSD_64; y <= DacConfig::DAC_DSD_512; y++)
	{
		SetDacConfig(y, DacConfigBytes::DSDFilter, value);
	}

	GuiItfSaveDacFilters();
}

void DacContainer::OnFirValueChanged(uint32_t value)
{
	// Clock2,AudioIF3,DSDFilter,	[FIR1, FIR2]	,DeEmp1,DeEmp2,DeltaSigma

	//address Register Name R/W Initial D7		D6 D5 D4 D3 D2 D1 D0
	//30h	FIR	Filter 1	R/W	 00h	0		0  0  0	 FirAlgo[3:0]
	//31h	FIR Filter 2	R/W	 00h	HpcMode 0  0  0  0	FirCoef[2:0]

	uint8_t mask = 0x7F;
	//Fir oFF
	if (value == 0)
	{
		for (int y = DacConfig::DAC_PCM_32_0KHZ; y <= DacConfig::DAC_PCM_768_0KHZ; y++)
		{
			SetDacConfig(y, DacConfigBytes::FIR1, 0);
			SetDacConfigWithMask(y, DacConfigBytes::FIR2, 0, mask);
		}
	}

	//Sharp Roll-Off
	if (value == 1)
	{
		SetDacConfig(DacConfig::DAC_PCM_32_0KHZ, DacConfigBytes::FIR1, 1);
		SetDacConfigWithMask(DacConfig::DAC_PCM_32_0KHZ, DacConfigBytes::FIR2, 0, mask);
		SetDacConfig(DacConfig::DAC_PCM_44_1KHZ, DacConfigBytes::FIR1, 1);
		SetDacConfigWithMask(DacConfig::DAC_PCM_44_1KHZ, DacConfigBytes::FIR2, 0, mask);
		SetDacConfig(DacConfig::DAC_PCM_48_0KHZ, DacConfigBytes::FIR1, 1);
		SetDacConfigWithMask(DacConfig::DAC_PCM_48_0KHZ, DacConfigBytes::FIR2, 0, mask);

		SetDacConfig(DacConfig::DAC_PCM_88_2KHZ, DacConfigBytes::FIR1, 2);
		SetDacConfigWithMask(DacConfig::DAC_PCM_88_2KHZ, DacConfigBytes::FIR2, 1, mask);
		SetDacConfig(DacConfig::DAC_PCM_96_0KHZ, DacConfigBytes::FIR1, 2);
		SetDacConfigWithMask(DacConfig::DAC_PCM_96_0KHZ, DacConfigBytes::FIR2, 1, mask);

		SetDacConfig(DacConfig::DAC_PCM_176_4KHZ, DacConfigBytes::FIR1, 4);
		SetDacConfigWithMask(DacConfig::DAC_PCM_176_4KHZ, DacConfigBytes::FIR2, 2, mask);
		SetDacConfig(DacConfig::DAC_PCM_192_KHZ, DacConfigBytes::FIR1, 4);
		SetDacConfigWithMask(DacConfig::DAC_PCM_192_KHZ, DacConfigBytes::FIR2, 2, mask);


		SetDacConfig(DacConfig::DAC_PCM_362_8KHZ, DacConfigBytes::FIR1, 8);
		SetDacConfigWithMask(DacConfig::DAC_PCM_362_8KHZ, DacConfigBytes::FIR2, 0, mask);
		SetDacConfig(DacConfig::DAC_PCM_384_0KHZ, DacConfigBytes::FIR1, 8);
		SetDacConfigWithMask(DacConfig::DAC_PCM_384_0KHZ, DacConfigBytes::FIR2, 0, mask);

		SetDacConfig(DacConfig::DAC_PCM_705_6KHZ, DacConfigBytes::FIR1, 8);
		SetDacConfigWithMask(DacConfig::DAC_PCM_705_6KHZ, DacConfigBytes::FIR2, 0, mask);
		SetDacConfig(DacConfig::DAC_PCM_768_0KHZ, DacConfigBytes::FIR1, 8);
		SetDacConfigWithMask(DacConfig::DAC_PCM_768_0KHZ, DacConfigBytes::FIR2, 0, mask);
	}

	//Slow Roll-OFF
	if (value == 2)
	{
		SetDacConfig(DacConfig::DAC_PCM_32_0KHZ, DacConfigBytes::FIR1, 1);
		SetDacConfigWithMask(DacConfig::DAC_PCM_32_0KHZ, DacConfigBytes::FIR2, 3, mask);
		SetDacConfig(DacConfig::DAC_PCM_44_1KHZ, DacConfigBytes::FIR1, 1);
		SetDacConfigWithMask(DacConfig::DAC_PCM_44_1KHZ, DacConfigBytes::FIR2, 3, mask);
		SetDacConfig(DacConfig::DAC_PCM_48_0KHZ, DacConfigBytes::FIR1, 1);
		SetDacConfigWithMask(DacConfig::DAC_PCM_48_0KHZ, DacConfigBytes::FIR2, 3, mask);

		SetDacConfig(DacConfig::DAC_PCM_88_2KHZ, DacConfigBytes::FIR1, 2);
		SetDacConfigWithMask(DacConfig::DAC_PCM_88_2KHZ, DacConfigBytes::FIR2, 4, mask);
		SetDacConfig(DacConfig::DAC_PCM_96_0KHZ, DacConfigBytes::FIR1, 2);
		SetDacConfigWithMask(DacConfig::DAC_PCM_96_0KHZ, DacConfigBytes::FIR2, 4, mask);

		SetDacConfig(DacConfig::DAC_PCM_176_4KHZ, DacConfigBytes::FIR1, 4);
		SetDacConfigWithMask(DacConfig::DAC_PCM_176_4KHZ, DacConfigBytes::FIR2, 5, mask);
		SetDacConfig(DacConfig::DAC_PCM_192_KHZ, DacConfigBytes::FIR1, 4);
		SetDacConfigWithMask(DacConfig::DAC_PCM_192_KHZ, DacConfigBytes::FIR2, 5, mask);


		SetDacConfig(DacConfig::DAC_PCM_362_8KHZ, DacConfigBytes::FIR1, 8);
		SetDacConfigWithMask(DacConfig::DAC_PCM_362_8KHZ, DacConfigBytes::FIR2, 0, mask);
		SetDacConfig(DacConfig::DAC_PCM_384_0KHZ, DacConfigBytes::FIR1, 8);
		SetDacConfigWithMask(DacConfig::DAC_PCM_384_0KHZ, DacConfigBytes::FIR2, 0, mask);

		SetDacConfig(DacConfig::DAC_PCM_705_6KHZ, DacConfigBytes::FIR1, 8);
		SetDacConfigWithMask(DacConfig::DAC_PCM_705_6KHZ, DacConfigBytes::FIR2, 0, mask);
		SetDacConfig(DacConfig::DAC_PCM_768_0KHZ, DacConfigBytes::FIR1, 8);
		SetDacConfigWithMask(DacConfig::DAC_PCM_768_0KHZ, DacConfigBytes::FIR2, 0, mask);
	}

	//SET HPC Mode
	//chbxHighPrecChanged();

	GuiItfSaveDacFilters();
}

void DacContainer::OnDeEmpValueChanged(uint32_t value)
{
	// Clock2,AudioIF3,DSDFilter,[FIR1, FIR2,	[DeEmp1,DeEmp2]	  ,DeltaSigma

	//address Register Name R/W Initial D7 D6 D5 D4 D3 D2 D1 D0
	//30h	De-Emphasis 1	R/W	 00h	0  0  0  0	0  0  DempFs[1:0]
	//31h	De-Emphasis 2	R/W	 00h    0  0  0  0  0  0  EnableLR[1:0]

	if (value == 0)
	{
		for (int y = DacConfig::DAC_PCM_32_0KHZ; y <= DacConfig::DAC_PCM_768_0KHZ; y++)
		{
			SetDacConfig(y, DacConfigBytes::DeEmp1, 0);
			SetDacConfig(y, DacConfigBytes::DeEmp2, 0);
		}
	}
	else
	{
		for (int y = DacConfig::DAC_PCM_32_0KHZ; y <= DacConfig::DAC_PCM_768_0KHZ; y++)
		{
			SetDacConfig(y, DacConfigBytes::DeEmp1, value);
			SetDacConfig(y, DacConfigBytes::DeEmp2, 3);
		}
	}

	GuiItfSaveDacFilters();
}

void DacContainer::OnDeltaSigmaValueChanged(uint32_t value)
{
	// Clock2,AudioIF3,DSDFilter,FIR1,FIR2,DeEmp1,DeEmp2,	[DeltaSigma]

	//address Register Name R/W Initial D7 D6 D5 D4			D3 D2 D1 D0
	//40h	  Delta Sigma 	R/W	 00h	0  0  0  DsSetting	0  0  DsOsr[1:0]

	if (value == 0)
	{
		for (int y = DacConfig::DAC_PCM_32_0KHZ; y <= DacConfig::DAC_PCM_768_0KHZ; y++)
		{
			SetDacConfig(y, DacConfigBytes::DeltaSigma, value);
		}
	}
	else
	{
		//DsSetting set to 1
		uint8_t ds = 0x10 + (value - 1);

		for (int y = DacConfig::DAC_PCM_32_0KHZ; y <= DacConfig::DAC_PCM_768_0KHZ; y++)
		{
			SetDacConfig(y, DacConfigBytes::DeltaSigma, ds);
		}
	}

	GuiItfSaveDacFilters();
}

void DacContainer::chbxSwapChanged()
{
	int OnSwapChanel = 0;

	if (chbxSwap.getState())
	{
		OnSwapChanel = 1;
	}
	else
	{
		OnSwapChanel = 0;
	}

	for (int y = DacConfig::DAC_PCM_32_0KHZ; y <= DacConfig::DAC_DSD_512; y++)
	{
		SetDacConfig(y, DacConfigBytes::AudioIF3, OnSwapChanel);
	}

	GuiItfSaveDacFilters();
}

void DacContainer::chbxPhaseChanged()
{
	//address Register Name R/W Initial D7 D6 D5 D4 D3 D2 D1 D0
	//06h			Clock 2	R/W	 00h	0  0  0  0  0  0  0  PhaseAdj

	int OnPhase = 0;
	if (chbxPhase.getState())
	{
		OnPhase = 1;
	}
	else
	{
		OnPhase = 0;
	}

	for (int y = DacConfig::DAC_PCM_32_0KHZ; y <= DacConfig::DAC_DSD_512; y++)
	{
		SetDacConfig(y, DacConfigBytes::Clock2, OnPhase);
	}

	GuiItfSaveDacFilters();
}

void DacContainer::chbxHighPrecChanged()
{
	//address Register Name R/W Initial D7		D6 D5 D4 D3 D2 D1 D0
	//31h	FIR Filter 2	R/W	 00h	HpcMode 0  0  0  0	FirCoef[2:0]
	uint8_t mask = 0x80;
	if (chbxHighPrec.getState())
	{
		for (int y = DacConfig::DAC_PCM_32_0KHZ; y <= DacConfig::DAC_PCM_192_KHZ; y++)
		{
			SetDacConfigWithMask(y, DacConfigBytes::FIR2, 0, mask);
		}
		for (int y = DacConfig::DAC_PCM_362_8KHZ; y <= DacConfig::DAC_PCM_768_0KHZ; y++)
		{
			SetDacConfigWithMask(y, DacConfigBytes::FIR2, 0x80, mask);
		}
	}
	else
	{
		for (int y = DacConfig::DAC_PCM_32_0KHZ; y <= DacConfig::DAC_PCM_768_0KHZ; y++)
		{
			SetDacConfigWithMask(y, DacConfigBytes::FIR2, 0x80, mask);
		}
	}

	//clear dsd
	for (int y = DacConfig::DAC_DSD_64; y <= DacConfig::DAC_DSD_512; y++)
	{
		SetDacConfig(y, DacConfigBytes::FIR2, 0);
	}

	GuiItfSaveDacFilters();
}

// ======================== VOLUME ========================

void DacContainer::chbxMuteChanged()
{
	GuiItfSetMute(chbxMute.getState() ? 1 : 0);
}

void DacContainer::sldrVolumeValueChanged(int value)
{
	if (!m_ShowInfo)
	{
		GuiItfSetVolume((uint8_t)value);
	}

	Unicode::snprintf(lblVolumeBuffer, LBLVOLUME_SIZE, "%d", value);
	lblVolume.invalidate();
}

// ======================== SRC ========================

void DacContainer::chbxEnableSRCChecked()
{
	if (!m_ShowInfo)
	{
		bool srcEnabled = chbxEnableSRC.getState();
		uint8_t dacRoute = GuiItfGetRoute();
		GuiItfSetSRCEnabled(srcEnabled);

		if (srcEnabled)
		{
			switch (dacRoute)
			{
			case ROUTE_USB_DAC:
				GuiItfSetRoute(DacRoute::ROUTE_USB_SRC_DAC);
				break;
			case ROUTE_HDMI_DAC:
				GuiItfSetRoute(DacRoute::ROUTE_HDMI_SRC_DAC);
				break;
			case ROUTE_BNC_DAC:
				GuiItfSetRoute(DacRoute::ROUTE_BNC_SRC_DAC);
				break;
			case ROUTE_RCA_DAC:
				GuiItfSetRoute(DacRoute::ROUTE_RCA_SRC_DAC);
				break;
			case ROUTE_XLR_DAC:
				GuiItfSetRoute(DacRoute::ROUTE_XLR_SRC_DAC);
				break; 
			default:
				break;
			}
		}
		else
		{
			switch (dacRoute)
			{
			case ROUTE_USB_SRC_DAC:
				GuiItfSetRoute(DacRoute::ROUTE_USB_DAC);
				break;
			case ROUTE_HDMI_SRC_DAC:
				GuiItfSetRoute(DacRoute::ROUTE_HDMI_DAC);
				break;
			case ROUTE_BNC_SRC_DAC:
				GuiItfSetRoute(DacRoute::ROUTE_BNC_DAC);
				break;
			case ROUTE_RCA_SRC_DAC:
				GuiItfSetRoute(DacRoute::ROUTE_RCA_DAC);
				break;
			case ROUTE_XLR_SRC_DAC:
				GuiItfSetRoute(DacRoute::ROUTE_XLR_DAC);
				break; 
			default:
				break;
			}
		}
	}
}

void DacContainer::rdbSRCFreqLowSelected()
{
	if (!m_ShowInfo)
		GuiItfSetSRCFreq(SRCFreq::SRCF_Low);
}

void DacContainer::rdbSRCFreqMidSelected()
{
	if (!m_ShowInfo)
		GuiItfSetSRCFreq(SRCFreq::SRCF_Mid);
}

void DacContainer::rdbSRCFreqHighSelected()
{
	if (!m_ShowInfo)
		GuiItfSetSRCFreq(SRCFreq::SRCF_High);
}

void DacContainer::rdbSRCBit16Selected()
{
	if (!m_ShowInfo)
		GuiItfSetSRCBit(SRCBit::SRC_Bit_16);
}

void DacContainer::rdbSRCBit24Selected()
{
	if (!m_ShowInfo)
		GuiItfSetSRCBit(SRCBit::SRC_Bit_24);
}
