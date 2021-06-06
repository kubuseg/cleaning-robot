#include "ILayer.h"

std::chrono::system_clock::time_point ILayer::updateModyficationTime() {
	modyficationDate = std::chrono::system_clock::now();
	return modyficationDate;
}

void ILayer::setActiveState(bool newState) {
	activeState = newState;
}

bool ILayer::getActiveState() {
	return activeState;
}

void ILayer::moveToPoint(uint8_t x, uint8_t y) {
	Point pos;
	pos.x = x;
	pos.y = y;

	position = pos;
}