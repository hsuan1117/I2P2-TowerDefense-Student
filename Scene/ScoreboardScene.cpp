#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "UI/Component/Slider.hpp"
#include "ScoreboardScene.hpp"
#include "Engine/LOG.hpp"
#include "UI/Component/Scoreboard.hpp"

Engine::Scoreboard* scb;

void ScoreboardScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    AddNewObject(new Engine::Label("Scoreboard", "pirulen.ttf", 48, halfW, 50, 255, 255, 255, 255, 0.5, 0.5));

    Engine::ImageButton* btn;
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW * 1/3 - 200, halfH * 3 / 2 - 50 , 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::PrevOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Prev Page", "pirulen.ttf", 48, halfW * 1/3, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW * 5/3 - 200, halfH * 3 / 2 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::NextOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Next Page", "pirulen.ttf", 48, halfW * 5/3, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));

//    //scoreboard component init
    std::string ss = "Resource/scoreboard.txt";

    scb = new Engine::Scoreboard(ss, 250, 100);
//    Engine::Scoreboard s(ss, 100, 100);
    //AddNewObject(scb);
    AddRefObject(*scb);
    AddRefControl(*scb);


    // Not safe if release resource while playing, however we only free while change scene, so it's fine.
    bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);
}
void ScoreboardScene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}
void ScoreboardScene::BackOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
void ScoreboardScene::PrevOnClick() {
    Engine::LOG(Engine::INFO) << "Prev Button Clicked!";
    scb->PrevPage();
}
void ScoreboardScene::NextOnClick() {
    Engine::LOG(Engine::INFO) << "Next Button Clicked!";
    scb->NextPage();
}
