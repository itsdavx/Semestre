#include <iostream>

using namespace std;

int main() {
    int dp[n+1];
    dp[0] = caso_base;

    for(int i = 1; i <= n; i++) {
        dp[i] = combinacion(dp[i-1], dp[i-2]);
    }
}