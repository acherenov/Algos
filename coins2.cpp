#include <stdlib.h>
#include <stdio.h> 
#include <limits.h>

long int min_n(long int *ar, int n, long int *k);
long int max_n(long int *ar, int n);

int main()
{
  int n, count = 0;
  long int result = -1;
  long int *table;
  long int *table_copy;
  long int *numbers;
  long int *send;
  long int s; 
  long int i, j;
  long int *send_copy;
  long int send_i;
  long int max;  
  long int check; 
  
  scanf("%d", &n);
 
  if (n == 0) {
    printf("%ld", result);
    return 0;
  }
  
  numbers = malloc(n * sizeof(long int));
  
  /* read-in notionals */
  for (i = 0; i < n; i++) {
    scanf("%ld", &numbers[i]);
  }
  
  scanf("%ld", &s);
  table = malloc((s + 1) * sizeof(long int));
  table_copy = malloc((s + 1) * sizeof(long int));
  send = malloc(n * sizeof(long int));
  send_copy = malloc(n * sizeof(long int));
  for (i = 1; i <= s; i++) {
    table[i] = LONG_MAX;
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
      printf("%ld\n", result);
      printf("%ld", numbers[i]);
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
        if (result != -1) {
          table[i] = result + 1;  
          table_copy[i] = send_copy[send_i];
        }
      }
    } else {
      for (j = 0; j < n; j++) {
        send[j] = table[i - numbers[j]];
      }
      result = min_n(send, n, &send_i);
      if (result != -1) {
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
    printf("%ld", result);
    return 0;
  }
  
  result = table[s];
  printf("%ld\n", result);
  j = s;
  while (result > 0) {
    printf("%ld ", table_copy[j]);
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

long int min_n(long int *ar, int n, long int *k) {
  int i;
  long int min = ar[0]; 
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

long int max_n(long int *ar, int n) {
  int i;
  long int max = ar[0]; 
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


