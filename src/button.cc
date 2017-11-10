// button.cpp
// by Glenn G. Chappell
// October 2003
//
// For CS 381
// Source code for Button class
// See button.h for description

#include "button.h"
#include <GL/glut.h>


// display
// Called by GLUT display function.
// Draws button appropriately, according to current state.
void Button::display()
{
   // Colors for parts of button
   const GLdouble dark1[3]        = { 0.50, 0.50, 0.50 };  // shadowed top & bottom
   const GLdouble dark2[3]        = { 0.55, 0.55, 0.55 };  // shadowed left & right
   const GLdouble light1[3]       = { 0.90, 0.90, 0.90 };  // unshadowed top & bottom
   const GLdouble light2[3]       = { 0.85, 0.85, 0.85 };  // unshadowed left & right
   const GLdouble main[3]         = { 0.70, 0.70, 0.70 };  // center part of button
   const GLdouble activetext[3]   = { 0.00, 0.00, 0.00 };  // text color when button is active
   const GLdouble inactivetext[3] = { 0.50, 0.50, 0.50 };  // text color when button is inactive

   // Other constants describing button
   const double inset = 0.02;             // How far in slanted sides of button extend
   const double textscale = 0.0007;       // Factor for scaling GLUT stroke text
   const double gluttextheight = 119.05;  // Height of GLUT stroke text, from GLUT doc's

   // Draw various non-text parts of button
   glBegin(GL_QUADS);
      // Draw button top
      glColor3dv(pressed ? dark1 : light1);
      glVertex2d(left, bottom+height);
      glVertex2d(left+inset, bottom+height-inset);
      glVertex2d(left+width-inset, bottom+height-inset);
      glVertex2d(left+width, bottom+height);

      // Draw button left
      glColor3dv(pressed ? dark2 : light2);
      glVertex2d(left, bottom);
      glVertex2d(left+inset, bottom+inset);
      glVertex2d(left+inset, bottom+height-inset);
      glVertex2d(left, bottom+height);

      // Draw button bottom
      glColor3dv(pressed ? light1 : dark1);
      glVertex2d(left+width, bottom);
      glVertex2d(left+width-inset, bottom+inset);
      glVertex2d(left+inset, bottom+inset);
      glVertex2d(left, bottom);

      // Draw button right
      glColor3dv(pressed ? light2 : dark2);
      glVertex2d(left+width, bottom+height);
      glVertex2d(left+width-inset, bottom+height-inset);
      glVertex2d(left+width-inset, bottom+inset);
      glVertex2d(left+width, bottom);

      // Draw buttom center
      glColor3dv(main);
      glVertex2d(left+inset, bottom+inset);
      glVertex2d(left+width-inset, bottom+inset);
      glVertex2d(left+width-inset, bottom+height-inset);
      glVertex2d(left+inset, bottom+height-inset);
   glEnd();

   // Figure out height & width of text label
   double labelheight = gluttextheight * textscale;
   double labelwidth = 0.;
   string::const_iterator ii;
   for (ii=label.begin(); ii!=label.end(); ++ii)
   {
      labelwidth += glutStrokeWidth(GLUT_STROKE_ROMAN, *ii);
   }
   labelwidth *= textscale;

   // Draw text label, centered on button
   GLdouble savelinewidth;  // Save current line width for later restoring
   glGetDoublev(GL_LINE_WIDTH, &savelinewidth);
   glLineWidth(1.0);
   glPushMatrix();
      glTranslated(left+width/2.-labelwidth/2., bottom+height/2.-labelheight/2., 0.);
      glScaled(textscale, textscale, 1.);
      glColor3dv(active ? activetext : inactivetext);
      for (ii=label.begin(); ii!= label.end(); ++ii)
      {
         glutStrokeCharacter(GLUT_STROKE_ROMAN, *ii);
      }
   glPopMatrix();
   glLineWidth(savelinewidth);  // Restore line width
}


// handlemouse
// Called by GLUT mouse function, using its own parameters.
// Determines whether mouse click is for this button.
// If so, handles it and returns true;
//  otherwise, returns false.
// Assumes no rotations or shears in transformation matrices.
bool Button::handlemouse(int button, int state, int x, int y)
{
   if (button != GLUT_LEFT) return false;

   bool ismine;  // Is this *my* button press (i.e., am I going to handle it)?
   bool inbutton = mouseinbutton(x, y);  // Is this mouse click inside me?

   if (state == GLUT_DOWN && active)  // Handle button-down if active
   {
      ismine = inbutton;
      trackingmouse = inbutton;
      if (pressed != inbutton)
      {
         pressed = inbutton;
         glutPostRedisplay();
      }
   }
   else if (state == GLUT_UP && trackingmouse)  // Handle button-up if tracking mouse
   {
      ismine = true;
      trackingmouse = false;
      if (pressed)
      {
         pressed = false;
         glutPostRedisplay();
      }
      if (active && inbutton && actionfunc) actionfunc();
   }
   else
   {
      ismine = false;
   }

   return ismine;
}


