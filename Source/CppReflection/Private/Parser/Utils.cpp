#include "Utils.h"

void CRToString(const CXString& str, std::string& output)
{
    auto cstr = clang_getCString(str);

    output = cstr;

    clang_disposeString(str);
}