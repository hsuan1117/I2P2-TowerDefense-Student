//
// Created by wuru8 on 2024/5/11.
//
#include <allegro5/allegro.h>
#include "Engine/IObject.hpp"
#include "UI/Component/Label.hpp"
#include "Scoreboard.hpp"

int upper;

namespace Engine {

    void Scoreboard::Draw() const {
        if (!show) {
            return;
        }
        const float scale = 0.7;

        //draw score


        if (i < max_line-1) {
            upper = i;
        } else {
            upper = max_line-1;
        }

        while (upper + ptr >= i) {
            upper--;
        }


        for (int j = 0; j < upper + 1; j++) {
            char temp[100];

            if (j + ptr + 1 >= 10) {
                sprintf_s(temp, 100, "%d      %s", j + ptr + 1, scb[j + ptr].name);
            } else {
                sprintf_s(temp, 100, " %d      %s", j + ptr + 1, scb[j + ptr].name);
            }

            al_draw_text(
                    menuFont,
                    al_map_rgb(r, g, b),
                    x,
                    y + 50 * j,
                    ALLEGRO_ALIGN_LEFT,
                    temp
            );

            sprintf_s(temp, 100, "%d", scb[j + ptr].score);

            al_draw_text(
                    menuFont,
                    al_map_rgb(r, g, b),
                    x+1000,
                    y + 50 * j,
                    ALLEGRO_ALIGN_RIGHT,
                    temp
            );
        }
    }

    void Scoreboard::AddNew(std::string username, int points) {
        FILE* score;

        if (remove(path.c_str()) == 0)
        {
            Engine::LOG(Engine::INFO) << path << (" deleted successfully");
        }
        else
        {
            Engine::LOG(Engine::ERROR) << ("Fail to delete ") << path;
        }


        if (fopen_s(&score, path.c_str(), "w+") != 0)
        {
            Engine::LOG(Engine::ERROR) << ("Fail to open new ScoreBoard");
        }
        else
        {
            Engine::LOG(Engine::INFO) << ("ScoreBoard File create Successfully");
        }

        bool flag = true;

        for (int i = 0; i < get_num(); i++)
        {
            if (points > scb[i].score && flag)
            {
                fprintf_s(score, "%s %d\n", username.c_str(), points);
                Engine::LOG(Engine::INFO) << username << points;
                flag = false;
                fprintf_s(score, "%s %d\n", scb[i].name, scb[i].score);
                Engine::LOG(Engine::INFO) << i;
                continue;
            }

            fprintf_s(score, "%s %d\n", scb[i].name, scb[i].score);
        }

        if (flag)
        {
            fprintf_s(score, "%s - %d\n", username.c_str(), points);
            flag = false;
        }

        ++i;

        fclose(score);
    }

    void Scoreboard::PtrInc() {
        ++ptr;
        if (ptr >= i-1) {
            ptr = i-1;
        }
    }

    void Scoreboard::NextPage() {
        if (ptr + max_line < i) {
            ptr += max_line;
        }
    }

    void Scoreboard::PtrDec() {
        --ptr;
        if (ptr < 0) {
            ptr = 0;
        }
    }

    void Scoreboard::PrevPage() {
        ptr -= max_line;
        if (ptr < 0) {
            ptr = 0;
        }
    }

    void Scoreboard::OnMouseScroll(int mx, int my, int delta) {
        if (!show) {
            return;
        }

        if (delta > 0)
        {
            //Engine::LOG(INFO) << "Mouse Wheel UP!";
            ptr--;
            if (ptr < 0)
            {
                ptr = 0;
            }
        }

        if (delta < 0)
        {
            //Engine::LOG(INFO) << "Mouse Wheel DOWN!";
            ptr++;
            if (ptr >= i)
            {
                ptr = i - 1;
            }
        }
    }

    int Scoreboard::get_num() const {
        return i;
    }

    void Scoreboard::MakeShow() {
        show = true;
    }

    void Scoreboard::MakeNotShow() {
        show = false;
    }
}