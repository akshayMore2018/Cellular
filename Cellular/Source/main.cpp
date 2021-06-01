#include "CEngine.h"
#include <memory>
#include <assimp/scene.h>

int main()
{
	auto engine = std::make_unique<CEngine>();

	bool success = engine->Initialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Cellular");

	if (success)
	{
		engine->Start();
	}

}
