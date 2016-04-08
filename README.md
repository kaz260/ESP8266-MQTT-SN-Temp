<h1 class="gh-header-title instapaper_title">ESP8266-MQTT-SN-Temp</h1>
Documentaion of the MQTT-SN implemented on ESP8266


<h2><a id="user-content-introduction" class="anchor" href="#introduction" aria-hidden="true"><span class="octicon octicon-link"></span></a>Introduction</h2>
MQTT-SN is a kind of protocol  for Internet of Things(IoT). MQTT-SN is optimized for limited processing and storage resources. Major differences between MQTT are following:

<h2><a id="user-content-configuration" class="anchor" href="#configuration" aria-hidden="true"><span class="octicon octicon-link"></span></a>Configuration</h2>
<pre><code># echonetlite:&lt;instance&gt;.host = &lt;ip&gt;
# echonetlite:&lt;instance&gt;.port = &lt;port&gt;
# echonetlite:&lt;instance&gt;.EDATA_HEAD = &lt;edata_head&gt;
Here, EDATA_HEAD contains Source ECHONET Lite object specification(3Bytes), Destination ECHONET Lite object specification(3Bytes), ECHONET Lite service(1 Byte) and number of processing propertites(OPC).

#ECHONET Lite LED Light, for example
echonetlite:light_a.host = 10.10.0.204
echonetlite:light_a.port = 3610
echonetlite:light_a.EDATA_HEAD = 0ef0010290016101
Here, '61' means 'set and confirm'.

echonetlite:light_a_status.host = 10.10.0.204
echonetlite:light_a_status.port = 3610
echonetlite:light_a_status.EDATA_HEAD = 0ef0010290016201
Here, '62' means 'get'.
</code></pre>

<h2><a id="user-content-items" class="anchor" href="#items" aria-hidden="true"><span class="octicon octicon-link"></span></a>Items</h2>
All items use the following format described below. Currently, only one EPC can be assgned. The state of the devices thus do not correspond to the current state of the devices. Valid combination of ECHONET Lite Property(EPC) and ECHONET Lite Data(EDT) are described in https://echonet.jp/english/

<pre><code>out: {echonetlite="&gt;[&lt;command&gt;:&lt;instance&gt;:&lt;EPC&gt;:&lt;EDT&gt;]"}
in:  {echonetlite="&lt;[&lt;instance&gt;:&lt;EPC&gt;:&lt;refreshintervalinmilliseconds&gt;]"}

#ECHONET Lite LED light, for example
{echonetlite="&gt;[ON:light_a:80:30] &gt;[OFF:light_a:31]"}
#ECHONET lite thermometer, for example
{echonetlite="&lt;[temp_a:e0:10000]"}
</code></pre>

<h2><a id="user-content-items" class="anchor" href="#items" aria-hidden="true"><span class="octicon octicon-link"></span></a>Configuration example</h2>
<a id="user-content-items" class="anchor" href="#items" aria-hidden="true"><span class="octicon octicon-link"></span></a>You can test the echonetlite binding using ECHONETLite emulator named 'MOEKADEN'. 'MOEKADEN' is able to download from http://kadecot.net/blog/1479/#more-1479
openhab.cfg
<pre><code>
echonetlite:hvac_a.host=10.10.0.200
echonetlite:hvac_a.port=3610
echonetlite:hvac_a.EDATA_HEAD=0ef0010130016101
echonetlite:hvac_a_status.host=10.10.0.200
echonetlite:hvac_a_status.port=3610
echonetlite:hvac_a_status.EDATA_HEAD=0ef0010130016201
echonetlite:light_a.host=10.10.0.200
echonetlite:light_a.port=3610
echonetlite:light_a.EDATA_HEAD=0ef0010290016101
echonetlite:light_a_status.host=10.10.0.200
echonetlite:light_a_status.port=3610
echonetlite:light_a_status.EDATA_HEAD=0ef0010290016201
echonetlite:curtain_a.host=10.10.0.200
echonetlite:curtain_a.port=3610
echonetlite:curtain_a.EDATA_HEAD=0ef0010260016101
echonetlite:door_a.host=10.10.0.200
echonetlite:door_a.port=3610
echonetlite:door_a.EDATA_HEAD=0ef001026f016101
echonetlite:temp_a.host=10.10.0.200
echonetlite:temp_a.port=3610
echonetlite:temp_a.EDATA_HEAD=0ef0010011016201
</code></pre>

Items
<pre><code>
Switch		HVAC_SW					{echonetlite=">[ON:hvac_a:80:30] >[OFF:hvac_a:80:31]"}
String		HVAC_MODE	"Mode [%s]"		{echonetlite=">[hvac_a:b0]"}
Number		HVAC_TEMP	"Temp [%d]"		{echonetlite=">[hvac_a:b3]"}
Switch		Light_a		"light_a"		{echonetlite=">[ON:light_a:80:30] >[OFF:light_a:80:31]"}
Switch		Curtain_a	"Curtain_1"             {echonetlite=">[ON:curtain_a:e0:41] >[OFF:curtain_a:e0:42]"}
Switch		Door_a		"Door_1"                {echonetlite=">[ON:door_a:e0:41] >[OFF:door_a:e0:42]"}
String		Temp_a		"Temp [%d]"             {echonetlite="<[temp_a:e0:10000]"}
</code></pre>

Sitemaps
<pre><code>
Switch 		item=HVAC_SW
Selection	item=HVAC_MODE	mappings=[41=Auto, 42=Cool, 43=Heat, 44=Dry, 45=Wind, 5=ERROR]
Setpoint	item=HVAC_TEMP	minValue=10 maxValue=40 step=1
Switch 		item=Light_a
Switch 		item=Curtain_a
Switch 		item=Door_a
Text		item=Temp_a
</code></pre>
