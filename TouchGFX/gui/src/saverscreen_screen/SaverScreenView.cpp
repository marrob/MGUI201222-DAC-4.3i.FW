#include <gui/saverscreen_screen/SaverScreenView.hpp>
#include <time.h>
#include <stdio.h>
#include <string.h>

int mTickSaverCount;
char FormatStr[10];
char BitDepth[10];
char Freq[12];
int contDir = -1; 

uint8_t  mSaverPreDacMode;

#ifdef SIMULATOR

time_t simSaverDateTime;
static uint8_t simDACSaverMode = DAC_DSD_256;

void SaverScreenView::GuiItfGetRtc(time_t* dt)
{
	if (simSaverDateTime == 0)
	{
		tm tm_info;
		tm_info.tm_year = 2022 - 1900;
		tm_info.tm_mon = 6 - 1;
		tm_info.tm_mday = 16;
		tm_info.tm_hour = 20;
		tm_info.tm_min = 21;
		tm_info.tm_sec = 22;
		tm_info.tm_isdst = 0;

		simSaverDateTime = mktime(&tm_info);
	}
	simSaverDateTime++;
	*dt = simSaverDateTime;
} 

uint8_t SaverScreenView::GuiItfGetConfig()
{
	return simDACSaverMode;
}

#else
extern "C"
{
	/*** RTC ***/
	void GuiItfGetRtc(time_t* dt); 
	uint8_t GuiItfGetConfig();
}
#endif


SaverScreenView::SaverScreenView()
{

}

void SaverScreenView::setupScreen()
{
	SaverScreenViewBase::setupScreen();

	RequestCurrentTime();
	RefreshCurrentAudio();
}

void SaverScreenView::tearDownScreen()
{
	SaverScreenViewBase::tearDownScreen();
}

void SaverScreenView::handleTickEvent()
{
	mTickSaverCount++;

	//Wait for 0.5sec
	if (mTickSaverCount % 10 == 0)
	{
		RequestCurrentTime();
		RefreshCurrentAudio(); 
	}

	if (mTickSaverCount % (60) == 0)
	{ 
		if (containerInfo.getY() < 0)
		{
			contDir = 1;
		}
		else if(containerInfo.getY() + containerInfo.getHeight() > this->getScreenHeight())
		{
			contDir = -1;
		}
		containerInfo.moveRelative(0, contDir*1); 
	}
}
  
void SaverScreenView::RequestCurrentTime()
{
	time_t dtp;
	GuiItfGetRtc(&dtp);
	struct tm* tm_info = gmtime(&dtp);
	char strDateTime[LBLDATETIME_SIZE];
	strftime(strDateTime, LBLDATETIME_SIZE, "%d.%m.%Y  %H:%M", tm_info);

	Unicode::UnicodeChar uni_DateTime[25];
	Unicode::fromUTF8((const uint8_t*)strDateTime, uni_DateTime, LBLDATETIME_SIZE);
	Unicode::snprintf(lblDateTimeBuffer, LBLDATETIME_SIZE, "%s", uni_DateTime);
	lblDateTime.invalidate();
}

void SaverScreenView::RefreshCurrentAudio()
{
	//Read audio format
	uint8_t  actualDacMode = GuiItfGetConfig();
	if (actualDacMode != mSaverPreDacMode)
	{
		SetDSDPCM(actualDacMode);
		//SetBitDepth(KRN_STAT);
		SetFreq(actualDacMode); 
	}
	mSaverPreDacMode = actualDacMode; 

	char audioFormat[LBLAUDIOFORMAT_SIZE];
	snprintf(audioFormat, LBLAUDIOFORMAT_SIZE, "%s - %s", SetDSDPCM(actualDacMode), SetFreq(actualDacMode));

	Unicode::UnicodeChar uniText[LBLAUDIOFORMAT_SIZE];
	Unicode::fromUTF8((const uint8_t*)audioFormat, uniText, LBLAUDIOFORMAT_SIZE);
	Unicode::snprintf(lblAudioFormatBuffer, LBLAUDIOFORMAT_SIZE, "%s", uniText);
}
    
char* SaverScreenView::SetDSDPCM(uint8_t p_AudiFormat)
{
	static char format[5];
	static char freq[5];
	bool isDsd = p_AudiFormat >= DAC_DSD_64;

	if (isDsd)
	{ 		 
		{
			strcpy(format, "DSD"); 
		} 
		 
		switch (p_AudiFormat)
		{
		case DAC_DSD_64:
		{
			strcpy(freq, "64"); 
		}break;
		case DAC_DSD_128:
		{	
			strcpy(freq, "128");
		}break;
		case DAC_DSD_256:
		{
			strcpy(freq, "256");
		}break;
		case DAC_DSD_512:
		{
			strcpy(freq, "512");
		}break;

		default:
			break;
		}
	}
	else
	{
		strcpy(format, "PCM"); 
	} 

	snprintf(FormatStr, 10, "%s%s", format, freq);

	return FormatStr;
}

char* SaverScreenView::SetFreq(uint8_t p_AudiFormat)
{
	strcpy(Freq, "N.a.");

	switch (p_AudiFormat)
	{
	case DAC_PCM_44_1KHZ:
	{
		strcpy(Freq, "44.1 kHz");
	}break;
	case DAC_PCM_48_0KHZ:
	{
		strcpy(Freq, "48 kHz");
	}break;
	case DAC_PCM_88_2KHZ:
	{
		strcpy(Freq, "88.2 kHz");
	}break;
	case DAC_PCM_96_0KHZ:
	{
		strcpy(Freq, "96 kHz");
	}break;
	case DAC_PCM_176_4KHZ:
	{
		strcpy(Freq, "176.4 kHz");
	}break;
	case DAC_PCM_192_KHZ:
	{
		strcpy(Freq, "192 kHz");
	}break;
	case DAC_PCM_362_8KHZ:
	{
		strcpy(Freq, "352.8 kHz");
	}break;
	case DAC_PCM_384_0KHZ:
	{
		strcpy(Freq, "384 kHz");
	}break;
	case DAC_PCM_705_6KHZ:
	{
		strcpy(Freq, "705.6 kHz");
	}break;
	case DAC_PCM_768_0KHZ:
	{
		strcpy(Freq, "768 kHz");
	}break;
	case DAC_DSD_64:
	{
		strcpy(Freq, "2.8 MHz");
	}break;
	case DAC_DSD_128:
	{
		strcpy(Freq, "5.8 MHz");
	}break;
	case DAC_DSD_256:
	{
		strcpy(Freq, "11.2 MHz");
	}break;
	case DAC_DSD_512:
	{
		strcpy(Freq, "22.6 MHz");
	}break;

	default:
		break;
	}

	return Freq;
}
