#include "2p11.h"
#include <time.h>

short *m_init()
{
    int cont = 1;
    short *mat = (short*)calloc(16, sizeof(short));

    turn(mat);
    turn(mat);
    return mat;
}
void move(short *mat, char move)
{
    if(move == 'L') {
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                if(j > 0 && *(mat + (i * 4) + j) != 0) {
                    for(int k = j; k > 0; k--) {
                        if(*(mat + (i * 4) + k - 1) == *(mat + (i * 4) + k)) {
                            *(mat + (i * 4) + k - 1) += *(mat + (i * 4) + k);
                            *(mat + (i * 4) + k) = 0;
                        } else if(*(mat + (i * 4) + k - 1) == 0) {
                            *(mat + (i * 4) + k - 1) = *(mat + (i * 4) + k); 
                            *(mat + (i * 4) + k) = 0;
                        }
                    }
                }
            }
        }
    } else if(move == 'R') {
        for(int i = 0; i < 4; i++) {
            for(int j = 3; j >= 0; j--) {
                if(j < 4 && *(mat + (i * 4) + j) != 0) {
                    for(int k = j; k < 3; k++) {
                        if(*(mat + (i * 4) + k + 1) == *(mat + (i * 4) + k)) {
                            *(mat + (i * 4) + k + 1) += *(mat + (i * 4) + k);
                            *(mat + (i * 4) + k) = 0;
                        } else if(*(mat + (i * 4) + k + 1) == 0) {
                            *(mat + (i * 4) + k + 1) = *(mat + (i * 4) + k);
                            *(mat + (i * 4) + k) = 0;
                        }
                    }
                }
            }
        }
    } else if(move == 'U') {
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                if(i > 0 && *(mat + (i * 4) + j) != 0) {
                    for(int k = i; k > 0; k--) {
                        if(*(mat + ((k - 1) * 4) + j) == *(mat + (k * 4) + j)) {
                            *(mat + ((k - 1) * 4) + j) += *(mat + (k * 4) + j);
                            *(mat + (k * 4) + j) = 0;
                        } else if(*(mat + ((k - 1) * 4) + j) == 0) {
                            *(mat + ((k - 1) * 4) + j) = *(mat + (k * 4) + j); 
                            *(mat + (k * 4) + j) = 0;
                        }

                    }
                }
            }
        }
    } else if(move == 'D') {
        for(int i = 3; i >= 0; i--) {
            for(int j = 0; j < 4; j++) {
                if(i < 4 && *(mat + (i * 4) + j) != 0) {
                    for(int k = i; k < 3; k++) {
                        if(*(mat + ((k + 1) * 4) + j) == *(mat + (k * 4) + j)) {
                            *(mat + ((k + 1) * 4) + j) += *(mat + (k * 4) + j);
                            *(mat + (k * 4) + j) = 0;
                        } else if(*(mat + ((k + 1) * 4) + j) == 0) {
                            *(mat + ((k + 1) * 4) + j) = *(mat + (k * 4) + j); 
                            *(mat + (k * 4) + j) = 0;
                        }

                    }
                }
            }
        }

    }
    turn(mat);
}
void turn(short *mat)
{
    srand(time(NULL));
    unsigned short x, y;
    unsigned short result[4] = {2, 2, 2, 4};
    while(1) {
        x = rand() % 4;
        y = rand() % 4;
        if( *(mat + (x*4) + y) == 0)
            break;
    }
    *(mat + (x*4) + y) = result[x];
}