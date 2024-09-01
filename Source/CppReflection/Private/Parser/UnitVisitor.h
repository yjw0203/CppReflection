#pragma once

template<class ConditionPolicy, class ActionPolicy>
class CRTranslationUnitVisitor
{
public:
    CRTranslationUnitVisitor(){};
    void Visit(CRTranslationUnit unit)
    {
        CRNamespace tempNamespace;
        dfs(unit.GetRootCursor(), tempNamespace);
    }
private:
    void dfs(CRCursor cursor, CRNamespace& currentNamespace)
    {
        int shouldVisitFlag = ShouldVisit(cursor, currentNamespace);
        if (shouldVisitFlag)DoAction(cursor, currentNamespace, shouldVisitFlag);

        bool push_ns = false;
        if (cursor.GetKind() == CXCursor_Namespace || cursor.GetKind() == CXCursor_ClassDecl || cursor.GetKind() == CXCursor_StructDecl || cursor.GetKind() == CXCursor_FieldDecl)
        {
            auto displayName = cursor.GetDisplayName();
            if (!displayName.empty())
            {
                currentNamespace.push_back(displayName);
                push_ns = true;
            }
        }

        CRCursor::List children = cursor.GetChildren();
        for (auto child : children)
        {
            dfs(child, currentNamespace);
        }

        if (push_ns)
        {
            currentNamespace.pop_back();
        }
    }
    bool ShouldVisit(CRCursor cursor, const CRNamespace& Namespace) { return m_condition.Condition(cursor, Namespace); }
    void DoAction(CRCursor cursor, const CRNamespace& Namespace,int flag) { m_handle.DoAction(cursor, Namespace, flag); }
private:
    ActionPolicy m_handle;
    ConditionPolicy m_condition;
};