// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      mainWinCallback.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     How to assign the main window callback.@EOL
 @keywords  fltk window callback
 @std       C++98 FLTKv1.3
 @see       
 @copyright 
  @parblock
  Copyright (c) 2003, 2017, Mitchell Jay Richling <https://www.mitchr.me> All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this list of conditions, and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions, and the following disclaimer in the documentation
     and/or other materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software
     without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
  DAMAGE.
  @endparblock
 @filedetails   

  The main window callback is invoked when the close button is hit.  This program illustrates how to bind this callback to a function that will quit the
  application -- this is actually the default behavior.  Use this callback to take care of things before an application is closed!

***************************************************************************************************************************************************************/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <FL/Fl.H>              /* FLTK main       FLTK  */
#include <FL/Fl_Window.H>       /* FLTK window     FLTK  */

#include <stdio.h>              /* I/O lib         ISOC  */
#include <stdlib.h>             /* Standard Lib    ISOC  */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void daWinCall(Fl_Widget *w, void *uData)
{
  printf("The window callback was called.\n");
  exit(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
  Fl_Window win(500, 500, "Main Window Callback Example Program");
  win.callback(daWinCall);
  win.show();
  return Fl::run();
}

