#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define numLetter 256
#define endMark 255
#define questionMark 254

typedef struct Vertex {
	int B[numLetter];

	struct Vertex **T_son_list;
	struct Vertex **A_son_list;

	struct Vertex *T_parent;
	struct Vertex *A_parent;
	
	int T_edge;
	int A_edge;

	int T_depth;
	int A_depth;

	int ifleaf;
}item;

item* newItem(item *T, item *A, int t, int a, int leaf);

void case2helper(int *x, item *u, item **dla, int c, int depth, int i);

void case3_helper(int *x, item *u, item **dla, int c, int i);

void case4_helper(int *x, item *u, item **dla, int c, int i);

item* PositionTree(item **dla, int *x,int end);

void recur(item * temp);
