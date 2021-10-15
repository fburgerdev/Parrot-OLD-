#pragma once
#include "Event.hpp"

namespace Parrot
{
	class Layer
	{
	public:
		virtual bool ResolveEvent(const Event& e) = 0;
		virtual void OnUpdate() = 0;
	};

	class LayerStack
	{
	public:
		static void PushLayer(Layer* layer);
		static void PopLayer();

		static void ResolveEvent(const Event& e);
		static void UpdateLayers();
	};
}