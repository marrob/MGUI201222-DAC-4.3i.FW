#include <gui/settingsscreen_screen/SettingsScreenView.hpp>

int mTickGUICount;
bool mSetupLoaded;

#ifdef SIMULATOR

static uint8_t simOutputState;
static uint8_t simMCLKState;
 
#else
extern "C"
{
	 
}
#endif


SettingsScreenView::SettingsScreenView()
{
	mSetupLoaded = false;
	//if (GuiItfGetKarunaOutputsAllEnabledAfterStart())
	//	radioButtonGroup1.setSelected(rdbtnEnableAll);
	//else
	//	radioButtonGroup1.setSelected(rdbtnLastState);

	//if (GuiItfGetKarunaMasterClkOnI2SIsEnabled())
	//	chbxMCLKON.forceState(true);
	//else
	//	chbxMCLKON.forceState(false);

	mSetupLoaded = true;

}

void SettingsScreenView::setupScreen()
{
	SettingsScreenViewBase::setupScreen(); 
}

void SettingsScreenView::tearDownScreen()
{
	SettingsScreenViewBase::tearDownScreen();
}