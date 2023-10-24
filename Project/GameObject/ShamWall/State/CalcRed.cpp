#include "WallColorState.h"
#include "GameObject/ShamWall/ShamWall.h"
#include "CalcRed.h"


void CalcRed::CalcColor(ShamWall* pWall) {

	float newColor = pWall->getRGBColor().x;

	if (pWall->GetColorState() == AddRed) {

		newColor = newColor + chengeSpeed_;

		pWall->SetRGBColorR(newColor);

		if (newColor >= 255) {

			newColor = 255;
			pWall->SetColorState(SubBlue);
			pWall->ChangeWallColorState(new CalcBlue);
		}
	}
	if (pWall->GetColorState() == SubRed) {

		newColor = newColor - chengeSpeed_;

		pWall->SetRGBColorR(newColor);

		if (newColor <= 0) {

			newColor = 0;
			pWall->SetColorState(AddBlue);
			pWall->ChangeWallColorState(new CalcBlue);
		}
	}
}

