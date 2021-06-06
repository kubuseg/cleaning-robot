#pragma once

#include "ILayer.h"
#include <list>

#define OUT

class Picture {
private:
	std::list<ILayer*> layerList;
	std::chrono::system_clock::time_point modyficationDate;

private:
	std::chrono::system_clock::time_point updateModyficationTime();

public:
	void addLayer(ILayer*, int);
	std::tuple<ILayer*, bool> getLayer(int);
	bool removeLayer(int);
	void moveLayerToPoint(int, int, int);
};