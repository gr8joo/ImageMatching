#include "PatternMatcher.h"

void main()
{
	FILE *in = fopen("input.txt", "rt"), *out = fopen("result.txt", "wt");
	double ***FullText, ***FullPattern;
	int **Text, **Pattern;
	int *x, *temp;
	
	int Plane;	
	int Tn, Tm;
	int Pn, Pm;

	item *root;
	item **dla;
	int l, i, j, end;

	int *check;
	int *valid;
	int *saver;
	int *min;

	int cnt;
	//int neg=0;

	fscanf(in, "%d ", &Plane);
	fscanf(in, "%d %d ", &Tn, &Tm);
	fscanf(in, "%d %d ", &Pn, &Pm);

	FullText = (double ***)calloc( Plane, sizeof(double**) );
	for(l=0; l < Plane; l++)
	{
		FullText[l] = (double**)calloc( Tn, sizeof(double*) );
		for(i=0; i < Tn; i++)
		{
			FullText[l][i] = (double*)calloc( Tm, sizeof(double) );
			for(j=0; j < Tm; j++)
				fscanf(in, "%lf ", &FullText[l][i][j]);
		}
	}

	FullPattern = (double ***)calloc( Plane, sizeof(double**) );
	for(l=0; l < Plane; l++)
	{
		FullPattern[l] = (double**)calloc( Pn, sizeof(double*) );
		for(i=0; i < Pn; i++)
		{
			FullPattern[l][i] = (double*)calloc( Pm, sizeof(double) );
			for(j=0; j < Pm; j++)
				fscanf(in, "%lf ", &FullPattern[l][i][j]);
		}
	}


//Setting check(# of rows at each position in Text), valid(# of valid hit at each position in Text), saver(position saver), min(optimized accumulation info)
	check = (int *)calloc( (Tn + 2*Pn) * (Tm + 2*Pm) +1, sizeof(int));
	valid = (int *)calloc( (Tn + 2*Pn) * (Tm + 2*Pm) +1, sizeof(int));
	saver = (int *)calloc( (Tn + 2*Pn) * (Tm + 2*Pm) +1, sizeof(int));
	
	min = (int *)calloc( 8, sizeof(int));
	min[0] = (Tn + 2*Pn) * (Tm + 2*Pm) +1;

	end = (Tn + 2*Pn) * (Tm + 2*Pm) + 1; 

	for(l = 0; l < Plane; l++)
	{
		cnt = 0;
//setting 2-dim Text and 1-dim x
		Text = (int **)calloc( Tn + 2*Pn, sizeof(int*));
		x = (int *)calloc( (Tn + 2*Pn) * (Tm + 2*Pm) +2, sizeof(int));

		for(i=0; i < Pn; i++)
		{
			Text[i] = (int *)calloc(Tm + 2*Pm +1, sizeof(int));
			for(j=0; j < Tm + 2*Pm; j++)
				x[cnt++] = Text[i][j] = questionMark;
		}

		for(i=Pn; i < Tn + Pn;i++)
		{
			Text[i] = (int *)calloc(Tm + 2*Pm +1, sizeof(int));
			for(j=0; j < Pm; j++)
				x[cnt++] = Text[i][j] = questionMark;
		
			for(j=Pm; j < Tm + Pm; j++)
				x[cnt++] = Text[i][j] = 100*FullText[l][i-Pn][j-Pm];
			
			for(j=Tm + Pm; j < Tm + 2*Pm; j++)
				x[cnt++] = Text[i][j] = questionMark;
		}

		for(i=Tn+Pn; i < Tn+2*Pn; i++)
		{
			Text[i] = (int *)calloc(Tm + 2*Pm +1, sizeof(int));
			for(j=0; j < Tm + 2*Pm; j++)
				x[cnt++] = Text[i][j] = questionMark;
		}
		/*
		printf("Expanded Text:\n");
		for(i=0; i < Tn + 2*Pn; i++)
		{
			for(j=0; j < Tm + 2*Pm; j++)
				printf("%4d", Text[i][j]);
			printf("\n");
		}
		*/

//Setting 2-dim Pattern	
		Pattern = (int **)calloc(Pn, sizeof(int*));
		for(i=0; i < Pn;i++)
		{
			Pattern[i] = (int *)calloc(Pm+1, sizeof(int));
			for(j=0; j < Pm; j++)		
				Pattern[i][j] = 100*FullPattern[l][i][j];
			Pattern[i][Pm] = -1;
		}
		
		/*
		printf("\nOriginal Pattern:\n");
			for(i=0; i < Pn; i++)
			{
				for(j=0; j < Pm; j++)
					printf("%d\t", Pattern[i][j]);
				printf("\n");
			}
		}
		*/

		x[end-1] = endMark;

		//Direct Leaf Access Setting
		dla = (item **)calloc(end, sizeof(item*));
		
		root = PositionTree(dla, x, end);
		for(i=0;i<Pn;i++)
			PatternMatcher(x, Pattern[i], root, 0, check, valid, saver, min, i, Plane, Tn+2*Pn, Tm+2*Pm, Pn, Pm, 0);	//Compare pattern with text

	}


	//Tn += 2*Pn;
	//Tm += 2*Pm;
	
	
//	printf("min[0] = %d\n", min[0]);

// Pixel Setting and
	
	
	
	


/*Saver saves all possilbe occurence of pattern in text but what we need is only the best option in terms of size. So, do not need to sort them			
	for(i=1;i<=saver[0];i++)
		for(j=i+1;j<=saver[0];j++)
			if(saver[i]>saver[j])
			{		
				end=saver[i];
				saver[i] = saver[j];
				saver[j] = end;
			}



	for(i=1;i<=saver[0];i++)
//		printf("%d\n", saver[i]);
		printf("%d %d\n", (saver[i]-1)/Tm+1, (saver[i]-1)%Tm+1);
*/

	
	printf("Valid hit: %d\n", min[7]);
	printf("Size: %d\n", min[0]);
	printf("Begining of row: %d\n", min[1]);
	printf("End of row: %d\n", min[2]);
	printf("Begining of column: %d\n", min[3]);
	printf("End of column: %d\n", min[4]);
	printf("Px: %d\n", min[5]);
	printf("Py: %d\n", min[6]);


	//printf("\nAccumulated Text: (following position numbers are in terms of expanded Text!)\n");
		
	for(i=0;i<Pn;i++)
		for(j=0;j<Pm;j++)
			if(Pattern[i][j] != questionMark)
				Text[i+min[5]-1][j+min[6]-1] = Pattern[i][j];
		
	for(i=min[1]-1;i<min[2];i++)
	{
		for(j=min[3]-1;j<min[4];j++)
		{
			if(Text[i][j] == questionMark)
				fprintf(out, "%d\t", 1);
			else
				fprintf(out, "%d\t", Text[i][j]);
		}
		fprintf(out, "\n");
	}




/*
	for(i=1;i<=(Tn + 2*Pn) * (Tm + 2*Pm);i++)
		if(valid[i] != 0)
			printf("%d %d\n", i, valid[i]);
	printf("\n");
*/

//	Memory Fresher
	//Text = (char **)calloc(Tn, sizeof(char*));
	//x = (char *)calloc(Tn*Tm+2, sizeof(char));
	//check = (int *)calloc(Tn*Tm+1, sizeof(int));
	for(i=0;i<Tn;i++)
		free(Text[i]);// = (char *)calloc(Tm, sizeof(char));
	free(Text);

	for(i=0;i<Pn;i++)
		free(Pattern[i]);// = (char *)calloc(Pm, sizeof(char));
	free(Pattern);
/*
	for(i=1;i<=Tn*Tm+1;i++)
	{
		printf("dla[%d] = ", i);
		recur(dla[i]);
		printf("\n");
	}

	for(i=0;i<Tn*Tm+1;i++)
		printf("%4d", x[i]);
	printf("\n");
*/
}







