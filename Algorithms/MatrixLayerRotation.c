typedef struct layer{
    int size;
    int *s;
    int *s2;
}layer;

void matrixRotation(int mr, int mc, int** mtx, int r) {
    int nL=(int)fmin(mr,mc)/2;
    //Strip the matrix into linear layers to perform modulo calculations
    layer *layers=malloc(nL*sizeof(layer));
    for(int z=0;z<nL;z++){
        layers[z].size=(mr+mc)*2-8*z-4;
        layers[z].s=malloc(layers[z].size*sizeof(int));
        layers[z].s2=malloc(layers[z].size*sizeof(int));
        int cont=0;
        //Imagine the layer wrapped around the rectangular matrix, have to copy each side
        //Copy top side
        for(int j=z;j<mc-z;j++){
            layers[z].s[cont]=mtx[z][j];
            cont++;
        }
        //Copy right side
        for(int i=z+1;i<mr-z;i++){
            layers[z].s[cont]=mtx[i][mc-z-1];
            cont++;
        }
        //Copy bottom side
        for(int j=mc-2-z;j>=z;j--){
            layers[z].s[cont]=mtx[mr-z-1][j];
            cont++;
        }
        //Copy left side 
        for(int i=mr-2-z;i>z;i--){
            layers[z].s[cont]=mtx[i][z];
            cont++;
        }
        //Perform the rotation on the layer
        //Every element swaps with the next rotation modulo
        int buffer=layers[z].s[0];
        int idx=r%layers[z].size;
        int llen=layers[z].size;
        for(int i=0;i<idx;i++){
            layers[z].s2[llen-idx+i]=layers[z].s[i];
        }
        for(int i=idx;i<llen;i++){
            layers[z].s2[i-idx]=layers[z].s[i];
        }
        cont=0;
        
        //Copy back to matrix
        //Copy top side
        for(int j=z;j<mc-z;j++){
            mtx[z][j]=layers[z].s2[cont];
            cont++;
        }
        //Copy right side
        for(int i=z+1;i<mr-z;i++){
            mtx[i][mc-z-1]=layers[z].s2[cont];
            cont++;
        }
        //Copy bottom side
        for(int j=mc-2-z;j>=z;j--){
            mtx[mr-z-1][j]=layers[z].s2[cont];
            cont++;
        }
        //Copy left side minus last element, it is the first one of top side
        for(int i=mr-2-z;i>z;i--){
            mtx[i][z]=layers[z].s2[cont];
            cont++;
        }
    }
    //Print the matrix
    for(int i=0;i<mr;i++){
        for(int j=0;j<mc;j++){
            printf("%d ",mtx[i][j]);
        }
        printf("\n");
    }
}
