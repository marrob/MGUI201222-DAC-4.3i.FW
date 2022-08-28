/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/DIContainerBase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>

DIContainerBase::DIContainerBase()
{
    setWidth(144);
    setHeight(40);
    lblDO.setXY(0, 0);
    lblDO.setColor(touchgfx::Color::getColorFromRGB(100, 100, 100));
    lblDO.setLinespacing(0);
    lblDO.setTypedText(touchgfx::TypedText(T___SINGLEUSE_39RD));

    circLed.setPosition(98, 0, 40, 40);
    circLed.setCenter(20, 20);
    circLed.setRadius(20);
    circLed.setLineWidth(0);
    circLed.setArc(0, 360);
    circLedPainter.setColor(touchgfx::Color::getColorFromRGB(150, 118, 73));
    circLed.setPainter(circLedPainter);

    add(lblDO);
    add(circLed);
}

void DIContainerBase::initialize()
{

}

