#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int scores[9];
	struct node *next[9];
}*TREE;

int over(int b[9]){
	int v[8] = {0};
    	for(int i = 0 ; i <= 8 ;i++){
        	int x = b[i];
        	v[i%3] += x;
        	v[(i / 3) + 3] += x;
        	if(i == 0 || i == 4 || i == 8){
            		v[6] += x;
        	}
        	if(i == 2 || i == 4 || i == 6){
            		v[7] += x;
        	}
    	}
    	for(int i = 0;i<=7;i++){
        	if(v[i] == 3 || v[i] == -3){
            		return 1;
        	}
    	}
    	return 0;
}

void afiseaza(int b[9]){
	char cc[3] = {'O','.','X'};
    	for(int i =0;i<=8;i++){
        	printf("%c ",cc[b[i] + 1]);
        	if(i%3 == 2){
            		printf("\n");
        	}
    	}
    	printf("\n\n");
}

int score(int b[9],int t,TREE tr,int d){
	if(over(b)){
		return -1;
	}
	if(d == 9){
		return 0;
	}
	int sc,scmax = -9;
	for(int i = 0;i<9;i++){
		if(b[i] != 0) continue;
		b[i] = t;
		tr->next[i] = malloc(sizeof(struct node));
		int sc = -score(b,0-t,tr->next[i],d+1);
		b[i] = 0;
		tr->scores[i] = sc;
		if(sc > scmax){
			scmax = sc;
		}
	}
	return scmax;
}

int bot(int b[9],TREE tr){
	int bi,bv=-3;
	for(int i = 0;i<9;i++){
		if(b[i] == 0 && tr->scores[i] > bv){
			bv = tr->scores[i];
			bi = i;
		}
	}
	return bi;
}

int main()
{
   	int t,ct,mv;
	int m[9] = {0};
	TREE tr=malloc(sizeof(struct node));
	score(m,1,tr,0);
	return 0;
	while(1){
        	printf("1) X\n2) O\n");
        	do{
            		scanf("%d",&ct);
        	}while(ct != 1 && ct != 2);
        	if(ct == 1){ct = -1;}
        	if(ct == 2){ct = 1;}
        	t = 1;
        	int d = 0;
		TREE auxtree = tr;
        	while(!over(m) && d != 9){
            		afiseaza(m);
            		if(t == ct){
                		mv = bot(m,auxtree);
            		}
            		else{
               			do{
                    			scanf("%d",&mv);
                		}while(mv < 1 || mv > 9 || m[mv-1] != 0);
                		mv--;
            		}
            		m[mv] = t;
			auxtree = auxtree->next[mv];
            		t = 0-t;
            		d++;
        	}
        	afiseaza(m);
        	for(int i =0;i<=8;i++){
            		m[i] = 0;
        	}
    	}
   	return 0;
}
