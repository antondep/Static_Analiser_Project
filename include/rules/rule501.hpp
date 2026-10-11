#pragma once

#include <clang/AST/ASTContext.h>
#include <clang/AST/Expr.h>
#include <clang/AST/OperationKinds.h>

class rule501
{
public:
    static void check(clang::BinaryOperator *op, clang::ASTContext *context);

private:
    static bool areEquivalentSubExprs(const clang::Expr *lhs,
                                      const clang::Expr *rhs,
                                      clang::ASTContext *context);
};