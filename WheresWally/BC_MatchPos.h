#ifndef matchPosition
#define matchPosition

#include "BC_Image.h"

class MatchPos : public Image {
public:
	int x, y;
	double accuracy;

	MatchPos();
	MatchPos(int x, int y, double accuracy);
	~MatchPos()
	{

	}

	bool operator == (MatchPos& temp) {
		return this->accuracy == temp.accuracy;
	}
};

#endif // !matchPosition

