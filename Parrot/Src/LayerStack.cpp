#include "Pch.hpp"
#include "LayerStack.hpp"

namespace Parrot
{
	static std::vector<Layer*> s_LayerStack;

	void LayerStack::PushLayer(Layer* layer)
	{
		s_LayerStack.push_back(layer);
	}
	void LayerStack::PopLayer()
	{
		s_LayerStack.pop_back();
	}

	void LayerStack::ResolveEvent(const Event& e)
	{
		if (s_LayerStack.size() == 0)
			return;
		int32_t i = (int32_t)s_LayerStack.size() - 1;
		while (i >= 0 && !s_LayerStack[i]->ResolveEvent(e))
			i--;
	}
	void LayerStack::UpdateLayers()
	{
		for (uint32_t i = 0; i < s_LayerStack.size(); i++)
			s_LayerStack[i]->OnUpdate();
	}
}
