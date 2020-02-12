#include <iostream>
using namespace std;

int i, temp;

i = 1;
temp = d[0];
for (i = 1; i <= SIZE; i++){
    temp = temp * v[i];
}
d[SIZE] = temp;

