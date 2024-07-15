#pragma once

#include "Forge/Config.h"

struct HIDDeviceInfo;
struct HIDController;

bool HIDIsSupportedPS5Controller(HIDDeviceInfo* devInfo);
int HIDOpenPS5Controller(HIDDeviceInfo* devInfo, HIDController* controller, uint8_t playerNum);
