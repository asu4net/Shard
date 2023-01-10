#pragma once
#include "Type.h"

namespace Shard
{
    class Object
    {        
    public:
        static Object* CreateObject() { return new Object(); }
        
        static const Type* GetType() { return &m_type; }
        
        template<typename T>
        T* Cast()
        {
            if (!IsChildOf(T::GetType())) return nullptr;
            return static_cast<T*>(this);
        }

    private:
        inline static Type m_type = Type("Object", nullptr, &Object::CreateObject);
    };
}

#define SHARD_OBJECT(_TYPE, _PARENT_TYPE) \
public: \
  static Shard::Object* CreateObject() \
  { \
    return new _TYPE(); \
  } \
  static const Shard::Type* GetType() { return &m_type; } \
private: \
  inline static Shard::Type m_type = Shard::Type(#_TYPE, _PARENT_TYPE::GetType(), &_TYPE::CreateObject);