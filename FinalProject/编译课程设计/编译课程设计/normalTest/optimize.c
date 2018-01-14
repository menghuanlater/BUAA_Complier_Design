const int MAX_NUM = 1024 ;

void complete_num{
    int k[1024];
    int i,j,n,s,x1;
    int m,k2,h,leap,x2;
    
    j=2;
    while(j< MAX_NUM){
        n = -1;
        s = j;

        i=1;
        while(i<j){
            x1 = (j/i) * i ;
            if( x1 == j ){
                n = n + 1;
                s = s - i;

	            if (n >= 1024)
                    printf("OVERFLOW! ");
                else
                    k[n] = i;
            }else{
                ;
            }
            i = i + 1;
        }

        if(s==0){
            printf("complete number: ",j);
            i = 0;
            while(i<=n){
                printf("  ",k[i]);
                i = i + 1;
            }
            printf("  ") ;
        }else{
            ;
        }
        j = j + 1;
    }
    printf("---------------------------------------------------------------");
    
    h = 0 ;
    leap = 1 ;

    m = 2;
    while(m <= MAX_NUM){
        k2 = m - 1;
        i = 2;
        while(i<=k2){
            x2 = (m/i)*i ;
            if( x2 == m){
                leap=0;
            }else{
                ;
            }
            i = i + 1;
        }
        if(leap == 1){
            printf(" ",m);
            h = h + 1;
            x2 = (h/10)*10 ;
            if( x2 == h)
                printf("  ");
            else
                ;
        }else{
            ;
        }
        leap=1;
        m = m + 1;
    }

    printf("The total is ",h);
}



void main(){
    complete_num;
}