#include <gui/containers/ServiceContainer.hpp>


#ifdef SIMULATOR

static uint32_t mUptimeCounterSim;
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

/*** Karuna ***/
uint8_t ServiceContainer::GuiItfGetKarunaVersion(char** fw, char** uid, char** pcb)
{
	char _fw[25] = "220613_1242";
	char _uidI[25] = "0123456789ABCDEF0000002";
	char _pcb[25] = "V02";
	*fw = _fw;
	*uid = _uidI;
	*pcb = _pcb;
	return 0;
}

uint32_t ServiceContainer::GuiItfGetKarunaUptimeCnt()
{
	mUptimeCounterSim++;
	return mUptimeCounterSim;
}

uint32_t ServiceContainer::GuiItfGetKarunaUartErrorCnt(void)
{
	return 2;
}

#ifdef KARUNA_7i
/*** DasClock ***/
uint8_t ServiceContainer::GuiItfGetDasClockVersion(char** fw, char** uid, char** pcb)
{
	char _fw[25] = "220613_1243";
	char _uidI[25] = "0123456789ABCDEF0000003";
	char _pcb[25] = "V03";
	*fw = _fw;
	*uid = _uidI;
	*pcb = _pcb;
	return 0;
}
uint32_t ServiceContainer::GuiItfGetDasClockUptimeCnt()
{
	mUptimeCounterSim++;
	return mUptimeCounterSim;
}
float ServiceContainer::GuiItfGetDasClockMV341Temp()
{
	return 50.0;
}
float ServiceContainer::GuiItfGetDasClockMVOCX1Temp()
{
	return 55.1f;
}
float ServiceContainer::GuiItfGetDasClockMVOCX2Temp()
{
	return 60.2f;
}
float ServiceContainer::GuiItfGetDasClockMV341Current()
{
	return 550.0f;
}
float ServiceContainer::GuiItfGetDasClockMVOCX1Current()
{
	return 160.1f;
}
float ServiceContainer::GuiItfGetDasClockMVOCX2Current()
{
	return 160.2f;
}
float ServiceContainer::GuiItfGetDasClockMainVoltage()
{
	return 12.5f;
}

uint32_t ServiceContainer::GuiItfGetDasClocUartErrorCnt(void)
{
	return 3;
}

#endif

#ifdef KARUNA_43i
/*** Tri Clock ***/

float ServiceContainer::GuiItfGetTempCh1(void)
{
	return 50.42;
}

uint8_t ServiceContainer::GuiItfGetDi1(void) {
	return 1;
}
uint8_t ServiceContainer::GuiItfGetDi11(void) {
	return 0;
}
uint8_t ServiceContainer::GuiItfGetDi13(void) {
	return 0;
}
uint8_t ServiceContainer::GuiItfGetDi15(void) {
	return 0;
}
#endif

uint32_t  ServiceContainer::GuiItfGetDasClockHeatedTemperature()
{
	return mHeatedTemp;
}

void ServiceContainer::GuiItfSetDasClockHeatedTemperature(uint32_t temp)
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

	/*** Karuna ***/
	uint8_t GuiItfGetKarunaVersion(char** fw, char** uid, char** pcb);
	uint32_t GuiItfGetKarunaUptimeCnt();
	uint32_t GuiItfGetKarunaUartErrorCnt(void);


#ifdef KARUNA_7i
	/*** DasClock ***/
	uint8_t GuiItfGetDasClockVersion(char** fw, char** uid, char** pcb);
	uint32_t GuiItfGetDasClockUptimeCnt();

	float GuiItfGetDasClockMV341Temp();
	float GuiItfGetDasClockMVOCX1Temp();
	float GuiItfGetDasClockMVOCX2Temp();
	float GuiItfGetDasClockMV341Current();
	float GuiItfGetDasClockMVOCX1Current();
	float GuiItfGetDasClockMVOCX2Current();
	float GuiItfGetDasClockMainVoltage();

	uint32_t GuiItfGetDasClocUartErrorCnt(void);

#endif 

