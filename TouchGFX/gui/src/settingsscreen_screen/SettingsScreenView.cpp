#include <gui/settingsscreen_screen/SettingsScreenView.hpp>

int mTickGUICount;
bool mSetupLoaded;

#ifdef SIMULATOR
 
#else
extern "C"
{
	 
}
#endif


SettingsScreenView::SettingsScreenView()
{
	mSetupLoaded = false;
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
