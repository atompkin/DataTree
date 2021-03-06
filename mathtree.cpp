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
    if(root->left != NULL) 
    {
	delete_tree(root->left);	
    }
    if(root->right != NULL)
    {
	delete_tree(root->right);	    	
    }
    delete root;
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
    // TODO
	if(is_binary_op() && left->is_val())
	{
		if(left->val == 1.0 && op == "*")
		{
			return right -> simplify();
		}
		if(left->val == 0.0 && op == "*")
		{
			return new Tree(0.0);
		}
		if(left->val == 0.0 && op == "+")
		{
			return right -> simplify();
		}
	}
	if(is_binary_op() && right->is_val())
	{
		if(right->val == 1.0 && op =="*")
		{
			return left -> simplify();
		}
		if(right->val == 0.0 && op =="*")
		{
			return new Tree(0.0);
		}
		if(right->val == 0.0 && op == "+")
		{
			return left -> simplify();
		}


	}
	if(is_unary_op())
	{
		if(op == "sin" && left->is_val())
		{
			return new Tree(sin(left->val));
		}
		if(op == "cos" && left->is_val())
		{
			return new Tree(cos(left->val));
		}
		if(op == "ln" && left-> is_val())
		{
			return new Tree(log(left->val));
		}
	}
	if(is_binary_op())
	{
		if(op == "+" && left->is_val() && right->is_val())
		{
			return new Tree(left->val + right->val);
		}
		if(op == "-" && left->is_val() && right->is_val())
		{
			return new Tree(left->val - right->val);
		}
		if(op == "*" && left->is_val() && right->is_val())
		{
			return new Tree(left->val * right->val);
		}
		if(op == "/" && left->is_val() && right->is_val())
		{
			return new Tree(left->val / right->val);
		}
		if(op == "^" && left->is_val() && right->is_val())
		{
			return new Tree(pow(left->val,right->val));
		}
	}
    if(is_binary_op()) return new Tree(op, left->simplify(), right->simplify());
    if(is_unary_op()) return new Tree(op, left->simplify(), NULL);
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
    if(is_var())
    {
	    return new Tree(1.0);
    }
    if(is_val())
    {
	    return new Tree(0.0);
    }
    if(op == "sin")
    {
	    return new Tree("*",new Tree("cos", left->clone(), NULL),left->derive());
    }
    if(op == "cos")
    {
	    return new Tree("-",new Tree(0.0),new Tree("*",new Tree("sin",left->clone(),NULL),left->derive()));
    }
    if(op == "ln")
    {
	    return new Tree("*",new Tree("/",new Tree(1.0),left->clone()),left->derive());
    }
    if(op == "+")
    {
	    return new Tree("+",left->derive(),right->derive());
    }
    if(op == "-")
    {
	    return new Tree("-",left->derive(),right->derive());
    }
    if(op == "*")
    {
	    return new Tree("+",new Tree("*",left->derive(),right->clone()),new Tree("*",left->clone(),right->derive()));
    }
    if(op == "/")
    {
	    return new Tree("/",new Tree("-",new Tree("*",left->derive(),right->clone()),new Tree("*",left->clone(),right->derive())),new Tree("^",right->clone(),new Tree(2.0)));
    }
    if(op == "^")
    {
	    return new Tree("*",new Tree("^",left->clone(),right->clone()),new Tree("+",new Tree("*", left->derive(),new Tree("/",right->clone(),left->clone())),new Tree("*",right->derive(),new Tree("ln",left->clone(),NULL))));
    }
    return clone();
}

void Tree::print_inorder()
{
    if(is_unary_op())
    {
	    cout << op << "(";
	    left->print_inorder();
	    cout << ")";
    }
    else if(op== "-" && left->val == 0.0 && left->op == "")
    {
	    cout << "-";
	    right->print_inorder();
    }
    else if(is_var())
    {
	    cout << var;
    }
    else if(is_val())
    {
	    cout << val;
    }
    else if(is_binary_op())
    {
	    cout << "(";
	    left->print_inorder();
	    cout << op;
	    right->print_inorder();
	    cout << ")";
    }

}

