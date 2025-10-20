#ifndef CUSTOMMATRIX_H
#define CUSTOMMATRIX_H

#include <iostream>

using namespace std;

class CustomMatrix
{
public:
    bool mat[3][3] = {0};
    CustomMatrix() {}

    //alternate way to instantiate the class
    CustomMatrix(bool m[3][3])
    {
        const int m_size = sizeof(m) / sizeof(m[0]);
        for (int i = 0; i < m_size; i++) {
            for (int j = 0; j < sizeof(m[0]); j++) {
                //cout << i << " " << j << endl;
                mat[i][j] = m[i][j];
            }
        }
    }

    void fillMatrix(bool m[3][3])
    {
        const int m_size = sizeof(m) / sizeof(m[0]);
        for (int i = 0; i < m_size; i++) {
            for (int j = 0; j < sizeof(m[0]); j++) {
                //cout << i << " " << j << endl;
                mat[i][j] = m[i][j];
            }
        }
    }
};

#endif // CUSTOMMATRIX_H
