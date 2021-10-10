#pragma once
#include "Ptpch.hpp"
#include "Core/Log.hpp"
#include <assert.h>
#include <glad/glad.h>

#ifdef PT_DEBUG
#define GlCall(x) Parrot::GlClearError(); x; assert(Parrot::GlLogCall(#x, __FILE__, __LINE__))
#else
#define GlCall(x) x
#endif

namespace Parrot
{
    static void GlClearError()
    {
        while (glGetError() != GL_NO_ERROR);
    }

    static int32_t GlLogCall(const char* function, const char* file, int32_t line)
    {
        int32_t noErrors = 1;
        while (GLenum error = glGetError())
        {
            Log::LogError("OpenGl error \"%s\" in file \"%s\", function \"%s\", line \"%i\"", error, file, function, line);
            noErrors = 0;
        }
        return noErrors;
    }
}