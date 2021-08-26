// $Id: interp.cpp,v 1.2 2015-07-16 16:57:30-07 - - $
/*
 * Partner: Evan Suther (esuther@ucsc.edu)
 * Partner: Derrick DeBose (ddebose@ucsc.edu)
 */

#include <memory>
#include <string>
#include <vector>
using namespace std;

#include <GL/freeglut.h>

#include "debug.h"
#include "interp.h"
#include "shape.h"
#include "util.h"

unordered_map<string,interpreter::interpreterfn>
interpreter::interp_map {
   {"define" , &interpreter::do_define },
   {"draw"   , &interpreter::do_draw   },
   {"moveby"   , &interpreter::do_moveby},
};

unordered_map<string,interpreter::factoryfn>
interpreter::factory_map {
   {"text"     , &interpreter::make_text     },
   {"ellipse"  , &interpreter::make_ellipse  },
   {"circle"   , &interpreter::make_circle   },
   {"polygon"  , &interpreter::make_polygon  },
   {"triangle" , &interpreter::make_polygon  },
   {"equilateral", &interpreter::make_equilateral},
   {"diamond"  , &interpreter::make_diamond  },
   {"rectangle", &interpreter::make_rectangle},
   {"square"   , &interpreter::make_square   },
};

interpreter::shape_map interpreter::objmap;
//interpreter::vec_obj;

GLfloat moveby_ = 4;

GLfloat interpreter::get_moveby(){
   DEBUGF ('f', moveby_);
   return moveby_;
}

interpreter::~interpreter() {
   for (const auto& itor: objmap) {
      cout << "objmap[" << itor.first << "] = "
           << *itor.second << endl;
   }
}

void interpreter::interpret (const parameters& params) {
   DEBUGF ('i', params);
   param begin = params.cbegin();
   string command = *begin;
   auto itor = interp_map.find (command);
   if (itor == interp_map.end()){
      cerr << "syntax error";
      return;
   }   
   interpreterfn func = itor->second;
   func (++begin, params.cend());
}

void interpreter::do_moveby (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   moveby_ = from_string<GLfloat> (begin[0]);
   DEBUGF ('f', moveby_);
}

void interpreter::do_define (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   string name = *begin;
   objmap.emplace (name, make_shape (++begin, end));
}


void interpreter::do_draw (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   if (end - begin != 4) throw runtime_error ("syntax error");
   string name = begin[1];
   shape_map::const_iterator itor = objmap.find (name);
   if (itor == objmap.end()) {
      cerr << name << ": no such shape";
      return;
   }
   //add these fields into the class object**************************
   rgbcolor color {begin[0]};
   vertex where {from_string<GLfloat> (begin[2]),
                 from_string<GLfloat> (begin[3])};
   //obj.color = color;
   //obj.center = where;
   object obj{color,where,itor->second};
   //vector<object> obj_ = ;
   window::putObj(obj);
}

shape_ptr interpreter::make_shape (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   string type = *begin++;
   auto itor = factory_map.find(type);
   if (itor == factory_map.end()) {
      throw runtime_error (type + ": no such shape");
   }
   factoryfn func = itor->second;
   return func (begin, end);
}

shape_ptr interpreter::make_text (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   return make_shared<text> (nullptr, string());
}

shape_ptr interpreter::make_ellipse (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   GLfloat first = from_string<GLfloat> (begin[0]);
   GLfloat second = from_string<GLfloat> (begin[1]);
   //add rectangle to window pshape************************
   //window::objects.pshape = make_shared<rectangle> (first, second);
   return make_shared<ellipse> (first, second);
}

shape_ptr interpreter::make_circle (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   GLfloat first = from_string<GLfloat> (begin[0]);
   return make_shared<circle> (first);
}

shape_ptr interpreter::make_equilateral (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   GLfloat first = from_string<GLfloat> (begin[0]);
   return make_shared<equilateral> (first);
}

shape_ptr interpreter::make_polygon (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   vertex_list vertices{};
   
   for(auto i = 0; i != end-begin; i = i +2){
      //if(begin[i+1] == nullptr) throw runtime_error ("sytax error");
      vertex where {from_string<GLfloat> (begin[i]),
                 from_string<GLfloat> (begin[i+1])};
      vertices.push_back(where);
      
   }
   return make_shared<polygon> (vertices);
}

shape_ptr interpreter::make_diamond (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   //pass in the values into rectangle constructor
   GLfloat first = from_string<GLfloat> (begin[0]);
   GLfloat second = from_string<GLfloat> (begin[1]);
   //add rectangle to window pshape************************
   //window::objects.pshape = make_shared<rectangle> (first, second);
   return make_shared<diamond> (first, second);
}

shape_ptr interpreter::make_rectangle (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   //pass in the values into rectangle constructor
   GLfloat first = from_string<GLfloat> (begin[0]);
   GLfloat second = from_string<GLfloat> (begin[1]);
   //add rectangle to window pshape************************
   //window::objects.pshape = make_shared<rectangle> (first, second);
   return make_shared<rectangle> (first, second);
}

shape_ptr interpreter::make_square (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   GLfloat first = from_string<GLfloat> (begin[0]);
   return make_shared<square> (first);
}

