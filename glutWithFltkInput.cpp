// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      glutWithFltkInput.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Simple GLUT-like code with FLTK interaction code.@EOL
 @keywords  glut fltk x11 graphics opengl
 @std       FLTKv1.3 C++98
 @copyright 
  @parblock
  Copyright (c) 2013, 2017, Mitchell Jay Richling <https://www.mitchr.me> All rights reserved.

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

  FLTK has an effective GLUT compatibility mode, but this functionality is more than just for compatibility.  This program
  demonstrates how to use FLTK's I/O facilities and windowing control with the goodness of GLUT.

***************************************************************************************************************************************************************/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>             /* Standard Lib    ISOC  */
#include <stdio.h>              /* I/O lib         ISOC  */

#include <FL/Fl.H>              /* FLTK main       FLTK  */
#include <FL/Fl_Window.H>       /* FLTK window     FLTK  */
#include <FL/Fl_Box.H>          /* FLTK box        FLTK  */
#include <FL/Fl_Button.H>       /* FLTK button     FLTK  */
#include <FL/Fl_Gl_Window.H>    /* FLTK OpenGL     FLTK  */
#include <FL/gl.h>              /* FLTK OpenGL     FLTK  */
#include <FL/glu.h>              /* FLTK OpenGL     FLTK  */
#include <FL/glut.H>            /* FLTK GLUT       FLTK  */

#ifdef __APPLE__
#include <OpenGL/glu.h>         /* Open GL Stuff   APPLE */
#else
#include <GL/glu.h>             /* Open GL Stuff   Linux */
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class myGLwindow : public Fl_Gl_Window
{
    void computeCurve();
    int handle(int event);
    void draw();
  public:
    myGLwindow(int x,int y,int w,int h,const char *l=0) : Fl_Gl_Window(x,y,w,h,l) {
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void myGLwindow::draw()
{
  if(!valid()) {  //valid() is magic set after first draw() call.
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40, 1, 10, 120);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 50, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glScalef(.3,.3,.3);
    
    computeCurve();
  }
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glCallList(1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int myGLwindow::handle(int event)
{
  static int x, y;
  static float rx, ry;
  switch(event) {
  case FL_PUSH:
    // mouse down pos in Fl::event_x() and Fl::event_y()
    x = Fl::event_x();
    y = Fl::event_y();
    return 1;
  case FL_DRAG: 
  {
    int cx = Fl::event_x();
    int cy = Fl::event_y();
    if(abs(x-cx)<100 && abs(y-cy)<100) {
      rx += -(x-cx)*0.5;
      ry += -(y-cy)*0.5;
      
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      gluLookAt(0, 0, 50, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
      glScalef(.3,.3,.3);
      glRotatef(ry, 1, 0, 0);
      glRotatef(rx, 0, 1, 0);
      redraw();
    }
    x = cx;
    y = cy;
  }
  return 1;
  case FL_RELEASE:
    return 1;
  case FL_FOCUS:
    return 1;                     // return 1 to get keyboard events
  case FL_UNFOCUS:
    return 1;                     // Return 1 to get keyboard events
  case FL_KEYBOARD:
                                  // key in Fl::event_key(), ascii in Fl::event_text()
    printf("Key: %s\n", Fl::event_text());
    return 0;                     // return 1 input was understood
  case FL_SHORTCUT:
                                  // key in Fl::event_key(), ascii in Fl::event_text()
    return 0;                     // return 1 input was understood
  default:
    return 1;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void myGLwindow::computeCurve()
{
  int maxBalls    = 5000;
  double tDelta   = 0.01;
  double x = 0.11;
  double y = 0.0;
  double z = 0;
  double a = 10;
  double b = 28;
  double c = 8.0 / 3.0;
  int numBalls;
  double xNew, yNew, zNew;

  glNewList(1, GL_COMPILE);
  glColor3f(1,1,1);
  glPointSize(1.0);
  glBegin(GL_LINE_STRIP);
  for(numBalls=0;numBalls<maxBalls;numBalls++) {
    xNew = x + a*(y-x)*tDelta;
    yNew = y + (x*(b-z)-y)*tDelta;
    zNew = z + (x*y-c*z)*tDelta;
    glColor3f(1.0*numBalls/maxBalls, 0.2, 1.0-numBalls/maxBalls);
    glVertex3f(xNew, yNew, zNew);
    x=xNew;
    y=yNew;
    z=zNew;
  }
  glEnd();

  // Draw the x/y/z axis
  glBegin(GL_LINE_STRIP);
  glColor3f(1, 0, 0);
  glVertex3f(0, 0, 0);
  glVertex3f(40, 0, 0);
  glVertex3f(0, 0, 0);
  glColor3f(0, 1, 0);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 40, 0);
  glVertex3f(0, 0, 0);
  glColor3f(0, 0, 1);
  glVertex3f(0, 0,  0);
  glVertex3f(0, 0, 40);
  glEnd();

  // Draw the box
  glBegin(GL_LINE_STRIP);
  glColor3f(1, 1, 1);
  glVertex3f( 40, -40, -40);
  glVertex3f( 40,  40, -40);
  glVertex3f(-40,  40, -40);
  glVertex3f(-40, -40, -40);
  glVertex3f( 40, -40, -40);

  glVertex3f( 40, -40,  40);
  glVertex3f( 40,  40,  40);
  glVertex3f(-40,  40,  40);
  glVertex3f(-40, -40,  40);
  glVertex3f( 40, -40,  40);

  glVertex3f( 40,  40,  40);
  glVertex3f( 40,  40, -40);

  glVertex3f(-40,  40, -40);
  glVertex3f(-40,  40,  40);

  glVertex3f(-40, -40,  40);
  glVertex3f(-40, -40, -40);

  glEnd();

  glEndList();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
  myGLwindow theGLwin(50, 50, 500, 500, "Interactive Lorenz Demo Program");
  theGLwin.show();

  return Fl::run();
}
