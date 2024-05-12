//
// Created by wuru8 on 2024/5/12.
//

#ifndef INC_2024_I2P2_TOWERDEFENSE_FLAMETANK_HPP
#define INC_2024_I2P2_TOWERDEFENSE_FLAMETANK_HPP

#include "Enemy.hpp"
#include "Engine/Sprite.hpp"

class FlameTank : public Enemy {
private:
    Sprite head;
    float targetRotation;
public:
    FlameTank(int x, int y);
    void Draw() const override;
    void Update(float deltaTime) override;
};

#endif //INC_2024_I2P2_TOWERDEFENSE_FLAMETANK_HPP
