#pragma once

template<class ConditionPolicy, class ActionPolicy>
class CRTranslationUnitVisitor : public ActionPolicy
{
public:
    using ActionPolicy::ActionPolicy;

    void Visit(CRTranslationUnit unit)
    {
        CRNamespace tempNamespace;
        dfs(unit.GetRootCursor(), tempNamespace);
    }
private:
    void dfs(CRCursor cursor, CRNamespace& currentNamespace)
    {
        int shouldVisitFlag = ShouldVisit(cursor, currentNamespace);
        if (shouldVisitFlag)DoActionInterface(cursor, currentNamespace, shouldVisitFlag);

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
    int ShouldVisit(CRCursor cursor, const CRNamespace& Namespace) { return m_condition.Condition(cursor, Namespace); }
    void DoActionInterface(CRCursor cursor, const CRNamespace& Namespace,int flag) { this->DoAction(cursor, Namespace, flag); }
private:
    ConditionPolicy m_condition;
};