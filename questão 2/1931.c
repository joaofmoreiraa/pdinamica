#include <stdio.h>
#include <string.h>

#define MOD 1000000007

int validPatterns[243][5]; 
int patternsCount = 0;

void generatePatterns(int currentM, int targetM, int* currentPattern) {
    if (currentM == targetM) {
        for (int i = 0; i < targetM; i++) {
            validPatterns[patternsCount][i] = currentPattern[i];
        }
        patternsCount++;
        return;
    }

    for (int color = 0; color < 3; color++) {
        if (currentM == 0 || currentPattern[currentM - 1] != color) {
            currentPattern[currentM] = color;
            generatePatterns(currentM + 1, targetM, currentPattern);
        }
    }
}

int areCompatible(int* p1, int* p2, int m) {
    for (int i = 0; i < m; i++) {
        if (p1[i] == p2[i]) {
            return 0; 
        }
    }
    return 1; 
}

int colorTheGrid(int m, int n) {
    patternsCount = 0;
    
    int tempPattern[5];
    generatePatterns(0, m, tempPattern);
    
    long long dp[243];
    long long next_dp[243];
    
    for (int i = 0; i < patternsCount; i++) {
        dp[i] = 1;
    }
    
    for (int col = 1; col < n; col++) {
        for(int k=0; k<patternsCount; k++) next_dp[k] = 0;
        
        for (int i = 0; i < patternsCount; i++) {
            for (int j = 0; j < patternsCount; j++) {
                if (areCompatible(validPatterns[i], validPatterns[j], m)) {
                    next_dp[i] = (next_dp[i] + dp[j]) % MOD;
                }
            }
        }
        
        for (int k = 0; k < patternsCount; k++) {
            dp[k] = next_dp[k];
        }
    }
    
    long long result = 0;
    for (int i = 0; i < patternsCount; i++) {
        result = (result + dp[i]) % MOD;
    }
    
    return (int)result;
}