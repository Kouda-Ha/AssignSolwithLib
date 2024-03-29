// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#pragma once
#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>

// OpenGL stuff
#define GLEW_STATIC // use the statically linked (i.e. non-dll) version of glew library
#include <gl/glew.h>
// glfw (OpenGL framework)
#include <GLFW/glfw3.h>
// glm (open gl maths - vectors and matrices)
#define GLM_FORCE_CTOR_INIT // force glm to initialize vectors and matrices to 0 and identity respectively (default behaviour until recently)
#define GLM_ENABLE_EXPERIMENTAL // allow some new stuff (e.g. rotate_vector extensions)
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/type_ptr.hpp>
