#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "diamond.h"

int nbConfigurations;

/**********************************
	 functions to mangage the board
***********************************/
board_t* createBoard()
{
	board_t* b = NULL;
	int i, j;
	
	if((b = malloc(sizeof(board_t))) == NULL)
	{
		perror("malloc createBoard");
		return NULL;
	}

	clearBoard(b);
	
	for(i = 0; i < 13; i++)
	{
		for(j = 0; j < 6; j++)
			b->neighbors[i][j] = NO_NEIGHBOR;
	}
	

	// define neighbors for cell 0
	
	b->neighbors[0][0] = 1;
	b->neighbors[0][1] = 3;
	b->neighbors[0][2] = 4;
	
	// define neighbors for cell 1
	
	b->neighbors[1][0] = 0;
	b->neighbors[1][1] = 2;
	b->neighbors[1][2] = 4;
	b->neighbors[1][3] = 5;
	
	// define neighbors for cell 2
	
	b->neighbors[2][0] = 1;
	b->neighbors[2][1] = 5;
	b->neighbors[2][2] = 6;
	
	// define neighbors for cell 3
	
	b->neighbors[3][0] = 0;
	b->neighbors[3][1] = 4;
	b->neighbors[3][2] = 7;
	
	// define neighbors for cell 4
	
	b->neighbors[4][0] = 0;
	b->neighbors[4][1] = 1;
	b->neighbors[4][2] = 3;
	b->neighbors[4][3] = 5;
	b->neighbors[4][4] = 7;
	b->neighbors[4][5] = 8;
	
	// define neighbors for cell 5
	
	b->neighbors[5][0] = 1;
	b->neighbors[5][1] = 2;
	b->neighbors[5][2] = 4;
	b->neighbors[5][3] = 6;
	b->neighbors[5][4] = 8;
	b->neighbors[5][5] = 9;
	
	// define neighbors for cell 6
	
	b->neighbors[6][0] = 2;
	b->neighbors[6][1] = 5;
	b->neighbors[6][2] = 9;
	
	// define neighbors for cell 7
	
	b->neighbors[7][0] = 3;
	b->neighbors[7][1] = 4;
	b->neighbors[7][2] = 8;
	b->neighbors[7][3] = 10;
	
	// define neighbors for cell 8
	
	b->neighbors[8][0] = 4;
	b->neighbors[8][1] = 5;
	b->neighbors[8][2] = 7;
	b->neighbors[8][3] = 9;
	b->neighbors[8][4] = 10;
	b->neighbors[8][5] = 11;
	
	// define neighbors for cell 9
	
	b->neighbors[9][0] = 5;
	b->neighbors[9][1] = 6;
	b->neighbors[9][2] = 8;
	b->neighbors[9][3] = 11;
	
	// define neighbors for cell 10
	
	b->neighbors[10][0] = 7;
	b->neighbors[10][1] = 8;
	b->neighbors[10][2] = 11;
	b->neighbors[10][3] = 12;
	
	// define neighbors for cell 11
	
	b->neighbors[11][0] = 8;
	b->neighbors[11][1] = 9;
	b->neighbors[11][2] = 10;
	b->neighbors[11][3] = 12;
	
	// define neighbors for cell 12
	
	b->neighbors[12][0] = 10;
	b->neighbors[12][1] = 11;
	
	return b;
}

void clearBoard(board_t* b)
{
	int i;
	
	for(i = 0; i < 13; i++)
		b->board[i] = VOID_CELL;
		
	b->blueScore = 0;
	b->redScore = 0;
}

int voidCellIndex(board_t* b)
{
	int i;
	
	for(i = 0; i < 13; i++)
	{
		if(b->board[i] == VOID_CELL)
			return i;			
	}
	
	return -1;
}

void computeScore(board_t* b)
{
	int idVoid, i;
	
	b->blueScore = 0;
	b->redScore = 0;

	idVoid = voidCellIndex(b);
	
	for(i = 0; i < 6; i++)
	{
		if(b->neighbors[idVoid][i] != NO_NEIGHBOR)
		{
			if(b->board[(int)(b->neighbors[idVoid][i])] <= 6)
				b->blueScore += b->board[(int)(b->neighbors[idVoid][i])];
			else
				b->redScore += (b->board[(int)(b->neighbors[idVoid][i])] - 6);

		}
	}
}

