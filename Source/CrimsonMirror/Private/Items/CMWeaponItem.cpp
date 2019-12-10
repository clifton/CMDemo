#include "CMWeaponItem.h"


// to be implemented in blueprint
UCMWeaponItem::UCMWeaponItem()
{
	ItemType = UCMAssetManager::WeaponItemType;
	AttackDelay = 1.f;
	AttackBaseDamage = 10.f;
}
