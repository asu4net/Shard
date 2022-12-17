#pragma once
#include <string>
#include "Type.h"

namespace Shard
{
    class Object
    {        
    public:
        static Object* CreateObject() { return new Object(); };

        static const Type* GetType() { return &m_type; }

    private:
        inline static Type m_type = Type("Object", nullptr, &Object::CreateObject);
    };
}

#define SHARD_OBJECT(_TYPE, _PARENT_TYPE) \
public: \
  static Object* CreateObject() \
  { \
    return new _TYPE(); \
  } \
  static const Type* GetType() { return &m_type; } \
private: \
  inline static Type m_type = Type(#_TYPE, _PARENT_TYPE::GetType(), &_TYPE::CreateObject);