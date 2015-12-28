# Arduino notes

This is based on Arduino 1.6.6 but holds true for most other Arduino IDEs.

## Avoid Delay, please

http://playground.arduino.cc/Code/AvoidDelay

The delay() function stops the entire code execution on the Arduino. Except for interrupts.
Thus during that time buttons, LEDs and other things you might want to check do not work any more.
delay() can be used if you are only checking one sensor and want to make sure you have a "frozen" condition just before polling.

Using millis() also allows us to very easily understand what a state machine is.
As the name suggests, a state machine is a box who knows what the current state of something is.
In your example we need a state machine for two LEDs.



## SDA (DAT) and SCL (CLK)

The Signal Data and Signal Clock lines can be found on your Arduino at various places.
The SCL on Arduino UNO its Analog #5, on the Leonardo its Digital #3, on the Mega its digital #21
The SDA on Arduino UNO its Analog #4, on the Leonardo its Digital #2, on the Mega its digital #20
Adafruit Flora has it labelled as such but can also serve as a Digital pin.

Here is a quick table

| Board              |  I2C / TWI pins                                  |
|--------------------|--------------------------------------------------|
| Uno, Ethernet |   A4 (SDA), A5 (SCL)                         |
| Mega2560       | 20 (SDA), 21 (SCL)                           |
| Leonardo         | 2 (SDA), 3 (SCL)                               |
| Due                  |20 (SDA), 21 (SCL), SDA1, SCL1     |

Src: https://www.arduino.cc/en/Reference/Wire

## I2C, SPI, TWI etc

### Serial Peripheral Interface

Src: https://www.arduino.cc/en/Reference/SPI

Serial Peripheral Interface (SPI) is a synchronous serial data protocol used by microcontrollers for communicating with one or more peripheral devices quickly over short distances. It can also be used for communication between two microcontrollers.

With an SPI connection there is always one master device (usually a microcontroller) which controls the peripheral devices. Typically there are three lines common to all the devices:

MISO (Master In Slave Out) - The Slave line for sending data to the master,
MOSI (Master Out Slave In) - The Master line for sending data to the peripherals,
SCK (Serial Clock)               - The clock pulses which synchronize data transmission generated by the master

and one line specific for every device:
SS (Slave Select)                 - The pin on each device that the master can use to enable and disable specific devices.

When a device's Slave Select pin is low, it communicates with the master. When it's high, it ignores the master. This allows you to have multiple SPI devices sharing the same MISO, MOSI, and CLK lines.

For more on SPI, see Wikipedia's page on SPI.

The following table display on which pins the SPI lines are broken out on the different Arduino boards:

| Arduino Board                |  MOSI               |       MISO         | SCK                  | SS (slave)  | SS (master) |
|----------------------------------|---------------------|----------------------|----------------------|----------------|------------------|
| Uno or Duemilanove       | 11 or ICSP-4    |  12 or ICSP-1   |  13 or ICSP-3   | 10               | -                   |
| Mega1280 or Mega2560 |   51 or ICSP-4  |    50 or ICSP-1 |   52 or ICSP-3  |  53              | -                   |
| Leonardo                         | ICSP-4             |  ICSP-1             | ICSP-3             |  -                | -                   |
| Due                                 | ICSP-4              | ICSP-1             | ICSP-3              |  -                | 4, 10, 52      |

On the ICSP header we have a consistent layout

| PIN | Function |
|-------|-------------|
| 1     | MISO      |
| 2     | +VCC     |
| 3     | SCK       |
| 4     | MOSI     |
| 5     | Reset     |
| 6     | GND      |

ICSPHeader.jpg

### Inter-Integrate Circuit (I squared C)

With the I2C protocol we can "daisy-chain" Arduinos.

To connect 2 Arduino UNOs connect Pin **A4** and **A5** between the two.
You also need a common Ground so connect GND too.

I2C_UNOs.jpg

### TWI

