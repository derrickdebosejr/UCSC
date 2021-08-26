// $Id: shape.cpp,v 1.2 2019-02-28 15:24:20-08 - - $
/*
 * Partner: Evan Suther (esuther@ucsc.edu)
 * Partner: Derrick DeBose (ddebose@ucsc.edu)
 */

#include <cmath>
#include <typeinfo>
#include <unordered_map>
using namespace std;

#include "shape.h"
#include "util.h"

static unordered_map<void*,string> fontname {
   {GLUT_BITMAP_8_BY_13       , "Fixed-8x13"    },
   {GLUT_BITMAP_9_BY_15       , "Fixed-9x15"    },
   {GLUT_BITMAP_HELVETICA_10  , "Helvetica-10"  },
   {GLUT_BITMAP_HELVETICA_12  , "Helvetica-12"  },
   {GLUT_BITMAP_HELVETICA_18  , "Helvetica-18"  },
   {GLUT_BITMAP_TIMES_ROMAN_10, "Times-Roman-10"},
   {GLUT_BITMAP_TIMES_ROMAN_24, "Times-Roman-24"},
};

static unordered_map<string,void*> fontcode {
   {"Fixed-8x13"    , GLUT_BITMAP_8_BY_13       },
   {"Fixed-9x15"    , GLUT_BITMAP_9_BY_15       },
   {"Helvetica-10"  , GLUT_BITMAP_HELVETICA_10  },
   {"Helvetica-12"  , GLUT_BITMAP_HELVETICA_12  },
   {"Helvetica-18"  , GLUT_BITMAP_HELVETICA_18  },
   {"Times-Roman-10", GLUT_BITMAP_TIMES_ROMAN_10},
   {"Times-Roman-24", GLUT_BITMAP_TIMES_ROMAN_24},
};

ostream& operator<< (ostream& out, const vertex& where) {
   out << "(" << where.xpos << "," << where.ypos << ")";
   return out;
}

shape::shape() {
   DEBUGF ('c', this);
}

text::text (void* glut_bitmap_font_, const string& textdata_):
      glut_bitmap_font(glut_bitmap_font_), textdata(textdata_) {
   DEBUGF ('c', this);
}

ellipse::ellipse (GLfloat width, GLfloat height):
dimension ({width, height}) {
   DEBUGF ('c', this);
}

circle::circle (GLfloat diameter): ellipse (diameter, diameter) {
   DEBUGF ('c', this);
}


polygon::polygon (const vertex_list& vertices_): vertices(vertices_) {
   DEBUGF ('c', this);

}

vertex_list polygon::make_equ_ver(GLfloat width){
   vertex_list vertices_;
   GLfloat height =  (width*sqrt(3.0))/2;
   vertex l {-width/2, -height/2};
   vertex r {width/2, -height/2};
   vertex t {0,height/2};
   vertices_.push_back(l);
   vertices_.push_back(r);
   vertices_.push_back(t);

   for(auto i = vertices_.begin(); i != vertices_.end(); ++i){
      cout << *i << endl;
   }
   //polygon(vertices_);
   DEBUGF ('c', this << "(" << l << "," << r << "," << t << ")" );
   
   return vertices_;
}

equilateral::equilateral (GLfloat width): polygon(make_equ_ver(width)){
   DEBUGF ('c', this);
}

vertex_list polygon::make_rec_ver(GLfloat width, GLfloat height){
   vertex_list vertices_;
   GLfloat xavg = (2 * width)/4;
   GLfloat yavg = (2 * height)/4;
   vertex bl {-xavg, -yavg};
   vertex br {xavg, -yavg};
   vertex tl {-xavg, yavg};
   vertex tr {xavg, yavg};              
   vertices_.push_back(bl);
   vertices_.push_back(br);
   vertices_.push_back(tr);
   vertices_.push_back(tl);
   for(auto i = vertices_.begin(); i != vertices_.end(); ++i){
      cout << *i << endl;
   }
   //polygon(vertices_);
   DEBUGF ('c', this << "(" << bl << "," << br << "," << tl << "," 
                     << tr << ")" );
   /*GLfloat xavg, yavg;
   for(auto i = vertices_.begin(); i != vertices_.end(); ++i){
      xavg = xavg + i->xpos;
      yavg = yavg + i->ypos;
   }
   xavg = xavg / vertices_.size();
   yavg = yavg / vertices_.size();*/
   DEBUGF ('c', this << "(" << xavg << "," << yavg << ")" );
   /*make_rec(width,height)*/
   
   return vertices_;
}

rectangle::rectangle (GLfloat width, GLfloat height):
            polygon(make_rec_ver(width, height)) {
   DEBUGF ('c', this << "(" << width << "," << height << ")" );
   
}

square::square (GLfloat width): rectangle (width, width) {
   DEBUGF ('c', this);
}

