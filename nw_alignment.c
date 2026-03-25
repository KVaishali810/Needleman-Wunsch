#include <stdio.h>
#include <string.h>

#define MATCH     1
#define MISMATCH -1
#define GAP      -2
#define MAXLEN    100

int score(char a, char b) {
    return (a == b) ? MATCH : MISMATCH;
}

int max3(int a, int b, int c) {
    if (a >= b && a >= c) return a;
    if (b >= a && b >= c) return b;
    return c;
}

void reverse(char *str) {
    int i = 0;
    int j = strlen(str) - 1;
    while (i < j) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

int main() {
    char seq1[MAXLEN], seq2[MAXLEN];

    printf("Enter sequence 1: ");
    scanf("%s", seq1);
    printf("Enter sequence 2: ");
    scanf("%s", seq2);

    int m = strlen(seq1);
    int n = strlen(seq2);

    printf("Seq1: %s (length %d)\n", seq1, m);
    printf("Seq2: %s (length %d)\n", seq2, n);

/* declare the DP matrix */
    int dp[MAXLEN][MAXLEN];
     /* fill the DP matrix */
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int diag = dp[i-1][j-1] + score(seq2[i-1], seq1[j-1]);
            int top  = dp[i-1][j]   + GAP;
            int left = dp[i][j-1]   + GAP;
            dp[i][j] = max3(diag, top, left);
        }
    }
    /* traceback */
    char align1[MAXLEN*2], align2[MAXLEN*2];
    int idx = 0;
    int i = n, j = m;

    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 &&
            dp[i][j] == dp[i-1][j-1] + score(seq2[i-1], seq1[j-1])) {
            /* came from diagonal */
            align1[idx] = seq1[j-1];
            align2[idx] = seq2[i-1];
            i--; j--;
        } else if (i > 0 && dp[i][j] == dp[i-1][j] + GAP) {
            /* came from top - gap in seq1 */
            align1[idx] = '-';
            align2[idx] = seq2[i-1];
            i--;
        } else {
            /* came from left - gap in seq2 */
            align1[idx] = seq1[j-1];
            align2[idx] = '-';
            j--;
        }
        idx++;
    }

    /* reverse the alignment strings */
    align1[idx] = '\0';
    align2[idx] = '\0';
    reverse(align1);
    reverse(align2);

    /* print alignment */
    printf("\n===== Needleman-Wunsch Alignment =====\n");
    printf("Seq1 : %s\n", align1);

    /* print match/mismatch line */
    printf("Mtch : ");
    for (int k = 0; k < idx; k++) {
        if (align1[k] == '-' || align2[k] == '-')
            printf(" ");        /* gap — print space */
        else if (align1[k] == align2[k])
            printf("|");        /* match */
        else
            printf(".");        /* mismatch */
    }
    printf("\n");

    printf("Seq2 : %s\n", align2);
    printf("\nAlignment score : %d\n", dp[n][m]);
    printf("======================================\n");
    
    /* initialize first row with gap penalties */
    for (int j = 0; j <= m; j++)
        dp[0][j] = j * GAP;

    /* initialize first column with gap penalties */
    for (int i = 0; i <= n; i++)
        dp[i][0] = i * GAP;

    /* print the initialized matrix */
    printf("\nInitialized matrix:\n");
    printf("     -  ");
    for (int j = 0; j < m; j++)
        printf("%3c  ", seq1[j]);
    printf("\n");

    for (int i = 0; i <= n; i++) {
        if (i == 0) printf("  - ");
        else        printf("  %c ", seq2[i-1]);
        for (int j = 0; j <= m; j++)
            printf("%3d  ", dp[i][j]);
        printf("\n");
    }
    return 0;
}
