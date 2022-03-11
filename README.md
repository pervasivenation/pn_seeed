# pn_seeed
Pervasive Nation Seeedstudio board tx/rx

Supports frequencies: 867.1MHz, 867.3MHz, 867.5MHz, 867.7MHz, 867.9MHz, 868.1MHz, 868.3MHz, 868.5MHz

Compile code using the Arduino IDE environment, with Seeeduino LoRa toolkit. 

Note, device DevAddr, DevEUI, and AppEUI need to be proivisioned on the Pervasive Nation Network, otherwise the device will not be able to communicate with the network. Please contact info@pervasivenation.ie to arrange this.

For example:

DevAddr: DA006039

DevEUI: 00DBBF7C763121C4

AppEUI: 2a7d151628bea2a6ace7158809de4f3b

We followed the instructions on http://wiki.seeedstudio.com/Seeeduino_LoRAWAN/ and modified the code to support the Pervasive Nation IoT testbed.


If Seeeduino LoRaWAN board connects to the network, you see the following in the Arduino IDE monitor tool. 

......

+JOIN: Start

+JOIN: NORMAL

Send string packet to Pervasive Nation NOC.

+MSG: LoRaWAN modem is busy

+JOIN: Network joined

+JOIN: NetID C00010 DevAddr FC:00:40:29

+JOIN: Done

Send string packet to Pervasive Nation NOC.

......

If Seeeduino LoRaWAN board fails to connect to the network, you see the followin in the Arduino IDE monitor tool. 

.....

+JOIN: Start

+JOIN: NORMAL

Send string packet to Pervasive Nation NOC.

+MSG: LoRaWAN modem is busy

+JOIN: Join failed

+JOIN: Done

+MSG: Please join network first

Send string packet to Pervasive Nation NOC.

......

If the Join Failed it might be an issue with proximity to the gateways, or the device has not been provisioned on the Pervasive Nation nework. However, if you are confident it should be on the network, simply restart the device.

On the Pervasive Nation platform data is recevied in Hexidecimal format:

Hex: 53616d706c654461746121   

converts to ASCII: SampleData!


Send data from Pervasive Nation network:

Hex: 0x6E 0x65 0x74 0x77 0x6F 0x72 0x6B 0x68 0x6

MSG: networkhi



_____________________________________________________________________________________________________________________________________________________________

TemperatureLoraWan.ino

- Connect the Shield to the Seeduino LoraWan board
- Attach temperature sensor V1.2 at the A0 port

- Upload the code
- Replace the lora.setID() values with the values that appear on the serial monitor
- Generate a random appkey at ttn and replace it to the lora.setkey()

-Sample output:

16:47:05.280 -> +ID: DevAddr, 27:01:14:C1
16:47:05.280 -> +ID: DevEui, 8C:F9:57:20:00:02:E5:70
16:47:05.280 -> +ID: AppEui, 8C:F9:57:20:00:00:00:00
16:47:05.561 -> +ID: DevAddr, 00:02:E5:70
16:47:05.561 -> +ID: DevEui, 8C:F9:57:20:00:02:E5:70
16:47:05.561 -> +ID: AppEui, 8C:F9:57:20:00:00:00:00
16:47:05.634 -> +KEY: NWKSKEY 14100A104343A00D68CC60AFCFF48EEE
16:47:06.721 -> +KEY: APPSKEY 14100A104343A00D68CC60AFCFF48EEE
16:47:07.817 -> +KEY: APPKEY 14100A104343A00D68CC60AFCFF48EEE
16:47:08.950 -> +MODE: LWOTAA
16:47:10.104 -> +DR: EU868
16:47:11.070 -> +DR: DR0
16:47:11.103 -> +DR: EU868 DR0  SF12 BW125K 
16:47:12.183 -> +CH: 0,868100000,DR0:DR5
16:47:13.273 -> +CH: 1,868300000,DR0:DR5
16:47:14.369 -> +CH: 2,868500000,DR0:DR5
16:47:15.470 -> +CH: 3,867100000,DR0:DR5
16:47:16.584 -> +CH: 4,867300000,DR0:DR5
16:47:17.686 -> +CH: 5,867500000,DR0:DR5
16:47:18.794 -> +CH: 6,867700000,DR0:DR5
16:47:19.894 -> +RXWIN1: 0,868100000
16:47:21.001 -> +RXWIN2: 869500000,DR3
16:47:22.075 -> +LW: DC, OFF, 0
16:47:23.182 -> +LW: JDC, OFF
16:47:24.293 -> +POWER: 14
16:47:25.421 -> +JOIN: Start
16:47:25.421 -> +JOIN: NORMAL
16:47:31.477 -> temperature = 24.88
16:47:31.477 -> Send string packet to Pervasive Nation NOC.
16:47:39.453 -> +MSG: LoRaWAN modem is busy
16:47:39.453 -> +JOIN: Network joined
16:47:39.453 -> +JOIN: NetID 000013 DevAddr 27:01:14:B7
16:47:39.453 -> +JOIN: Done
16:47:39.453 -> temperature = 24.80



