#pragma once


class ShamWall;


enum ColorState {
	AddRed,
	SubRed,
	AddGreen,
	SubGreen,
	AddBlue,
	SubBlue,
};



class WallColorState {

public:

	virtual void CalcColor(ShamWall* wall) = 0;

protected:

	int chengeSpeed_ = 3;
};

