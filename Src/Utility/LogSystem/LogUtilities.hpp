#pragma once
#include <string>
#include <typeindex>

#if defined(__clang__) || defined(__GNUG__)
#include <cxxabi.h>
#endif

namespace Utility
{
    inline std::string PrettyTypeName(const std::type_index& typeIndex)
    {
        std::string typeName = typeIndex.name();

#if defined(__clang__) || defined(__GNUG__)
        int status;
        auto demangledName = abi::__cxa_demangle(typeName.c_str(), nullptr, nullptr, &status);
        if(status == 0)
        {
            typeName = demangledName;
            std::free(demangledName);
        }
#endif

        return typeName;
    }
}