// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      glutWithFltk.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Simple example of FLTK's GLUT compatibility features.@EOL
 @keywords  glut fltk opengl x11
 @std       FLTKv1.3 C++98
 @copyright 
  @parblock
  Copyright (c) 1993,1997,2003,2017 Mitchell Jay Richling <https://www.mitchr.me> All rights reserved.

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

  FLTK has a nice GLUT compatibility layer that makes creating sophisticated OpenGL programs a snap.  Many GLUT programs will compile out of the box with
  nothing more than a change in include path!  This tiny program is such an example -- it is a GLUT program with the include path changed.

***************************************************************************************************************************************************************/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <FL/glut.H>            /* FLTK GLUT       FLTK  */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static float r1 = 1, r2 = 0, r3 = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void displayCall()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glRotatef(0.5, r1, r2, r3);
  glCallList(1);
  glutSwapBuffers();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void idleCall()
{
  static int c = 0;
  c++;
  if(c > 100) {
    c = 0;
    if(r1 > 0) {
      r1 = 0; r2 = 1; r3 = 0;
    } else if(r2 > 0) {
      r1 = 0; r2 = 0; r3 = 1;
    } else if(r3 > 0) {
      r1 = 1; r2 = 0; r3 = 0;
    }
  }
  glutPostRedisplay();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void computeCurve()
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
  glPointSize(2.0);
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
  glEndList();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(10, 10);
  glutCreateWindow("GLUT Compatibility Mode Demo Program");
  glutDisplayFunc(displayCall);
  glutIdleFunc(idleCall);
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 500.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glScalef(.03,.03,.03);
  computeCurve();
  glutMainLoop();
  return 0;
}
