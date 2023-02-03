#include <gui/main_screen/MainView.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/containers/buttons/ImageButtonStyle.hpp>
#include "BitmapDatabase.hpp"
#include <time.h> 
#include <gui/containers/DacContainer.hpp>


time_t saverDateTime;

#ifdef SIMULATOR

//Sumlated Time
time_t simMainDateTime;

static uint8_t simDACMode = DacConfig::DAC_PCM_384_0KHZ;

/*** Time ***/

void MainView::GuiItfGetRtc(time_t* dt)
{
	if (simMainDateTime == 0)
	{
		tm tm_info;
		tm_info.tm_year = 2022 - 1900;
		tm_info.tm_mon = 6 - 1;
		tm_info.tm_mday = 16;
		tm_info.tm_hour = 20;
		tm_info.tm_min = 21;
		tm_info.tm_sec = 22;
		tm_info.tm_isdst = 0;

		simMainDateTime = mktime(&tm_info);
	}
	simMainDateTime++;
	*dt = simMainDateTime;
}

/*** Display ***/
uint8_t MainView::GuiItfGetScreenSaverEnable()
{
	return false;
}

/*** Clock Temp ***/
uint32_t  MainView::GuiItfGetClockHeatedTemperature()
{
	return 55;
}

void MainView::GuiItfSetClockHeatedTemperature(uint32_t temp)
{
}

/*** DAC Config, Volume ***/

uint8_t MainView::GuiItfGetConfig()
{
	return simDACMode;
}

uint8_t MainView::GuiItfGetRoute()
{
	return DacContainer::simDACRoute;
}

void MainView::GuiItfSetRoute(uint8_t p_Route)
{
	DacContainer::simDACRoute = p_Route;
}

void MainView::GuiItfSetVolume(uint8_t p_Volume)
{
	DacContainer::simVolume = p_Volume;
}

uint8_t MainView::GuiItfGetVolume()
{
	return DacContainer::simVolume;
}

void MainView::GuiItfSetMute(uint8_t p_Mute)
{
	DacContainer::simMute = p_Mute;
}

uint8_t MainView::GuiItfGetMute()
{
	return DacContainer::simMute;
}

uint8_t(*MainView::GuiItfGetDacFilters())[DAC_SETTINGS_SIZE_COLS]
{
	return DacContainer::DacConfigArray;
}

/*** SRC ***/
uint8_t MainView::GuiItfGetSRCEnable(){
	return DacContainer::simSRCEn;
}
uint8_t MainView::GuiItfGetSRCFsout() {
	return DacContainer::simSRCFreq;
}

uint8_t MainView::GuiItfGetSRCBits()
{
	return DacContainer::simSrcBit;
}

#else
extern "C"
{
	/*** Time ***/
	void GuiItfGetRtc(time_t* dt);

	/*** Display ***/
	uint8_t GuiItfGetScreenSaverEnable();

	/*** Clock Temp ***/
	uint32_t GuiItfGetClockHeatedTemperature();
	void GuiItfSetDasClockHeatedTemperature(uint32_t temp);

	/*** DAC Config, Volume ***/
	uint8_t GuiItfGetConfig();
	uint8_t GuiItfGetRoute();
	void GuiItfSetRoute(uint8_t p_Route);

	void GuiItfSetVolume(uint8_t p_Volume);
	uint8_t GuiItfGetVolume();
	void GuiItfSetMute(uint8_t p_Mute);
	uint8_t GuiItfGetMute();
	uint8_t(*GuiItfGetDacFilters())[DAC_SETTINGS_SIZE_COLS];

	/*** SRC ***/
	uint8_t GuiItfGetSRCEnable();
	uint8_t GuiItfGetSRCFsout();
	uint8_t GuiItfGetSRCBits();
}
#endif

//CLOCKS
static bool mIs24Locked;
static bool mIs245Locked;
static bool mIs22Locked;
static bool mIsIntExt;

//Default colors
colortype GRAYCOLOR;
colortype MIDGRAYCOLOR;
colortype BLACKCOLOR;
colortype CORECOLOR;
colortype DARKGRAYCOLOR;
colortype REDCOLOR;

//Buttons
uint8_t mKarunaControl;

//Temperature
int mTemp;

