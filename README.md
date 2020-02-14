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
