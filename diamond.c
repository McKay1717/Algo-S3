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
	
	if((b = malloc(sizeof(board_t)) == NULL)
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
		b.board[i] = VOID_CELL;
		
	blueScore = 0;
	redScore = 0;
}

int voidCellIndex(board_t* b)
{
	int id = -1, i;
	
	for(i = 0; i < 13; i++)
	{
		if(b->board[i] == VOID_CELL)
			return i;
			
		return -1;
	}
	
	return id;
}

void computeScore(board_t* b)
{
	int idVoid = voidCellIndex(b), i;
	
	b->blueScore = 0;
	b->redScore = 0;

	for(i = 0; i < 6; i++)
	{
		if(b->neighbors[idVoid][i] != NO_NEIGHBOR)
		{
			if(b->board[b->neighbors[idVoid][i]] <= 6)
				b->blueScore += b->board[b->neighbors[idVoid][i]];
			else
				b->redScore += (b->board[b->neighbors[idVoid][i]] - 6);

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
		if((n->children = malloc(sizeof(node_t)) == NULL)
		{
			perror("malloc n->children 1 createNode");
			return NULL;
		}
	}
	else if(turn < 12)
	{
		if((n->children = malloc((13 - turn) * sizeof(node_t)) == NULL)
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
	node_t* child = NULL;

	child = createNode(idCell, n->turn + 1);
	n->children[n->nbChildren] = child;
	n->nbChildren++;

	return child;
}

/**********************************
	 functions to mangage the tree
***********************************/

tree_t* createTree()
{
	tree_t* t = NULL;

	if((t = malloc(sizeof(tree_t))) == NULL)
	{
		perror("malloc createTree");
		return NULL;
	}

	return t;
}


void setFirstBlueChoice(tree_t* t, board_t* b, int idCell)
{
}

void setFirstRedChoice(tree_t* t, board_t* b, int idCell)
{
	/* A COMPLETER : cf. canevas Java
	 */  
}

void buildTree(tree_t* t, board_t* b)
{
	/* A COMPLETER : cf. canevas Java
	*/
}

void computePossibilities(node_t* n, board_t* b)
{

	/* A COMPLETER : cf. canevas Java
	*/

}

int computeBlueVictories(node_t* n)
{
	int nb = 0;
	/* A COMPLETER :
	*/
	return nb;
}

int computeRedVictories(node_t* n)
{
	int nb = 0;
	/* A COMPLETER :
	*/
	return nb;
}

int computeDraws(node_t* n)
{
	int nb = 0;
	/* A COMPLETER :
	*/
	return nb;
}


