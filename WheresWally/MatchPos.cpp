#include "BC_MatchPos.h"

MatchPos::MatchPos() {

}

MatchPos::MatchPos(int x, int y, double accuracy) {
	this->x = x;
	this->y = y;
	this->accuracy = accuracy;
}