//Audio
uint8_t  mPreDacMode;
uint8_t  mPreDacRoute;
bool mOnlyRefreshInputUI;
uint8_t(*CurrentDacConfigPtr)[DAC_SETTINGS_SIZE_COLS];
bool m_ShowDacInfo = false;
Unicode::UnicodeChar mUniVolume[5];

//Gui Refresh
int mTickCount;

MainView::MainView()
{
	GRAYCOLOR = touchgfx::Color::getColorFrom24BitRGB(128, 128, 128);
	CORECOLOR = touchgfx::Color::getColorFrom24BitRGB(150, 118, 73);
	BLACKCOLOR = touchgfx::Color::getColorFrom24BitRGB(0, 0, 0);
	DARKGRAYCOLOR = touchgfx::Color::getColorFrom24BitRGB(32, 32, 32);
	MIDGRAYCOLOR = touchgfx::Color::getColorFrom24BitRGB(64, 64, 64);
	REDCOLOR = touchgfx::Color::getColorFrom24BitRGB(0x8B, 0, 0);

	CurrentDacConfigPtr = GuiItfGetDacFilters();
	mPreDacMode = mPreDacRoute = 0xFF;

	//Audio and Clocks temperature
	RefreshUI();
	GuiItfGetRtc(&saverDateTime);
	RequestCurrentTime();
}

// Toogle inputs

void MainView::rdbXLRInputsSelected()
{
	bxInput.moveTo(rdbXLR.getX(), rdbXLR.getY());
	if (!mOnlyRefreshInputUI)
		GuiItfSetRoute(DacRoute::ROUTE_XLR_DAC);
}

void MainView::rdbUSBInputsSelected()
{
	bxInput.moveTo(rdbUSB.getX(), rdbUSB.getY());
	if (!mOnlyRefreshInputUI)
		GuiItfSetRoute(DacRoute::ROUTE_USB_DAC);
}

void MainView::rdbHDMIInputsSelected()
{
	bxInput.moveTo(rdbHDMI.getX(), rdbHDMI.getY());
	if (!mOnlyRefreshInputUI)
		GuiItfSetRoute(DacRoute::ROUTE_HDMI_DAC);
}

void MainView::rdbRCAInputsSelected()
{
	bxInput.moveTo(rdbRCA.getX(), rdbRCA.getY());
	if (!mOnlyRefreshInputUI)
		GuiItfSetRoute(DacRoute::ROUTE_RCA_DAC);
}

void MainView::rdbBNCInputsSelected()
{
	bxInput.moveTo(rdbBNC.getX(), rdbXLR.getY());
	if (!mOnlyRefreshInputUI)
		GuiItfSetRoute(DacRoute::ROUTE_BNC_DAC);
}

// CLOCK PROPS

void MainView::Refresh24Lock()
{
	box24.setColor(GetLockColor(mIs24Locked));
	box24.invalidate();
}

void MainView::Refresh245Lock()
{
	box245.setColor(GetLockColor(mIs245Locked));
	box245.invalidate();
}

void MainView::Refresh22Lock()
{
	box22.setColor(GetLockColor(mIs22Locked));
	box22.invalidate();
}

void MainView::RefreshIntExt()
{
	boxIntExt.setColor(GetLockColor(mIsIntExt));
	if (mIsIntExt)
	{
		imgIntExt.setBitmap(Bitmap(BITMAP_CLOCKEXT_80X80_I_ID));
	}
	else
	{
		imgIntExt.setBitmap(Bitmap(BITMAP_CLOCKINT_80X80_I_ID));
	}
	boxIntExt.invalidate();
}

// CLOCK TEMP

