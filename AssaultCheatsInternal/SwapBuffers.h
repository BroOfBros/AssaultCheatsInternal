// OpenGL wglSwapBuffers hook.

#pragma once

#include "stdafx.h"

// OpenGL wglSwapBuffers hook definitions
typedef BOOL(__stdcall* tWglSwapBuffers) (HDC hDc);