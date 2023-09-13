# ----------------------------------------------------------------------------
# SOSpin Library
# Copyright (C) 2023 SOSpin Project
#
#   Authors:
#
#     Nuno Cardoso (nuno.cardoso@tecnico.ulisboa.pt)
#     David Emmanuel-Costa (david.costa@tecnico.ulisboa.pt)
#     Nuno Gonçalves (nunogon@deec.uc.pt)
#     Catarina Simoes (csimoes@ulg.ac.be)
#
# ----------------------------------------------------------------------------
# This file is part of SOSpin Library.
#
# SOSpin Library is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or any
# later version.
#
# SOSpin Library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with SOSpin Library.  If not, see <http:#www.gnu.org/licenses/>.
# ----------------------------------------------------------------------------

BUILD = build
OUT = out

CURRENT_DIR = $(shell pwd)
BUILD := $(CURRENT_DIR)/$(BUILD)
OUT := $(CURRENT_DIR)/$(OUT)
BUILT = $(BUILD)/.built
INSTALLED = $(BUILD)/install_manifest.txt

OPTION_SOURCES := -name '*.c' -o -name '*.cc' -o -name '*.cxx' -o -name '*.cpp'
OPTION_HEADERS := -name '*.h' -o -name '*.hxx'
OPTION_ALL := $(OPTION_SOURCES) -o $(OPTION_HEADERS)

SOURCES := $(shell find $(CURRENT_DIR)/src $(OPTION_SOURCES))
SOURCES += $(shell find $(CURRENT_DIR)/app $(OPTION_SOURCES))
HEADERS := $(shell find $(CURRENT_DIR)/include $(OPTION_HEADERS))
TEST_SOURCES := $(shell find $(CURRENT_DIR)/test $(OPTION_ALL))

all : $(BUILT)
	@#

# Building and install chain
$(BUILD) :
	@cmake -S . -B $(BUILD)

$(BUILT) : $(HEADERS) $(SOURCES) $(TEST_SOURCES) $(BUILD)
	@cmake --build $(BUILD) && touch $(BUILT)

$(INSTALLED) : $(BUILT)
	@cmake --install $(BUILD) 

# Commands
.PHONY : clean build install test doxygen-doc doc format info

clean :
	@find . -name ".DS_Store" -name ".project"  -name ".cproject" | xargs rm -rf
	@find . -name "build" | xargs rm -rf
	@rm -rf .settings .vscode $(OUT) $(BUILD)

build :
	@cmake --build $(BUILD) && touch $(BUILT)

install : $(BUILT) 
	@cmake --install $(BUILD)

test : $(BUILD) $(BUILT)
	@ctest --test-dir $(BUILD) --output-on-failure

doxygen-doc : $(BUILT)
	@make -f $(BUILD)/doc/Makefile doxygen-doc

doc : doxygen-doc
	@#

format : $(SOURCES) $(HEADERS)
	@for item in $^ ; do clang-format -i $$item; done

info :
	@echo Headers:
	@for item in $(HEADERS) ; do echo "    $$item"; done
	@echo Sources:
	@for item in $(SOURCES) ; do echo "    $$item"; done
	@echo Test Sources:
	@for item in $(TEST_SOURCES) ; do echo "    $$item"; done