void  MainView::SetTemp(int p_Temp)
{
	int heatedTemp = GuiItfGetClockHeatedTemperature();

	if (p_Temp < heatedTemp - 30)
	{
		PaintDot(MIDGRAYCOLOR, MIDGRAYCOLOR, MIDGRAYCOLOR);
	}
	else if (p_Temp >= heatedTemp - 30 && p_Temp < heatedTemp - 20)
	{
		PaintDot(CORECOLOR, MIDGRAYCOLOR, MIDGRAYCOLOR);
	}
	else if (p_Temp >= heatedTemp - 20 && p_Temp < heatedTemp - 10)
	{
		PaintDot(CORECOLOR, CORECOLOR, MIDGRAYCOLOR);
	}
	else if (p_Temp >= heatedTemp - 10 && p_Temp < heatedTemp + 10)
	{
		PaintDot(CORECOLOR, CORECOLOR, CORECOLOR);
	}
	else if (p_Temp >= heatedTemp + 10 && p_Temp < heatedTemp + 15)
	{
		PaintDot(REDCOLOR, CORECOLOR, CORECOLOR);
	}
	else if (p_Temp >= heatedTemp + 15 && p_Temp < heatedTemp + 20)
	{
		PaintDot(REDCOLOR, REDCOLOR, CORECOLOR);
	}
	else if (p_Temp >= heatedTemp + 20)
	{
		PaintDot(REDCOLOR, REDCOLOR, REDCOLOR);
	}
}

void MainView::PaintDot(colortype p_Dot1, colortype p_Dot2, colortype p_Dot3)
{
	circTemp1Painter.setColor(p_Dot1);
	circTemp2Painter.setColor(p_Dot2);
	circTemp3Painter.setColor(p_Dot3);

	circTemp1.invalidate();
	circTemp2.invalidate();
	circTemp3.invalidate();
}


//SET GUI AUDIO VALUE

void MainView::RefreshSRCInfo(uint8_t p_AudiFormat)
{
	if (p_AudiFormat < DacConfig::DAC_DSD_64)
	{
		bool isSRCEnabled = GuiItfGetSRCEnable() &&
			(p_AudiFormat == DacConfig::DAC_PCM_44_1KHZ ||
				p_AudiFormat == DacConfig::DAC_PCM_88_2KHZ ||
				p_AudiFormat == DacConfig::DAC_PCM_176_4KHZ ||
				p_AudiFormat == DacConfig::DAC_PCM_48_0KHZ ||
				p_AudiFormat == DacConfig::DAC_PCM_96_0KHZ ||
				p_AudiFormat == DacConfig::DAC_PCM_192_KHZ);

		if (isSRCEnabled)
		{
			Unicode::strncpy(lblValueFormatBuffer, "SRC", LBLVALUEFORMAT_SIZE);

			switch (GuiItfGetSRCBits())
			{
			case SRC_Bit_16:
			{
				Unicode::strncpy(lblDSDValueBuffer, "16 bit", LBLDSDVALUE_SIZE);
			}
			break;
			case SRC_Bit_24:
			{
				Unicode::strncpy(lblDSDValueBuffer, "24 bit", LBLDSDVALUE_SIZE);
			}
			break;
			default:
				break;
			}

			uint8_t srcFreq = GuiItfGetSRCFsout();

			if (p_AudiFormat == DacConfig::DAC_PCM_44_1KHZ ||
				p_AudiFormat == DacConfig::DAC_PCM_88_2KHZ ||
				p_AudiFormat == DacConfig::DAC_PCM_176_4KHZ)
			{
				switch (srcFreq)
				{
				case SRCF_Low:
				{
					Unicode::strncpy(lblSRCFreqBuffer, "44.1 kHz", LBLSRCFREQ_SIZE);
				}
				break;
				case SRCF_Mid:
				{
					Unicode::strncpy(lblSRCFreqBuffer, "88.2 kHz", LBLSRCFREQ_SIZE);
				}
				break;
				case SRCF_High:
				{
					Unicode::strncpy(lblSRCFreqBuffer, "176.4 kHz", LBLSRCFREQ_SIZE);
				}
				break;
				default:
					break;
				}
			}
			else if (p_AudiFormat == DacConfig::DAC_PCM_48_0KHZ ||
				p_AudiFormat == DacConfig::DAC_PCM_96_0KHZ ||
				p_AudiFormat == DacConfig::DAC_PCM_192_KHZ)
			{
				switch (srcFreq)
				{
				case SRCF_Low:
				{
					Unicode::strncpy(lblSRCFreqBuffer, "48 kHz", LBLSRCFREQ_SIZE);
				}
				break;
				case SRCF_Mid:
				{
					Unicode::strncpy(lblSRCFreqBuffer, "96 kHz", LBLSRCFREQ_SIZE);
				}
				break;
				case SRCF_High:
				{
					Unicode::strncpy(lblSRCFreqBuffer, "192 kHz", LBLSRCFREQ_SIZE);
				}
				break;
				default:
					break;
				}
			}
		}
		pbxSRCOn.setVisible(isSRCEnabled);
		lblDSDValue.setVisible(isSRCEnabled);
		lblSRCFreq.setVisible(isSRCEnabled);

		lblDSDValue.invalidate();
		lblValueFormat.invalidate();
		lblSRCFreq.invalidate();
	}
	else
	{
		pbxSRCOn.setVisible(false);
		lblSRCFreq.setVisible(false);
		lblSRCFreq.invalidate();
	}

}

