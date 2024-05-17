//
// Created by wuru8 on 2024/5/12.
//
#include <allegro5/base.h>
#include <random>

#include "Engine/Point.hpp"
#include "FlameTank.hpp"

FlameTank::FlameTank(int x, int y) : Enemy("play/enemy-6.png", x, y, 25, 28, 500, 100),
                                     head("play/enemy-2.png", x, y), targetRotation(0) {
}
void FlameTank::Draw() const {
    Enemy::Draw();
    //head.Draw();
}
void FlameTank::Update(float deltaTime) {
    Enemy::Update(deltaTime);
    //head.Position = Position;
    // Choose arbitrary one.
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist(0.0f, 4.0f);
    float rnd = dist(rng);
    if (rnd < deltaTime) {
        // Head arbitrary rotation.
        std::uniform_real_distribution<> distRadian(-ALLEGRO_PI, ALLEGRO_PI);
        targetRotation = distRadian(rng);
    }
    head.Rotation = (head.Rotation + deltaTime * targetRotation) / (1 + deltaTime);
}
