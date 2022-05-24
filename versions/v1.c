#include <stdio.h>

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

int bot(int b[9]){
	for(int i = 0;i<9;i++){
		if(!b[i]){
			return i;
		}
	}
}

int main()
{
   	int t,ct,mv;
	int m[9] = {0};
	while(1){
        	printf("1) X\n2) O\n");
        	do{
            		scanf("%d",&ct);
        	}while(ct != 1 && ct != 2);
        	if(ct == 1){ct = -1;}
        	if(ct == 2){ct = 1;}
        	t = 1;
        	int d = 0;
        	while(!over(m) && d != 9){
            		afiseaza(m);
            		if(t == ct){
                		mv = bot(m);
            		}
            		else{
               			do{
                    			scanf("%d",&mv);
                		}while(mv < 1 || mv > 9 || m[mv-1] != 0);
                		mv--;
            		}
            		m[mv] = t;
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
