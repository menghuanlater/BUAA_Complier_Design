
const int int1 = 666,int2 = +233,int3 = -1000,int4 = 0;
const char char1 = '1',char2 = '_',char3='+',char4 = 'a';


int gInt1,gInt2[10],gInt3[10],gInt4,gInt5[10];
char gCh1,gCh2[10],gCh3[10],gCh4,gCh5[10];


void testAllDefine{
    const int int1=333,int2 = +789,int3 = -7125,int4 = -1;
    
    const char char1 = '0',char2 = '-',char3='*',char4 = 'D',char5 = 'g',
    char6 = '+',char7 = '/',char8 = '9',char9 = 'Z',char10 = 'y';
    
    int gInt1,gInt2[10],gInt3[10],gInt4,gInt5[10];
    
    char gCh1,gCh2[10],gCh3[10],gCh4,gCh5[10];

    int i;

    gInt1 = 10*1;
    gInt4 = 10*4;
    gCh1 = '0';
    gCh4 = '9';

    i = (0+0*0-0-(0-'a'+'b'-1)*34445);
    while(i<(333-222-111+19-9+gCh4-'8'-1)){
        gInt2[i] = 2*10+i;
        gInt3[i] = 3*10+i;
        gInt5[i] = 5*10+i;
        gCh2[i] = 'a';
        gCh3[i] = 'b';
        gCh5[i] = 'c';
        i = i + '8' - '7';
    }


    printf("int1:",int1);
    printf("int2:",int2);
    printf("int3:",int3);
    printf("int4:",int4);

    printf("char1:",char1);
    printf("char2:",char2);
    printf("char3:",char3);
    printf("char4:",char4);

    printf("gInt1:",gInt1);
    printf("gInt4:",gInt4);

    printf("gCh1:",gCh1);
    printf("gCh4:",gCh4);

    i = 0;
    printf("gIn2[]:");
    while(i<10){
        i = i + 1;
        printf(gInt2[i-1]);
    }
    i = 0;
    printf("gInt3[]:");
    while(i<10){
        i = i + 1;
        printf(gInt3[i-1]);
    }
    i = 0;
    printf("gInt5[]:");
    while(i<10){
        i = i + 1;
        printf(gInt5[i-1]);
    }

    printf("gCh2[3]:",gCh2[3]);
    printf("gCh2[6]:",gCh2[6]);

    printf("gCh3[3]:",gCh3[3]);
    printf("gCh3[6]:",gCh3[6]);

    printf("gCh5[3]:",gCh5[3]);
    printf("gCh5[6]:",gCh5[6]);

}

void giveValueToGlobalVar{
    int i;

    gInt1 = 100*1;
    gInt4 = 100*4;
    gCh1 = 'D';
    gCh4 = 'F';

    i = 0;
    while(i<10){
        gInt2[i] = 2*100+i;
        gInt3[i] = 3*100+i;
        gInt5[i] = 5*100+i;
        gCh2[i] = 'i';
        gCh3[i] = 'j';
        gCh5[i] = 'k';
        i = i + 'B' - 'A';
    }
}


int calculateFactorial(int item){
    if(item < 0 ){
        printf("The factorial number must >= 0 .");
        return (0);
    }else{
        if(item == 0)
            return (1);
        else
            return (calculateFactorial(item-1)*item);
    }
}

int Fibonaci(int n){
    if(n<=2){
        if((n+1)<=1){
            printf("The Fibonaci number must >=1.");
            return (0);
        }else{
            ;
        }
        return (1);
    }
    else
        return (Fibonaci(n-1)+Fibonaci(n-2));
}

void main(){

    const int _testNumberMax = 10;

    int giveValueToGlobalVar;
    int testAllDefine[10];
    char calculateFactorial;
    char Fibnaci[10];

    giveValueToGlobalVar;
    testAllDefine;

    giveValueToGlobalVar = Fibonaci(8);
    testAllDefine[1] = calculateFactorial(10);

    printf("xxx:",giveValueToGlobalVar);
    printf("yyy:",testAllDefine[1]);
    printf("Over,Ok!");
    return;
}