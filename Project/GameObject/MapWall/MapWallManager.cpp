#include"MapWallManager.h"

MapWallManager::MapWallManager()
{
}

MapWallManager::~MapWallManager()
{
}

void MapWallManager::Initialize()
{
	mapWall_ = make_unique<MapWall>();
	mapWall_->Initialize();
}

void MapWallManager::Update()
{
	mapWall_->Update();
}

void MapWallManager::Draw(ViewProjection view)
{
	mapWall_->Draw(view);
}

void MapWallManager::CheckMapWall()
{
	list<IMapWall*>::iterator itrA = object_.begin();

	for (; itrA != object_.end(); ++itrA) {

		IMapWall* IMWA = *itrA;	
		Riflection(IMWA);
	}
}

void MapWallManager::Riflection(IMapWall* mA)
{
	if (mA->GetWorldPosition().z + mA->GetSize()+mA->GetVelocity().z> static_cast<float>(FILD_MAP_SIZE_Z))
	{
		mA->OnTopWall();
	}
	if (mA->GetWorldPosition().z - mA->GetSize() + mA->GetVelocity().z < -static_cast<float>(FILD_MAP_SIZE_Z))
	{
		mA->OnBottomWall();
	}
	if (mA->GetWorldPosition().x + mA->GetSize() + mA->GetVelocity().x > static_cast<float>(FILD_MAP_SIZE_X))
	{
		mA->OnRightWall();
	}
	if (mA->GetWorldPosition().x - mA->GetSize() + mA->GetVelocity().x < -static_cast<float>(FILD_MAP_SIZE_X))
	{
		mA->OnLeftWall();
	}
}
