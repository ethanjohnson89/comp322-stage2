/****************************************
Group #: 2
Members: Steve Patterson, James Mart, Nick Halvorsen, Ethan Johnson
Course: Comp 322
Date: 12/4/13
****************************************/


#ifndef _WORLDMAP_H
#define _WORLDMAP_H

#include "cinder/gl/gl.h"
#include "globals.h"
#include "EnigmaArea.h"
#include <vector>
#include <string>
using std::vector;
using std::string;
using namespace ci;
using namespace windowNS;


class Worldmap
{
private: 
	vector<EnigmaArea*> areas;
	int areaIndex;
	int defaultArea;
	string backgroundFilename;
	gl::Texture background;
	bool hasBackground;

public:
	Worldmap();

	virtual void  draw();
	virtual int   mapClicked(int x, int y);

	virtual EnigmaArea* getArea(int index) {return areas[index];}
	virtual EnigmaArea* getCurrentArea() {return getArea(areaIndex);}
	virtual int   getCurrentAreaIndex() {return areaIndex;}
	virtual int	  getAreaCount() {return areas.size();}
	virtual void  setDefaultArea(int a) {defaultArea = a;}
	virtual void  setAreaToDefault() {areaIndex = defaultArea;}
	virtual void  setBackgroundPicture(gl::Texture back) {background = back; hasBackground = true;}
	virtual void  setCurrentArea(int index);
	virtual void  addArea(EnigmaArea *newArea);
};
#endif

