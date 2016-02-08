#ifndef ASCIITREE_H
#define ASCIITREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mathtree.h"

typedef struct asciinode_struct asciinode;

struct asciinode_struct
{
	asciinode * left, * right;

	//length of the edge from this node to its children
	int edge_length;

	int height;

	int lablen;

	//-1=I am left, 0=I am root, 1=right
	int parent_dir;

	//max supported unit32 in dec, 10 digits max
	char label[11];
};

asciinode * build_ascii_tree_recursive(struct Tree * t);
asciinode * build_ascii_tree(struct Tree * t);
void free_ascii_tree(asciinode *node);
void compute_lprofile(asciinode *node, int x, int y);
void compute_rprofile(asciinode *node, int x, int y);
void compute_edge_lengths(asciinode *node);
void print_level(asciinode *node, int x, int level);
void print_ascii_tree(struct Tree * t);

#endif