void  MainView::SetDSDPCM(int p_AudiFormat)
{
	bool isDsd = p_AudiFormat >= DacConfig::DAC_DSD_64;

	if (isDsd)
	{
		/*bool isDoP = !ToBinary(p_AudiFormat, 3);
		if (isDoP)
		{
			Unicode::strncpy(lblValueFormatBuffer, "DoP", LBLVALUEFORMAT_SIZE);
		}
		else*/
		{
			Unicode::strncpy(lblValueFormatBuffer, "DSD", LBLVALUEFORMAT_SIZE);
		}
		int dsdFormat = p_AudiFormat >> 1;
		dsdFormat = dsdFormat & 0b00000011;

		Unicode::strncpy(lblDSDValueBuffer, "N.A.", LBLDSDVALUE_SIZE);


		switch (p_AudiFormat)
		{
		case DAC_DSD_64:
		{
			Unicode::strncpy(lblDSDValueBuffer, "64", LBLDSDVALUE_SIZE);
		}break;
		case DAC_DSD_128:
		{
			Unicode::strncpy(lblDSDValueBuffer, "128", LBLDSDVALUE_SIZE);
		}break;
		case DAC_DSD_256:
		{
			Unicode::strncpy(lblDSDValueBuffer, "256", LBLDSDVALUE_SIZE);
		}break;
		case DAC_DSD_512:
		{
			Unicode::strncpy(lblDSDValueBuffer, "512", LBLDSDVALUE_SIZE);
		}break;

		default:
			break;
		}
	}
	else
	{
		{
			Unicode::strncpy(lblValueFormatBuffer, "PCM", LBLVALUEFORMAT_SIZE);
		}
	}

	lblDSDValue.setVisible(isDsd);
	RefreshSRCInfo(p_AudiFormat);

	lblDSDValue.invalidate();
	lblValueFormat.invalidate();
}

void  MainView::SetFreq(int p_AudiFormat)
{
	Unicode::strncpy(lblValueFreqBuffer, "N.A.", LBLVALUEFREQ_SIZE);

	switch (p_AudiFormat)
	{
	case DAC_PCM_44_1KHZ:
	{
		Unicode::strncpy(lblValueFreqBuffer, "44.1 kHz", LBLVALUEFREQ_SIZE);
	}break;
	case DAC_PCM_48_0KHZ:
	{
		Unicode::strncpy(lblValueFreqBuffer, "48 kHz", LBLVALUEFREQ_SIZE);
	}break;
	case DAC_PCM_88_2KHZ:
	{
		Unicode::strncpy(lblValueFreqBuffer, "88.2 kHz", LBLVALUEFREQ_SIZE);
	}break;
	case DAC_PCM_96_0KHZ:
	{
		Unicode::strncpy(lblValueFreqBuffer, "96 kHz", LBLVALUEFREQ_SIZE);
	}break;
	case DAC_PCM_176_4KHZ:
	{
		Unicode::strncpy(lblValueFreqBuffer, "176.4 kHz", LBLVALUEFREQ_SIZE);
	}break;
	case DAC_PCM_192_KHZ:
	{
		Unicode::strncpy(lblValueFreqBuffer, "192 kHz", LBLVALUEFREQ_SIZE);
	}break;
	case DAC_PCM_362_8KHZ:
	{
		Unicode::strncpy(lblValueFreqBuffer, "352.8 kHz", LBLVALUEFREQ_SIZE);
	}break;
	case DAC_PCM_384_0KHZ:
	{
		Unicode::strncpy(lblValueFreqBuffer, "384 kHz", LBLVALUEFREQ_SIZE);
	}break;
	case DAC_PCM_705_6KHZ:
	{
		Unicode::strncpy(lblValueFreqBuffer, "705.6 kHz", LBLVALUEFREQ_SIZE);
	}break;
	case DAC_PCM_768_0KHZ:
	{
		Unicode::strncpy(lblValueFreqBuffer, "768 kHz", LBLVALUEFREQ_SIZE);
	}break;
	case DAC_DSD_64:
	{
		Unicode::strncpy(lblValueFreqBuffer, "2.8 MHz", LBLVALUEFREQ_SIZE);
	}break;
	case DAC_DSD_128:
	{
		Unicode::strncpy(lblValueFreqBuffer, "5.8 MHz", LBLVALUEFREQ_SIZE);
	}break;
	case DAC_DSD_256:
	{
		Unicode::strncpy(lblValueFreqBuffer, "11.2 MHz", LBLVALUEFREQ_SIZE);
	}break;
	case DAC_DSD_512:
	{
		Unicode::strncpy(lblValueFreqBuffer, "22.6 MHz", LBLVALUEFREQ_SIZE);
	}break;

	default:
		break;
	}

	RefreshSRCInfo(p_AudiFormat);

	lblValueFreq.invalidate();
}

