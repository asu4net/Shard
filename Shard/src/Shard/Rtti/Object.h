#pragma once
#include <string>
#include "Type.h"

namespace Shard
{
    class Object
    {        
    public:
        static Object* CreateObject() { return new Object(); };

        const Type* GetType() const { return &m_type; }

    private:
        inline static Type m_type = Type("Object", nullptr, &Object::CreateObject);
    };
}

#define DECLARE_OBJECT(_TYPE, _PARENT_TYPE) \
public: \
  static Object* CreateObject() \
  { \
    return new _TYPE(); \
  } \
  static const Type* GetType() const { return &m_type; } \
private: \
  inline static Type m_type = _TYPE(#_TYPE, _PARENT_TYPE::GetStaticType(), &_TYPE::CreateObject);