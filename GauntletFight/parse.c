#include "game.h"

//If you haven't knocked yourself out in boss.c, do it here.
//Otherwise, knock yourself out again. 

void ParseShieldInfo(Shield* s, FILE* fp)
{
	//malloc space for the line to be read into
	//break that line into tokens
	//fill the shield/sword info in
	char* ShieldInfo = malloc(sizeof(char)*MAXFILELINELENGTH);
	
	fgets(ShieldInfo, MAXFILELINELENGTH, fp);
	char* token = strtok(ShieldInfo, "|\n");
	int i;
	int info;
	//did a switch statement to make the code more condensed and easier to read
	for(i = 0; i < 4; i++)
	{
		switch(i)
		{
			case 0: 
				strcpy(s->name,token);
				break;
			
			case 1:
				info = atoi(token); //turn info into an int since it needs to be used for subtacting cost/defense purposes
				s->cost = info;
				break;
				
			case 2:
				info = atoi(token);
				s->defense = info;
				break;
			
			case 3: 
				strcpy(s->description,token+1); //token+1 for the description to take out the space at the beginning
				break;
		}
		
		token = strtok(NULL, "|\n");
	}
	
	free(token);
	free(ShieldInfo);
}

void ParseSwordInfo(Sword* s, FILE* fp)
{
	//same code as above only for the sword
	char* SwordInfo = malloc(sizeof(char)*MAXFILELINELENGTH);
	
	fgets(SwordInfo, MAXFILELINELENGTH, fp);
	char* token = strtok(SwordInfo, "|\n");
	
	int i;
	int info;
	for(i = 0; i < 4; i++)
	{
		switch(i)
		{
			case 0: 
				strcpy(s->name,token);
				break;
			
			case 1:
				info = atoi(token);
				s->cost = info;
				break;
				
			case 2:
				info = atoi(token);
				s->attack = info;
				break;
			
			case 3: 
				strcpy(s->description,token+1);
				break;
		}
		
		token = strtok(NULL, "|\n");
	}
	
	free(SwordInfo);
	free(token);
}
