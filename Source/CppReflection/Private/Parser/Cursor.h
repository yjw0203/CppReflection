#pragma once
#include <clang-c/Index.h>
#include <vector>
#include <string>
typedef std::vector<std::string> CRNamespace;

class CRCursor
{
public:
    typedef std::vector<CRCursor> List;
    CRCursor(const CXCursor& handle);
    operator CXCursor();

    List GetChildren(void) const;
    std::string GetDisplayName(void) const;
    CXCursorKind CRCursor::GetKind(void) const;
    bool CRCursor::IsDefinition(void) const;

private:
    CXCursor m_handle;
}; 