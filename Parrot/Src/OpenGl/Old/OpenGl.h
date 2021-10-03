#pragma once

//#ifndef WIN32
//static_assert(0, "Only WIN32 systems are supported!");
//#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Buffer/VertexBuffer.h"
#include "Buffer/IndexBuffer.h"
#include "Buffer/VertexArray.h"
#include "Buffer/VertexBufferLayout.h"

#include "Shader/Shader.h"
#include "Shader/ShaderSnippetLib.h"

//#include "Font/Font.h"

#include "CreateWindow.h"
#include "GlDebug.h"
#include "Texture.h"

#include "BatchRenderer/BatchRenderer2D.h"
