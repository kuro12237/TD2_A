#include "WallColorState.h"
#include "GameObject/ShamWall/ShamWall.h"
#include "CalcBlue.h"



void CalcBlue::CalcColor(ShamWall* pWall) {

	float newColor = pWall->getRGBColor().z;

	if (pWall->GetColorState() == AddBlue) {

		newColor = newColor + chengeSpeed_;

		pWall->SetRGBColorB(newColor);

		if (newColor >= 255) {

			newColor = 255;
			pWall->SetColorState(SubGreen);
			pWall->ChangeWallColorState(new CalcGreen);
		}
	}
	else if (pWall->GetColorState() == SubBlue) {

		newColor = newColor - chengeSpeed_;

		pWall->SetRGBColorB(newColor);

		if (newColor <= 0) {

			newColor = 0;
			pWall->SetColorState(AddGreen);
			pWall->ChangeWallColorState(new CalcGreen);
		}
	}
}

