#include "ble_switch_handler.h"
#include "esphome.h"  // Include esphome.h

#pragma once

#include "esphome/core/defines.h"
#ifdef USE_SWITCH

#include <string>
#include "esphome.h"
#include "esphome/components/global/global.h"
#include "esphome/components/switch/switch.h"
#include "ble_component_handler.h"

using std::string;

namespace esphome {
namespace esp32_ble_controller {

using switch_::Switch;

class BLESwitchHandler : public BLEComponentHandler<Switch> {
public:
  BLESwitchHandler(Switch* component, const BLECharacteristicInfoForHandler& characteristic_info) : BLEComponentHandler(component, characteristic_info) {}
  virtual ~BLESwitchHandler() {}

protected:
  virtual bool can_receive_writes() { return true; }
  virtual void on_characteristic_written() override {
    // ...
    uint8_t on = std::stoi(value);
    // ...

    // Asigna el valor a la variable global
    auto switch_value = global::GlobalsComponent::get_global_by_id("switch_value");
    switch_value->value() = on;
  }
};

} // namespace esp32_ble_controller
} // namespace esphome

#endif

