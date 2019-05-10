#pragma once

#ifdef RAINBOW_PLATFORM_WINDOWS

extern Rainbow::Application* Rainbow::CreateApplication();

int main(int argc, char** argv){
	auto app = Rainbow::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif