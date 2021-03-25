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
		int MAX =500;
        
        while(MAX<10001)
        {
            srand(time(NULL));
            cout << "     MAX = "<< MAX << endl;
            
		    //double A[MAX][MAX], x[MAX], y[MAX];
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
            //t0=clock();
            auto start = chrono::steady_clock::now();
            for ( i = 0; i < MAX ; i++)
                for ( j = 0; j < MAX ; j++)
                    y[ i ] += A[i][j] * x[ j ];
            //t1=clock();
            auto end = chrono::steady_clock::now();
            cout << " First Pair of loops  = " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;
            //double time = (double(t1-t0)/CLOCKS_PER_SEC);
            //cout << "First Pair of loops - Execution Time: " << time << endl;
            /* Assign y = 0 */
            
            /* Second pair of loops */
            //t2=clock();
            auto start1 = chrono::steady_clock::now();
            for (j = 0; j < MAX ; j ++)
                for (i = 0; i < MAX ; i ++)
                    y[i] += A[i][j]* x[j];
            //t3=clock();
            auto end1 = chrono::steady_clock::now();
            cout << " Second Pair of loops = " << chrono::duration_cast<chrono::milliseconds>(end1 - start1).count() << endl;
            //time = (double(t3-t2)/CLOCKS_PER_SEC);
            //cout << "Second Pair of loops - Execution Time: " << time << endl;

        MAX += 500;
        A.clear();
        x.clear();
        y.clear();
        //cout << endl;
        }
		return 0;
}