"""
ESPHome external component — irrigoto
Wraps the irrigoto firmware (irrigoto.c) as an ESPHome component.

YAML key: irrigoto
  id: irrigoto   # optional, needed if referenced in lambdas / services
"""

import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID
from esphome.components.esp32 import add_idf_component, include_builtin_idf_component
from esphome.components.deep_sleep import DeepSleepComponent
from esphome.components.safe_mode import SafeModeComponent   # b542
from esphome.components.logger import request_log_listener   # b512
from esphome.components import wifi                           # b543

CONF_DEEP_SLEEP_ID = "deep_sleep_id"
CONF_SAFE_MODE_ID = "safe_mode_id"   # b542

# HTML fragment "headers" (*_html.h) sit at the component ROOT so
# ESPHome's standard source copy ships them into the build tree next to
# irrigoto.c, where its bare #include "cal_html.h" resolves via normal
# quote-include lookup — no include flags needed. They are not real C
# headers (raw R"...(...)..." string bodies, only valid when #included
# inside a string literal definition); nothing includes them except the
# specific web-handler sites in irrigoto.c, so root placement is safe.
# The editable .html sources + regen.py stay in ./html/ (not copied to
# the build tree — not needed there).
#
# HISTORY (GitHub issue #4): they used to live in ./html/ with a
# cg.add_build_flag("-I<abs source path>") escape hatch, because ESPHome
# never copies component subdirs. ESPHome 2026.7's native ESP-IDF
# builder (PlatformIO dropped) forwards -D/-W build flags but silently
# drops -I flags, which broke every build from a clean checkout. Do NOT
# reintroduce include-path flags for these; root placement is the only
# mechanism that works across ESPHome versions.

CODEOWNERS = ["@rob-farrellrobotics"]
# b543: irrigoto.cpp reaches wifi::global_wifi_component directly (AP mode,
# provisioning, scan list), so the wifi component is a hard dependency.
DEPENDENCIES = ["wifi"]
AUTO_LOAD = []

# Declare the C++ namespace and class that ESPHome will instantiate
irrigoto_ns = cg.esphome_ns.namespace("irrigoto")
IrrigotoComponent = irrigoto_ns.class_(
    "IrrigotoComponent", cg.Component
)

# Top-level YAML schema: just an optional id
CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(IrrigotoComponent),
        # Optional link to ESPHome's deep_sleep component. If provided,
        # all sleep requests from irrigoto.c are routed through it so HA
        # gets a graceful "going to sleep" notification.
        cv.Optional(CONF_DEEP_SLEEP_ID): cv.use_id(DeepSleepComponent),
        # b542: optional link to ESPHome's safe_mode component so the
        # low-battery boot gate can clear the boot-loop counter before it
        # deep-sleeps directly (that path never reaches ESPHome's shutdown
        # hooks). Without it the counter is left untouched on that path.
        cv.Optional(CONF_SAFE_MODE_ID): cv.use_id(SafeModeComponent),
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    # ESPHome excludes these IDF components by default (see DEFAULT_EXCLUDED_IDF_COMPONENTS
    # in esp32/__init__.py) — re-include them since irrigoto.c uses them.
    include_builtin_idf_component("driver")    # legacy I2C driver (driver/i2c.h)
    include_builtin_idf_component("esp_adc")   # esp_adc/adc_oneshot.h

    # Managed component for LittleFS persistence.
    add_idf_component(name="joltwallet/littlefs", ref="^1.21.1")

    # Tell irrigoto.c it is being compiled as an ESPHome component.
    # Activates irrigoto_init() and deactivates app_main() / wifi_init().
    cg.add_build_flag("-DESPHOME_COMPONENT=1")
    # b512: irrigoto owns a deferred, non-blocking UART console (ESPHome's
    # own UART logger stays off). Reserve a logger callback slot for it.
    request_log_listener()
    # b543: GET /wifi/scan reads WiFiComponent's scan results from the httpd
    # task, so ask wifi to compile in the lock that guards them (what the
    # captive portal does); irrigoto.cpp holds wifi::ScanResultsLock while it
    # copies the list. On a core without the helper the lock class is a no-op
    # and the read is unguarded, as the captive portal's was before it existed.
    if (req_lock := getattr(wifi, "request_wifi_scan_results_lock", None)) is not None:
        req_lock()
    # Silence legacy I2C deprecation warnings (we use it intentionally).
    cg.add_build_flag("-Wno-deprecated-declarations")
    # NOTE: no -I flags here — see the *_html.h placement note at the
    # top of this file (ESPHome 2026.7+ drops -I from add_build_flag).

    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    if (ds_id := config.get(CONF_DEEP_SLEEP_ID)) is not None:
        ds = await cg.get_variable(ds_id)
        cg.add(var.set_deep_sleep(ds))

    if (sm_id := config.get(CONF_SAFE_MODE_ID)) is not None:
        sm = await cg.get_variable(sm_id)
        cg.add(var.set_safe_mode(sm))
