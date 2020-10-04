#include <stdlib.h>
#include <stdio.h> 

long int min_n(long int *ar, int n);

int main()
{
  int n, count = 0, countn = 0;
  long int result = -1;
  long int *table;
  long int *numbers;
  long int *send;
  long int s; 
  long int i, j;
  long int check;
  long int rn; 
  
  scanf("%d", &n);
 
  if (n == 0) {
    printf("%ld", result);
    return 0;
  }
  
  numbers = malloc(n * sizeof(long int));
  
  for (i = 0; i < n; i++) {
    scanf("%ld", &rn);
    if (countn == 0) {
      numbers[countn] = rn;
      countn++;
    } else {
      if (numbers[countn - 1] != rn) {
        numbers[countn] = rn;
        countn++;
      }
    }
  }
  scanf("%ld", &s);
  n = countn;
  for (i = 0; i < n; i++) {
    if (numbers[i] < s) {
      count++;
    }
    if (numbers[i] == s) {
      result = 1;
      printf("%ld\n", result);
      printf("%ld", numbers[i]);
      free(numbers);
      return 0;
    }
  }
  
  if (count == 0) {
    result = -1;
    printf("%ld", result);
    free(numbers);
    return 0;
  }
  
  table = malloc(s * sizeof(long int *));
  send = malloc(n * sizeof(long int *));
  for (i = 0; i < s; i++) {
    table[i] = -1;
  }
  
  for (i = 0; i < n; i++) {
    table[numbers[i] - 1] = 1;
  }
  
  for (i = 0; i < s; i++) {
    if (table[i] == -1) { 
      countn = 0;
      for (j = 0; j < n; j++) {
        if (i - numbers[j] >= 0) {
          send[countn] = table[i - numbers[j]]; 
          countn++;
        }
      }
      if (countn == 0) {
        continue;
      } else {
        table[i] = min_n(send, countn) + 1;  
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
  check = 1; 
  while (check <= result) {
    if (table[j] == 1) {
      printf("%ld", j + 1);
      break;
    }
    
    for (i = 0; i < n; i++) {
      if (table[j - numbers[i]] == table[j] - 1) {
        printf("%ld ", numbers[i]);
        check++;
        j -= numbers[i];
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
  long int min; 
  int count = 0;
  for (i = 0; i < n; i++) {
    if (ar[i] == -1) {
      continue;
    }
    if (count == 0) {
      min = ar[0];
      count++;
    } else {
      if (ar[i] < min) {
        min = ar[i];
      }
    }
  }
  return min;
}
