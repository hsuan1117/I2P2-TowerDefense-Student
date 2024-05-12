//
// Created by wuru8 on 2024/5/11.
//

#ifndef INC_2024_I2P2_TOWERDEFENSE_SCOREBOARD_HPP
#define INC_2024_I2P2_TOWERDEFENSE_SCOREBOARD_HPP
#include <allegro5/bitmap.h>
#include <memory>
#include <string>

#include "Engine/IObject.hpp"
#include "Engine/LOG.hpp"
#include "Engine/IControl.hpp"


typedef struct
{
    int score;
    char name[100];
} ScoreBoardInstance;

extern int upper;

namespace Engine {
    class Scoreboard : public IObject, public IControl {
    private:
        static const int max_line = 10;
        std::basic_string<char> path;

        int x;
        int y;

        int i;

        int ptr;

        int n;

        int r;
        int g;
        int b;

        ALLEGRO_FONT* menuFont;

        bool show = true;

    public:
        ScoreBoardInstance* scb;

        Scoreboard(std::string _path, int _x, int _y, int _r, int _g, int _b) : path(_path), x(_x), y(_y), i(0), scb(), ptr(0), n(99), r(_r), g(_g), b(_b)
        {
            menuFont = al_load_font("Resource/fonts/pirulen.ttf", 30, 0);

            //load string
            FILE* score;

            scb = static_cast<ScoreBoardInstance *>(malloc(sizeof(ScoreBoardInstance) * n));

            while (n > 1 && scb == NULL)
            {
                scb = static_cast<ScoreBoardInstance *>(malloc(sizeof(ScoreBoardInstance) * --n));
            }

            if (scb == NULL)
            {
                Engine::LOG(Engine::ERROR) << "scoreboard memory alloc failed";
            }
            else
            {
                Engine::LOG(Engine::INFO) << "Scoreboard memory successfully alloc! " << n;
            }


            if (fopen_s(&score, path.c_str(), "r") != 0)
            {
                Engine::LOG(Engine::ERROR) << "Fail to open ScoreBoard: " << path;
            }
            else
            {
                Engine::LOG(Engine::INFO) << "ScoreBoard File Load Successfully";
            }


            for (i; i < n; i++)
            {
                if (fscanf_s(score, "%s%d", scb[i].name, sizeof(char) * 100, &scb[i].score) == 2)
                {
                    Engine::LOG(Engine::INFO) << "scoreboard read:" <<  scb[i].name << " " << scb[i].score;
                }
                else
                {
                    Engine::LOG(Engine::INFO) << "scoreboard ends";
                    break;
                }
            }

            fclose(score);
        }

        Scoreboard(std::string _path, int _x, int _y) : path(_path), x(_x), y(_y), i(0), scb(), ptr(0), n(99), r(255), g(255), b(255)
        {
            menuFont = al_load_font("Resource/fonts/pirulen.ttf", 30, 0);

            //load string
            FILE* score;

            scb = static_cast<ScoreBoardInstance *>(malloc(sizeof(ScoreBoardInstance) * n));

            while (n > 1 && scb == NULL)
            {
                scb = static_cast<ScoreBoardInstance *>(malloc(sizeof(ScoreBoardInstance) * --n));
            }

            if (scb == NULL)
            {
                Engine::LOG(Engine::ERROR) << "scoreboard memory alloc failed";
            }
            else
            {
                Engine::LOG(Engine::INFO) << "Scoreboard memory successfully alloc! " << n;
            }


            if (fopen_s(&score, path.c_str(), "r") != 0)
            {
                Engine::LOG(Engine::ERROR) << "Fail to open ScoreBoard: " << path;
            }
            else
            {
                Engine::LOG(Engine::INFO) << "ScoreBoard File Load Successfully";
            }


            for (i; i < n; i++)
            {
                if (fscanf_s(score, "%s%d", scb[i].name, sizeof(char) * 100, &scb[i].score) == 2)
                {
                    Engine::LOG(Engine::INFO) << "scoreboard read:" <<  scb[i].name << " " << scb[i].score;
                }
                else
                {
                    Engine::LOG(Engine::INFO) << "scoreboard ends";
                    break;
                }
            }

            fclose(score);
        }

        ~Scoreboard()
        {
            free(scb);
        }

        void Draw() const override;

        void PtrInc();
        void NextPage();
        void PtrDec();
        void PrevPage();

        void OnMouseScroll(int mx, int my, int delta) override;

        int get_num() const;

        void MakeShow();
        void MakeNotShow();
    };
}


#endif //INC_2024_I2P2_TOWERDEFENSE_SCOREBOARD_HPP