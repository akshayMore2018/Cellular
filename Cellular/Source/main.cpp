#include "CEngine.h"
#include <memory>

int main()
{
	auto engine = std::make_unique<CEngine>();

	bool success = engine->initialize(640, 480, "Cellular");

	if (success)
	{
		engine->run();
	}

}
