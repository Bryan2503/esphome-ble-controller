#include "ble_switch_handler.h"
#include "esphome.h"  // Include esphome.h
#include "esphome/components/text_sensor/text_sensor.h"  // Include the text_sensor component

#ifdef USE_SWITCH

#include "esphome/core/log.h"

using namespace esphome;  // Use the esphome namespace

namespace esp32_ble_controller {

static const char *TAG = "ble_switch_handler";

void BLESwitchHandler::on_characteristic_written() {
  std::string value = get_characteristic()->getValue();
  if (!value.empty()) {
    uint8_t on = std::stoi(value);
    ESP_LOGD(TAG, "Switch chracteristic written: %d", on);
    if (on)
      get_component()->turn_on();
    else
      get_component()->turn_off();

    // Store the value in the text_sensor
    auto on_value = id(on_value_text_sensor);
    on_value->publish_state(std::to_string(on));
  }
}


} // namespace esp32_ble_controller

#endif
