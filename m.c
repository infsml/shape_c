#include <stdio.h>
#include <stdlib.h>

float signF(float t){
    if(t==0)return 0;
    else if(t>0)return 1;
    else return -1;
}

float fFunc(float t, float *xyc, int k){
    int i;
    int n=xyc[0];
    int ncr[n];// = (int*)malloc(sizeof(int)*n);
    float tarr[n];// = (int*)malloc(sizeof(int)*n);
    float t_1arr[n];// = (int*)malloc(sizeof(int)*n);
    ncr[0]=1;
    tarr[0]=1;
    t_1arr[n-1]=1;
    for(i=1;i<n;i++){
        ncr[i]=(ncr[i-1]*(n-i))/i;
        tarr[i]=tarr[i-1]*t;
        t_1arr[n-i-1]=t_1arr[n-i]*(1-t);
    }
    float upperterm = 0;
    for(i=0;i<n;i++){
        upperterm += ncr[i]*tarr[i]*t_1arr[i]*xyc[i+k];
    }
    return upperterm;
}

float diffFunc(float t, float *xyc, float d,int k){
    int i;
    int n=xyc[0];
    int ncr[n];// = (int*)malloc(sizeof(int)*n);
    float tarr[n];// = (int*)malloc(sizeof(int)*n);
    float t_1arr[n];// = (int*)malloc(sizeof(int)*n);
    ncr[0]=1;
    tarr[0]=1;
    t_1arr[n-1]=1;
    for(i=1;i<n;i++){
        ncr[i]=(ncr[i-1]*(n-i))/i;
        tarr[i]=tarr[i-1]*t;
        t_1arr[n-i-1]=t_1arr[n-i]*(1-t);
    }
    float upperterm = 0;
    for(i=0;i<n;i++){
        upperterm += ncr[i]*tarr[i]*t_1arr[i]*xyc[i+k];
    }
    int n2=n-1;
    int ncr2[n2];
    ncr2[0]=1;
    for(i=1;i<n2;i++)
        ncr2[i]=(ncr2[i-1]*(n2-i))/i;
    float lowerterm = 0;
    for(i=0;i<n2;i++){
        lowerterm += ncr2[i]*tarr[i]*t_1arr[i+1]*(xyc[i+k+1]-xyc[i+k]);
    }
    if(lowerterm == 0)return 0;
    float tnew = (upperterm-d)/((n-1)*lowerterm);
    return tnew;
}

int *Bezier(int w,int h,float *xyc){
    /*int *c;
    int (*k)[w];
    int (*canvas)[w] = (int (*)[w])malloc(sizeof(int)*h*w);
    c = (int *)canvas;
    c[7] = 1;
    printf("canvas[0][0]%d\n",canvas[0][0]);
    k = (int (*)[w])c;
    k[1][0] = -1;
    printf("canvas[0][0]%d\n",canvas[1][0]);*/
    int i,j;
    int n=xyc[0];
    int *ncr = (int*)malloc(sizeof(int)*n);
    ncr[0]=1;
    for(i=1;i<n;i++)
        ncr[i]=(ncr[i-1]*(n-i))/i;
    float x0 = xyc[1];
    float y0 = xyc[n+1];
    int walls[4];
    walls[0] = x0;
    walls[1] = walls[0]+1;
    walls[2] = y0;
    walls[3] = walls[2]+1;
    float wallsT[4];
    for(i=0;i<4;i++){
        wallsT[i]=0;
        for(j=0;j<10;j++){
            wallsT[i] -= diffFunc(wallsT[i],xyc,walls[i],(i/2)*n+1);
        }
    }
    float cwall = 1;
    int cin = -1;
    for(i=0;i<4;i++){
        if(wallsT[i]>=0&&wallsT[i]<cwall){
            cwall=wallsT[i];
            cin = i;
        }
    }
    printf("%f\n",cwall);
    printf("%d\n",cin);
    float cy = walls[cin];
    float cx = fFunc(cwall,xyc,1);
    printf("%f\n",cx);
    int walls2[3];
    walls2[0]=cx;
    walls2[1]=walls2[0]+1;
    walls2[2]=cy+signF(cy-y0);
    float wallsT2[3];
    for(i=0;i<3;i++){
        wallsT2[i]=cwall;
        for(j=0;j<10;j++){
            wallsT2[i] -= diffFunc(wallsT2[i],xyc,walls2[i],(i/2)*n+1);
        }
    }
    cwall = 1;
    cin = -1;
    for(i=0;i<4;i++){
        if(wallsT2[i]>=0&&wallsT2[i]<cwall){
            cwall=wallsT2[i];
            cin = i;
        }
    }
    printf("%f\n",cwall);
    printf("%d\n",cin);
    return NULL;
}

void main(){
    int w=7,h=5,i,j;
    int *k;
    float xyc[]={6,6.46,5.46,5.34,3.97,2.93,2.45,3.46,0.57,0.89,5.09,5.02,2.57};
    int n = xyc[0];
    float *xycp;
    xycp = (float *)malloc(sizeof(float)*(xyc[0]*2)+1);
    for(i=0;i<=2*xyc[0];i++)
        xycp[i]=xyc[i];
    Bezier(w,h,xycp);
    //for(i=0;i<n;i++)printf("%d ",k[i]);
    /*for(i=0;i<h;i++){
        for(j=0;j<w;j++){
            //canvas[w][h]=1;
            printf("%p ",&(canvas[i][j]));
        }
        printf("\n");
    }
    printf("%p \n",&(canvas[0][0]));*/
}
