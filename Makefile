.PHONY: build rebuild debug asan clean

build:
	ninja -C build

rebuild:
	meson setup build --reconfigure --buildtype=debug
	ninja -C build

debug:
	meson setup build --reconfigure --buildtype=debug
	ninja -C build
	gdb build/playon

asan:
	meson setup build --reconfigure --buildtype=debug -Db_sanitize=address
	ninja -C build

clean:
	ninja -C build -t clean