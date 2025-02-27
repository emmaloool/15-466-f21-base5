#include "Mode.hpp"

#include "Scene.hpp"
#include "WalkMesh.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <deque>

struct PlayMode : Mode {
	PlayMode();
	virtual ~PlayMode();

	//functions called by main loop:
	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) override;
	virtual void update(float elapsed) override;
	virtual void draw(glm::uvec2 const &drawable_size) override;

	//----- game state -----

	//input tracking:
	struct Button {
		uint8_t downs = 0;
		uint8_t pressed = 0;
	} left, right, down, up;

	//local copy of the game scene (so code can change it during gameplay):
	Scene scene;

	//player info:
	struct Player {
		WalkPoint at;
		//transform is at player's feet and will be yawed by mouse left/right motion:
		Scene::Transform *transform = nullptr;
		//camera is at player's head and will be pitched by mouse up/down motion:
		Scene::Camera *camera = nullptr;
	} player;

	// ---------------------- cat game state ----------------------

	std::vector<Scene::Drawable *> obj_drawables;
	std::vector<bool> available_objs; 		// used to skip/expedite collision testing for fruits already collected
	std::vector<float> y_offset;
	
	float dist_threshold = 10.0f;

	uint8_t fish_collected = 0;
	uint8_t bones_collected = 0;
	int8_t total_score = 0;

	Scene::Drawable *player_drawable;

	float game_time = 0.0f;
};
