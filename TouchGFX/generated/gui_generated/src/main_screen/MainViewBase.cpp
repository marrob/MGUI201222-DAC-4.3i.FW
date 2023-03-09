/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/main_screen/MainViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>


MainViewBase::MainViewBase() :
    buttonCallback(this, &MainViewBase::buttonCallbackHandler),
    flexButtonCallback(this, &MainViewBase::flexButtonCallbackHandler),
    sliderValueChangedCallback(this, &MainViewBase::sliderValueChangedCallbackHandler),
    radioButtonSelectedCallback(this, &MainViewBase::radioButtonSelectedCallbackHandler),
    showInputsEndedCallback(this, &MainViewBase::showInputsEndedCallbackHandler),
    hideInputsEndedCallback(this, &MainViewBase::hideInputsEndedCallbackHandler)
{

    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);

    __background.setPosition(0, 0, 800, 480);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    box1.setPosition(0, 0, 800, 480);
    box1.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    boxWithBorder1.setPosition(4, 80, 792, 320);
    boxWithBorder1.setColor(touchgfx::Color::getColorFromRGB(25, 25, 25));
    boxWithBorder1.setBorderColor(touchgfx::Color::getColorFromRGB(100, 100, 100));
    boxWithBorder1.setBorderSize(1);

    containerVolume.setPosition(9, 80, 271, 264);

    pbxSwap.setBitmap(touchgfx::Bitmap(BITMAP_SWAPON_ID));
    pbxSwap.setPosition(144, 158, 60, 33);
    pbxSwap.setScalingAlgorithm(touchgfx::ScalableImage::BILINEAR_INTERPOLATION);
    containerVolume.add(pbxSwap);

    btnVolume.setWildcardText(TypedText(T___SINGLEUSE_9CVP));
    btnVolume.setWildcardTextBuffer(TypedText(T___SINGLEUSE_UAA6).getText());
    btnVolume.setWildcardTextPosition(0, -7, 174, 72);
    btnVolume.setWildcardTextColors(touchgfx::Color::getColorFromRGB(150, 118, 73), touchgfx::Color::getColorFromRGB(10, 10, 10));
    btnVolume.setPosition(52, 96, 174, 72);
    btnVolume.setAction(flexButtonCallback);
    containerVolume.add(btnVolume);

    lblDescVolume.setPosition(86, 11, 106, 28);
    lblDescVolume.setColor(touchgfx::Color::getColorFromRGB(100, 100, 100));
    lblDescVolume.setLinespacing(0);
    lblDescVolume.setTypedText(touchgfx::TypedText(T___SINGLEUSE_S2EB));
    containerVolume.add(lblDescVolume);

    containerFormat.setPosition(265, 80, 265, 264);

    lblDescFormat.setPosition(79, 11, 106, 28);
    lblDescFormat.setColor(touchgfx::Color::getColorFromRGB(100, 100, 100));
    lblDescFormat.setLinespacing(0);
    lblDescFormat.setTypedText(touchgfx::TypedText(T___SINGLEUSE_GOXD));
    containerFormat.add(lblDescFormat);

    lblValueFormat.setPosition(-3, 100, 268, 52);
    lblValueFormat.setColor(touchgfx::Color::getColorFromRGB(150, 118, 73));
    lblValueFormat.setLinespacing(0);
    Unicode::snprintf(lblValueFormatBuffer, LBLVALUEFORMAT_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_G2P3).getText());
    lblValueFormat.setWildcard(lblValueFormatBuffer);
    lblValueFormat.setTypedText(touchgfx::TypedText(T___SINGLEUSE_8EJL));
    containerFormat.add(lblValueFormat);

    lblDSDValue.setPosition(121, 158, 96, 33);
    lblDSDValue.setColor(touchgfx::Color::getColorFromRGB(150, 118, 73));
    lblDSDValue.setLinespacing(0);
    Unicode::snprintf(lblDSDValueBuffer, LBLDSDVALUE_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_4TRH).getText());
    lblDSDValue.setWildcard(lblDSDValueBuffer);
    lblDSDValue.setTypedText(touchgfx::TypedText(T___SINGLEUSE_IO3K));
    containerFormat.add(lblDSDValue);

    lblDSDValue_2.setPosition(78, 158, 71, 33);
    lblDSDValue_2.setVisible(false);
    lblDSDValue_2.setColor(touchgfx::Color::getColorFromRGB(150, 118, 73));
    lblDSDValue_2.setLinespacing(0);
    lblDSDValue_2.setTypedText(touchgfx::TypedText(T___SINGLEUSE_TVNE));
    containerFormat.add(lblDSDValue_2);

    containerFreq.setPosition(519, 80, 275, 264);

    lblSRCFreq.setPosition(124, 158, 110, 33);
    lblSRCFreq.setColor(touchgfx::Color::getColorFromRGB(150, 118, 73));
    lblSRCFreq.setLinespacing(0);
    Unicode::snprintf(lblSRCFreqBuffer, LBLSRCFREQ_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_QH1M).getText());
    lblSRCFreq.setWildcard(lblSRCFreqBuffer);
    lblSRCFreq.setTypedText(touchgfx::TypedText(T___SINGLEUSE_ZIQ7));
    containerFreq.add(lblSRCFreq);

    lblDescFreq.setPosition(52, 11, 166, 28);
    lblDescFreq.setColor(touchgfx::Color::getColorFromRGB(100, 100, 100));
    lblDescFreq.setLinespacing(0);
    lblDescFreq.setTypedText(touchgfx::TypedText(T___SINGLEUSE_LPXD));
    containerFreq.add(lblDescFreq);

    lblValueFreq.setPosition(9, 100, 253, 52);
    lblValueFreq.setColor(touchgfx::Color::getColorFromRGB(150, 118, 73));
    lblValueFreq.setLinespacing(0);
    Unicode::snprintf(lblValueFreqBuffer, LBLVALUEFREQ_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_3FKW).getText());
    lblValueFreq.setWildcard(lblValueFreqBuffer);
    lblValueFreq.setTypedText(touchgfx::TypedText(T___SINGLEUSE_YD6A));
    containerFreq.add(lblValueFreq);

    pbxSRCOn.setBitmap(touchgfx::Bitmap(BITMAP_RIGHTSRC_ID));
    pbxSRCOn.setPosition(84, 158, 32, 32);
    pbxSRCOn.setScalingAlgorithm(touchgfx::ScalableImage::BILINEAR_INTERPOLATION);
    containerFreq.add(pbxSRCOn);

    box22.setPosition(580, 4, 72, 72);
    box22.setColor(touchgfx::Color::getColorFromRGB(150, 118, 73));
    box22.setBorderColor(touchgfx::Color::getColorFromRGB(64, 64, 64));
    box22.setBorderSize(5);

    img22.setBitmap(touchgfx::Bitmap(BITMAP_CLOCK22_80X80_I_ID));
    img22.setPosition(580, 4, 72, 72);
    img22.setScalingAlgorithm(touchgfx::ScalableImage::NEAREST_NEIGHBOR);

    box24.setPosition(508, 4, 72, 72);
    box24.setColor(touchgfx::Color::getColorFromRGB(150, 118, 73));
    box24.setBorderColor(touchgfx::Color::getColorFromRGB(64, 64, 64));
    box24.setBorderSize(5);

    img24.setBitmap(touchgfx::Bitmap(BITMAP_CLOCK240_80X80_I_ID));
    img24.setPosition(508, 4, 72, 72);
    img24.setScalingAlgorithm(touchgfx::ScalableImage::NEAREST_NEIGHBOR);

    box245.setPosition(652, 4, 72, 72);
    box245.setColor(touchgfx::Color::getColorFromRGB(150, 118, 73));
    box245.setBorderColor(touchgfx::Color::getColorFromRGB(64, 64, 64));
    box245.setBorderSize(5);

    img245.setBitmap(touchgfx::Bitmap(BITMAP_CLOCK245_80X80_I_ID));
    img245.setPosition(652, 4, 72, 72);
    img245.setScalingAlgorithm(touchgfx::ScalableImage::NEAREST_NEIGHBOR);

    boxIntExt.setPosition(724, 4, 72, 72);
    boxIntExt.setColor(touchgfx::Color::getColorFromRGB(64, 64, 64));
    boxIntExt.setBorderColor(touchgfx::Color::getColorFromRGB(64, 64, 64));
    boxIntExt.setBorderSize(5);

    imgIntExt.setBitmap(touchgfx::Bitmap(BITMAP_CLOCKEXT_80X80_I_ID));
    imgIntExt.setPosition(724, 4, 72, 72);
    imgIntExt.setScalingAlgorithm(touchgfx::ScalableImage::NEAREST_NEIGHBOR);

    btnSettings.setBoxWithBorderPosition(0, 0, 394, 72);
    btnSettings.setBorderSize(1);
    btnSettings.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 0, 0), touchgfx::Color::getColorFromRGB(32, 32, 32), touchgfx::Color::getColorFromRGB(100, 100, 100), touchgfx::Color::getColorFromRGB(100, 100, 100));
    btnSettings.setBitmaps(Bitmap(BITMAP_SETTINGS_ID), Bitmap(BITMAP_SETTINGS_ID));
    btnSettings.setBitmapXY(20, 5);
    btnSettings.setText(TypedText(T___SINGLEUSE_VB1R));
    btnSettings.setTextPosition(-20, 20, 394, 72);
    btnSettings.setTextColors(touchgfx::Color::getColorFromRGB(150, 118, 73), touchgfx::Color::getColorFromRGB(64, 64, 64));
    btnSettings.setPosition(4, 404, 394, 72);
    btnSettings.setAction(flexButtonCallback);

    btnDisplay.setBoxWithBorderPosition(0, 0, 394, 72);
    btnDisplay.setBorderSize(1);
    btnDisplay.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 0, 0), touchgfx::Color::getColorFromRGB(32, 32, 32), touchgfx::Color::getColorFromRGB(100, 100, 100), touchgfx::Color::getColorFromRGB(100, 100, 100));
    btnDisplay.setBitmaps(Bitmap(BITMAP_DISPLAY_ID), Bitmap(BITMAP_DISPLAY_ID));
    btnDisplay.setBitmapXY(20, 5);
    btnDisplay.setText(TypedText(T___SINGLEUSE_SPLI));
    btnDisplay.setTextPosition(-20, 20, 394, 72);
    btnDisplay.setTextColors(touchgfx::Color::getColorFromRGB(150, 118, 73), touchgfx::Color::getColorFromRGB(64, 64, 64));
    btnDisplay.setPosition(402, 404, 394, 72);
    btnDisplay.setAction(flexButtonCallback);

    lblDateTime.setPosition(483, 304, 298, 34);
    lblDateTime.setVisible(false);
    lblDateTime.setColor(touchgfx::Color::getColorFromRGB(100, 100, 100));
    lblDateTime.setLinespacing(0);
    Unicode::snprintf(lblDateTimeBuffer, LBLDATETIME_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_GJVC).getText());
    lblDateTime.setWildcard(lblDateTimeBuffer);
    lblDateTime.setTypedText(touchgfx::TypedText(T___SINGLEUSE_HGJP));

    btnShowSaver.setBoxWithBorderPosition(0, 0, 18, 21);
    btnShowSaver.setBorderSize(5);
    btnShowSaver.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 0, 0), touchgfx::Color::getColorFromRGB(0, 0, 0), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    btnShowSaver.setPosition(4, 455, 18, 21);
    btnShowSaver.setVisible(false);
    btnShowSaver.setAction(flexButtonCallback);

    containerTemperature.setPosition(325, 8, 150, 65);

    circTemp3.setPosition(100, 8, 50, 50);
    circTemp3.setCenter(25, 25);
    circTemp3.setRadius(20);
    circTemp3.setLineWidth(0);
    circTemp3.setArc(0, 360);
    circTemp3Painter.setColor(touchgfx::Color::getColorFromRGB(64, 64, 64));
    circTemp3.setPainter(circTemp3Painter);
    containerTemperature.add(circTemp3);

    circTemp2.setPosition(50, 8, 50, 50);
    circTemp2.setCenter(25, 25);
    circTemp2.setRadius(20);
    circTemp2.setLineWidth(0);
    circTemp2.setArc(0, 360);
    circTemp2Painter.setColor(touchgfx::Color::getColorFromRGB(150, 118, 73));
    circTemp2.setPainter(circTemp2Painter);
    containerTemperature.add(circTemp2);

    circTemp1.setPosition(0, 8, 50, 50);
    circTemp1.setCenter(25, 25);
    circTemp1.setRadius(20);
    circTemp1.setLineWidth(0);
    circTemp1.setArc(0, 360);
    circTemp1Painter.setColor(touchgfx::Color::getColorFromRGB(150, 118, 73));
    circTemp1.setPainter(circTemp1Painter);
    containerTemperature.add(circTemp1);

    containerDACFilter.setPosition(5, 334, 790, 56);

    pbxPhase.setBitmap(touchgfx::Bitmap(BITMAP_PHASEON_ID));
    pbxPhase.setPosition(30, 7, 80, 43);
    pbxPhase.setScalingAlgorithm(touchgfx::ScalableImage::BILINEAR_INTERPOLATION);
    containerDACFilter.add(pbxPhase);

    pbxPrec.setBitmap(touchgfx::Bitmap(BITMAP_HIGHPRECON_ID));
    pbxPrec.setPosition(160, 7, 80, 43);
    pbxPrec.setScalingAlgorithm(touchgfx::ScalableImage::BILINEAR_INTERPOLATION);
    containerDACFilter.add(pbxPrec);

    tbxDeEmp.setPosition(420, 17, 80, 22);
    tbxDeEmp.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    tbxDeEmp.setLinespacing(0);
    tbxDeEmp.setTypedText(touchgfx::TypedText(T___SINGLEUSE_9TVO));
    containerDACFilter.add(tbxDeEmp);

    pbxFIR.setBitmap(touchgfx::Bitmap(BITMAP_FIRON_ID));
    pbxFIR.setPosition(290, 7, 80, 43);
    pbxFIR.setScalingAlgorithm(touchgfx::ScalableImage::BILINEAR_INTERPOLATION);
    containerDACFilter.add(pbxFIR);

    pbxDeltaSigma.setBitmap(touchgfx::Bitmap(BITMAP_DELTASIGMAON_ID));
    pbxDeltaSigma.setPosition(550, 13, 80, 31);
    pbxDeltaSigma.setScalingAlgorithm(touchgfx::ScalableImage::BILINEAR_INTERPOLATION);
    containerDACFilter.add(pbxDeltaSigma);

    pbxDSD.setBitmap(touchgfx::Bitmap(BITMAP_DSDOFF_ID));
    pbxDSD.setPosition(680, 13, 80, 31);
    pbxDSD.setScalingAlgorithm(touchgfx::ScalableImage::BILINEAR_INTERPOLATION);
    containerDACFilter.add(pbxDSD);

    containerSelectInput.setPosition(0, 0, 295, 80);

    boxWithBorder4.setPosition(4, 4, 285, 72);
    boxWithBorder4.setVisible(false);
    boxWithBorder4.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    boxWithBorder4.setBorderColor(touchgfx::Color::getColorFromRGB(100, 100, 100));
    boxWithBorder4.setBorderSize(1);
    containerSelectInput.add(boxWithBorder4);

    btnHideInputs.setText(TypedText(T___SINGLEUSE_WPEH));
    btnHideInputs.setTextPosition(-20, 20, 210, 72);
    btnHideInputs.setTextColors(touchgfx::Color::getColorFromRGB(150, 118, 73), touchgfx::Color::getColorFromRGB(64, 64, 64));
    btnHideInputs.setPosition(79, 4, 210, 72);
    btnHideInputs.setAction(flexButtonCallback);
    containerSelectInput.add(btnHideInputs);

    btnSelectInput.setBoxWithBorderPosition(0, 1, 200, 67);
    btnSelectInput.setBorderSize(5);
    btnSelectInput.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 0, 0), touchgfx::Color::getColorFromRGB(0, 0, 0), touchgfx::Color::getColorFromRGB(0, 0, 0), touchgfx::Color::getColorFromRGB(0, 0, 0));
    btnSelectInput.setText(TypedText(T___SINGLEUSE_HIE3));
    btnSelectInput.setTextPosition(-20, 20, 210, 72);
    btnSelectInput.setTextColors(touchgfx::Color::getColorFromRGB(150, 118, 73), touchgfx::Color::getColorFromRGB(64, 64, 64));
    btnSelectInput.setPosition(79, 4, 210, 72);
    btnSelectInput.setAction(flexButtonCallback);
    containerSelectInput.add(btnSelectInput);

    boxinput.setPosition(9, 8, 64, 64);
    boxinput.setColor(touchgfx::Color::getColorFromRGB(150, 118, 73));
    containerSelectInput.add(boxinput);

    pbxInput.setBitmap(touchgfx::Bitmap(BITMAP_BNC_80X80_FB_ID));
    pbxInput.setPosition(9, 8, 64, 64);
    pbxInput.setScalingAlgorithm(touchgfx::ScalableImage::BILINEAR_INTERPOLATION);
    containerSelectInput.add(pbxInput);

    containerInputs.setPosition(305, -88, 491, 79);

    boxWithBorder3.setPosition(0, 4, 491, 71);
    boxWithBorder3.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    boxWithBorder3.setBorderColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    boxWithBorder3.setBorderSize(5);
    containerInputs.add(boxWithBorder3);

    bxInput.setPosition(138, 7, 64, 64);
    bxInput.setColor(touchgfx::Color::getColorFromRGB(150, 118, 73));
    containerInputs.add(bxInput);

    rdbBNC.setXY(282, 7);
    rdbBNC.setBitmaps(touchgfx::Bitmap(BITMAP_BNC_80X80_S_ID), touchgfx::Bitmap(BITMAP_BNC_80X80_FB_ID), touchgfx::Bitmap(BITMAP_BNC_80X80_FB_ID), touchgfx::Bitmap(BITMAP_BNC_80X80_S_ID));
    rdbBNC.setSelected(false);
    rdbBNC.setDeselectionEnabled(false);
    containerInputs.add(rdbBNC);

    rdbRCA.setXY(354, 7);
    rdbRCA.setBitmaps(touchgfx::Bitmap(BITMAP_RCA_80X80_S_ID), touchgfx::Bitmap(BITMAP_RCA_80X80_FB_ID), touchgfx::Bitmap(BITMAP_RCA_80X80_FB_ID), touchgfx::Bitmap(BITMAP_RCA_80X80_S_ID));
    rdbRCA.setSelected(false);
    rdbRCA.setDeselectionEnabled(false);
    containerInputs.add(rdbRCA);

    rdbHDMI.setXY(210, 7);
    rdbHDMI.setBitmaps(touchgfx::Bitmap(BITMAP_HDMI_80X80_S_ID), touchgfx::Bitmap(BITMAP_HDMI_80X80_FB_ID), touchgfx::Bitmap(BITMAP_HDMI_80X80_FB_ID), touchgfx::Bitmap(BITMAP_HDMI_80X80_S_ID));
    rdbHDMI.setSelected(false);
    rdbHDMI.setDeselectionEnabled(false);
    containerInputs.add(rdbHDMI);

    rdbUSB.setXY(138, 7);
    rdbUSB.setBitmaps(touchgfx::Bitmap(BITMAP_USB_80X80_S_ID), touchgfx::Bitmap(BITMAP_USB_80X80_FB_ID), touchgfx::Bitmap(BITMAP_USB_80X80_FB_ID), touchgfx::Bitmap(BITMAP_USB_80X80_S_ID));
    rdbUSB.setSelected(true);
    rdbUSB.setDeselectionEnabled(false);
    containerInputs.add(rdbUSB);

    rdbXLR.setXY(424, 7);
    rdbXLR.setBitmaps(touchgfx::Bitmap(BITMAP_XLR_80X80_S_ID), touchgfx::Bitmap(BITMAP_XLR_80X80_FB_ID), touchgfx::Bitmap(BITMAP_XLR_80X80_FB_ID), touchgfx::Bitmap(BITMAP_XLR_80X80_S_ID));
    rdbXLR.setSelected(false);
    rdbXLR.setDeselectionEnabled(false);
    containerInputs.add(rdbXLR);

    containerVolumeSet.setPosition(6, -200, 789, 199);

    boxWithBorder2.setPosition(-4, -36, 789, 199);
    boxWithBorder2.setColor(touchgfx::Color::getColorFromRGB(32, 32, 32));
    boxWithBorder2.setBorderColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    boxWithBorder2.setBorderSize(5);
    containerVolumeSet.add(boxWithBorder2);

    sldrVolume.setXY(32, 129);
    sldrVolume.setBitmaps(touchgfx::Bitmap(BITMAP_SLIDER_930_ID), touchgfx::Bitmap(BITMAP_SLIDER_930_ID), touchgfx::Bitmap(BITMAP_ON_44X44_ID));
    sldrVolume.setupHorizontalSlider(2, 16, 0, 0, 688);
    sldrVolume.setValueRange(0, 100);
    sldrVolume.setValue(100);
    sldrVolume.setNewValueCallback(sliderValueChangedCallback);
    containerVolumeSet.add(sldrVolume);

    lblVolume.setPosition(202, 91, 77, 44);
    lblVolume.setColor(touchgfx::Color::getColorFromRGB(200, 200, 200));
    lblVolume.setLinespacing(0);
    Unicode::snprintf(lblVolumeBuffer, LBLVOLUME_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_2A2C).getText());
    lblVolume.setWildcard(lblVolumeBuffer);
    lblVolume.setTypedText(touchgfx::TypedText(T___SINGLEUSE_CCHA));
    containerVolumeSet.add(lblVolume);

    chbxMute.setXY(719, 41);
    chbxMute.setBitmaps(touchgfx::Bitmap(BITMAP_OFF_44X44_ID), touchgfx::Bitmap(BITMAP_ON_44X44_ID));
    chbxMute.setAction(buttonCallback);
    containerVolumeSet.add(chbxMute);

    lblVolumeLevel.setPosition(23, 91, 184, 44);
    lblVolumeLevel.setColor(touchgfx::Color::getColorFromRGB(200, 200, 200));
    lblVolumeLevel.setLinespacing(0);
    lblVolumeLevel.setTypedText(touchgfx::TypedText(T___SINGLEUSE_8F58));
    containerVolumeSet.add(lblVolumeLevel);

    lblMute.setPosition(629, 41, 82, 44);
    lblMute.setColor(touchgfx::Color::getColorFromRGB(200, 200, 200));
    lblMute.setLinespacing(0);
    lblMute.setTypedText(touchgfx::TypedText(T___SINGLEUSE_5WVY));
    containerVolumeSet.add(lblMute);

    btnBackVolume.setBoxWithBorderPosition(0, 0, 134, 44);
    btnBackVolume.setBorderSize(2);
    btnBackVolume.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(21, 21, 21), touchgfx::Color::getColorFromRGB(32, 32, 32), touchgfx::Color::getColorFromRGB(0, 0, 0), touchgfx::Color::getColorFromRGB(0, 0, 0));
    btnBackVolume.setText(TypedText(T___SINGLEUSE_B3K6));
    btnBackVolume.setTextPosition(0, 0, 134, 44);
    btnBackVolume.setTextColors(touchgfx::Color::getColorFromRGB(150, 118, 73), touchgfx::Color::getColorFromRGB(150, 118, 73));
    btnBackVolume.setPosition(23, 19, 134, 44);
    btnBackVolume.setAction(flexButtonCallback);
    containerVolumeSet.add(btnBackVolume);

    add(__background);
    add(box1);
    add(boxWithBorder1);
    add(containerVolume);
    add(containerFormat);
    add(containerFreq);
    add(box22);
    add(img22);
    add(box24);
    add(img24);
    add(box245);
    add(img245);
    add(boxIntExt);
    add(imgIntExt);
    add(btnSettings);
    add(btnDisplay);
    add(lblDateTime);
    add(btnShowSaver);
    add(containerTemperature);
    add(containerDACFilter);
    add(containerSelectInput);
    add(containerInputs);
    add(containerVolumeSet);
    inputs.add(rdbBNC);
    inputs.add(rdbRCA);
    inputs.add(rdbHDMI);
    inputs.add(rdbUSB);
    inputs.add(rdbXLR);
    inputs.setRadioButtonSelectedHandler(radioButtonSelectedCallback);
}

