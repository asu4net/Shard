#pragma once

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <memory>
#include <thread>
#include <utility>
#include <cmath>

#include <string>
#include <sstream>
#include <fstream>
#include <array>
#include <vector>
#include <map>
#include <unordered_map>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/common.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/type_ptr.hpp"

const glm::quat IdentityQuat = {1, 0, 0, 0};

#include "Math/Color.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/SimpleStructs.h"

#include "Event.h"

namespace Shard
{
    constexpr float ToRadians = 0.0174533f;
    
    template <typename T>
    std::string StringFromNumber(T value)
    {
        std::ostringstream stream;
        stream << std::fixed << value;
        return stream.str();
    }
}