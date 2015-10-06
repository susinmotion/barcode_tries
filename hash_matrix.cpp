int ** initializeHashMtx(){
    int ** ppHashMatrixPointer = new int*[400];
    short int count;
    for (int row = 0; row < 400; row++){
        ppHashMatrixPointer[row]=new int[5];
        for (int col = 0; col < 5; col++){
            *(* (ppHashMatrixPointer+row)+col) = count;
            count++;
        }
    }
    return ppHashMatrixPointer;
}

