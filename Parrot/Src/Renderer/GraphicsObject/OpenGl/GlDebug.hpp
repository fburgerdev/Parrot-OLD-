#pragma once
#include "Ptpch.hpp"
#include <glad/glad.h>
#include "Debug/Log.hpp"

#ifdef PT_DEBUG
#define GlCall(x) Parrot::GlClearError(); x; GlLogAssert(__FUNCTION__, __FILE__, __LINE__)
#else
#define GlCall(x) x
#endif

namespace Parrot
{
    static void GlClearError()
    {
        while (glGetError() != GL_NO_ERROR);
    }

    static void GlLogAssert(const char* function, const char* file, int32_t line)
    {
        bool failed = false;
        while (GLenum error = glGetError())
        {
            Log::LogError("OpenGl error with error code \"%\" in file \"%\", function \"%\", line \"%\"!", error, file, function, line);
            failed = true;
        }
        Log::LogAssert(!failed, "Fatal OpenGl fail!");
    }
}