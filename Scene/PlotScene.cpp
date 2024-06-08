//
// Created by wuru8 on 2024/6/8.
//

#include "PlotScene.hpp"

#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>
#include <sstream>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "ScoreboardScene.hpp"
#include "Engine/LOG.hpp"
#include "UI/Component/Scoreboard.hpp"

void splitLine(const std::string& line, std::vector<std::string>& words) {
    std::istringstream iss(line);
    std::string word;
    while (iss >> word) {
        words.push_back(word);
    }
}

void PlotScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    text = "uninitialized";
    name = "uninitialized";

    // Read plot from file
    std::string line;
    std::ifstream plot("Resource/plot/test.txt");
    while (std::getline(plot, line)) {
        std::vector<std::string> words;
        splitLine(line, words);

        std::vector<std::string> out;

        // check syntex

        line.erase(0, words[0].size()+1);

        if (words[0] == "NULL") {
            words[0] = "";
        }
        out.push_back(words[0]);

        if (line[0] != '"' || line[line.size()-1] != '"') {
            Engine::LOG(Engine::ERROR) << "Plot Script Syntex Error";
        } else {
            line.erase(0,1);
            line.erase(line.size()-1, 1);
        }
        out.push_back(line);

        queue_of_text.emplace(out);
    }

    pText = new Engine::Label(&text, "pirulen.ttf", 32, 250, 635, 255, 255, 255, 220, 0.5, 0.5);
    AddRefObject(*pText);

    pName = new Engine::Label(&name, "pirulen.ttf", 32, 150, 575, 220, 220, 255, 220, 0.5, 0.5);
    AddRefObject(*pName);


    Engine::ImageButton* btn;
    btn = new Engine::ImageButton("stage-select/arrow_left.png", "stage-select/arrow_left_hovered.png", 1350, 20, 64, 64);
    btn->SetOnClickCallback([] { Engine::GameEngine::GetInstance().ChangeScene("stage-select"); });
    AddNewControlObject(btn);


    auto lam = [this]{
        if (!queue_of_text.empty()) {
            name = queue_of_text.front()[0];
            text = queue_of_text.front()[1];
            queue_of_text.pop();
        } else {
            Engine::GameEngine::GetInstance().ChangeScene("stage-select");
        }
    };

    btn = new Engine::ImageButton("stage-select/arrow_left.png", "stage-select/arrow_left_hovered.png", 0, 0, 64, 64);
    btn->SetOnClickCallback(lam);
    AddNewControlObject(btn);

    // Not safe if release resource while playing, however we only free while change scene, so it's fine.
    bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);

    lam();
}
void PlotScene::Update(float deltaTime) {
    //title_name = (std::string)"Scoreboard - " + "stage" + (char)(scene + '0')/* + (money_or_life == 0 ? ":Money" : ":Life")*/;
}

void PlotScene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}
