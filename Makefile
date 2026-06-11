.PHONY: build rebuild clean

build:
	ninja -C build

rebuild:
	meson setup build --reconfigure && ninja -C build

clean:
	ninja -C build -t clean