#include <stdio.h>
#include <math.h>

void swaps(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int partition(int array[], int start, int end) {
    int pivot = array[end];

    int p_idx = start;
 
    for (int i = start; i < end; i++) {
        if (array[i] >= pivot) {
            swaps(&array[i], &array[p_idx]);
            p_idx++;
        }
    }
 
    swaps(&array[p_idx], &array[end]);
 
    return p_idx;
}

void quick_sort(int array[], int start, int end) {
    if (start < end) {
        int p = partition(array, start, end);
  
        quick_sort(array, start, p - 1);
        quick_sort(array, p + 1, end);
    }
}



void print(int lines, int table[][lines + 1]) {
    for(int i = 0; i <= lines; i++) {
        for(int j = 0; j < i + 1; j++)
            printf("%i ", table[i][j]);
        printf("\n");
    }

}

void bkt(int array[], int visited[], int size, int current_line, int nr_lines, int result[][nr_lines + 1]) {
    if (current_line == nr_lines + 1)
        return;
    
    // process candidates
    for (int i = 1; i < size; i++) {
        if (visited[i]) continue;
        
        result[current_line][0] = array[i];
        visited[i] = 1;
        
        // fill in the entire current line
        for(int j = 1; j <= current_line; j++) {
            result[current_line][j] = result[current_line - 1][j - 1] - result[current_line][j - 1];
        }
        
    
        int areEqual = 1;
        
        int marked_as_visited[size];
        int idx = 0;

        for (int b = 1; b <= current_line; b++) {
            int isPresent = 0;
            for (int a = 1; a < size; a++) {
                if (visited[a]) continue;
                
                if (result[current_line][b] == array[a]) {
                    isPresent = 1;
                    visited[a] = 1;
                    marked_as_visited[idx++] = a;
                    break;
                }
            }
            
            if (!isPresent) {
                areEqual = 0;
            }
        }

        if (!areEqual) {
            for (int u = 0; u < idx; u++) {
                visited[marked_as_visited[u]] = 0;
            }
            visited[i] = 0;
            continue;
        }
        bkt(array, visited, size, current_line + 1, nr_lines, result);
        
    }
}


int main(void) {
    // 88, 39, 49, 15, 24, 25, 12, 13, 11, 4, 1, 3, 8, 5, 7
    

     int arr[] = {133814, 60889, 72925, 28710, 32179, 40746, \
       14273, 14437, 17742, 23004, \
        7501,   6772,   7665,  10077,  12927, \
        4117,   3384,   3388,   4277,   5800,   7127, \
        2317,   1800,   1584,   1804,   2473,   3327,   3800, \
        1314,   1003,    797,    787,   1017,   1456,   1871,   1929, \
         740,    574,    429,    368,    419,    598,   858,   1013,    916, \
         409,    331,    243,    186,    182,    237,   361,    497 ,   516 ,   400, \
         220 ,   189 ,   142,    101,    85 ,    97,    140,    221,    276,    240,    160, \
         114 ,   106,     83 ,    59,     42 ,    43 ,    54,     86,    135,    141,     99 ,    61, \
          55 ,    59 ,    47,     36,     23,     19 ,    24 ,    30 ,    56 ,    79 ,    62,     37 ,    24, \
          22 ,    33,     26 ,    21 ,    15 ,     8 ,    11 ,    13 ,    17,     39,     40,     22,     15 ,     9 ,\
         4 ,    18,     15,     11,     10,      5 ,     3  ,    8 ,     5  ,   12    , 27 ,    13    ,  9  ,    6  ,    3 };

//    int arr[] = {91, 52, 39,24, 28, 11, 5, 19, 9, 2, 3, 2, 17, -8, 10};
    int size = sizeof(arr) / sizeof(int);
    int nr_lines = 14;
    quick_sort(arr, 0, size - 1);
    
    int table[nr_lines + 1][nr_lines + 1];
    int result[nr_lines + 1][nr_lines + 1];
    int visited[size];
    
    visited[0] = 1;
    
    for(int i = 1; i < size; i++)
        visited[i] = 0;
    
    int row = 0;
    int col = 0;
    int i = 0;
    while(i < size) {
        col++;
        for(int j = 0; j < col; j++) {
            table[row][j] = arr[i++];
        }
        row++;
    }
        
    
    result[0][0] = arr[0];
    bkt(arr, visited, size, 1, nr_lines, result);

    print(nr_lines, table);
    printf("\n");
    print(nr_lines, result);
    /* 1. input array: [1, 3, 4, 5, 6, 10] -> [10, 5, 6, 1, 4, 3]
       2. input array: [1, 1, 2, 3, 3, 4, 5, 8, 9, 17] ->
                ->  [17, 8, 9, 3, 5, 4, 1, 2, 3, 1]
     
     
                          10
                       6      4
                    5     1      3
     
     
       
                         17
                      9      8
                   4     5      3
                1     3      2     1
     
     
     [17, 9, 8, 5, 4, 3, 3, 2, 1, 1]
     
                     17
                  9      8
               4     5      3
            1     3      2     1
     
     
     [10, 6, 5, 4, 3, 1]  ->   [10, 6, 4, 5, 1, 3]
     
     
     
                7
             4     3
          2     2     1
     
     [7, 4, 3, 2, 2, 1] -> [7, 4, 3, 2, 2, 1]
     */
    
    return 0;
}
