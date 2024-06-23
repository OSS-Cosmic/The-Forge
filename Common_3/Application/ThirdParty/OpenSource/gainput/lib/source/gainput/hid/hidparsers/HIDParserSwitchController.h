#pragma once

#include "Common_3/Application/Config.h"

struct HIDDeviceInfo;
struct HIDController;

bool HIDIsSupportedSwitchController(HIDDeviceInfo* devInfo);
int HIDOpenSwitchController(HIDDeviceInfo* devInfo, HIDController* controller, uint8_t playerNum);
