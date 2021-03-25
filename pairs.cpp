#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <vector>
#include <chrono>
//#define MAX 100
using namespace std;


unsigned t0, t1, t2, t3;

int randomizer()
{
    int num = 1 + rand() % (100000 - 1);
    return num;
}

int main()
{
		int MAX =1000;
        
        while(MAX<10001)
        {
            srand(time(NULL));
            cout << "     MAX = "<< MAX << endl;

            vector<vector<int>>A;
            vector<int> x;
            vector<int> y;

            x.resize(MAX);
            y.resize(MAX);
            A.resize(MAX);

            for (int i = 0; i < MAX; i++){
	        	A[i].resize(MAX);
	        }

            for (int i = 0; i < MAX; i++)
                for (int j = 0; j < MAX; j++)
                    A[i][j] = randomizer();
                    //cout<<A[i][j]<<endl;

                
            for (int j = 0; j < MAX; j++)
                x[j] = randomizer();
                //cout<<x[j]<<endl;
            
            /* Initialize A and x, assign y = 0 */
            //int y=0;
            int i , j;
            
            /* First pair of loops */
         
            auto start = chrono::steady_clock::now();
            for ( i = 0; i < MAX ; i++)
                for ( j = 0; j < MAX ; j++)
                    y[ i ] += A[i][j] * x[ j ];
          
            auto end = chrono::steady_clock::now();
            cout << " First Pair of loops  = " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;
            /* Assign y = 0 */
    
            /* Second pair of loops */
           
            auto start1 = chrono::steady_clock::now();
            for (j = 0; j < MAX ; j ++)
                for (i = 0; i < MAX ; i ++)
                    y[i] += A[i][j]* x[j];
          
            auto end1 = chrono::steady_clock::now();
            cout << " Second Pair of loops = " << chrono::duration_cast<chrono::milliseconds>(end1 - start1).count() << endl;

        MAX += 500;
        A.clear();
        x.clear();
        y.clear();
        //cout << endl;
        }
		return 0;
}