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
#include "Shard/Ecs/Scene/Scene.h"

#include "Shard/Ecs/Systems/Physics2DSystem.h"
#include "Shard/Ecs/Systems/TextSystem.h"
#include "Shard/Ecs/Systems/SimpleSpriteAnimationSystem.h"
#include "Shard/Ecs/Systems/BasicShapesSystem.h"
#include "Shard/Ecs/Systems/SpriteSystem.h"
#include "Shard/Ecs/Systems/CameraSystem.h"
#include "Shard/Ecs/Systems/TransformSystem.h"

#include "Shard/Ecs/Scripting/Native/Parallax.h"
#include "Shard/Ecs/Scripting/Native/CameraController.h"