vertex_list polygon::make_dia_ver(GLfloat width, GLfloat height){
   vertex_list vertices_;
   GLfloat xavg = (2 * width)/4;
   GLfloat yavg = (2 * height)/4;
   vertex l {-xavg, 0.0};
   vertex d {0.0, -yavg};
   vertex r {xavg, 0.0};
   vertex t {0.0, yavg};              
   vertices_.push_back(l);
   vertices_.push_back(d);
   vertices_.push_back(r);
   vertices_.push_back(t);
   for(auto i = vertices_.begin(); i != vertices_.end(); ++i){
      cout << *i << endl;
   }
   //polygon(vertices_);
   DEBUGF ('c', this << "(" << l << "," << d << "," << r << "," 
                     << t << ")" );
   /*GLfloat xavg, yavg;
   for(auto i = vertices_.begin(); i != vertices_.end(); ++i){
      xavg = xavg + i->xpos;
      yavg = yavg + i->ypos;
   }
   xavg = xavg / vertices_.size();
   yavg = yavg / vertices_.size();*/
   DEBUGF ('c', this << "(" << xavg << "," << yavg << ")" );
   /*make_rec(width,height)*/
   
   return vertices_;
}

diamond::diamond (GLfloat width, GLfloat height):
            polygon(make_dia_ver(width, height)) {
   DEBUGF ('c', this << "(" << width << "," << height << ")" );
   
}

void text::draw (const vertex& center, const rgbcolor& color) const {
   DEBUGF ('d', this << "(" << center << "," << color << ")");
}

void ellipse::draw (const vertex& center, const rgbcolor& color) const {
   DEBUGF ('d', this << "(" << center << "," << color << ")");
   glBegin (GL_POLYGON);
   glColor3ubv (color.ubvec);
   const float delta = 2 * M_PI / 32;
   float width = dimension.xpos;
   float height = dimension.ypos;
   for (float theta = 0; theta < 2 * M_PI; theta += delta) {
      float xpos_ = width * cos (theta) + center.xpos;
      float ypos_ = height * sin (theta) + center.ypos;
      glVertex2f (xpos_, ypos_);
   }
   glEnd();
}

void polygon::draw (const vertex& center, const rgbcolor& color) const {
   DEBUGF ('d', this << "(" << center << "," << color << ")" );
   vertex_list vertices_ = vertices;
   for(size_t i = 0; i != vertices_.size(); ++i){
      cout << vertices.at(i).xpos << "  " << vertices.at(i).ypos;
      cout << " "<< endl;

   }
   glBegin (GL_POLYGON);
   glColor3ubv (color.ubvec);
   for(auto i: vertices){
      GLfloat blx = (i.xpos + center.xpos);
      GLfloat bly = (i.ypos + center.ypos);
      cout << "bl " << blx <<" "<< bly << endl;
      glVertex2f (blx,bly);
   }
   glEnd();
   /*if(vertices.size() == 4){
      
      GLfloat blx = (vertices.at(0).xpos + center.xpos);
      GLfloat bly = (vertices.at(0).ypos + center.ypos);
      GLfloat brx = (vertices.at(1).xpos + center.xpos);
      GLfloat bry = (vertices.at(1).ypos + center.ypos);
      GLfloat trx = (vertices.at(2).xpos + center.xpos);
      GLfloat tr_y = (vertices.at(2).ypos + center.ypos);
      GLfloat tlx = (vertices.at(3).xpos + center.xpos);
      GLfloat tly = (vertices.at(3).ypos + center.ypos);
      cout << "br " << brx <<" "<< bry << endl;
      cout << "tr " << trx <<" "<< tr_y << endl;
      cout << "tl " << tlx <<" "<< tly << endl;
         //i->xpos = i->xpos + center.xpos;
         //i->ypos = i->ypos + center.ypos;
      cout << this << "(" << blx << "," << ")";
      glVertex2f (brx,bry);
      glVertex2f (trx,tr_y);
      glVertex2f (tlx,tly);
      //glVertex2f (xpos + width, ypos);
      //glVertex2f (xpos + width, ypos + width);
      //glVertex2f (xpos, ypos + width);
      
      //glutPostRedisplay();
      
   }*/
}

void shape::show (ostream& out) const {
   out << this << "->" << demangle (*this) << ": ";
}

void text::show (ostream& out) const {
   shape::show (out);
   out << glut_bitmap_font << "(" << fontname[glut_bitmap_font]
       << ") \"" << textdata << "\"";
}

void ellipse::show (ostream& out) const {
   shape::show (out);
   out << "{" << dimension << "}";
}

void polygon::show (ostream& out) const {
   shape::show (out);
   out << "{" << vertices << "}";
}

ostream& operator<< (ostream& out, const shape& obj) {
   obj.show (out);
   return out;
}

