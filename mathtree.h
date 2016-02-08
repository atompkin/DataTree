#ifndef MATH_TREE_H
#define MATH_TREE_H

#include <string>

struct asciinode_struct;

struct Tree
{
    Tree();
    Tree(double val);
    Tree(char var);
    Tree(std::string op, struct Tree *left, struct Tree *right);
    struct Tree *clone();
    struct Tree *derive();
    struct Tree *simplify();
    struct Tree *simplify_rec();
    bool equals(struct Tree *other);
    void print_inorder();
    bool is_var();
    bool is_val();
    bool is_unary_op();
    bool is_binary_op();

    struct Tree *left;
    struct Tree *right;
    std::string op;
    double val;
    char var;
};

void delete_tree(struct Tree *);

#endif
