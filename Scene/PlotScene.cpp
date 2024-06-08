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
#include "PlayScene.hpp"
#include "Engine/LOG.hpp"

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

    auto onClickCallback = [this]{
        while (!queue_of_text.empty()) {
            auto words = queue_of_text.front();
            if (words[0] == "show") {
                image_map[words[1]].img->ChangeImageTo(image_map[words[1]].path, atoi(words[3].c_str()), atoi(words[4].c_str()));
            } else if (words[0] == "hide") {
                image_map[words[1]].img->ChangeImageTo("plot/transparent.png", 0, 0);
            } else if (words[0] == "play") {
                al_play_sample(music_map[words[1]].sample, 0.5, 0.5, 1.0, ALLEGRO_PLAYMODE::ALLEGRO_PLAYMODE_ONCE, &music_map[words[1]].id);

            } else if (words[0] == "stop") {
                auto temp = music_map[words[1]].id;
                if (&temp != nullptr) {
                    al_stop_sample(&temp);
                }
            } else {
                break;
            }
            queue_of_text.pop();
        }
        if (!queue_of_text.empty()) {
            auto temp = queue_of_text.front();
            name = temp[0];
            text = temp[1];
            queue_of_text.pop();
        } else {
            Engine::GameEngine::GetInstance().ChangeScene("stage-select");
        }
    };

    Engine::ImageButton* btn;

    btn = new Engine::ImageButton("plot/black.png", "plot/black.png", 0, 0, 1600, 832);
    btn->SetOnClickCallback(onClickCallback);
    AddNewControlObject(btn);

    // Read plot from file
    std::string line;
    std::ifstream plot("Resource/plot/test.txt");

    // Pre Processing
    while (std::getline(plot, line)) {

        if (line == "Plot_Start:") {
            break;
        } else if (line == "") {
            continue;
        }

        std::vector<std::string> words;
        splitLine(line, words);


        // check syntex
        if (words[0] == "image" && words.size() == 6) {
            if (words[2][0] != '"' || words[2][words[2].size()-1] != '"') {
                Engine::LOG(Engine::ERROR) << "Plot Script Syntax Error";
                Engine::GameEngine::GetInstance().ChangeScene("stage-select");
            } else {
                words[2].erase(0,1);
                words[2].erase(words[2].size()-1, 1);
            }
            image_info i = {nullptr, words[2], atoi(words[4].c_str()), atoi(words[5].c_str())};
            i.SetDftImage();
            image_map.emplace(words[1], i);
        } else if (words[0] == "audio" && words.size() == 3) {
            if (words[2][0] != '"' || words[2][words[2].size()-1] != '"') {
                Engine::LOG(Engine::ERROR) << "Plot Script Syntax Error";
                Engine::GameEngine::GetInstance().ChangeScene("stage-select");
            } else {
                words[2].erase(0,1);
                words[2].erase(words[2].size()-1, 1);
            }
            std::string fullpath = "Resource/audios/";
            fullpath += words[2];
            auto sam = al_load_sample(fullpath.c_str());
            if (sam == nullptr) {
                Engine::LOG(Engine::ERROR) << "Plot Audio Load Failed";
            }
            audio_info a = {sam, 0};
            music_map.emplace(words[1], a);
        } else {
            Engine::LOG(Engine::ERROR) << "Plot Pre-Processing Syntax Error";
            Engine::GameEngine::GetInstance().ChangeScene("stage-select");
        }
    }
    // Reading Script
    while (std::getline(plot, line)) {

        if (line == "") {
            continue;
        }

        std::vector<std::string> words;
        splitLine(line, words);

        std::vector<std::string> out;

        // check syntax
        if (words[0] == "show") {
            if (words.size() != 5) {
                Engine::LOG(Engine::ERROR) << "Plot Script Syntax Error";
            } else if (words.size() >= 3 && words[2] != "at") {
                Engine::LOG(Engine::ERROR) << "Plot Script Syntax Error";
            }
            for (auto i : words) {
                out.push_back(i);
            }
        } else if (words[0] == "hide") {
            if (words.size() != 2) {
                Engine::LOG(Engine::ERROR) << "Plot Script Syntax Error";
            }
            for (auto i : words) {
                out.push_back(i);
            }
        } else {
            line.erase(0, words[0].size() + 1);

            if (words[0] == "NULL") {
                words[0] = "";
            }
            out.push_back(words[0]);

            if (line[0] != '"' || line[line.size() - 1] != '"') {
                Engine::LOG(Engine::ERROR) << "Plot Script Syntax Error";
            } else {
                line.erase(0, 1);
                line.erase(line.size() - 1, 1);
            }
            out.push_back(line);
        }
        queue_of_text.emplace(out);
    }
    onClickCallback();

    for (auto i : image_map) {
        AddRefObject(*i.second.img);
    }

    pText = new Engine::Label(&text, "pirulen.ttf", 32, 250, 635, 255, 255, 255, 220, 0.5, 0.5);
    AddRefObject(*pText);

    pName = new Engine::Label(&name, "pirulen.ttf", 32, 150, 575, 220, 220, 255, 220, 0.5, 0.5);
    AddRefObject(*pName);

    btn = new Engine::ImageButton("stage-select/arrow_left.png", "stage-select/arrow_left_hovered.png", 1350, 20, 64, 64);
    btn->SetOnClickCallback([] { Engine::GameEngine::GetInstance().ChangeScene("stage-select"); });
    AddNewControlObject(btn);



    // Not safe if release resource while playing, however we only free while change scene, so it's fine.
    //bgmInstance = AudioHelper::PlaySample("BeyondSunshine.ogg", true, AudioHelper::BGMVolume);
}
void PlotScene::Update(float deltaTime) {
    //title_name = (std::string)"Scoreboard - " + "stage" + (char)(scene + '0')/* + (money_or_life == 0 ? ":Money" : ":Life")*/;
}

void PlotScene::Terminate() {
    //AudioHelper::StopSample(bgmInstance);
    al_stop_samples();
    for (auto i : music_map) {
        al_destroy_sample(i.second.sample);
    }
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}
