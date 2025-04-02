PROJECT     = overwatch
VERSION     = 1.0.1

ifeq ($(PREFIX),)
PREFIX      = /usr/local
endif

CMAKE       = cmake

BIN         = bin
BUILD       = build
SOURCE      = $(PROJECT)

SOURCES     = $(wildcard $(SOURCE)/*.cpp)
OBJECTS     = $(patsubst $(SOURCE)/%.cpp,$(BUILD)/CMakeFiles/$(PROJECT).dir/$(SOURCE)/%.cpp.o,$(SOURCES))

all: $(PROJECT)
release: $(PROJECT)
tests: bin/vpr-$(PROJECT)-tests

$(PROJECT): $(OBJECTS)
	$(CMAKE) -B $(BUILD)
	$(CMAKE) --build $(BUILD) $(CMAKE_FLAGS)

bin/vpr-$(PROJECT)-tests: $(PROJECT)
	./$@

.PHONY: $(OBJECTS)
CMakeLists.txt: $(OBJECTS)
	make clean

.PHONY: clean
clean:
	rm -fr ./bin/*
	rm -fr ./lib/*
	rm -fr ./build/*
	rm -f ./*.zip
	rm -f ./*log.txt
	rm -f ./temp.txt

.PHONY: extra-clean
extra-clean:
	rm -fr ./bin
	rm -fr ./lib
	rm -fr ./build
	rm -f ./*.zip
	rm -f ./*log.txt
	rm -f ./temp.txt
