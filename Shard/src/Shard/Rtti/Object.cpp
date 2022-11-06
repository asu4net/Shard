#include "shpch.h"
#include "Object.h"

namespace Shard
{
    Type Object::m_Type = Type("Base Object", &Object::CreateObject);
}