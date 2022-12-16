#pragma once
#include "Shard/Core/Application.h"
#include "Shard/Core/Event.h"
#include "Shard/Core/Input.h"
#include "Shard/Core/KeyCodes.h"
#include "Shard/Core/TimeData.h"

#include "Shard/Rendering/Renderer.h"
#include "Shard/Rendering/Window.h"
#include "Shard/Rendering/Primitives.h"
#include  "Shard/Rendering/Font.h"

#include "Shard/ImGui/ImGuiRenderer.h"
#include "imgui.h"
#include "Shard/ImGui/ImGuiGLFW.h"
#include "Shard/ImGui/ImGuiOpenGL.h"

#include "Shard/Ecs/Components.h"
#include "Shard/Ecs/Entity.h"
#include "Shard/Ecs/Scene.h"

#include "Shard/Ecs/Physics2DSystem.h"
#include "Shard/Ecs/TextSystem.h"
#include "Shard/Ecs/SimpleSpriteAnimationSystem.h"
#include "Shard/Ecs/BasicShapesSystem.h"
#include "Shard/Ecs/SpriteSystem.h"
#include "Shard/Ecs/CameraSystem.h"
#include "Shard/Ecs/TransformSystem.h"

// ReSharper disable CppClangTidyClangDiagnosticHeaderHygiene
#ifdef USE_SHARD_NAMESPACES
using namespace Shard;
using namespace Math;
using namespace Rendering;
using namespace Primitives;
using namespace Ecs;
#endif