sources := \
$(wildcard Inc/*.h) \
$(wildcard Src/*.c) 

docs: $(sources) Doxyfile
	doxygen


gcc-arm-none-eabi-5_4-2016q3/bin/arm-none-eabi-gcc:
	wget https://launchpad.net/gcc-arm-embedded/5.0/5-2016-q3-update/+download/gcc-arm-none-eabi-5_4-2016q3-20160926-linux.tar.bz2
	tar xf gcc-arm-*.tar.bz2

toolchain: gcc-arm-none-eabi-5_4-2016q3/bin/arm-none-eabi-gcc

clean:
	rm -r docs