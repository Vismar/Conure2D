#pragma once
/*! \file */
#include <string>
#include <typeindex>

#if defined(__clang__) || defined(__GNUG__)
#include <cxxabi.h>
#endif

namespace C2D
{
#define S1(x) #x
#define S2(x) S1(x)

    /*!
     * \brief Simple macro that unifies __FILE__ and __LINE__ preprocessor things in format "FileName:LineNumber".
     */
    #define LOCATION __FILE__ ":" S2(__LINE__)

    /*!
     * \brief Demangles (makes readable by human) name of a specified type.
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