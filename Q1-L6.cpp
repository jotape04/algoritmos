#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

int subsetSums(int *itens, int n, int minQuantity, int maxSum) {
    int count = 0;
    //use dynamic programming
    bool **dp = new bool*[n+1];
    for (int i=0; i<=n; i++) {
        dp[i] = new bool[maxSum+1];
    }

    //initialize first column as true. 0 sum is possible with all elements.
    for (int i=0; i<=n; i++) {
        dp[i][0] = true;
    }

    //initialize top row, except dp[0][0], as false. 0 sum is not possible with any element except 0.
    for (int i=1; i<=maxSum; i++) {
        dp[0][i] = false;
    }

    //fill the dp table
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=maxSum; j++) {
            //if current element is greater than sum, then it can't be included in the subset
            if (itens[i-1] > j) {
                dp[i][j] = dp[i-1][j];
            }
            //else, check if sum can be obtained by any of the following:
            //1. including the current element
            //2. excluding the current element
            else {
                dp[i][j] = dp[i-1][j] || dp[i-1][j-itens[i-1]];
            }
        }
    }   

    //count the number of subsets with sum not greater than maxSum
    for (int i=minQuantity; i<=n; i++) {
        for (int j=0; j<=maxSum; j++) {
            if (dp[i][j]) {
                count++;
            }
        }
    }
    
    return count;
}

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int casesQuantity;
    cin >> casesQuantity;

    for (int i=0; i<casesQuantity; i++) {
        int itensQuantity;
        cin >> itensQuantity;

        int itens[itensQuantity];
        for (int j=0; j<itensQuantity; j++) {
            cin >> itens[j];
        }

        int minQuantity, maxSum;
        cin >> minQuantity >> maxSum;

        cout << "caso " << i << ": " << subsetSums(itens, itensQuantity, minQuantity, maxSum) << endl;
    }

    return 0;
}
