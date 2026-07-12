# SkyForge Firmware Roadmap

## BSP

### GPIO
- [x] Write Pin
- [x] Read Pin
- [x] Toggle Pin
- [x] LED Test
- [x] Button Test
- [ ] EXTI
- [ ] Debounce

### UART
- [ ] Initialization
- [ ] Transmit Byte
- [ ] Transmit Buffer
- [ ] Transmit String
- [ ] Receive Byte
- [ ] Interrupt Mode
- [ ] DMA Mode

### I2C
- [ ] Device Ready
- [ ] Register Read
- [ ] Register Write
- [ ] Burst Read
- [ ] Burst Write
- [ ] Error Handling

### SPI
- [ ] Transmit
- [ ] Receive
- [ ] Full Duplex
- [ ] DMA

### ADC
- [ ] Single Conversion
- [ ] Continuous Conversion
- [ ] DMA
- [ ] Voltage Conversion

### PWM
- [ ] Start
- [ ] Stop
- [ ] Duty Cycle
- [ ] Pulse Width

---

## Drivers

### MPU6050
- [ ] WHO_AM_I
- [ ] Wake-up
- [ ] Configuration
- [ ] Raw Accelerometer
- [ ] Raw Gyroscope
- [ ] Temperature
- [ ] Unit Conversion
- [ ] Calibration
- [ ] Complementary Filter
- [ ] Mahony Filter

### BMP388
- [ ] Chip ID
- [ ] Temperature
- [ ] Pressure
- [ ] Altitude

### GPS
- [ ] NMEA Parsing
- [ ] Latitude/Longitude
- [ ] Speed
- [ ] UTC Time

---

## Application Tests

- [x] GPIO LED
- [x] GPIO Button
- [ ] UART
- [ ] I2C Scanner
- [ ] MPU6050
- [ ] BMP388
- [ ] GPS