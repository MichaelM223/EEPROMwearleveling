#include <EEPROM.h>
#include <EEPROMWearLeveler.h>
EEPROMWearLeveler eepromwl(1024, 64); //class(eeprom_size, num_of_addresses) 1024/64 = 16x more read/write cycles

void setup(void){
  Serial.begin(115200);
  eepromwl.write(0, 223);
  if(eepromwl.read(0) == 223){
    Serial.print("EEPROM OK!");
  }else{
    Serial.print("EEPROM FAIL!");
  }
  WriteLongEEPROM(1, 1234567890);
  if(ReadLongEEPROM(1) == 1234567890){
    Serial.print("Long read/write OK!");
  }else{
    Serial.print("Long read/write FAIL!");
  }
}

void loop(void){
}

void WriteLongEEPROM(byte addr, unsigned long data){
  byte buf[4];
  buf[0] = (byte)((data >> 24) & 0xff);
  buf[1] = (byte)((data >> 16) & 0xff);
  buf[2] = (byte)((data >> 8) & 0xff);
  buf[3] = (byte)(data & 0xff);
  for(byte i=0; i<4; i++)eepromwl.write(addr+i, buf[i]);
}

unsigned long ReadLongEEPROM(byte addr){
  byte buf[4];
  unsigned long waarde;
  for (byte i=0; i<4; i++)buf[i] = eepromwl.read(addr+i);
  waarde = ((unsigned long)buf[0]) << 24;
  waarde |= ((unsigned long)buf[1]) << 16;
  waarde |= ((unsigned long)buf[2]) << 8;
  waarde |= buf[3];
  return waarde;
}
