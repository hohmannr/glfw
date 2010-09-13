//========================================================================
// GLFW - An OpenGL framework
// Platform:    Any
// API version: 3.0
// WWW:         http://www.glfw.org/
//------------------------------------------------------------------------
// Copyright (c) 2002-2006 Marcus Geelnard
// Copyright (c) 2006-2010 Camilla Berglund <elmindreda@elmindreda.org>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================

#include "internal.h"

#include <stdlib.h>


//========================================================================
// Lexical comparison function for GLFW video modes, used by qsort
//========================================================================

static int compareVideoModes(const void* firstPtr, const void* secondPtr)
{
    int firstBPP, secondBPP, firstSize, secondSize;
    GLFWvidmode* first = (GLFWvidmode*) firstPtr;
    GLFWvidmode* second = (GLFWvidmode*) secondPtr;

    // First sort on color bits per pixel

    firstBPP = first->redBits +
               first->greenBits +
               first->blueBits;
    secondBPP = second->redBits +
                second->greenBits +
                second->blueBits;

    if (firstBPP != secondBPP)
        return firstBPP - secondBPP;

    // Then sort on screen area, in pixels

    firstSize = first->width * first->height;
    secondSize = second->width * second->height;

    return firstSize - secondSize;
}

//////////////////////////////////////////////////////////////////////////
//////                        GLFW public API                       //////
//////////////////////////////////////////////////////////////////////////

//========================================================================
// Get a list of available video modes
//========================================================================

GLFWAPI int glfwGetVideoModes(GLFWvidmode* list, int maxcount)
{
    int count;

    if (!_glfwInitialized)
    {
        _glfwSetError(GLFW_NOT_INITIALIZED);
        return;
    }

    if (maxcount <= 0 || list == NULL)
    {
        // TODO: Figure out if this is an error
        return 0;
    }

    count = _glfwPlatformGetVideoModes(list, maxcount);
    if (count > 0)
        qsort(list, count, sizeof(GLFWvidmode), compareVideoModes);

    return count;
}


//========================================================================
// Get the desktop video mode
//========================================================================

GLFWAPI void glfwGetDesktopMode(GLFWvidmode* mode)
{
    if (!_glfwInitialized)
    {
        _glfwSetError(GLFW_NOT_INITIALIZED);
        return;
    }

    if (mode == NULL)
    {
        _glfwSetError(GLFW_INVALID_VALUE);
        return;
    }

    _glfwPlatformGetDesktopMode(mode);
}

