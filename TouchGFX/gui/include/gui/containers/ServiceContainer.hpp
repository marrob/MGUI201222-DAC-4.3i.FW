#ifndef SERVICECONTAINER_HPP
#define SERVICECONTAINER_HPP

#include <gui_generated/containers/ServiceContainerBase.hpp>

class ServiceContainer : public ServiceContainerBase
{
public:
    ServiceContainer();
    virtual ~ServiceContainer() {}

    virtual void initialize();
     
    virtual void OnClickFactoryReset();
    virtual void OnClickSoftReset();
    void RefreshServiceInfo();
    void GetVersionInfo(); 

#ifdef SIMULATOR

    /*** GUI ***/
    uint8_t GuiItfGetVersion(char** fw, char** uid, char** pcb);
    uint32_t GuiItfGetBootupCnt(void);
    uint32_t GuiItfGetBusUartErrorCnt(void);
    void GuiItfFacotryReset(void);
    void GuiItfSoftReset(void);

    /*** Denpo DAC ***/
    uint32_t GuiItfGetClockHeatedTemperature();
    void GuiItfSetClockHeatedTemperature(uint32_t temp);

#endif


protected:

private:
    /*
     * Callback Declarations
     */
    touchgfx::Callback<ServiceContainer,uint32_t> ValueChangedTriggerCallback;
    /*
     * Callback Handler Declarations
     */
    void OffsetValueChangedCallbackHandler(uint32_t Value);
    void RefresTempRanges(uint32_t heatedTemp);
};

#endif // SERVICECONTAINER_HPP
