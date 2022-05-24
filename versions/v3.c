#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int scores[9];
	int eval;
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

void update_position(TREE *aux, int m[9],int d){
	for(int i = 0;i<d;i++){
		for(int ii = 0;ii<9;ii++){
			if(i%2==0 && m[ii] == 1){
				m[ii] = 7;
				*aux = (*aux)->next[ii];
				break;
			}
			if(i%2==1 && m[ii] == -1){
				m[ii] = -7;
				*aux = (*aux)->next[ii];
				break;
			}
		}
	}
	for(int i = 0;i<9;i++){
		if(m[i] == 7) m[i] = 1;
		if(m[i] == -7) m[i] = -1;
	}
}

int score(int b[9],int t,TREE tr,int d,TREE initree,int calculated){
	if(over(b)){
		tr->eval = -1;
		return -1;
	}
	if(calculated){
		for(int i = 0;i<9;i++) tr->next[i] = initree->next[i];
		update_position(&tr,b,d);
		return tr->eval;
	}
	if(d == 9){
		tr->eval = 0;
		return 0;
	}
	int sc,scmax = -9;
	int calc = d > 1;
	int last=0;
	for(int i = 0;i<9;i++){
		if(b[i] == t) last = i;
	}
	for(int i = 0;i<9;i++){
		if(i == last) calc = 0;
		if(b[i] != 0) continue;
		tr->next[i] = malloc(sizeof(struct node));
		b[i] = t;
		int sc = 0-score(b,0-t,tr->next[i],d+1,initree,calc);
		b[i] = 0;
		tr->scores[i] = sc;
		if(sc > scmax){
			scmax = sc;
		}
	}
	tr->eval = scmax;
	return scmax;
}

int bot(int b[9],TREE tr){
	int bi,bv=-900;
	for(int i = 0;i < 9;i++){
		if(b[i] == 0 && tr->scores[i] > bv){
			bv = tr->scores[i];
			bi = i;
			if(bv == 1) break;
		}
	}
	return bi;
}



int main()
{
   	int t,ct,mv;
	int m[9] = {0};
	TREE tr=malloc(sizeof(struct node));
	score(m,1,tr,0,tr,0);
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
			d+=1;
			//auxtree = auxtree->next[mv];
			auxtree = tr;
			update_position(&auxtree,m,d);
            		t = 0-t;
        	}
        	afiseaza(m);
        	for(int i =0;i<=8;i++){
            		m[i] = 0;
        	}
    	}
   	return 0;
}
