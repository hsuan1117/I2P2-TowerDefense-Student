//
// Created by wuru8 on 2024/5/12.
//

#ifndef INC_2024_I2P2_TOWERDEFENSE_MOMOITURRET_HPP
#define INC_2024_I2P2_TOWERDEFENSE_MOMOITURRET_HPP
#include "Turret.hpp"

class MomoiTurret: public Turret {
public:
    static const int Price;
    MomoiTurret(float x, float y);
    void CreateBullet() override;
};

#endif //INC_2024_I2P2_TOWERDEFENSE_MOMOITURRET_HPP
