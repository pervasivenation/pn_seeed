#include <Arduino.h>
#include <LoRaWan.h>
#include "sensirion_common.h"
#include "sgp30.h"

//unsigned char buffer[128] = {0xef, 0xff, 0x55, 3, 4, 5, 6, 7, 8, 9,};
unsigned char data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0xA,};
char buffer[256];

//These Guides are useful for the SGP30_Gas_Sensor to measure MEASURE IAQ (tVOC / CO2eq) AND SIGNAL VALUES. 
//https://github.com/Seeed-Studio/SGP30_Gas_Sensor
//https://wiki.seeedstudio.com/Grove-VOC_and_eCO2_Gas_Sensor-SGP30/
//https://wiki.seeedstudio.com/How_to_install_Arduino_Library/
//https://files.seeedstudio.com/wiki/Grove-VOC_and_eCO2_Gas_Sensor-SGP30/res/Sensirion_Gas_Sensors_SGP30_Driver-Integration-Guide_HW_I2C.pdf

void setup(void)
{
    //SPG30 VOC and eCO2 gas sensor - end
    s16 err;
    u16 scaled_ethanol_signal, scaled_h2_signal;
    Serial.begin(115200);
    Serial.println("serial start!!");

    /*For wio link!*/
    #if defined(ESP8266)
    pinMode(15, OUTPUT);
    digitalWrite(15, 1);
    Serial.println("Set wio link power!");
    delay(500);
    #endif
    /*  Init module,Reset all baseline,The initialization takes up to around 15 seconds, during which
        all APIs measuring IAQ(Indoor air quality ) output will not change.Default value is 400(ppm) for co2,0(ppb) for tvoc*/
    while (sgp_probe() != STATUS_OK) {
        Serial.println("SGP failed");
        while (1);
    }
    /*Read H2 and Ethanol signal in the way of blocking*/
    err = sgp_measure_signals_blocking_read(&scaled_ethanol_signal,
                                            &scaled_h2_signal);
    if (err == STATUS_OK) {
        Serial.println("get ram signal!");
    } else {
        Serial.println("error reading signals");
    }
    err = sgp_iaq_init();
    //
    //SPG30 VOC and eCO2 gas sensor - end
    
    SerialUSB.begin(115200);
    while(!SerialUSB);
    
    lora.init();

    memset(buffer, 0, 256);

    lora.getVersion(buffer, 256, 1);

    SerialUSB.print(buffer); 

    memset(buffer, 0, 256);
    lora.getId(buffer, 256, 1);
    SerialUSB.print(buffer);
    
    
    // void setId(char *DevAddr, char *DevEUI, char *AppEUI);
    lora.setId(NULL, "00DBBF7C763121C4", "8CF9572000000000");
    // setKey(char *NwkSKey, char *AppSKey, char *AppKey);
    lora.setKey("45EF308FBB07EFD411E1515C464C8527", NULL, "2a7d151628bea2a6ace7158809de4f3b");
    
    lora.setDeciveMode(LWOTAA);
    lora.setDataRate(DR0, EU868);

    lora.setChannel(0, 868.1);
    lora.setChannel(1, 868.3);
    lora.setChannel(2, 868.5);
    lora.setChannel(3, 867.1);
    lora.setChannel(4, 867.3);
    lora.setChannel(5, 867.5);
    lora.setChannel(6, 867.7);
    lora.setReceiceWindowFirst(0, 868.1);
    lora.setReceiceWindowSecond(869.5, DR3);

    lora.setDutyCycle(false);
    lora.setJoinDutyCycle(false);
    lora.setPower(30);
    while(!lora.setOTAAJoin(JOIN)){
      SerialUSB.println("Trying to Join network");
    }
}

void loop(void)
{
    bool result = false;

    //SPG30 VOC and eCO2 gas sensor - beginning
    s16 err = 0;
    u16 tvoc_ppb, co2_eq_ppm;
    err = sgp_measure_iaq_blocking_read(&tvoc_ppb, &co2_eq_ppm);
    if (err == STATUS_OK) {
        Serial.print("tVOC  Concentration:");
        Serial.print(tvoc_ppb);
        Serial.println("ppb");

        Serial.print("CO2eq Concentration:");
        Serial.print(co2_eq_ppm);
        Serial.println("ppm");

        //SPG30 VOC and eCO2 gas sensor - end
        
        SerialUSB.println("Send string packet to Pervasive Nation NOC.");
        //This sketch will broadcast a string to Pervasive Nation Network 
        result = lora.transferPacket("tvoc_ppb!", tvoc_ppb);
        
        if(result)
        {
            short length;
            short rssi;
            SerialUSB.print("Result is: ");
            memset(buffer, 0, 256);
            length = lora.receivePacket(buffer, 256, &rssi);
            if(length)
            {
                SerialUSB.print("Length is: ");
                SerialUSB.println(length);
                SerialUSB.print("RSSI is: ");
                SerialUSB.println(rssi);
                SerialUSB.print("Data is: ");
                for(unsigned char i = 0; i < length; i ++)
                {
                    SerialUSB.print("0x");
                    SerialUSB.print(buffer[i], HEX);
                    SerialUSB.print(" ");
                }
                SerialUSB.println();
            }
    } else {
        Serial.println("error reading IAQ values\n");
    }
    }
    SerialUSB.print("Sleep for 240000 ms (4minutes) ");
    delay(240000);
}
