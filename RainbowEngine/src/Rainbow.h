#pragma once

//For use by Rainbow Application (making inclusion easier)

#include "Rainbow\Application.h"

// ----------------- Entry Point -----------------
#include "Rainbow\EntryPoint.h"
// -----------------------------------------------

// ----------------- Basic -----------------
#include "Rainbow\Camera.h"
#include "Rainbow\Light.h"
#include "Rainbow\Positionable.h"
// -----------------------------------------

// ----------------- Sounds -----------------
#include "Rainbow\SoundManager.h"
#include "Rainbow\SoundContext.h"
#include "Rainbow\Sound.h"
// ------------------------------------------

// ----------------- Physics -----------------
#include "Rainbow\Force.h"
#include "Rainbow\PhysicObject.h"
// -------------------------------------------

// ----------------- Graphics -----------------
#include "Rainbow\Mesh.h"
#include "Rainbow\MeshFactory.h"
#include "Rainbow\Material.h"
// --------------------------------------------

// ----------------- Abstraction -----------------
#include "Rainbow\Object.h"
#include "Rainbow\ObjectFactory.h"
#include "Rainbow\Scene.h"
// -----------------------------------------------

// ----------------- ImGui -----------------
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"
// -----------------------------------------

/*To ADD ?
//OpenGL Abstraction
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Shader.h"
#include "Renderer.h"
#include "Macros.h"

*/