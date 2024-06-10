//
// Created by wuru8 on 2024/5/12.
//

#ifndef INC_2024_I2P2_TOWERDEFENSE_MOMOIBULLET_HPP
#define INC_2024_I2P2_TOWERDEFENSE_MOMOIBULLET_HPP

#include <allegro5/base.h>
#include <list>

#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
    struct Point;
}  // namespace Engine

class MomoiBullet : public Bullet {
public:
    explicit MomoiBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
    void OnExplode(Enemy* enemy) override;
};

#endif //INC_2024_I2P2_TOWERDEFENSE_MOMOIBULLET_HPP
