
#include <LoRaWan.h>


//https://www.seeedstudio.com/Grove-Gas-Sensor-MQ2.html
//https://docs.particle.io/assets/datasheets/electronsensorkit/MQ-2.pdf

//unsigned char buffer[128] = {0xef, 0xff, 0x55, 3, 4, 5, 6, 7, 8, 9,};
unsigned char data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0xA,};
char buffer[256];

void setup(void)
{
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
   float sensor_volt;
   float RS_air; // Get the value of RS via in a clear air
   float R0; // Get the value of R0 via in H2
    float RS_gas; // Get value of RS in a GAS
    float ratio; // Get ratio RS_GAS/RS_air
    int sensorValue = analogRead(A0);
    sensor_volt=(float)sensorValue/1024*5.0;
    RS_gas = (5.0-sensor_volt)/sensor_volt; // omit *RL
    /*-Replace the name "R0" with the value of R0 in the demo of First Test -*/
    ratio = RS_gas/R0; // ratio = RS/R0
    /*-----------------------------------------------------------------------*/
    Serial.print("sensor_volt = ");
    Serial.println(sensor_volt);
    Serial.print("RS_ratio = ");
    Serial.println(RS_gas);
    Serial.print("Rs/R0 = ");
    Serial.println(ratio);
    Serial.print("\n\n");
    delay(1000);

    bool result = false;

    SerialUSB.println("Send string packet to Pervasive Nation NOC.");
    //This sketch will broadcast a string to Pervasive Nation Network 
    result = lora.transferPacket("RS_ratio!", RS_gas);
    
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
    }
    SerialUSB.print("Sleep for 240000 ms (4minutes) ");
    delay(240000);
}
