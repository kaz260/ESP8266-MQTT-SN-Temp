<h1 class="gh-header-title instapaper_title">ESP8266-MQTT-SN-Temp</h1>
Documentaion of the MQTT-SN implemented on ESP8266

<h2><a id="user-content-items" class="anchor" href="#items" aria-hidden="true"><span class="octicon octicon-link"></span></a>Protocol Specification</h2>
Please refer http://mqtt.org/new/wp-content/uploads/2009/06/MQTT-SN_spec_v1.2.pdf

<h2><a id="user-content-items" class="anchor" href="#items" aria-hidden="true"><span class="octicon octicon-link"></span></a>This implementation</h2>
ESP8266-MQTT-SN-Temp is temperature sensor using ESP8266 SoC and SHT25 temperature sensor.
This implementation almost depends on https://github.com/ty4tw/MQTT-SN. I added NetWorkWiFI library and kSHT2x library for ESP8266. If you test this code, you need to prepare AsycGateway and MQTT broker.
