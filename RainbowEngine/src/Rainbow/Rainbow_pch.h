#pragma once

//standard librairy
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream> 
#include <unordered_map> 
#include <memory> 
#include <vector>
#include <thread>
#include <string>

//Windows specific 
#include <windows.h>

//OpenGL
#include "GL/glew.h"
#include "GLFW/glfw3.h"

//OpenAL
#include "al.h"
#include "alc.h"

//Libsnd-file (.wav parser)
#define ENABLE_SNDFILE_WINDOWS_PROTOTYPES 1
#include "sndfile.h"

//glm (math lib)
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"

//ImGui (graphic interface)
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

//stb_image (image reader for textures)
#include "stb_image\stb_image.h"

/*
//OpenGL Abstraction
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Shader.h" 
#include "Renderer.h"
#include "Macros.h"
#include "Material.h"  

//Object abstraction (+ factory)
#include "Object.h"
#include "ObjectFactory.h"
*/
//Sound
#include "Sound.h"
#include "SoundContext.h"
