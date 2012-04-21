#include "../include/Input.h"

InputReceiver::InputReceiver()
{
    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
        KeyIsDown[i] = false;
}

bool InputReceiver::OnEvent(const SEvent& event)
{
    // Remember whether each key is down or up
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    //Joystick
    if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT
            && event.JoystickEvent.Joystick == 0)
    {
            JoystickState0 = event.JoystickEvent;
    }
    if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT
            && event.JoystickEvent.Joystick == 1)
    {
            JoystickState1 = event.JoystickEvent;
    }
    return false;
}

const SEvent::SJoystickEvent & InputReceiver::GetJoystickState(void) const
{
    if(joystick==0)
        return JoystickState0;
    if(joystick==1)
        return JoystickState1;
    return JoystickState0;;
}

bool InputReceiver::IsKeyDown(EKEY_CODE keyCode) const
{
    return KeyIsDown[keyCode];
}

bool InputReceiver::IsJoyDown(int joyCode,int joystick)
{
    this->joystick=joystick;
    const SEvent::SJoystickEvent & joystickData = GetJoystickState();
    moveHorizontal=(f32)GetJoystickState().Axis[SEvent::SJoystickEvent::AXIS_X] / 32767.f;
    moveVertical=(f32)GetJoystickState().Axis[SEvent::SJoystickEvent::AXIS_Y] / -32767.f;
    if(moveVertical<0 && joyCode==-2)
        return true;
    if(moveHorizontal<0 && joyCode==-4)
        return true;
    if(moveHorizontal>0 && joyCode==-6)
        return true;
    if(moveVertical>0 && joyCode==-8)
        return true;
    if(joystickData.IsButtonPressed(joyCode))
        return true;
    return false;
}