void MainViewBase::setupScreen()
{

}

void MainViewBase::showInputsEndedCallbackHandler(const touchgfx::MoveAnimator<touchgfx::Container>& comp)
{
    //HideInputButton
    //When ShowInputs completed hide btnSelectInput
    //Hide btnSelectInput
    btnSelectInput.setVisible(false);
    btnSelectInput.invalidate();
}

void MainViewBase::hideInputsEndedCallbackHandler(const touchgfx::MoveAnimator<touchgfx::Container>& comp)
{
    //ShowInputButton
    //When HideInputs completed show btnSelectInput
    //Show btnSelectInput
    btnSelectInput.setVisible(true);
    btnSelectInput.invalidate();
}

void MainViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &chbxMute)
    {
        //OnMuteChanged
        //When chbxMute clicked call virtual function
        //Call chbxMuteChanged
        chbxMuteChanged();
    }
}

void MainViewBase::flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src)
{
    if (&src == &btnVolume)
    {
        //ShowVolumeSet
        //When btnVolume clicked move containerVolumeSet
        //Move containerVolumeSet to x:6, y:81 with SineIn easing in 500 ms (30 Ticks)
        containerVolumeSet.clearMoveAnimationEndedAction();
        containerVolumeSet.startMoveAnimation(6, 81, 30, touchgfx::EasingEquations::sineEaseIn, touchgfx::EasingEquations::sineEaseIn);
    }
    else if (&src == &btnSettings)
    {
        //ShowSettings
        //When btnSettings clicked change screen to SettingsScreen
        //Go to SettingsScreen with screen transition towards East
        application().gotoSettingsScreenScreenSlideTransitionEast();
    }
    else if (&src == &btnDisplay)
    {
        //ShowDipslay
        //When btnDisplay clicked change screen to DisplayScreen
        //Go to DisplayScreen with screen transition towards East
        application().gotoDisplayScreenScreenSlideTransitionEast();
    }
    else if (&src == &btnShowSaver)
    {
        //ShowSaver
        //When btnShowSaver clicked change screen to SaverScreen
        //Go to SaverScreen with screen transition towards East
        application().gotoSaverScreenScreenWipeTransitionEast();
    }
    else if (&src == &btnHideInputs)
    {
        //HideInputs
        //When btnHideInputs clicked move containerInputs
        //Move containerInputs to x:303, y:-100 with SineOut easing in 300 ms (18 Ticks)
        containerInputs.clearMoveAnimationEndedAction();
        containerInputs.startMoveAnimation(303, -100, 18, touchgfx::EasingEquations::sineEaseOut, touchgfx::EasingEquations::sineEaseOut);
        containerInputs.setMoveAnimationEndedAction(hideInputsEndedCallback);
    }
    else if (&src == &btnSelectInput)
    {
        //ShowInputs
        //When btnSelectInput clicked move containerInputs
        //Move containerInputs to x:303, y:0 with SineIn easing in 300 ms (18 Ticks)
        containerInputs.clearMoveAnimationEndedAction();
        containerInputs.startMoveAnimation(303, 0, 18, touchgfx::EasingEquations::sineEaseIn, touchgfx::EasingEquations::sineEaseIn);
        containerInputs.setMoveAnimationEndedAction(showInputsEndedCallback);
    }
    else if (&src == &btnBackVolume)
    {
        //HideVolumeSet
        //When btnBackVolume clicked move containerVolumeSet
        //Move containerVolumeSet to x:6, y:-210 with SineOut easing in 500 ms (30 Ticks)
        containerVolumeSet.clearMoveAnimationEndedAction();
        containerVolumeSet.startMoveAnimation(6, -210, 30, touchgfx::EasingEquations::sineEaseOut, touchgfx::EasingEquations::sineEaseOut);
    }
}

