#include "OpenGUI.h"

const char* FormattedFloat(float a, uint8_t minDecimals, uint8_t maxdecimals)
{
	bool isNegative = a < 0.0f ? true : false;
	if (a < 0.0f)
		a = -a;

	int64_t aInt = (int64_t)round(a * pow(10, maxdecimals - minDecimals));
	uint8_t wholeDigits = 1;
	while (a > pow(10, wholeDigits))
		wholeDigits++;
	uint8_t decimals = minDecimals;
	for (uint8_t i = minDecimals; i < maxdecimals; i++)
	{
		int32_t digit = aInt % 10;
		if (digit != 0)
		{
			decimals = maxdecimals + minDecimals - i;
			break;
		}
		aInt /= 10;
	}

	aInt = (int32_t)round(a * pow(10, decimals));

	uint32_t charLength;
	if (decimals > 0)
		charLength = wholeDigits + decimals + 2;
	else
		charLength = wholeDigits + 1;
	if (isNegative)
		charLength++;
	char* output = new char[charLength];
	if (isNegative)
	{
		output[0] = '-';
		output++;
	}

	for (uint32_t i = 0; i < decimals; i++)
	{
		int32_t digit = aInt % 10;
		aInt /= 10;
		output[wholeDigits + decimals - i] = digit + '0';
	}

	if (decimals > 0)
		output[wholeDigits] = '.';

	for (uint32_t i = 0; i < wholeDigits; i++)
	{
		int32_t digit = aInt % 10;
		aInt /= 10;
		output[wholeDigits - 1 - i] = digit + '0';
	}

	if (isNegative)
		output--;
	output[charLength - 1] = '\0';
	return output;
}

static constexpr uint32_t c_Padding = 10;
static constexpr uint32_t c_TextHeight = 20;
static constexpr uint32_t c_SliderLongDim = 30;
static constexpr uint32_t c_SliderShortDim = 20;

static Vec4f s_TextColor = Vec4f(0.4f, 0.7f, 0.9f, 1.0f);
static Vec4f s_SlideColor = Vec4f(0.5f);
static Vec4f s_SliderColor = Vec4f(0.0f, 0.15f, 0.5f, 0.5f);

static GLFWwindow* s_Window;
static Vec2u s_WindowDim;
static Font* s_Font;
static VerSlider s_Scroller;
static std::vector<Text> s_Names;
static uint32_t s_Height;

struct OpenGUIFloat
{
	float* data;
	Vec2f boundaries;
	HorSlider slider;

	OpenGUIFloat(float* data, Vec2f boundaries, uint32_t yOffset)
		: data(data), boundaries(boundaries), slider(Vec2u(0, yOffset + c_TextHeight), s_WindowDim.x - c_SliderShortDim - c_Padding, Vec2u(c_SliderLongDim, c_SliderShortDim)) { AdjustSlider(); }

	void AdjustSlider() { slider.SetProgressPercent((*data - boundaries.a) / (boundaries.b - boundaries.a)); }
	void AdjustData(bool isMouseButtonPressed, Vec2u mousePos) 
	{
		if (slider.IsTriggered(isMouseButtonPressed, mousePos)) 
			*data = slider.GetProgressPercent() * (boundaries.b - boundaries.a) + boundaries.a;
	}
	void PushToBatch(Font& font)
	{
		const char* num = FormattedFloat(*data, 3, 3);
		Text text(num, Vec3u((slider.slideLength >> 1), slider.slidePos.y, 0), font, c_TextHeight, s_TextColor, Anchor::MIDDLE);
		text.PushToBatch();
		BatchRenderer2D::PushQuad(FlatQuad(Vec3u(slider.slidePos, 10), Vec2u(slider.slideLength, slider.sliderDim.y), s_SlideColor));
		BatchRenderer2D::PushQuad(FlatQuad(Vec3u(slider.slidePos + Vec2u(slider.sliderProgress, 0), 0), slider.sliderDim, s_SliderColor));
		delete[] num;
	}
};

static std::vector<OpenGUIFloat> s_Floats;

void OpenGUI::Init(const char* title, Vec2u windowDim, Vec2u screenPos)
{
	s_Window = GLFWCreateWindow(title, windowDim.x, windowDim.y, false, false);
	glfwSetWindowPos(s_Window, screenPos.x, screenPos.y);
	glClearColor(0.3f, 0.3f, 0.35f, 1.0f);

	s_Font = new Font("Src/OpenGl/Font/StandardFonts/Consola/consola.ttf");

	s_Scroller.slideLength = windowDim.y;
	s_Scroller.slidePos = Vec2u(windowDim.x - c_SliderShortDim, 0);
	s_Scroller.sliderDim.x = c_SliderShortDim;
	s_Scroller.sliderProgress = 0;

	s_WindowDim = windowDim;
	s_Height = 0;
}

