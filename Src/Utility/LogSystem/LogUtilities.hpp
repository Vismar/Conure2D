#pragma once
#include <string>
#include <typeindex>

#if defined(__clang__) || defined(__GNUG__)
#include <cxxabi.h>
#endif

namespace Utility
{
    /*!
     * \brief Demangle (makes readable by human) name of a specified type.
     * \param typeIndex - type of which name function will return.
     * \return Demangled name of a specified type.
     */
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