void MainView::SetInput(int actualDacRoute)
{
	mOnlyRefreshInputUI = true;

	switch (actualDacRoute)
	{
	case ROUTE_NONE_DAC:
	{
		pbxInput.setBitmap(Bitmap(BITMAP_DARK_ICONS_INFO_48_ID));
	}
	break;
	case ROUTE_MUTE_DAC:
	{
		pbxInput.setBitmap(Bitmap(BITMAP_DARK_ICONS_INFO_48_ID));
	}
	break;
	case ROUTE_USB_DAC:
	{
		pbxInput.setBitmap(Bitmap(BITMAP_USB_80X80_FB_ID));
		rdbUSB.setSelected(true);
	}
	break;
	case ROUTE_USB_SRC_DAC:
	{
		pbxInput.setBitmap(Bitmap(BITMAP_USB_80X80_FB_ID));
		rdbUSB.setSelected(true);
	}
	break;
	case ROUTE_HDMI_DAC:
	{
		pbxInput.setBitmap(Bitmap(BITMAP_HDMI_80X80_FB_ID));
		rdbHDMI.setSelected(true);
	}
	break;
	case ROUTE_HDMI_SRC_DAC:
	{
		pbxInput.setBitmap(Bitmap(BITMAP_HDMI_80X80_FB_ID));
		rdbHDMI.setSelected(true);
	}
	break;
	case ROUTE_BNC_DAC:
	{
		pbxInput.setBitmap(Bitmap(BITMAP_BNC_80X80_FB_ID));
		rdbBNC.setSelected(true);

	}
	break;
	case ROUTE_BNC_SRC_DAC:
	{
		pbxInput.setBitmap(Bitmap(BITMAP_BNC_80X80_FB_ID));
		rdbBNC.setSelected(true);

	}
	break;
	case ROUTE_RCA_DAC:
	{
		pbxInput.setBitmap(Bitmap(BITMAP_RCA_80X80_FB_ID));
		rdbRCA.setSelected(true);
	}
	break;
	case ROUTE_RCA_SRC_DAC:
	{
		pbxInput.setBitmap(Bitmap(BITMAP_RCA_80X80_FB_ID));
		rdbRCA.setSelected(true);
	}
	break;
	case ROUTE_XLR_DAC:
	{
		pbxInput.setBitmap(Bitmap(BITMAP_XLR_80X80_FB_ID));
		rdbXLR.setSelected(true);
	}
	break;
	case ROUTE_XLR_SRC_DAC:
	{
		pbxInput.setBitmap(Bitmap(BITMAP_XLR_80X80_FB_ID));
		rdbXLR.setSelected(true);
	}
	break;
	default:
		break;
	}
	pbxInput.invalidate();
	mOnlyRefreshInputUI = false;
}

colortype MainView::GetOutputPressColor(bool p_State)
{
	if (!p_State)
	{
		return BLACKCOLOR;
	}
	else
	{
		return CORECOLOR;
	}
}

