//
// Created by wuru8 on 2024/6/8.
//

#ifndef INC_2024_I2P2_TOWERDEFENSE_PLOTSCENE_HPP
#define INC_2024_I2P2_TOWERDEFENSE_PLOTSCENE_HPP

#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"
#include "UI/Component/Label.hpp"
#include "UI/Component/Image.hpp"
#include <queue>
#include <vector>
#include <unordered_map>
#include "UI/Component/RefImage.hpp"

void UpdateText(std::queue<std::list<std::string>>& queue_of_text, std::string& text, std::string& name);

class PlotScene final : public Engine::IScene {
private:
    struct image_info {
        std::shared_ptr<Engine::RefImage> img;
        std::string path;
        int w;
        int h;

        void SetDftImage(){
            img = std::make_shared<Engine::RefImage>("plot/transparent.png",0, 0, w, h, 0, 0);
        }
    };

    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    Engine::Label *pText = nullptr;
    Engine::Label *pName = nullptr;
    std::string text;
    std::string name;

    std::unordered_map<std::string, image_info> image_map;
    std::unordered_map<std::string, ALLEGRO_SAMPLE*> music_map;

    std::queue<std::vector<std::string>> queue_of_text;

public:
    explicit PlotScene() = default;
    void Initialize() override;
    void Terminate() override;
    static void SkipOnClick();
    static void AutoOnClick();
    static void BackOnClick(int stage);
    void Update(float deltaTime) override;
};


#endif //INC_2024_I2P2_TOWERDEFENSE_PLOTSCENE_HPP
