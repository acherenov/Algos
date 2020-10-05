#include <stdlib.h>
#include <stdio.h> 

long int min_n(long int *ar, int n);
long int max_n(long int *ar, int n);

int main()
{
  int n, count = 0;
  long int result = -1;
  long int *table;
  long int *numbers;
  long int *send;
  long int s; 
  long int i, j;
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
  
  if (s % max_n(numbers, n) == 0) {
    j =  max_n(numbers, n);
    result = s / j;
    printf("%ld\n", result);
    for (i = 0; i < result; i++) {
      printf("%ld ", j);  
    }
    free(numbers);
    return 0;
  }
  
  if (count == 0) {
    result = -1;
    printf("%ld", result);
    free(numbers);
    return 0;
  }
  
  check = 1;
  for (i = 0; i < n; i++) {
    if (numbers[i] % 2 == 0) {
      check = 0;
    }
  }
  
  if (check != 0 && (s % 2) == 0) {
    result = -1;
    printf("%ld", result);
    free(numbers);
    return 0;
  }
  
  table = malloc(s * sizeof(long int));
  send = malloc(n * sizeof(long int));
  for (i = 0; i < s; i++) {
    table[i] = -1;
  }
  
  for (i = 0; i < n; i++) {
    table[numbers[i] - 1] = 1;
  }
  
  j = max_n(numbers, n);
  for (i = 2 * j - 1; i < s; i += j) {
    table[i] = (i + 1) / j;
  }
  
  j = min_n(numbers, n);
  for (i = j; i < s; i++) {
    if (table[i] == -1) { 
      count = 0;
      for (j = 0; j < n; j++) {
        if (i - numbers[j] >= 0) {
          if (table[i - numbers[j]] != -1) {
            send[count] = table[i - numbers[j]]; 
            count++;  
          }
        }
      }
      if (count == 0) {
        continue;
      } else {
        if (min_n(send, count) != -1) {
          table[i] = min_n(send, count) + 1;  
        }
      }
    }
  }
  
  if (table[s-1] == -1) { 
    result = -1; 
    free(send);
    free(numbers);
    free(table);
    printf("%ld", result);
    return 0;
  }
  
  result = table[s - 1];
  printf("%ld\n", result);
  j = s - 1;
  while (result > 0) {
    if (table[j] == 1) {
      printf("%ld", j + 1);
      break;
    }
    for (i = 0; i < n; i++) {
      if (j - numbers[i] >= 0){
        if (table[j - numbers[i]] == table[j] - 1) {
          printf("%ld ", numbers[i]);
          result -= 1;
          j -= numbers[i];
        } 
      }
    }
  }
  
  free(send);
  free(numbers);
  free(table);
  return 0;
  
}

long int min_n(long int *ar, int n) {
  int i;
  long int min = ar[0]; 
  for (i = 0; i < n; i++) {
    if (ar[i] == -1) {
      continue;
    }
    if (ar[i] < min) {
      min = ar[i];
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