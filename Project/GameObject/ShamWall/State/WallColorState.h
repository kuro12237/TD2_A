#pragma once



class ShamWall;


class WallColorState {

public:

	virtual void CalcColor(ShamWall* wall) = 0;
};

