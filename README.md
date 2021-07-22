# MMA7455L-stm32
Basic implementation of SPI comunication between an MMA7455L acelerometer module and a STM32 development board.
The files MMA7455L.c and MMA7455L.h can be found in the respective folders of the project.
The datasheet is also avaliable in the repo in case someone want to implement the same.
To meassure data from an axis(X, Y, Z) in SPI mode first you have to use the function that init 8G mode, the device also have a 2G and 4G mode but for time reasons it was not implemented(maybe in the future); after that you can just call the function that meassure the data in 8 bits or 10 bits mode, from that its also implemented a function that read the pitch and roll angle.
In the example I send the function by UART to an ESP8266 Wifi Module.
In general in order to read/write a register in the MMA7455L module first you have to send the address with the mode, if you choose reading mode the module will send back the value in that register, if you choose write mode the module will be expecting you to send the value that you want to write after sending the address.
There's a lot of another option that you can implement, just take a look at the datasheet, there's a section for SPI comunication