colortype MainView::GetOutputReleaseColor(bool p_State)
{
	if (!p_State)
	{
		return DARKGRAYCOLOR;
	}
	else
	{
		return CORECOLOR;
	}
}

colortype MainView::GetLockColor(bool p_State)
{
	if (!p_State)
	{
		return MIDGRAYCOLOR;
	}
	else
	{
		return CORECOLOR;
	}
}

bool MainView::ToBinary(int number, int position)
{
	bool ret = ((1 << position) & number) != 0;
	return ret;
}

// Tick event

void MainView::handleTickEvent()
{
	mTickCount++;

	RefreshUI();
	//Wait for 0.5sec
	if (mTickCount % 10 == 0)
	{
		time_t actualTime = RequestCurrentTime();

		if (!GuiItfGetScreenSaverEnable() && (actualTime - saverDateTime > 60))
		{
			application().gotoSaverScreenScreenWipeTransitionEast();
		}
	}
}

void MainView::RefreshUI()
{
	//Read audio format
	uint8_t  actualDacMode = GuiItfGetConfig();
	if (actualDacMode != mPreDacMode)
	{
		SetDSDPCM(actualDacMode);
		//SetBitDepth(KRN_STAT);
		SetFreq(actualDacMode);

		ShowDacConfigs(actualDacMode);
	}
	mPreDacMode = actualDacMode;

	//VOLUME
	uint8_t volume = GuiItfGetVolume();
	bool mute = GuiItfGetMute() == 1;

	chbxMute.forceState(mute);
	Unicode::snprintf(lblVolumeBuffer, LBLVOLUME_SIZE, "%d", volume);
	lblVolume.invalidate();

	Unicode::snprintf(mUniVolume, 5, "%d", volume);
	btnVolume.setWildcardTextBuffer(mUniVolume);

	colortype volColor = mute ? BLACKCOLOR : CORECOLOR;
	btnVolume.setWildcardTextColors(volColor, volColor);
	btnVolume.invalidate();

	//Read Inut
	uint8_t  actualDacRoute = GuiItfGetRoute();
	if (mPreDacRoute != actualDacRoute)
	{
		SetInput(actualDacRoute);
}
	mPreDacRoute = actualDacRoute;


	float temp = 0;

	//CLOCKs
#ifdef KARUNA_7i
	/*** DAS Clock ***/
	mIs22Locked = GuiItfGetDasClockStatusLock1();
	mIs245Locked = GuiItfGetDasClockStatusLock2();
	mIs24Locked = mIs245Locked && mIs22Locked;
	mIsIntExt = GuiItfGetDasClockIsExt();

	temp = GuiItfGetDasClockMV341Temp();

#endif

#ifdef KARUNA_43i
	/*** Tri Clock ***/
	mIs24Locked = GuiItfGetDi13();
	mIs22Locked = GuiItfGetDi15();
	mIs245Locked = GuiItfGetDi1();
	mIsIntExt = GuiItfGetDi11();

	temp = GuiItfGetTempCh1();

#endif

	SetTemp((int)temp);

	Refresh24Lock();
	Refresh245Lock();
	Refresh22Lock();
	RefreshIntExt();

}

time_t MainView::RequestCurrentTime()
{
	time_t dtp;
	GuiItfGetRtc(&dtp);
	struct tm* tm_info = gmtime(&dtp);
	char strDateTime[LBLDATETIME_SIZE];
	strftime(strDateTime, LBLDATETIME_SIZE, "%d.%m.%Y  %H:%M", tm_info);

	Unicode::UnicodeChar uni_DateTime[LBLDATETIME_SIZE];
	Unicode::fromUTF8((const uint8_t*)strDateTime, uni_DateTime, LBLDATETIME_SIZE);
	Unicode::snprintf(lblDateTimeBuffer, LBLDATETIME_SIZE, "%s", uni_DateTime);
	lblDateTime.invalidate();

	return dtp;
}

// ======================== DAC ========================


