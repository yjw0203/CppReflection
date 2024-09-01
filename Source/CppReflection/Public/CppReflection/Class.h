#pragma once
#include "Public/CppReflection/Macro.h"
#include "Public/CppReflection/Object.h"

namespace ref
{
    class Class
    {
        friend class ClassFactory;
    public:
        Class();
        const char* GetName();
    private:
        void* m_def = nullptr;
    };

    class ClassFactory
    {
    public:
        template<typename T>
        static Class* CreateClass();

#ifdef __REFLECTION_TOOL__
        static Class* CreateClass();
#endif
    };
}