#ifdef KARUNA_43i
	/*** Tri Clock ***/
	float GuiItfGetTempCh1(void);
	uint8_t GuiItfGetDi1(void);
	uint8_t GuiItfGetDi11(void);
	uint8_t GuiItfGetDi13(void);
	uint8_t GuiItfGetDi15(void);
#endif

	uint32_t GuiItfGetDasClockHeatedTemperature();
	void GuiItfSetDasClockHeatedTemperature(uint32_t temp);
}
#endif


ServiceContainer::ServiceContainer() :
	ValueChangedTriggerCallback(this, &ServiceContainer::OffsetValueChangedCallbackHandler)
{
	OffsetUpDownContainer.setValueChangedTriggerCallback(ValueChangedTriggerCallback);

	uint32_t heatedTemp = GuiItfGetDasClockHeatedTemperature();
	OffsetUpDownContainer.SetValue(heatedTemp);
	RefresTempRanges(heatedTemp);

}

void ServiceContainer::OffsetValueChangedCallbackHandler(uint32_t value)
{
	GuiItfSetDasClockHeatedTemperature(value);
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

	/*** Karuna ***/
	uint32_t uptimeKaruna = GuiItfGetKarunaUptimeCnt();
	Unicode::snprintf(lblKarunaUptimeBuffer, LBLBOOTUPCNT_SIZE, "%d", uptimeKaruna);
	lblKarunaUptime.invalidate();

	uint32_t karunaUartError = GuiItfGetKarunaUartErrorCnt();
	Unicode::snprintf(lblKarunaUartErrorCntBuffer, LBLBOOTUPCNT_SIZE, "%d", karunaUartError);
	lblKarunaUartErrorCnt.invalidate();

#ifdef KARUNA_7i
	/*** DasClock ***/
	uint32_t uptimeDasClock = GuiItfGetDasClockUptimeCnt();
	Unicode::snprintf(lblClockUptimeBuffer, LBLBOOTUPCNT_SIZE, "%d", uptimeDasClock);
	lblClockUptime.invalidate();

	uint32_t dasClocUartError = GuiItfGetDasClocUartErrorCnt();
	Unicode::snprintf(DasClockErrorCntBuffer, LBLBOOTUPCNT_SIZE, "%d", dasClocUartError);
	DasClockErrorCnt.invalidate();

	float mv341_temp = GuiItfGetDasClockMV341Temp();
	Unicode::snprintfFloat(lblClocktemp_0Buffer, LBLBOOTUPCNT_SIZE, "%0.2f", mv341_temp);
	lblClocktemp_0.invalidate();

	float ocxo_1_temp = GuiItfGetDasClockMVOCX1Temp();
	Unicode::snprintfFloat(lblClocktemp_1Buffer, LBLBOOTUPCNT_SIZE, "%0.2f", ocxo_1_temp);
	lblClocktemp_1.invalidate();

	float ocxo_2_temp = GuiItfGetDasClockMVOCX2Temp();
	Unicode::snprintfFloat(lblClocktemp_2Buffer, LBLBOOTUPCNT_SIZE, "%0.2f", ocxo_2_temp);
	lblClocktemp_2.invalidate();

	float mv341_Current = GuiItfGetDasClockMV341Current();
	Unicode::snprintfFloat(lblClockCurrent_0Buffer, LBLBOOTUPCNT_SIZE, "%0.2f", mv341_Current);
	lblClockCurrent_0.invalidate();

	float ocxo1_Current = GuiItfGetDasClockMVOCX1Current();
	Unicode::snprintfFloat(lblClockCurrent_1Buffer, LBLBOOTUPCNT_SIZE, "%0.2f", ocxo1_Current);
	lblClockCurrent_1.invalidate();


	float ocxo_2_Current = GuiItfGetDasClockMVOCX2Current();
	Unicode::snprintfFloat(lblClockCurrent_2Buffer, LBLBOOTUPCNT_SIZE, "%0.2f", ocxo_2_Current);
	lblClockCurrent_2.invalidate();

	float mainVoltage = GuiItfGetDasClockMainVoltage();
	Unicode::snprintfFloat(lblDASClockSupplyVoltageBuffer, LBLBOOTUPCNT_SIZE, "%0.2f", mainVoltage);
	lblDASClockSupplyVoltage.invalidate();
#endif

#ifdef KARUNA_43i
	/*** Tri Clock ***/

	//TEMP
	float mv341_temp = GuiItfGetTempCh1();
	Unicode::snprintfFloat(lblClocktemp_0Buffer, LBLBOOTUPCNT_SIZE, "%0.2f", mv341_temp);
	lblClocktemp_0.invalidate();

	//LOCK
	//mIs24Locked = GuiItfGetDi13();
	//mIs22Locked = GuiItfGetDi15();
	//mIs245Locked = GuiItfGetDi1();
	//mIsIntExt = GuiItfGetDi11();

	char lock[] = "Locked";
	char unlock[] = "Unlocked";

	char* value0 = GuiItfGetDi13() ? lock : unlock;
	Unicode::UnicodeChar uni_value0[LBLCLOCKLOCK_0_SIZE];
	Unicode::fromUTF8((const uint8_t*)value0, uni_value0, sizeof(uni_value0));
	Unicode::snprintf(lblClockLock_0Buffer, LBLCLOCKLOCK_0_SIZE, "%s", uni_value0);
	lblClockLock_0.invalidate();

	char* value1 = GuiItfGetDi15() ? lock : unlock;
	Unicode::UnicodeChar uni_value1[LBLCLOCKLOCK_1_SIZE];
	Unicode::fromUTF8((const uint8_t*)value1, uni_value1, sizeof(uni_value1));
	Unicode::snprintf(lblClockLock_1Buffer, LBLCLOCKLOCK_1_SIZE, "%s", uni_value1);
	lblClockLock_1.invalidate();


	char* value2 = GuiItfGetDi1() ? lock : unlock;
	Unicode::UnicodeChar uni_value2[LBLCLOCKLOCK_2_SIZE];
	Unicode::fromUTF8((const uint8_t*)value2, uni_value2, sizeof(uni_value2));
	Unicode::snprintf(lblClockLock_2Buffer, LBLCLOCKLOCK_2_SIZE, "%s", uni_value2);
	lblClockLock_2.invalidate();

	//INT - EXT

	char exter[] = "External";
	char inter[] = "Internal";

	char* valueIE = GuiItfGetDi11() ? exter : inter;
	Unicode::UnicodeChar uni_valueIE[LBLCLOCKCURRENT_INTEXT_SIZE];
	Unicode::fromUTF8((const uint8_t*)valueIE, uni_valueIE, sizeof(uni_valueIE));
	Unicode::snprintf(lblClockCurrent_IntextBuffer, LBLCLOCKCURRENT_INTEXT_SIZE, "%s", uni_valueIE);
	lblClockCurrent_Intext.invalidate();
#endif

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

	GuiItfGetKarunaVersion(&fw, &uid, &pcb);
	Unicode::fromUTF8((const uint8_t*)fw, uni_fw, sizeof(uni_fw));
	Unicode::fromUTF8((const uint8_t*)uid, uni_uid, sizeof(uni_uid));
	Unicode::fromUTF8((const uint8_t*)pcb, uni_pcb, sizeof(uni_pcb));
	Unicode::snprintf(lblKarunaFwVersionBuffer, LBLKARUNAFWVERSION_SIZE, "%s-%s-%s", uni_fw, uni_uid, uni_pcb);
	lblKarunaFwVersion.invalidate();

#ifdef KARUNA_7i
	GuiItfGetDasClockVersion(&fw, &uid, &pcb);
	Unicode::fromUTF8((const uint8_t*)fw, uni_fw, sizeof(uni_fw));
	Unicode::fromUTF8((const uint8_t*)uid, uni_uid, sizeof(uni_uid));
	Unicode::fromUTF8((const uint8_t*)pcb, uni_pcb, sizeof(uni_pcb));
	Unicode::snprintf(lblDASClockFwVersionBuffer, LBLDASCLOCKFWVERSION_SIZE, "%s-%s-%s", uni_fw, uni_uid, uni_pcb);
	lblDASClockFwVersion.invalidate();
#endif
}

void ServiceContainer::OnClickFactoryReset()
{
	GuiItfFacotryReset();
}

void ServiceContainer::OnClickSoftReset()
{
	GuiItfSoftReset();
}
