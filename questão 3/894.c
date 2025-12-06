#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* createNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}


struct TreeNode** allPossibleFBT(int n, int* returnSize) {
    
    if (n % 2 == 0) {
        *returnSize = 0;
        return NULL;
    }

    
    struct TreeNode*** dp = (struct TreeNode***)malloc((n + 1) * sizeof(struct TreeNode**));
    
    int* sizes = (int*)calloc((n + 1), sizeof(int));

    dp[1] = (struct TreeNode**)malloc(sizeof(struct TreeNode*));
    dp[1][0] = createNode(0);
    sizes[1] = 1;

    for (int i = 3; i <= n; i += 2) {
        
        
        dp[i] = (struct TreeNode**)malloc(5000 * sizeof(struct TreeNode*));
        int count = 0;

        
        for (int j = 1; j < i; j += 2) {
            int k = i - 1 - j; 
            
            for (int leftIdx = 0; leftIdx < sizes[j]; leftIdx++) {
                for (int rightIdx = 0; rightIdx < sizes[k]; rightIdx++) {
                    struct TreeNode* root = createNode(0);
                    
                    root->left = dp[j][leftIdx];
                    root->right = dp[k][rightIdx];
                    
                    dp[i][count++] = root;
                }
            }
        }
        sizes[i] = count;
    }

    *returnSize = sizes[n];
    struct TreeNode** result = dp[n];

    for (int i = 1; i < n; i += 2) {
        free(dp[i]);
    }
    free(dp);
    free(sizes);

    return result;
}