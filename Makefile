# Hardware version
MCU = atmega32u4

# Compilation
CXX = avr-g++
CXXFLAGS = -Wall -Wextra -mmcu=$(MCU) -O3
INCLUDES = -I. -I/usr/avr/include

# Getting onto hardware
AVRDUDE = avrdude
AVR_DEVICE ?= m32u4
AVR_PROGRAMMER ?= avr109
AVR_PORT ?= /dev/ttyACM1

# Files
BINARY = aqi
OBJECTS = main.o

.PHONY: all clean upload

all: $(BINARY).hex

$(BINARY).hex: $(BINARY)
	avr-objcopy -O ihex $< $@

$(BINARY): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJECTS) -o $@
	@avr-size $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -c -o $@

clean:
	@rm -rf $(OBJECTS) $(BINARY).hex $(BINARY)

upload: $(BINARY).hex
	$(AVRDUDE) -c $(AVR_PROGRAMMER) -p $(AVR_DEVICE) -P $(AVR_PORT) -U flash:w:$<