// handlemotion
// Called by GLUT motion function, using its own parameters.
// Determines whether mouse movement is for this button.
// If so, handles it and returns true;
//  otherwise, returns false.
// Assumes no rotations or shears in transformation matrices.
bool Button::handlemotion(int x, int y)
{
   bool ismine;  // Is this *my* button press (i.e., am I going to handle it)?
   bool inbutton = mouseinbutton(x, y);  // Is this mouse click inside me?

   if (trackingmouse)
   {
      if (pressed != inbutton)
      {
         pressed = inbutton;
         glutPostRedisplay();
      }
      ismine = true;
   }
   else
   {
      ismine = false;
   }

   return ismine;
}


// mouseinbutton - internal use only
// Given a mouse position, in GLUT format
// Determines whether this position lies inside the button.
// Assumes no rotations or shears in transformation matrices.
bool Button::mouseinbutton(int x, int y)
{
   return inrect(x, y, left, bottom, left+width, bottom+height);
}


// *******************************************************
// The following was copied from "mouseinrect.cpp".
// Only minor changes have been made.
// (Changed lines are marked with "%%".)
// *******************************************************

// inrect - internal use only %%
// Given a position (in the format that GLUT gives mouse positions)
//  and the boundaries of a screen-aligned rectangle, in 2-D object coordinates.
// Determine whether the position lies in the rectangle.
// Returns true if so, false if not.
// Assumes that the various transformations do not contain any rotations or shears;
//  only translation, scaling, and the usual projections are allowed.
bool Button::inrect(int mx, int my,  // position, as GLUT gives mouse positions %%
                    double left, double bottom, double right, double top)    // %%
                                     // bdaries of rectangle (object coord's)   %%
{
   // GLUT likes y to increase top-to-bottom; OpenGL prefers bottom-to-top.
   // We convert GLUT-style y-coord "my" to OpenGL-style "my2".

   const int window_height = glutGet(GLUT_WINDOW_HEIGHT);  // Get window height
   const int my2 = window_height - my;                     // Convert "my" to zero-at-bottom

   // Now convert mx, my2 to eye coordinates in ex, ey.
   // Range is -1..+1 in both coords, with -1 being the left (resp. bottom) side
   //  of the viewport, and +1 being the right (resp. top).

   GLint viewport_dims[4];
   glGetIntegerv(GL_VIEWPORT, viewport_dims);  // Get viewport left, bottom, width, height
   const double ex = double(mx  - viewport_dims[0])/viewport_dims[2]*2.-1.;
   const double ey = double(my2 - viewport_dims[1])/viewport_dims[3]*2.-1.;

   // Get the model/view & projection transformation matrices.

   GLdouble modelviewd[16];
   glGetDoublev(GL_MODELVIEW_MATRIX, modelviewd);    // Get model/view matrix
   GLdouble projectiond[16];
   glGetDoublev(GL_PROJECTION_MATRIX, projectiond);  // Get projection matrix

   // Multiply the model/view & projection matrices together to obtain a single
   //  matrix representing the combination of the two transformations.
   // Store this matrix in the array "mymatrix".

   double mymatrix[4][4];  // Holds combination matrix
   int i, j, k;            // Loop counters
   for (i=0; i<4; ++i)
   {
      for (j=0; j<4; ++j)
      {
         double value = 0.;
         for (k=0; k<4; ++k)
         {
            value += modelviewd[i+4*k] * projectiond[k+4*j];
         }
         mymatrix[i][j] = value;
      }
   }

   // Convert the point (left, bottom) from object coordinates to eye coordinates:
   //  multiply the combination model/view+projection matrix by (left, bottom, 0).

   double vertin[4], vertout[4];  // Hold original & transformed vertices, respectively.
   vertin[0] = left;
   vertin[1] = bottom;
   vertin[2] = 0.;
   vertin[3] = 1.;
   for (i=0; i<4; ++i)
   {
      double value = 0.;
      for (j=0; j<4; ++j)
      {
         value += (mymatrix[i][j]*vertin[j]);
      }
      vertout[i] = value;
   }
   double eye_left   = vertout[0]/vertout[3];
   double eye_bottom = vertout[1]/vertout[3];

   // Convert the point (right, top) from object coordinates to eye coordinates:
   //  multiply the combination model/view+projection matrix by (right, top, 0).

   vertin[0] = right;
   vertin[1] = top;
   vertin[2] = 0.;
   vertin[3] = 1.;
   for (i=0; i<4; ++i)
   {
      double value = 0.;
      for (j=0; j<4; ++j)
      {
         value += (mymatrix[i][j]*vertin[j]);
      }
      vertout[i] = value;
   }
   const double eye_right  = vertout[0]/vertout[3];
   const double eye_top    = vertout[1]/vertout[3];

   // Now we have the given position and rectangle boundaries, all in eye coordinates.
   // Check whether the position lies inside the rectangle, and return the appropriate bool.
   // We check ">=" for one boundary, "<" for opposite boundary, to guarantee that
   //  the mouse will never lie inside both of two rectangles that share a boundary edge.

   return (ex >= eye_left
        && ex <  eye_right
        && ey >= eye_bottom
        && ey <  eye_top);
}

// *******************************************************
// End of code copied from "mouseinrect.cpp".
// *******************************************************
