#include "ble_switch_handler.h"
#include "esphome.h"  // Include esphome.h

#ifdef USE_SWITCH

#include "esphome/core/log.h"
#include "esphome/components/global/global_string.h"  // Include the global_string component

using namespace esphome;  // Use the esphome namespace

namespace esp32_ble_controller {

static const char *TAG = "ble_switch_handler";

void BLESwitchHandler::on_characteristic_written() {
  ESP_LOGD(TAG, "on_characteristic_written called");
  std::string value = get_characteristic()->getValue();
  ESP_LOGD(TAG, "Characteristic value: %s", value.c_str());
  if (!value.empty()) {
    uint8_t on = std::stoi(value);
    ESP_LOGD(TAG, "Switch chracteristic written: %d", on);
    if (on)
      get_component()->turn_on();
    else
      get_component()->turn_off();

    // Store the value in the global
    auto on_value_global = global_string::GlobalsComponent::get_global_by_id("on_value_global");
    on_value_global->value() = std::to_string(on);
    ESP_LOGD(TAG, "Published state to on_value_global");
  }
}

} // namespace esp32_ble_controller

#endif

