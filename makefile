PROJECT     = overwatch
VERSION     = 1.0.1

ifeq ($(PREFIX),)
PREFIX      = /usr/local
endif

ifneq ($(USERPROFILE),) # hack fix for windows output directory
WIN_BIN_PREFX = Debug
endif

CMAKE       = cmake

BIN         = bin
BUILD       = build
SOURCE      = $(PROJECT)

SOURCES     = $(wildcard $(SOURCE)/*.cpp)
OBJECTS     = $(patsubst $(SOURCE)/%.cpp,$(BUILD)/CMakeFiles/$(PROJECT).dir/$(SOURCE)/%.cpp.o,$(SOURCES))

TESTS       = $(BIN)/$(WIN_BIN_PREFX)/vpr-$(PROJECT)-tests

all:     $(PROJECT)
release: $(PROJECT)
tests:   $(TESTS)

$(PROJECT): $(OBJECTS)
	$(CMAKE) -B $(BUILD)
	$(CMAKE) --build $(BUILD) $(CMAKE_FLAGS)

.PHONY: $(TESTS)
$(TESTS): $(PROJECT)
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