void MainView::ShowDacConfigs(uint8_t p_Mode)
{
	m_ShowDacInfo = true;


	//LrSwap: Audio Data Swap Control
	uint8_t	swap = CurrentDacConfigPtr[p_Mode][DacConfigBytes::AudioIF3];
	if (swap == 1)
	{
		pbxSwap.setBitmap(Bitmap(BITMAP_SWAPON_ID));
	}
	else
	{
		pbxSwap.setBitmap(Bitmap(BITMAP_SWAPOFF_ID));
	}
	pbxSwap.setWidth(60);
	pbxSwap.setHeight(33);
	pbxSwap.invalidate();

	//PhaseAdj: Phase Adjustment Control for Internal Clock
	uint8_t	phaseAdj = CurrentDacConfigPtr[p_Mode][DacConfigBytes::Clock2];
	if (phaseAdj == 1)
	{
		pbxPhase.setBitmap(Bitmap(BITMAP_PHASEON_ID));
	}
	else
	{
		pbxPhase.setBitmap(Bitmap(BITMAP_PHASEOFF_ID));
	}
	pbxPhase.setWidth(80);
	pbxPhase.setHeight(43);
	pbxPhase.invalidate();

	//Sampling Frequency  for De-Emphasis (For PCM mode) 
	uint8_t	deempEnabled = CurrentDacConfigPtr[p_Mode][DacConfigBytes::DeEmp2];
	if (deempEnabled == 0)
	{
		tbxDeEmp.setColor(BLACKCOLOR);
	}
	else
	{
		tbxDeEmp.setColor(CORECOLOR);
	}
	tbxDeEmp.setWidth(80);
	tbxDeEmp.setHeight(22);
	tbxDeEmp.invalidate();

	// Oversampling Rate Selection for delta-sigma Modulator
	uint8_t	deltaSigma = CurrentDacConfigPtr[p_Mode][DacConfigBytes::DeltaSigma];
	if (deltaSigma == 0)
	{
		pbxDeltaSigma.setBitmap(Bitmap(BITMAP_DELTASIGMAOFF_ID));
	}
	else
	{
		pbxDeltaSigma.setBitmap(Bitmap(BITMAP_DELTASIGMAON_ID));
	}
	pbxDeltaSigma.setWidth(80);
	pbxDeltaSigma.setHeight(31);
	pbxDeltaSigma.invalidate();

	//FIR Filters - Sharp Roll-Off/Slow Roll-Off
	uint8_t	fir1 = CurrentDacConfigPtr[p_Mode][DacConfigBytes::FIR1];
	if (fir1 == 0 || fir1 == 8)
	{
		pbxFIR.setBitmap(Bitmap(BITMAP_FIROFF_ID));
	}
	else
	{
		pbxFIR.setBitmap(Bitmap(BITMAP_FIRON_ID));
	}
	pbxFIR.setWidth(80);
	pbxFIR.setHeight(43);
	pbxFIR.invalidate();

	// High Precision Calculation Mode Control (For PCM mode)
	uint8_t	HPCM = CurrentDacConfigPtr[p_Mode][DacConfigBytes::FIR2] & 0x80;
	if (HPCM == 0)
	{
		pbxPrec.setBitmap(Bitmap(BITMAP_HIGHPRECON_ID));
	}
	else
	{
		pbxPrec.setBitmap(Bitmap(BITMAP_HIGHPRECOFF_ID));
	}
	pbxPrec.setWidth(80);
	pbxPrec.setHeight(43);
	pbxPrec.invalidate();

	//Cut Off Frequency of DSD Filter
	uint8_t	DSDFilter = CurrentDacConfigPtr[p_Mode][DacConfigBytes::DSDFilter];
	if (DSDFilter == 0)
	{
		pbxDSD.setBitmap(Bitmap(BITMAP_DSDOFF_ID));
	}
	else
	{
		pbxDSD.setBitmap(Bitmap(BITMAP_DSDON_ID));
	}
	pbxDSD.setWidth(80);
	pbxDSD.setHeight(31);
	pbxDSD.invalidate();

	sldrVolume.setValue(GuiItfGetVolume());

	m_ShowDacInfo = false;
}

void MainView::chbxMuteChanged()
{
	GuiItfSetMute(chbxMute.getState() ? 1 : 0);
}

void MainView::sldrVolumeValueChanged(int value)
{
	if (!m_ShowDacInfo)
	{
		GuiItfSetVolume((uint8_t)value);
	}

}
