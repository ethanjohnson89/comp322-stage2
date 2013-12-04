
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

	void  draw();
	int   mapClicked(int x, int y);
	
	EnigmaArea* getArea(int index) {return areas[index];}
	EnigmaArea* getCurrentArea() {return getArea(areaIndex);}
	int   getCurrentAreaIndex() {return areaIndex;}
	int	  getAreaCount() {return areas.size();}
	void  setDefaultArea(int a) {defaultArea = a;}
	void  setAreaToDefault() {areaIndex = defaultArea;}
	void  setBackgroundPicture(gl::Texture back) {background = back; hasBackground = true;}

	void  setCurrentArea(int index);
	void  addArea(EnigmaArea *newArea);
};
#endif

