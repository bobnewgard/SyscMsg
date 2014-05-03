#
# Copyright 2013 Robert Newgard
#
# This file is part of SyscMsg.
#
# SyscMsg is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# SyscMsg is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with SyscMsg.  If not, see <http://www.gnu.org/licenses/>.
#

# define library name
# ------------------------------------------------------------------------------
LNAM := syscmsg
#
# clear rules
# ------------------------------------------------------------------------------
MAKEFLAGS += --no-builtin-rules
.SUFFIXES:
#
# includes
# ------------------------------------------------------------------------------
include dep.mk
#
# defines
# ------------------------------------------------------------------------------
define print-hint-header
	@col=$$(tput cols) ; while [ "$$col" -gt 0 ] ; do echo -n '-' ; col=$$(($$col - 1)) ; done
	@echo
endef
#
define print-hints
	@echo "lib        build library"
	@echo "test       build test"
	@echo "run        run test"
	@echo "dox        doxygen generate"
	@echo "clean      remove build intermediates"
	@echo "spotless   remove build intermediates and library"
endef
#
define compile-for-obj
	g++ $(CXX_VER) -c $(DFLAGS) $(IPATH) -Wall $(CFLAGS) -o $@ $<
endef
#
define ar-for-archive
        ar cr $@ $%
endef
#
define link-for-shared-obj
	g++ $(CFLAGS) -shared -Wl,--whole-archive $^ -Wl,--no-whole-archive -o $@
endef
#
define link-for-executable
	g++ $(CFLAGS) -o $@ $(LPATH) $(LFLAGS) -l$(LNAM) $<
endef
#
define cpp-for-depends
	@echo "[INF] building $@"
	rm -f $@
        for file in $^ ; do cpp $(CXX_VER) -MM -MG $(IPATH) $$file ; done >> $@
        for file in $^ ; do cpp $(CXX_VER) -MM -MG -MT $@ $(IPATH) $$file >> $@ ; done
endef
#
define lib-sources
	SyscMsg.cxx
endef
#
define phonys
    run clean hint hint-header
endef

define dox
        rm -f Readme.md
        echo "\\mainpage %SyscMsg Project" >> Readme.md
        cat README.md >> Readme.md
        doxygen dox.conf
endef

# variables
# ------------------------------------------------------------------------------
SHELL     := /bin/bash
#
IPATH     := -I . -isystem /opt/systemc/2.3.0/include
LPATH     := -L . -L /opt/systemc/2.3.0/lib-linux64
#
CXX_VER   := -x c++ -std=c++11
#
DFLAGS    :=
CFLAGS    := -m64 -g -pthread -fPIC
LFLAGS    := -lsystemc -pthread
#
# lib
LIB_CPP   := $(strip $(lib-sources))
LIB_OBJ   := $(patsubst %.cxx,%.o,$(LIB_CPP))
LIB_AR    := lib$(LNAM).a($(LIB_OBJ))
LIB_ARNAM := lib$(LNAM).a
LIB_SONAM := lib$(LNAM).so
#
# test
TEST_PREQ := sc_main.o $(LIB_SONAM)
#
# intermediate object files: position dependent
# ------------------------------------------------------------------------------
.INTERMEDIATE : $(LIB_OBJ)
#
# common implicit rules
# ------------------------------------------------------------------------------
(%) : % ; $(ar-for-archive)
#
# lib rules
# ------------------------------------------------------------------------------
%.o            : ./%.cxx       ; $(compile-for-obj)
$(LIB_ARNAM)   : $(LIB_AR)     ;
$(LIB_SONAM)   : $(LIB_ARNAM)  ; $(link-for-shared-obj)
dep.mk         : $(LIB_CPP)    ; $(cpp-for-depends)
#
# Other rules
# ------------------------------------------------------------------------------
hints          : hint-header   ; $(print-hints)
hint-header    :               ; $(print-hint-header)
lib            : $(LIB_SONAM)  ;
test           : $(TEST_PREQ)  ; $(link-for-executable)
run            : test          ; export LD_LIBRARY_PATH=.:/opt/systemc/2.3.0/lib-linux64 ; ./test
dox            :               ; $(dox)
clean          :               ; rm -f test *.o *.pyc
spotless       : clean         ; rm -rf *.so *.a doxygen dep.mk Readme.md
srcs           :               ; @echo \"$(LIB_CPP)\"
objs           :               ; @echo \"$(LIB_OBJ)\"
.PHONY         : $(phonys)     ;
#
.DEFAULT_GOAL := hints
