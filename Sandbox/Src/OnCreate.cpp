#include "Windows/MainWindow.hpp"

namespace Parrot
{
	void Application::OnCreate()
	{
		new MainWindow("Main Window", { 1080, 720 });
		new MainWindow("Window 2", { 300, 200 });
		new MainWindow("Window 3", { 300, 200 });
	}
}