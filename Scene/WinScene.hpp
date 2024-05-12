#ifndef WINSCENE_HPP
#define WINSCENE_HPP
#include <allegro5/allegro_audio.h>
#include "Engine/IScene.hpp"

extern std::string username;

class WinScene final : public Engine::IScene {
private:
	float ticks;
	ALLEGRO_SAMPLE_ID bgmId;
protected:
//    static std::string username;
//    static int name_ptr;
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