void OpenGUI::Terminate()
{
	glfwMakeContextCurrent(s_Window);
	delete s_Font;
	glfwDestroyWindow(s_Window);
	s_Window = nullptr;
}

void OpenGUI::PushName(const std::string& name)
{
	glfwMakeContextCurrent(s_Window);
	s_Height += c_TextHeight;
	s_Names.emplace_back(name + ':', Vec3u(0, s_Height, 0), *s_Font, c_TextHeight, s_TextColor);
}

void OpenGUI::PushOpenGUIFloat(float* data, Vec2f boundaries)
{
	glfwMakeContextCurrent(s_Window);
	s_Floats.emplace_back(data, boundaries, s_Height);
	s_Height += c_SliderShortDim + c_TextHeight;
}

void OpenGUI::PushFloat(const std::string& name, float* data, Vec2f boundaries)
{
	PushName(name);
	PushOpenGUIFloat(data, boundaries);
	s_Height += c_Padding;
}

void OpenGUI::PushVec2f(const std::string& name, Vec2f* data, Vec2f boundaries)
{
	PushName(name);
	PushOpenGUIFloat(&data->x, boundaries);
	PushOpenGUIFloat(&data->y, boundaries);
	s_Height += c_Padding;
}

void OpenGUI::PushVec3f(const std::string& name, Vec3f* data, Vec2f boundaries)
{
	PushName(name);
	PushOpenGUIFloat(&data->x, boundaries);
	PushOpenGUIFloat(&data->y, boundaries);
	PushOpenGUIFloat(&data->z, boundaries);
	s_Height += c_Padding;
}

void OpenGUI::PushVec4f(const std::string& name, Vec4f* data, Vec2f boundaries)
{
	PushName(name);
	PushOpenGUIFloat(&data->x, boundaries);
	PushOpenGUIFloat(&data->y, boundaries);
	PushOpenGUIFloat(&data->z, boundaries);
	PushOpenGUIFloat(&data->w, boundaries);
	s_Height += c_Padding;
}

void OpenGUI::Update()
{
	if (s_Window == nullptr)
		return;

	if (glfwWindowShouldClose(s_Window))
	{
		Terminate();
		return;
	}

	glfwMakeContextCurrent(s_Window);
	UpdateTitleFrames(s_Window);
	glViewport(0, 0, (GLsizei)s_WindowDim.x, (GLsizei)s_WindowDim.y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	uint32_t yOffset = s_Height > s_WindowDim.y ? (uint32_t)(s_Scroller.GetProgressPercent() * (s_Height - s_WindowDim.y)) : 0;
	 
	bool isMouseButtonPressed = glfwGetMouseButton(s_Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
	double mouseX, mouseY;
	glfwGetCursorPos(glfwGetCurrentContext(), &mouseX, &mouseY);
	Vec2u mousePos((uint32_t)mouseX, (uint32_t)mouseY + yOffset);
	
	BatchRenderer2D::SetContext(s_Window);
	BatchRenderer2D::SetGlobalOffset(Vec2i(0, -(int32_t)yOffset));
	
	// GUI scroller
	if (s_Height > s_WindowDim.y)
	{
		s_Scroller.sliderDim.y = s_WindowDim.y * s_WindowDim.y / s_Height;
		s_Scroller.IsTriggered(isMouseButtonPressed, Vec2u((uint32_t)mouseX, (uint32_t)mouseY));
		BatchRenderer2D::PushQuad(FlatQuad(Vec3u(s_Scroller.slidePos + Vec2u(0, yOffset), 10), Vec2u(c_SliderShortDim, s_Scroller.slideLength), s_SlideColor));
		BatchRenderer2D::PushQuad(FlatQuad(Vec3u(s_Scroller.slidePos + Vec2u(0, yOffset) + Vec2u(0, s_Scroller.sliderProgress), 0), s_Scroller.sliderDim, s_SliderColor));
	}
	
	for (uint32_t i = 0; i < s_Names.size(); i++)
		s_Names[i].PushToBatch();
	
	for (uint32_t i = 0; i < s_Floats.size(); i++)
	{
		s_Floats[i].AdjustData(isMouseButtonPressed, mousePos);
		s_Floats[i].PushToBatch(*s_Font);
	}
	BatchRenderer2D::Flush();

	//glfwPollEvents();
	glfwSwapBuffers(s_Window);
}
