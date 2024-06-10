#ifndef WINSCENE_HPP
#define WINSCENE_HPP
#include <allegro5/allegro_audio.h>
#include "Engine/IScene.hpp"

void SetLastStage(int stage);
void SetLastGameInfo(int money, int life);


struct WinSceneInfo {
    int last_stage;
    int money_left;
    int life_left;
};

class WinScene final : public Engine::IScene {
private:
	float ticks;
	ALLEGRO_SAMPLE_ID bgmId;
protected:
//    static std::string username;
//    static int name_ptr;
    std::string username = "";
    bool Rshift = false;
    bool Lshift = false;
public:
	explicit WinScene() = default;
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void BackOnClick(int stage);
    void OnKeyDown(int keyCode) final override;
    void OnKeyUp(int keyCode) final override;
};

#endif // WINSCENE_HPP