void setPawn(board_t* b, int idCell, char value)
{
	b->board[idCell] = value;
}


/**********************************
	 functions to mangage the nodes
***********************************/

node_t* createNode(int idCell, int turn)
{
	node_t* n = NULL;
	
	if((n = malloc(sizeof(node_t))) == NULL)
	{
		perror("malloc createNode");
		return NULL;
	}
	
	n->idCell = (char)idCell;
	n->turn = (char)turn;

	if(turn == 1)
	{
		if((n->children = calloc(1, sizeof(node_t*))) == NULL)
		{
			perror("malloc n->children 1 createNode");
			return NULL;
		}
	}
	else if(turn < 12)
	{
		if((n->children = calloc((13 - turn), sizeof(node_t*))) == NULL)
		{
			perror("malloc n->children 2 createNode");
			return NULL;
		}
	}
	else
		n->children = NULL;
		
	n->nbChildren = 0;
	n->result = NO_RESULT;

	return n;
}

node_t* addChild(node_t* n, int idCell)
{
	n->children[(int)n->nbChildren] = createNode(idCell, n->turn + 1);
	n->nbChildren++;

	return n->children[(int)(n->nbChildren - 1)];
}

/**********************************
	 functions to mangage the tree
***********************************/

tree_t* createTree()
{
	tree_t* t = NULL;

	if((t = calloc(1, sizeof(tree_t))) == NULL)
	{
		perror("malloc createTree");
		return NULL;
	}

	nbConfigurations = 0;
	
	return t;
}

void freeNode(node_t *n)
{
	int i;

	for(i = 0; i < n->nbChildren; i++)
		freeNode(n->children[i]);

	free(n);
}

void setFirstBlueChoice(tree_t* t, board_t* b, int idCell)
{
	t->root = createNode(idCell, 1);
	setPawn(b, idCell, (char)1);
}
	
void setFirstRedChoice(tree_t* t, board_t* b, int idCell)
{
	addChild(t->root, idCell);
	setPawn(b, idCell, (char)7);
}

void buildTree(tree_t* t, board_t* b)
{
	node_t *n;
	nbConfigurations = 0;
	
	n = t->root->children[0];
	computePossibilities(n, b);
	
	printf(" done.\n");
}

void computePossibilities(node_t* n, board_t* b)
{
	if(n->turn == 12)
	{
		computeScore(b);
		
		int r = b->redScore;
		int b_ = b->blueScore;
		
		if(b_ == r)
			n->result = DRAW_PARTY;
		else if(b_ < r)
			n->result = BLUE_WINS;
		else
			n->result = RED_WINS;
			
		nbConfigurations++;
		
		if(!(nbConfigurations % 1000000))
			printf(".");
			
		return;
	}
	
	int nextPawnValue = (n->turn + 2) / 2, i;
	
	if(!((n->turn + 1) % 2))
		nextPawnValue += 6;
		
	for(i = 0; i < 13; i++)
	{
		if(b->board[i] == VOID_CELL)
		{
			setPawn(b, i, (char)nextPawnValue);
			node_t *child = addChild(n, i);

			computePossibilities(child, b);
			setPawn(b, i, VOID_CELL);
		}
	}
}

int computeBlueVictories(node_t* n)
{
	int nb = 0, i;

	if(!n->nbChildren && n->result == BLUE_WINS)
		nb++;

	for(i = 0; i < n->nbChildren; i++)
		nb += computeBlueVictories(n->children[i]);
	
	return nb;
}

int computeRedVictories(node_t* n)
{
	int nb = 0, i;

	if(!n->nbChildren && n->result == RED_WINS)
		nb++;

	for(i = 0; i < n->nbChildren; i++)
		nb += computeRedVictories(n->children[i]);
	
	return nb;
}

int computeDraws(node_t* n)
{
	int nb = 0, i;

	if(!n->nbChildren && n->result == DRAW_PARTY)
		nb++;

	for(i = 0; i < n->nbChildren; i++)
		nb += computeDraws(n->children[i]);
	
	return nb;
}

void printDiamond(board_t *b)
{
	int i;
	
	for(i = 0; i < 13; i++)
	{
		printf("%d ", b->board[i]);
	}
	
	printf("\n");
}
