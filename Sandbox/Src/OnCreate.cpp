#include "Windows/MainWindow.hpp"
#include "Assets/Formats/PtWindow.hpp"

namespace Parrot
{
	void Application::OnCreate()
	{
		//std::ofstream stream("..//Parrot//Src//Assets//Defaults//Quad.PTMESH", std::ios::binary);
		//MeshVertex vertices[4];
		//vertices[0] = MeshVertex({ -0.5f, +0.5f, +0.0f }, { 0.0f, 0.0f, 1.0f }, {0.0f, 0.0f});
		//vertices[1] = MeshVertex({ +0.5f, +0.5f, +0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f });
		//vertices[2] = MeshVertex({ +0.5f, -0.5f, +0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f });
		//vertices[3] = MeshVertex({ -0.5f, -0.5f, +0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f });
		//uint32_t quad = 1;
		//uint32_t size = 4;
		//stream.write((char*)&quad, 4);
		//stream.write((char*)&size, 4);
		//stream.write((char*)vertices, sizeof(MeshVertex) * size);
		//stream.close();

		//std::ofstream stream("..//Parrot//Src//Assets//Defaults//MainWindow.WNDW", std::ios::binary);
		//std::string name = "Scene1\n";
		//Math::Vec2u size(1080, 720);
		//stream.write(name.c_str(), name.size());
		//stream.write((char*)&size, 8);
		//stream.close();
		//PtWindow window(Utils::Filepath("MainWindow.WNDW"));
		//Log::LogInfo("%, %", window.GetData().defaultScene, window.GetData().size);

		new MainWindow("Main Window", { 1080, 720 });
	}
}