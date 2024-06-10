#include "ble_switch_handler.h"
#include "esphome/components/text_sensor/text_sensor.h"  // Incluye el componente text_sensor

#ifdef USE_SWITCH

#include "esphome/core/log.h"

namespace esphome {
namespace esp32_ble_controller {

static const char *TAG = "ble_switch_handler";

// Declara el text_sensor
text_sensor::TextSensor *on_value = new text_sensor::TextSensor();

void BLESwitchHandler::on_characteristic_written() {
  std::string value = get_characteristic()->getValue();
  if (value.length() == 1) {
    uint8_t on = value[0];
    ESP_LOGD(TAG, "Switch chracteristic written: %d", on);
    if (on)
      get_component()->turn_on();
    else
      get_component()->turn_off();

    // Almacena el valor en el text_sensor
    on_value->publish_state(std::to_string(on));
  }
}

} // namespace esp32_ble_controller
} // namespace esphome

#endif
