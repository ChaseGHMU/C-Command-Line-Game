#include "game.h"

//Knock yourself out boys and girls.

Boss* loadBoss()
{
	/*Create Boss Pointer
	  fill his name, health, defense, attack, and speed
	  make max health = 7500
	  create the first BST node and the action list outside of while loop
	  make a while loop that goes til end of file and fill the rest of the nodes and pointers
	  */
	  
	FILE* fp = fopen("Boss.txt","r"); //open file
	if(!fp)
	{
		printf("ERROR OPENING FILE.\n\n\n");
		return NULL;
	}
	
	Boss* villian = malloc(sizeof(Boss)); 
	int numNodes;
	int i;
	
	//read in all the info for boss
	fscanf(fp,"%s | %d | %d | %d | %d", villian->name, &villian->health, &villian->baseDefense, &villian->baseAttack, &villian->baseSpeed);
	villian->maxHealth = villian->health;
	
	//fill the node and an int to hold the number of nodes
	villian->root = malloc(sizeof(DecisionTreeNode));
	fscanf(fp,"%d | %d | %d", &villian->root->healthFloor, &villian->root->healthCeiling, &numNodes); 
	
	//make pointers at the bottom of the BST null just in case
	villian->root->left = NULL;
	villian->root->right = NULL;
	
	villian->root->FirstAction = malloc(sizeof(ActionNode));
	fscanf(fp,"%u", &villian->root->FirstAction->decision); //fill the first action inside the tree with first decision
	villian->root->FirstAction->next = NULL;

	
	//go to the end of the list
	//going to numNodes-1 here since first action was already filled into first action
	for(i = 0; i < numNodes-1; i++)
	{
		ActionNode* new = malloc(sizeof(ActionNode));
		fscanf(fp,"%u", &new->decision);
		new->next = NULL;
		villian->root->FirstAction = addActionToList(villian->root->FirstAction,new);
	}

	while(!feof(fp)) //continue what happened above for the rest of the file
	{

		DecisionTreeNode* branch = malloc(sizeof(DecisionTreeNode));
		fscanf(fp,"%d | %d | %d", &branch->healthFloor, &branch->healthCeiling, &numNodes);
		
		branch->FirstAction = malloc(sizeof(ActionNode));
		fscanf(fp,"%u",&branch->FirstAction->decision);
		branch->FirstAction->next = NULL;
		
		for(i = 0; i < numNodes-1; i++)
		{
			ActionNode* new = malloc(sizeof(ActionNode));
			fscanf(fp,"%u",&new->decision);
			new->next = NULL;
			branch->FirstAction = addActionToList(branch->FirstAction,new);
		}
		
		branch->left = NULL;
		branch->right = NULL;
		
		villian->root = addNodeToTree(villian->root,branch);
	}
	//return the boss, his tree, and his action list
	return villian;
}

ActionNode* addActionToList(ActionNode* front, ActionNode* newAction)
{
	//take in front of the list and newAction
	//continue to the end of the front of the list
	//fill the newAction at the end of the list
	//return the front of the list
	
	ActionNode* current;
	current = front;
		
	if(front==NULL)
	{	
		front = newAction;
		return front;
	}
	
	while(current->next != NULL)
	{
		current = current->next;
	}
	
	current->next = newAction;

	return front;
}

DecisionTreeNode* addNodeToTree(DecisionTreeNode* root, DecisionTreeNode* newNode)
{	
	//traverse tree to find the right spot to put node using recursion
	//if the health is higher than that nodes ceiling
	//look to the right side of the tree
	//if not, look to the left side
	//when you get to a the end of the BST add the new node there
	if(root == NULL)
	{
		return newNode;
	}
	if(newNode->healthCeiling > root->healthCeiling)
	{
		root->right = addNodeToTree(root->right,newNode);
	}
	else
	{
		root->left = addNodeToTree(root->left, newNode);
	}
	
	return root;
}

ActionNode* fetchNewList(Boss* boss, DecisionTreeNode* root)
{	
	//start at beginning of the tree
	//if i find the right node return the list
	//if not keep traversing the list
	//if for some reason can't find anything return NULL
	while(root!=NULL)
	{
		if(boss->health <= root->healthCeiling && boss->health >= root->healthFloor)
			return root->FirstAction;

		else if(boss->health < root->healthFloor)
		{
			root = root->left;
		}
		else 
			root = root->right;
	}
	
	return NULL;
}

void freeBossTree(DecisionTreeNode* root)
{
	//traverse all the way through the tree
	//free that list in postorder fashion
	//then free that root
	
	if(root == NULL)
		return;
	
	freeBossTree(root->left);
	freeActionListInNode(root->FirstAction);
	freeBossTree(root->right);
	
	free(root);
}

void freeActionListInNode(ActionNode* head)
{
	//if there's nothing more to free then end
	if(head == NULL)
		return;
	
	ActionNode* previous;
	previous = head;
	//go through list and free the nodes until there's nothing left to free
	while(head != NULL)
	{ 
		head = head->next;
		free(previous);
		previous = head;	
	}
	
}
