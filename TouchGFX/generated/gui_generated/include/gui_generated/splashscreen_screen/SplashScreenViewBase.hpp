/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SPLASHSCREENVIEWBASE_HPP
#define SPLASHSCREENVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/splashscreen_screen/SplashScreenPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/BoxWithBorder.hpp>
#include <touchgfx/widgets/canvas/Line.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/containers/buttons/Buttons.hpp>

class SplashScreenViewBase : public touchgfx::View<SplashScreenPresenter>
{
public:
    SplashScreenViewBase();
    virtual ~SplashScreenViewBase() {}
    virtual void setupScreen();

    /*
     * Custom Actions
     */
    virtual void action1();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Box box1;
    touchgfx::BoxWithBorder boxWithBorder1;
    touchgfx::Line lineMidle;
    touchgfx::PainterRGB565 lineMidlePainter;
    touchgfx::TextArea lblCoreAudio;
    touchgfx::TextArea lblDeviceName;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  btnShowMain;

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<SplashScreenViewBase, const touchgfx::AbstractButtonContainer&> flexButtonCallback;

    /*
     * Callback Handler Declarations
     */
    void flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src);

    /*
     * Canvas Buffer Size
     */
    static const uint16_t CANVAS_BUFFER_SIZE = 12000;
    uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];
};

#endif // SPLASHSCREENVIEWBASE_HPP