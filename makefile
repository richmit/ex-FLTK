# -*- Mode:Makefile; Coding:us-ascii-unix; fill-column:158 -*-
################################################################################################################################################################
##
# @file      makefile
# @author    Mitch Richling <https://www.mitchr.me>
# @brief     Build example FLTK programs.@EOL
# @keywords  fltk make c++ opengl glut gui x11
# @std       GNUmake
# @copyright 
#  @parblock
#  Copyright (c) 1997,2017, Mitchell Jay Richling <https://www.mitchr.me> All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
#
#  1. Redistributions of source code must retain the above copyright notice, this list of conditions, and the following disclaimer.
#
#  2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions, and the following disclaimer in the documentation
#     and/or other materials provided with the distribution.
#
#  3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without
#     specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
#  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
#  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
#  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#  @endparblock
################################################################################################################################################################

################################################################################################################################################################

FLUID = /Applications/DarwinPorts/fltk/fluid
FLUID = /usr/bin/fluid

XGLL = -lGLU -lGL

# Uncomment to build all when make file changes
#SPECDEP=makefile

# Put targets here
TARGETS = minimalFLTK mainWinCallback simpleButton simpleButtonOO glutWithFltk glutWithFltkInput simpleFluid

################################################################################################################################################################

CXX      := $(shell fltk-config --use-glut --use-gl --cxx)

CXXFLAGS := $(shell fltk-config --use-glut --use-gl --cxxflags)

# Note the -lGLU & -lGL at the end of the following command line.  This is required on some platforms, but may cause issues on others.  Adjust as necessary.

LDFLAGS  := $(shell fltk-config --use-glut --use-gl --ldflags) 
#-lGLU -lGL

################################################################################################################################################################

all : $(TARGETS)
	@echo Make Complete

clean :
	rm -rf a.out *~ *.bak $(TARGETS)
	rm -rf simpleFluid.cpp simpleFluid.h
	@echo Make Complete

########################################################################################################################

minimalFLTK : minimalFLTK.cpp $(SPECDEP)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) minimalFLTK.cpp -o minimalFLTK

mainWinCallback : mainWinCallback.cpp $(SPECDEP)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) mainWinCallback.cpp -o mainWinCallback

simpleButton : simpleButton.cpp $(SPECDEP)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) simpleButton.cpp -o simpleButton

simpleButtonOO : simpleButtonOO.cpp $(SPECDEP)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) simpleButtonOO.cpp -o simpleButtonOO

glutWithFltk : glutWithFltk.cpp $(SPECDEP)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) glutWithFltk.cpp -o glutWithFltk

glutWithFltkInput : glutWithFltkInput.cpp $(SPECDEP)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) glutWithFltkInput.cpp -o glutWithFltkInput

simpleFluid.cpp : simpleFluid.fl $(SPECDEP)
	$(FLUID) -c -o simpleFluid.cpp -h simpleFluid.h simpleFluid.fl

simpleFluid : simpleFluid.cpp simpleFluid.h  $(SPECDEP)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) simpleFluid.cpp -o simpleFluid
