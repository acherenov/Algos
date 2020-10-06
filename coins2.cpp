#include <stdlib.h>
#include <stdio.h> 
#include <limits.h>

int min_n(int *ar, int n, int *k);
int max_n(int *ar, int n);

int main()
{
  int n, count = 0;
  int result = -1;
  int *table;
  int *table_copy;
  int *numbers;
  int *send;
  int s; 
  int i, j;
  int *send_copy;
  int send_i;
  int max;  
  int check; 
  
  scanf("%d", &n);
 
  if (n == 0) {
    printf("%d", result);
    return 0;
  }
  
  numbers = malloc(n * sizeof(int));
  
  /* read-in notionals */
  for (i = 0; i < n; i++) {
    scanf("%d", &numbers[i]);
  }
  
  scanf("%d", &s);
  table = malloc((s + 1) * sizeof(int));
  table_copy = malloc((s + 1) * sizeof(int));
  send = malloc(n * sizeof(int));
  send_copy = malloc(n * sizeof(int));
  for (i = 1; i <= s; i++) {
    table[i] = INT_MAX;
  }
  table[0] = 0;
  count = 0;
  for (i = 0; i < n; i++) {
    if (numbers[i] < s) {
      if (count == 0) {
        numbers[0] = numbers[i];
        count++;
      } else {
        check = 0;
        for (j = 0; j < count; j++) {
          if (numbers[j] == numbers[i]) {
            check = 1;
          }
        }
        if (check == 0) {
          numbers[count] = numbers[i];
          count++;
        }
          
      }
      
    }
    if (numbers[i] == s) {
      result = 1;
      printf("%d\n", result);
      printf("%d", numbers[i]);
      free(numbers);
      return 0;
    }
  }
  n = count;
  max = max_n(numbers, n);
  for (i = 1; i <= s; i++) {
    count = 0;
    if (i < max) {
      for (j = 0; j < n; j++) {
        if (i - numbers[j] >= 0) {
          send[count] = table[i - numbers[j]];
          send_copy[count] = numbers[j];
          count++; 
        }
      }
      if (count == 0) {
        continue;
      } else {
        result = min_n(send, count, &send_i);
        if (result != INT_MAX) {
          table[i] = result + 1;  
          table_copy[i] = send_copy[send_i];
        }
      }
    } else {
      for (j = 0; j < n; j++) {
        send[j] = table[i - numbers[j]];
      }
      result = min_n(send, n, &send_i);
      if (result != INT_MAX) {
        table[i] = result + 1;  
        table_copy[i] = numbers[send_i];
      }
    }
  }
  
  if (table[s] == -1) { 
    result = -1; 
    free(send);
    free(numbers);
    free(table);
    free(send_copy);
    free(table_copy);
    printf("%d", result);
    return 0;
  }
  
  result = table[s];
  printf("%d\n", result);
  j = s;
  while (result > 0) {
    printf("%d ", table_copy[j]);
    j -= table_copy[j];
    result -= 1;
  }
  
  free(send);
  free(numbers);
  free(table);
  free(send_copy);
  free(table_copy);
  return 0;
  
}

int min_n(int *ar, int n, int *k) {
  int i;
  int min = ar[0]; 
  *k = 0;
  for (i = 0; i < n; i++) {
    if (ar[i] == -1) {
      continue;
    }
    if (ar[i] < min) {
      min = ar[i];
      *k = i;
    }
  }
  return min;
}

int max_n(int *ar, int n) {
  int i;
  int max = ar[0]; 
  for (i = 0; i < n; i++) {
    if (ar[i] == -1) {
      continue;
    }
    if (ar[i] > max) {
      max = ar[i];
    }
  }
  return max;
}


