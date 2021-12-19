#pragma once

namespace Parrot
{
	class Console
	{
	public:
		enum class Color : uint8_t
		{
			White = 15, Green = 10, Yellow = 14, Red = 12
		};

		static void Show();
		static void Hide();
		static void SetColor(Color color);
	private:
		static void Init(bool show);
		friend void OnCreate();
	};
}