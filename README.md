# I2C LCD

**I2C LCD** is small project where it will tell time based on NTP server.

## Schema

Coming soon!

## How to run

Prequesites:
- Install platformio

Before running the command below, it is recommended to check platformio.ini file and add your own env.

Run this to install dependencies
```bash
pio lib install
```
If the environment is Arduino Uno.

Build files
```bash
pio run
```

Upload to board 
```bash
pio run -t upload 
```

If you don't find the environment that you use, I strongly suggest to check [Platformio](https://platformio.org/) to look for your preferred boards and frameworks.

### Technologies & Stacks
- [Arduino](https://www.arduino.cc/)
- [NTPClient](https://github.com/arduino-libraries/NTPClient)
- [Time](https://github.com/PaulStoffregen/Time)
- [LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C)

### What it does
The device will show current time based on timezone provided by NTP server.