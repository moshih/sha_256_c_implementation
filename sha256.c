//#include <stdio.h>

unsigned  int H_0=0x6a09e667;
unsigned  int H_1=0xbb67ae85;
unsigned  int H_2=0x3c6ef372;
unsigned  int H_3=0xa54ff53a;
unsigned  int H_4=0x510e527f;
unsigned  int H_5=0x9b05688c;
unsigned  int H_6=0x1f83d9ab;
unsigned  int H_7=0x5be0cd19;

unsigned  int K[64]={0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

unsigned int rotl (unsigned int input,unsigned int amount){
    return ((input<<amount)|(input>>(32-amount)));
}

unsigned int rotr (unsigned int input,unsigned int amount){
    return ((input>>amount)|(input<<(32-amount)));
}

unsigned int ch(unsigned int x, unsigned int  y, unsigned int  z){
    return (x & y) ^ ((~ x) & (z));
}

unsigned int maj(unsigned int x, unsigned int  y, unsigned int  z){
    return (x & y) ^ (x & z) ^ (y & z) ;
}


unsigned int sum_zero(unsigned int x){
    return rotr(x,2) ^rotr(x,13) ^rotr(x,22) ;
    //return (x>>2)^(x>>13)^(x>>22);
}


unsigned int sum_one(unsigned int x){
    return rotr(x,6) ^rotr(x,11) ^rotr(x,25) ;
    //return (x>>6)^(x>>11)^(x>>25);
}

unsigned int sigma_zero(unsigned int x){
    return rotr(x,7) ^rotr(x,18) ^(x>>3) ;
    //return (x>>7)^(x>>18)^rotr(x,3);
}


unsigned int sigma_one(unsigned int x){
    return (rotr(x,17) ^rotr(x,19) ^(x>>10)) ;
    //return (x>>17)^(x>>19)^rotr(x,10);
}

int main()
{
    //00000000
    //unsigned int M[16]={2147483648,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    unsigned int M[16]={0b01100001100000000000000000000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8};
    //unsigned int M[16]={3271557120,2147483648,0,0,0,0,0,0,0,0,0,0,0,0,0,32};
    //{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,0xe9b5dba5};
    unsigned int W[64];

    int i;

    for (i=0; i<16; i++){
        W[i]=M[i];
    }
    for (i=16;i<64;  i++){
        W[i]=sigma_one(W[i-2])+W[i-7]+sigma_zero(W[i-15])+W[i-16];
    }
    
    unsigned int a=H_0;
    unsigned int b=H_1;
    unsigned int c=H_2;
    unsigned int d=H_3;
    unsigned int e=H_4;
    unsigned int f=H_5;
    unsigned int g=H_6;
    unsigned int h=H_7;
    
    for (i=0;i<64;  i++){
        unsigned int T1=h+sum_one(e)+ch(e,f,g)+K[i]+W[i];
        unsigned int T2=sum_zero(a)+maj(a,b,c);
        h=g;
        g=f;
        f=e;
        e=d+T1;
        d=c;
        c=b;
        b=a;
        a=T1+T2;
    }
    
    unsigned int H_01=H_0+a;
    unsigned int H_11=H_1+b;
    unsigned int H_21=H_2+c;
    unsigned int H_31=H_3+d;
    unsigned int H_41=H_4+e;
    unsigned int H_51=H_5+f;
    unsigned int H_61=H_6+g;
    unsigned int H_71=H_7+h;
/* 
    printf("%x\n",H_01);
    printf("%x\n",H_11);
    printf("%x\n",H_21);
    printf("%x\n",H_31);
    printf("%x\n",H_41);
    printf("%x\n",H_51);
    printf("%x\n",H_61);
    printf("%x\n",H_71);
    
    printf("The following is correct %u\n",rotr(5,1));
    unsigned int message[8];
    message[0]=0xca978112;
    message[1]=0xca1bbdca;
    message[2]=0xfac231b3;
    message[3]=0x9a23dc4d;
    message[4]=0xa786eff8;
    message[5]=0x147c4e72;
    message[6]=0xb9807785;
    message[7]=0xafee48bb;
    for (i=0;i<8;  i++){
        printf("%x\n",message[i]);
    }
*/
    

}


