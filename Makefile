baud=57600
avrType=atmega32u4 
avrFreq=8000000L
programmerDev=/dev/cu.usbmodem1411
programmerType=avr109
avrConf=config/avrdude.conf
bootloaderFile=bootloader/Caterina-Feather32u4.hex

cflags=-std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -flto -w -x c++ -CC -DF_CPU=$(avrFreq) -mmcu=$(avrType) -Os -Iinc/ 
avrflags=-DARDUINO=10807 -DARDUINO_AVR_FEATHER32U4 -DARDUINO_ARCH_AVR -DUSB_VID=0x239A -DUSB_PID=0x800C "-DUSB_MANUFACTURER=\"Adafruit\"" "-DUSB_PRODUCT=\"Feather 32u4\""

CORE_FILES := $(shell find core -type f -name "*.cpp" -o -name "*.c")
32u4_FILES=$(shell find src/32u4/ -type f -name "*.cpp" -o -name "*.c")
CLIENT_FILES=$(shell find src/client/ -type f -name "*.cpp" -o -name "*.c")

CLIENT_CXXSTD := -std=c++11 -Wno-deprecated-register -g -O0

all: objects move_obj main.elf main.hex

client:
	g++ $(CLIENT_CXXSTD) -Iinc/ $(CLIENT_FILES) -o bin/client

objects:
	avr-gcc $(cflags) $(avrflags) -c $(CORE_FILES) $(32u4_FILES)

move_obj:
	mv *.o obj/

main.elf:
	avr-gcc -std=gnu++11 -Wall -Wextra -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=$(avrType) obj/*.o -o bin/$@ -lm

main.hex:
	avr-objcopy -O ihex -R .eeprom bin/main.elf bin/main.hex

upload:
	python util/trigger_bootloader.py $(programmerDev)
	sleep 1.5
	avrdude -F -V -c $(programmerType) -p $(avrType) -P $(programmerDev) -b $(baud) -D -U flash:w:bin/main.hex