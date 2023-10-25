#pragma once
#include<cstdint>

const uint32_t kCollisionAttributePlayer = 0b0001;
const uint32_t kCollisionAttributeEnemy = 0b0010;
const uint32_t kCollisionAttributeEnemyBomb = 0b0100;

const uint32_t kCollisionMaskPlayer = 0b1111;
const uint32_t kCollisionMaskEnemy = 0b1111;
const uint32_t kCollisionMaskEnemyBomb = 0b1111;