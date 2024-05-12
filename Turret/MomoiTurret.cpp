//
// Created by wuru8 on 2024/5/12.
//

#include "MomoiTurret.hpp"

#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Bullet/FireBullet.hpp"
#include "Bullet/MomoiBullet.hpp"
#include "Engine/Group.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

const int MomoiTurret::Price = 100;
MomoiTurret::MomoiTurret(float x, float y) :
        Turret("play/tower-base.png", "play/momoi64x64.png", x, y, 200, Price, 0.25) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y -= 8.0f / GetBitmapHeight();
}
void MomoiTurret::CreateBullet() {
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
    // Change bullet position to the front of the gun barrel.
    getPlayScene()->BulletGroup->AddNewObject(new MomoiBullet(Position + normalized * 36, diff, rotation, this));
    AudioHelper::PlayAudio("gun.wav");
}
