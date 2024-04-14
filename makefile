PROJECT     = vpr-overwatch
VERSION     = 1.0.0

ifeq ($(PREFIX),)
PREFIX      = /usr/local
endif

CMAKE       = cmake

BIN         = bin
BUILD       = build
SOURCE      = src
INCLUDE     = include
TEST        = src/test

SOURCES     = $(wildcard $(SOURCE)/*.cpp)
OBJECTS     = $(patsubst $(SOURCE)/%.cpp,$(BUILD)/CMakeFiles/$(PROJECT).dir/$(SOURCE)/%.cpp.o,$(SOURCES))

all: $(PROJECT)
release: $(PROJECT)

$(PROJECT):
	$(CMAKE) -B $(BUILD)
	$(CMAKE) --build $(BUILD) $(CMAKE_FLAGS)

.PHONY: $(OBJECTS)
CMakeLists.txt: $(OBJECTS)
	make clean

.PHONY: install
install: $(PROJECT)
	install -d $(PREFIX)/bin
	install -m 551 $(BIN)/$(PROJECT) $(PREFIX)/bin

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
