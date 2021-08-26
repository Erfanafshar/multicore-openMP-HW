#include <iostream>
using namespace std;

int main()
{

cout<<"Welcome to DataFlair tutorials!"<<endl<<endl;

int i, j, k, sample[3][2][3], size;
size=3*2*3; // Size of the 3D array is the product of size of each array
cout<<"Enter "<< size << " elements "<<endl;

for(i = 0; i < 3; ++i)
{
for (j = 0; j < 2; ++j)
{
for(k = 0; k < 3; ++k )
{
cin>>sample[i][j][k];
}
}
}
cout<<"The values are: "<<endl; // To display the values of elements according to their index
for(i = 0; i < 3; i++)
{
for (j = 0; j < 2; j++)
{
for(k = 0; k < 3; k++)
{
cout<<"sample [ "<< i <<" ][ "<< j << "] [ " << k << " ] = "<< sample[i][j][k] <<endl;
}
}
}
return 0;
}