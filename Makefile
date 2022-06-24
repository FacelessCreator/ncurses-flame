.PHONY: all clear flame

all: flame

flame: build/flame
	build/flame

clear:
	rm -r build

build:
	mkdir -p build

build/flame: build src/*.cpp
	g++ src/*.cpp -lncurses -o build/flame
