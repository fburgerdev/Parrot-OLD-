#include "Parrot.hpp"
#include "CamControllerOrtho.hpp"
#include "CamControllerPers.hpp"

class Sandbox : public Parrot::Application
{
	using Parrot::Application::Application;

	CamControllerPers* camController;

	Parrot::Texture textureParrot;
	Parrot::SceneObject::TexQuad texQuad;
	virtual void OnCreate() override
	{
		Parrot::Texture::Config texConfig;
		texConfig.mipmap = Parrot::Texture::Config::Mipmap::Linear;
		textureParrot.LoadTextureFromPath("Src/Images/ParrotSketch.png", texConfig);
		
		camController = new CamControllerPers(Parrot::Vector::Vec3f(0), Parrot::Vector::Vec3f(0, 0, 1), Parrot::Vector::c_Pi / 2, Parrot::Vector::Vec2f(0.1f, 10000.0f), 100.0f, 0.0005f);
		//camController = new CamControllerOrtho(100.0f, 100.0f);
		Parrot::LayerStack::PushLayer(camController);

		texQuad.SetPosition(0, 0, 0);
		texQuad.SetDimension(5000, 5000);
		texQuad.SetTexture(textureParrot);
	}

	virtual void OnEvent(const Parrot::Event& e) override
	{
		if (e.type == Parrot::Event::Type::WindowCloseRequestEvent)
			Terminate();

		Parrot::LayerStack::ResolveEvent(e);
	}
	
	virtual void OnUpdate() override
	{
		Parrot::LayerStack::UpdateLayers();

		Parrot::Window::ClearColorBuffer(Parrot::Vector::Vec4f(1, 0, 1, 1));
		Parrot::Window::ClearDepthBuffer();

		Parrot::Renderer::BeginScene(camController->GetCam());
		Parrot::Renderer::DrawTexQuad(texQuad);
		Parrot::Renderer::EndScene();
	}
	
	virtual void OnTerminate() override
	{
		delete camController;
	}
};

const std::string Parrot::c_PathToParrot = std::string("../Parrot/");
Parrot::Application* Parrot::CreateApplication()
{
	return new Sandbox("Sandbox", Parrot::Vector::Vec2u(1080, 720));
}