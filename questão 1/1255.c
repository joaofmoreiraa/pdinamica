#include <string.h>

int maxScoreWords(char** words, int wordsSize, char* letters, int lettersSize, int* score, int scoreSize) {
    int totalLetters[26] = {0};
    for (int i = 0; i < lettersSize; i++) {
        totalLetters[letters[i] - 'a']++;
    }

    int maxScore = 0;
    
    int totalSubsets = 1 << wordsSize;

    for (int mask = 0; mask < totalSubsets; mask++) {
        
        int currentSubsetCounts[26] = {0};
        int currentScore = 0;
        int isValid = 1;

        for (int i = 0; i < wordsSize; i++) {
            if ((mask >> i) & 1) {
                char* w = words[i];
                for (int j = 0; w[j] != '\0'; j++) {
                    int charIdx = w[j] - 'a';
                    currentSubsetCounts[charIdx]++;
                    currentScore += score[charIdx];
                }
            }
        }

        for (int k = 0; k < 26; k++) {
            if (currentSubsetCounts[k] > totalLetters[k]) {
                isValid = 0;
                break;
            }
        }

        if (isValid && currentScore > maxScore) {
            maxScore = currentScore;
        }
    }

    return maxScore;
}