#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

int subsetSums(int *itens, int n, int minQuantity, int maxSum) {
    int count = 0;
    for (int i=0; i<(1<<n); i++) {
        int sum = 0;
        int quantity = 0;
        for (int j=0; j<n; j++) {
            if (i & (1<<j)) {
                sum += itens[j];
                quantity++;
            }
        }
        if (sum <= maxSum && quantity >= minQuantity) {
            count++;
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
