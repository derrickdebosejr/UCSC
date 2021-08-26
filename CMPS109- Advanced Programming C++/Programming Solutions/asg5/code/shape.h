// $Id: shape.h,v 1.2 2016-05-04 16:26:26-07 - - $
/*
 * Partner: Evan Suther (esuther@ucsc.edu)
 * Partner: Derrick DeBose (ddebose@ucsc.edu)
 */

#ifndef __SHAPE_H__
#define __SHAPE_H__

#include <iomanip>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
using namespace std;

#include "rgbcolor.h"

//
// Shapes constitute a single-inheritance hierarchy, summarized
// here, with the superclass listed first, and subclasses indented
// under their immediate superclass.
//
// shape
//    text
//    ellipse
//       circle
//    polygon
//       rectangle
//          square
//       diamond
//       triangle
//          right_triangle
//          isosceles
//          equilateral
//

class shape;
struct vertex {
   GLfloat xpos; 
   GLfloat ypos;
   //void inc_xpos(GLfloat xcenter){xpos = xpos + xcenter;}
   //void inc_ypos(GLfloat ycenter){ypos = ypos + ycenter;}
   /*void norm(const vertex center){
      xpos = xpos + center.xpos;
      ypos = ypos + center.ypos;
   }*/
};
using vertex_list = vector<vertex>;
using shape_ptr = shared_ptr<shape>; 

//
// Abstract base class for all shapes in this system.
//

class shape {
   friend ostream& operator<< (ostream& out, const shape&);
   protected:
      inline shape(); // Only subclass may instantiate.
   public:
      shape (const shape&) = delete; // Prevent copying.
      shape& operator= (const shape&) = delete; // Prevent copying.
      shape (shape&&) = delete; // Prevent moving.
      shape& operator= (shape&&) = delete; // Prevent moving.
      virtual ~shape() {}
      virtual void draw (const vertex&, const rgbcolor&) const = 0;
      virtual void show (ostream&) const;
};


//
// Class for printing text.
//

class text: public shape {
   protected:
      void* glut_bitmap_font = nullptr;
      // GLUT_BITMAP_8_BY_13
      // GLUT_BITMAP_9_BY_15
      // GLUT_BITMAP_HELVETICA_10
      // GLUT_BITMAP_HELVETICA_12
      // GLUT_BITMAP_HELVETICA_18 
      // GLUT_BITMAP_TIMES_ROMAN_10
      // GLUT_BITMAP_TIMES_ROMAN_24
      string textdata;
   public:
      text (void* glut_bitmap_font, const string& textdata);
      virtual void draw (const vertex&, const rgbcolor&) const override;
      virtual void show (ostream&) const override;
};

//
// Classes for ellipse and circle.
//

class ellipse: public shape {
   protected:
      vertex dimension;
   public:
      ellipse (GLfloat width, GLfloat height);
      virtual void draw (const vertex&, const rgbcolor&) const override;
      virtual void show (ostream&) const override;
};

class circle: public ellipse {
   public:
      circle (GLfloat diameter);
};

//
// Class polygon.
//

class polygon: public shape {
   protected:
      vertex_list vertices;
   public:
      polygon (const vertex_list& vertices);
      virtual void draw (const vertex&, const rgbcolor&) const override;
      virtual void show (ostream&) const override;
      vertex_list make_rec_ver(GLfloat width, GLfloat height);
      vertex_list make_dia_ver(GLfloat width, GLfloat height);
      vertex_list make_equ_ver(GLfloat width);
};


//
// Classes rectangle, square, etc.
//

class rectangle: public polygon {
   public:
      rectangle (GLfloat width, GLfloat height);
};

class equilateral: public polygon {
   public:
      equilateral (GLfloat width);
};

class square: public rectangle {
   public:
      square (GLfloat width);
};

class diamond: public polygon {
   public:
      diamond (GLfloat width, GLfloat height);
};

ostream& operator<< (ostream& out, const shape&);


#endif

