PROJECT     = vpr-overwatch
VERSION     = 0.1

ifeq ($(PREFIX),)
PREFIX    = /usr/local
endif

CMAKE       = cmake
TOOLCHAIN   = -DCMAKE_TOOLCHAIN_FILE="gcc-gnu-toolchain.cmake"

BIN         = bin
BUILD       = build
SOURCE      = src
INCLUDE     = include
TEST        = src/test

SOURCES     = $(wildcard $(SOURCE)/*.c)
OBJECTS     = $(patsubst $(SOURCE)/%.c,$(BUILD)/CMakeFiles/$(PROJECT).dir/$(SOURCE)/%.c.o,$(SOURCES))

all: $(PROJECT)
release: $(PROJECT)

$(PROJECT):
	$(CMAKE) -B $(BUILD) $(TOOLCHAIN)
	$(CMAKE) --build $(BUILD) $(CMAKE_FLAGS)

.PHONY: $(OBJECTS)
CMakeLists.txt: $(OBJECTS)
	make clean

.PHONY: install
install: $(PROJECT)
	cp $(BIN)/$(PROJECT) $(BIN)/$(PROJECT)
	install -d $(PREFIX)/bin
	install -m 555 $(BIN)/$(PROJECT) $(PREFIX)/bin

.PHONY: release
release:
	zip $(PROJECT)-$(VERSION).zip $(BIN)/$(PROJECT)

clean:
	rm -fr ./bin/*
	rm -fr ./lib/*
	rm -fr ./build/*
	rm -f ./*.zip
	rm -f ./*log.txt
	rm -f ./temp.txt

extra-clean:
	rm -fr ./bin
	rm -fr ./lib
	rm -fr ./build
	rm -f ./*.zip
	rm -f ./*log.txt
	rm -f ./temp.txt
