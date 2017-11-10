// button.h
// by Glenn G. Chappell
// October 2003
//
// For CS 381
// Header for Button class

#ifndef BUTTON_H_GGC  // Have we already included this file?
#define BUTTON_H_GGC

#include <string>
using std::string;


// **************************************************************
// class Button
// **************************************************************

// Simple button class
// For use in OpenGL/GLUT programs
//
// To create a button object, call the constructor, then set properties with:
//    setpos    - position of lower-left corner of button (in object coord's)
//    setsize   - button size (in object coord's)
//    setlabel  - button's text label
//    setaction - function to call when button is pressed, or NULL if none.
//    setactive - set button's active/inactive state
// Active buttons are drawn with black text; they respond to the mouse.
// Inactive buttons are drawn with gray text; they ignore mouse-down events.
// When a button press is detected, the action function is called.
//
// Then call the following member functions:
//    display      - in the GLUT display function
//    handlemouse  - in the GLUT mouse function
//    handlemotion - in the GLUT motion function
// The latter two functions return true if the current mouse click/motion
// is being handled by this button, false otherwise.
//
// To hide a button, do not call the above functions.
// Button objects are destroyed using the destructor, as usual.

class Button
{

// ***** Button ctor(s), dctor *****
public:
   Button():
      left(0.),bottom(0.),width(1.),height(1.),label("Button"),actionfunc(0),
      active(false),trackingmouse(false),pressed(false)
   {}
   ~Button() {}

// ***** Button public interface *****
public:
   void setpos(double theleft, double thebottom)
      // Set button position
   { left = theleft; bottom = thebottom; }
   void setsize(double thewidth, double theheight)
      // Set button size
   { width = thewidth; height = theheight; }
   void setlabel(const string & thelabel)
      // Set button label
   { label = thelabel; }
   void setaction(void (* theactionfunc)())
      // Set button action callback (NULL for none)
   { actionfunc = theactionfunc; }
   void setactive(bool activestate)
      // Set button active/inactive
   { active = activestate; }

   void display();
      // Called by GLUT display function.
      //  Display button using current model/view transformation
   bool handlemouse(int button, int state, int x, int y);
      // Called by GLUT mouse function, using its parameters.
      //  Returns true if this is "my" mouse click; false otherwise.
   bool handlemotion(int x, int y);
      // Called by GLUT motion function, using its parameters.
      //  Returns true if this is "my" mouse motion; false otherwise.

// ***** Button disabled functions *****
private:
   // We do not want anyone using our copy ctor, operator=
   //  So we declare them private, and we do not define them.
   Button(const Button & other);
   Button & operator=(const Button & rhs);

// ***** Button internal-use functions *****
private:
   bool mouseinbutton(int x, int y);
      // Determine whether mouse position (from GLUT) is in this button
   bool inrect(int x, int y,
               double left, double bottom, double right, double top);
      // Determine whether position lies in rectangle.
      // Copied from "mouseinrect.cpp".

// ***** Button data members *****
private:
   // Var's holding application-settable button properties
   double left, bottom;   // lower-left corner of button, in object coord's
   double width, height;  // size of button rectangle, in object coord's
   string label;          // text label for button
   void (* actionfunc)(); // Function to call when button-press-release
                          //  event happens. If null, no action
   bool active;           // true if button is active
                          //  inactive button is shown with grayed text

   // Var's holding current button state
   bool trackingmouse;    // true if we are currently handling a mouse-down
                          //  in this button
   bool pressed;          // true if button currently has "pressed"
                          //  appearance
};


#endif // #ifdef BUTTON_H_GGC
