#include "WallColorState.h"
#include "GameObject/ShamWall/ShamWall.h"
#include "CalcGreen.h"



void CalcGreen::CalcColor(ShamWall* pWall) {

	float newColor = pWall->getRGBColor().y;

	if (pWall->GetColorState() == AddGreen) {

		newColor = newColor + chengeSpeed_;

		pWall->SetRGBColorG(newColor);

		if (newColor >= 255.0f) {

			newColor = 255;
			pWall->SetColorState(SubRed);
			pWall->ChangeWallColorState(new CalcRed);
		}
	}
	else if (pWall->GetColorState() == SubGreen) {

		newColor = newColor - chengeSpeed_;

		pWall->SetRGBColorG(newColor);

		if (newColor <= 0) {

			newColor = 0;
			pWall->SetColorState(AddRed);
			pWall->ChangeWallColorState(new CalcRed);
		}
	}
}

