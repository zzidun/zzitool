CC:= g++

TINY_TARGET:= string_sort

MAKEFILE_PATH:= $(abspath $(lastword $(MAKEFILE_LIST)))
CUR_DIR:= $(patsubst %/Makefile, %, $(MAKEFILE_PATH))

OUTPUT_DIR:= $(CUR_DIR)/bin
BUILD_DIR:= $(CUR_DIR)/build
INSTALL_DIR:= /opt/tiny-tool

.PHONY: all
all : $(TINY_TARGET)

%: %.cc
	mkdir -p $(OUTPUT_DIR)
	$(CC) $^ -o $(OUTPUT_DIR)/$@

.PHONY: install
install: all
	mkdir -p $(INSTALL_DIR)
	mv $(OUTPUT_DIR)/* $(INSTALL_DIR)/

.PHONY: remove
remove: all
	rm -r $(INSTALL_DIR)

.PHONY: clean
clean:
ifneq ($(wildcard $(BUILD_DIR) ), )
	rm -r $(BUILD_DIR)
endif

.PHONY: distclean
distclean:
ifneq ($(wildcard $(OUTPUT_DIR) ), )
	rm -r $(OUTPUT_DIR)
endif
ifneq ($(wildcard $(BUILD_DIR) ), )
	rm -r $(BUILD_DIR)
endif