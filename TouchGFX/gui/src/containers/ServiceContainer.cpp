#include <gui/containers/ServiceContainer.hpp>


#ifdef SIMULATOR

static uint32_t mHeatedTemp = 30;

/*** GUI ***/
uint8_t ServiceContainer::GuiItfGetVersion(char** fw, char** uid, char** pcb)
{
	char _fw[25] = "220613_1241";
	char _uidI[25] = "0123456789ABCDEF0000001";
	char _pcb[25] = "V01";
	*fw = _fw;
	*uid = _uidI;
	*pcb = _pcb;
	return 0;
}

uint32_t ServiceContainer::GuiItfGetBootupCnt(void)
{
	return 10000;
}

uint32_t ServiceContainer::GuiItfGetBusUartErrorCnt(void)
{
	return 1;
}

void ServiceContainer::GuiItfFacotryReset(void)
{

}

void ServiceContainer::GuiItfSoftReset(void)
{

}

uint32_t  ServiceContainer::GuiItfGetClockHeatedTemperature()
{
	return mHeatedTemp;
}

void ServiceContainer::GuiItfSetClockHeatedTemperature(uint32_t temp)
{
	mHeatedTemp = temp;
}

#else
extern "C"
{
	/*** GUI ***/
	uint8_t GuiItfGetVersion(char** fw, char** uid, char** pcb);
	uint32_t GuiItfGetBootupCnt(void);
	uint32_t GuiItfGetBusUartErrorCnt(void);
	void GuiItfFacotryReset(void);
	void GuiItfSoftReset(void);
	uint32_t GuiItfGetClockHeatedTemperature();
	void GuiItfSetClockHeatedTemperature(uint32_t temp);
}
#endif


ServiceContainer::ServiceContainer() :
	ValueChangedTriggerCallback(this, &ServiceContainer::OffsetValueChangedCallbackHandler)
{
	OffsetUpDownContainer.setValueChangedTriggerCallback(ValueChangedTriggerCallback);
	uint32_t heatedTemp = GuiItfGetClockHeatedTemperature();
	OffsetUpDownContainer.SetValue(heatedTemp);
	RefresTempRanges(heatedTemp); 
}

void ServiceContainer::OffsetValueChangedCallbackHandler(uint32_t value)
{
	GuiItfSetClockHeatedTemperature(value);
	//0-30 < 30-40 < 40-50 <<< 50-70 >>> 70-75 > 75-80 > 80
	int heatedTemp = value; 
	RefresTempRanges(heatedTemp);
}

void ServiceContainer::RefresTempRanges(uint32_t heatedTemp)
{
	Unicode::snprintf(lblTempOffsetRangesBuffer, LBLTEMPOFFSETRANGES_SIZE, "..%d < %d-%d < %d-%d <<< %d-%d >>> %d-%d > %d-%d > %d..",
		heatedTemp - 30, heatedTemp - 30, heatedTemp - 20, heatedTemp - 20, heatedTemp - 10,
		heatedTemp - 10, heatedTemp + 10,
		heatedTemp + 10, heatedTemp + 15, heatedTemp + 15, heatedTemp + 20, heatedTemp + 20);
	lblTempOffsetRanges.invalidate();
}


void ServiceContainer::initialize()
{
	ServiceContainerBase::initialize();
	GetVersionInfo();
}

void ServiceContainer::RefreshServiceInfo()
{
	/*** Gui ***/
	uint32_t bootUp = GuiItfGetBootupCnt();
	Unicode::snprintf(lblBootupCntBuffer, LBLBOOTUPCNT_SIZE, "%d", bootUp);
	lblBootupCnt.invalidate();
	uint32_t busUartError = GuiItfGetBusUartErrorCnt();
	Unicode::snprintf(lblBusUartErrorCntBuffer, LBLBOOTUPCNT_SIZE, "%d", busUartError);
	lblBusUartErrorCnt.invalidate();
}

void ServiceContainer::GetVersionInfo()
{
	char* fw = nullptr;
	char* uid = nullptr;
	char* pcb = nullptr;
	Unicode::UnicodeChar uni_fw[LBLGUIFWVERSION_SIZE];
	Unicode::UnicodeChar uni_uid[LBLGUIFWVERSION_SIZE];
	Unicode::UnicodeChar uni_pcb[LBLGUIFWVERSION_SIZE];

	GuiItfGetVersion(&fw, &uid, &pcb);
	Unicode::fromUTF8((const uint8_t*)fw, uni_fw, sizeof(uni_fw));
	Unicode::fromUTF8((const uint8_t*)uid, uni_uid, sizeof(uni_uid));
	Unicode::fromUTF8((const uint8_t*)pcb, uni_pcb, sizeof(uni_pcb));
	Unicode::snprintf(lblGUIFwVersionBuffer, LBLGUIFWVERSION_SIZE, "%s-%s-%s", uni_fw, uni_uid, uni_pcb);
	lblGUIFwVersion.invalidate();

}

void ServiceContainer::OnClickFactoryReset()
{
	GuiItfFacotryReset();
}

void ServiceContainer::OnClickSoftReset()
{
	GuiItfSoftReset();
}
