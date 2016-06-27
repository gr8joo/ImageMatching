#include"PositionTree.h"

item* newItem(item *T, item *A, int t, int a, int leaf)
{
	item *temp = (item *)malloc(sizeof(item));
	//temp -> B = (int *)calloc(numLetter, sizeof(int));
	temp -> T_son_list = (item **)calloc(numLetter, sizeof(item*));
	temp -> A_son_list = (item **)calloc(numLetter, sizeof(item*));

	temp -> T_parent = T;
	temp -> A_parent = A;

	temp -> T_edge = t;
	temp -> A_edge = a;
	
	if(temp -> T_parent == NULL && temp -> A_parent == NULL)
	{
		temp -> T_depth = 0;
		temp -> A_depth = 0;
	}
	else
	{
		temp -> T_depth = temp->T_parent->T_depth + 1;
		temp -> A_depth = temp->A_parent->A_depth + 1;
	}

	temp -> ifleaf = leaf;
	
	return temp;
}

void case2helper(int *x, item *u, item **dla, int c, int depth, int i)
{
	static item *v;
	static int k;
	int l1, l2;
	if(u -> A_son_list[c] == NULL)
		case2helper(x, u -> T_parent,dla, c, depth+1, i);
	else
	{
		v = u -> A_son_list[c];
		k = v -> ifleaf;
		v -> ifleaf = 0;
		dla[k] = NULL;
		return;
	}

	l1 = u->T_edge;								//C1~Cq

	v -> T_son_list[l1] =
	u -> A_son_list[c] =
		newItem(v, u, u -> T_edge, x[i-1], 0);
	
	//making new Vh+1 under Vh
	memcpy(v -> T_son_list[l1] -> B, v -> B, numLetter*sizeof(int));					//Copy B

	v = v -> T_son_list[l1];							//Now goes to V from Vparent
	

	if(depth == 0)
	{
		//printf("%d %c %c\n",i, c[i + u->T_depth], c[k + u->T_depth]);
		l1 = x[ i + u->T_depth];
		dla[i]=	v -> T_son_list[l1]=
			u -> T_son_list[l1] -> A_son_list[c]=
				newItem(v, u->T_son_list[l1], x[ i + u->T_depth], x[i-1], i);
		
		l2 = x[ k + u->T_depth];
		dla[k]=	v -> T_son_list[l2] = 
			u -> T_son_list[l2] -> A_son_list[c] = 
				newItem(v, u->T_son_list[l2], x[ k + u->T_depth], x[i-1], k);
		memcpy(v->T_son_list[l2]->B, v->B, numLetter*sizeof(int));
	}
}

void case3_helper(int *x, item *u, item **dla, int c, int i)
{
	int l1, l2;
	item *v = u -> A_son_list[c];
	int k = v->ifleaf;
	v->ifleaf = 0;
	//printf("%d %d\n", c, k);
	
	l1 = x[ i + u->T_depth];
	dla[i]=	v -> T_son_list[l1]=
		u -> T_son_list[l1] -> A_son_list[c]=
			newItem(v, u->T_son_list[l1], x[ i + u->T_depth], x[i-1], i);
		
	l2 = x[ k + u->T_depth];
	dla[k]=	v -> T_son_list[l2]=
		u -> T_son_list[l2] -> A_son_list[c]=
			newItem(v, u->T_son_list[l2], x[ k + u->T_depth], x[i-1], k);
	memcpy(v->T_son_list[l2]->B, v->B, numLetter*sizeof(int));
	
}

void case4_helper(int *x, item *u, item **dla, int c, int i)
{
	int l1;
	item *v = u -> A_son_list[c];
	//int k = v->ifleaf;

	l1 = x[ i + u->T_depth];
	dla[i]=	v -> T_son_list[l1]=
		u->T_son_list[l1]->A_son_list[c]=
			newItem(v, u->T_son_list[l1], x[ i + u->T_depth], x[i-1], i);
		
}

item* PositionTree(item **dla, int *x, int end)
{
	int c;
	int i, k;
	item *root, *temp = NULL;
	int m;

	temp = NULL;

//Root and Tn+1 An+1 Setting
	root = newItem(NULL, NULL, -1, -1, 0);
	root->B[endMark] = 1;

	dla[end]= root->T_son_list[endMark]
		= root->A_son_list[endMark]
			= newItem(root, root, endMark, endMark, end);


	for(k=end-2; k>=0; k--)
	{
		c = x[k];
		
		i = k+1;
		temp = dla[i+1];
		//m=0;
		while(temp != NULL &&temp->B[c] != 1)	//find uy
		{
			temp->B[c] = 1;
			temp = temp->T_parent;
			m++;
		}
		
		if(temp == NULL)			//Case 1
		{
			root -> B[c] = 1;
			dla[i] = root -> T_son_list[c] = root->A_son_list[c] = newItem(root, root, c, c, i);
			//printf("%d: Case 1\n", i);
		}
		
		else if(temp->A_son_list[c] == 0)	//Case 2
		{
			case2helper(x, temp, dla, c, 0, i);			
			//printf("%d: Case 2\n", i);
		}

		else if(temp -> A_son_list[c] -> ifleaf != 0)	//case 3 a)
		{
			case3_helper(x, temp, dla, c, i);
			//printf("%d: Case 3_a)\n", i);
		}
		else							//case 3 b)
		{
			case4_helper(x, temp, dla, c, i);
			//printf("%d: Case 3_b)\n", i);
		}
	}

	return root;
}
void recur(item * temp)		//traverse the tree from the bottom, which is leaf, to top.
{
	if(temp -> T_parent == NULL && temp -> A_parent == NULL)
		return;
	else
		recur(temp -> T_parent);
	printf("%4d", temp->T_edge);
}
