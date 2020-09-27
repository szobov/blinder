compile:
	arduino -v --verify --board esp8266:esp8266:nodemcuv2 --port /dev/ttyUSB0 robo_roller_blinds.ino

upload:
	arduino -v --upload --board esp8266:esp8266:nodemcuv2 --port /dev/ttyUSB0 robo_roller_blinds.ino


.PHONY = compile
