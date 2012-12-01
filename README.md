------------------------------------------------------------------------
SSBoot - STM32 SPI Bootloader
Autor: Krzysztof Dziuba <krzysztof.dziuba@gmail.com>
------------------------------------------------------------------------

STM32 secondary bootloader for flashing devices over SPI. Primary used 
as a part of RaspberryPi controlled mobile robot.

Supported CPUs: 
- STM32F100C4T6

License:
Project uses some example files from STMicroelectronics. They are mostly
unchanged. Other files are licensed under simplified BSD License (see
below).


How to build:
- Get Linux (eg. Ubuntu)
- Get compiler (eg. Linaro bare-metal gcc-arm-none-eabi)
- Edit Makefile and check BOARD variable (currently only one board is 
  supported)
- In terminal run make
- Flash bootloader to your board (eg. using OpenOCD)


TO DO:
- SPI protocol description
- hardware description


------------------------------------------------------------------------
Simplified BSD License:

Copyright (c) 2012, Krzysztof Dziuba
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met: 

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies, 
either expressed or implied, of the SSBoot Project.
