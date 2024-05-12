//
// Created by wuru8 on 2024/5/11.
//

#ifndef INC_2024_I2P2_TOWERDEFENSE_SCOREBOARDSCENE_HPP
#define INC_2024_I2P2_TOWERDEFENSE_SCOREBOARDSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"

class ScoreboardScene final : public Engine::IScene {
private:
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    Engine::Label *Lscb;
    std::string title_name = "Scoreboard - stage1";

public:
    explicit ScoreboardScene() = default;
    void Initialize() override;
    void Terminate() override;
    void PrevOnClick();
    void NextOnClick();
    void BackOnClick(int stage);
    void Update(float deltaTime) override;
};




#endif //INC_2024_I2P2_TOWERDEFENSE_SCOREBOARDSCENE_HPP
