#include <gui/containers/UpDownContainer.hpp>


 

UpDownContainer::UpDownContainer()
{
    mValue = 0;
    MinValue = 0;
    MaxValue = 100;
}

void UpDownContainer::initialize()
{
    UpDownContainerBase::initialize();
}

void UpDownContainer::OnBtnUpClick()
{
    mValue++; 
    RefreshValue();
    emitValueChangedTriggerCallback(mValue);
}


void UpDownContainer::OnBtnDownClick()
{
    mValue--;
    RefreshValue(); 
    emitValueChangedTriggerCallback(mValue);
}

void UpDownContainer::RefreshValue()
{
    if (mValue < MinValue)
    {
        mValue = MinValue;
    }
    if (mValue > MaxValue)
    {
        mValue = MaxValue;
    }
    Unicode::snprintf(lblValueBuffer, LBLVALUE_SIZE, "%d", mValue);
    lblValue.invalidate();
}

int UpDownContainer::GetValue()
{
    return mValue;
}

void UpDownContainer::SetValue(int value)
{
   
    mValue = value;
    RefreshValue();
}
