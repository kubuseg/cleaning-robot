#include "Picture.h"
#include <tuple>

void Picture::addLayer(ILayer* layer, int pos) {
	std::list<ILayer*>::iterator iter;
	int i;
	for (iter = layerList.begin(), i = 0; iter != layerList.end() && i != pos; iter++, i++) {

	}
	layerList.insert(iter, layer);
	layer->updateModyficationTime();
	modyficationDate = std::chrono::system_clock::now();
}

std::tuple<ILayer*, bool> Picture::getLayer(int pos) {
	// if out of range return false to show failure
	if (static_cast<int>(layerList.size()) <= pos) {
		return std::make_tuple<ILayer*, bool>(NULL, false);
	}

	std::list<ILayer*>::iterator iter;
	int i;
	for (iter = layerList.begin(), i = 0; iter != layerList.end() && i != pos; iter++, i++) {

	}

	// if ILayer is in range return true
	return std::make_tuple<ILayer*, bool>((ILayer*)*iter, true);
}

bool Picture::removeLayer(int pos) {
	// if out of range return false to show failure
	if (static_cast<int>(layerList.size()) <= pos)
		return false;

	std::list<ILayer*>::iterator iter;
	int i;
	for (iter = layerList.begin(), i = 0; iter != layerList.end() && i != pos; iter++, i++) {

	}

	(*iter)->setActiveState(false);

	// if pos is in range return true
	return true;
}

std::chrono::system_clock::time_point Picture::updateModyficationTime() {
	modyficationDate = std::chrono::system_clock::now();
	return modyficationDate;
}