void MainViewBase::sliderValueChangedCallbackHandler(const touchgfx::Slider& src, int value)
{
    if (&src == &sldrVolume)
    {
        //OnVolumeValueChanged
        //When sldrVolume value changed call virtual function
        //Call sldrVolumeValueChanged
        sldrVolumeValueChanged(value);
    }
}

void MainViewBase::radioButtonSelectedCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &rdbXLR)
    {
        //XLRInputsSelected
        //When rdbXLR selected call virtual function
        //Call rdbXLRInputsSelected
        rdbXLRInputsSelected();
    }
    else if (&src == &rdbUSB)
    {
        //USBInputsSelected
        //When rdbUSB selected call virtual function
        //Call rdbUSBInputsSelected
        rdbUSBInputsSelected();
    }
    else if (&src == &rdbHDMI)
    {
        //HDMIInputsSelected
        //When rdbHDMI selected call virtual function
        //Call rdbHDMIInputsSelected
        rdbHDMIInputsSelected();
    }
    else if (&src == &rdbRCA)
    {
        //RCAInputsSelected
        //When rdbRCA selected call virtual function
        //Call rdbRCAInputsSelected
        rdbRCAInputsSelected();
    }
    else if (&src == &rdbBNC)
    {
        //BNCInputsSelected
        //When rdbBNC selected call virtual function
        //Call rdbBNCInputsSelected
        rdbBNCInputsSelected();
    }
}
