#include <cmath>
#include <iostream>
#include "mathtree.h"
using namespace std;

Tree::Tree()
{
    left = NULL;
    right = NULL;
    op = "";
    val = 0.0;
    var = 0;
}

Tree::Tree(double val)
{
    left = NULL;
    right = NULL;
    op = "";
    this->val = val;
    var = 0;
}

Tree::Tree(char var)
{
    left = NULL;
    right = NULL;
    op = "";
    val = 0.0;
    this->var = var;
}

Tree::Tree(string op, Tree *left, Tree *right)
{
    this->left = left;
    this->right = right;
    this->op = op;
    val = 0.0;
    var = 0;
}

bool Tree::is_var()
{
    return (op == "" && left == NULL && right == NULL && var != 0);
}

bool Tree::is_val()
{
    return (op == "" && left == NULL && right == NULL && var == 0);
}

bool Tree::is_unary_op()
{
    return (op != "" && left != NULL && right == NULL);
}

bool Tree::is_binary_op()
{
    return (op != "" && left != NULL && right != NULL);
}

void delete_tree(struct Tree *root)
{
    // TODO
        if(root -> is_var)
    {
        delete [] root;
    }
    else
    {
        while(left != NULL)
        {
            delete_tree(left);
        }
        while(right != NULL)
        {
            delete_tree(right);
        }
    }
}

bool Tree::equals(struct Tree *other)
{
    if(is_val() && other->is_val() && val == other->val) { return true; }
    if(is_var() && other->is_var() && var == other->var) { return true; }
    if(is_unary_op() && other->is_unary_op() && op == other->op && left->equals(other->left)) { return true; }
    if(is_binary_op() && other->is_binary_op() && op == other->op && left->equals(other->left) && right->equals(other->right)) { return true; }
    return false;
}

struct Tree *Tree::clone()
{
       struct Tree *t;
       if(is_val()){
           t = new Tree(val);
       }
       else if(is_var()){
           t = new Tree(var);
       }
       else if(right == NULL){
           t = new Tree(op, left->clone(), NULL);
       }
       else{
           t = new Tree(op, left->clone(), right->clone());
       }
       return t;
}

struct Tree *Tree::simplify_rec()
{
    // TODe

    return clone();
}

struct Tree *Tree::simplify()
{
    struct Tree *priortree = clone();
    struct Tree *newtree = priortree->simplify_rec();

    // simplify over-and-over until the output is the same
    while(!priortree->equals(newtree))
    {
        delete_tree(priortree);
        priortree = newtree;
        newtree = priortree->simplify_rec();
    }
    delete_tree(priortree);
    return newtree;
}

struct Tree *Tree::derive()
{
    // TODO

    return clone();
}

void Tree::print_inorder()
{
    // TODO
}

