#include <stdlib.h>
#include <stdio.h> 

int main()
{
  int n, count = 0, countn = 0;
  long int result = -1;
  long int **table;
  long int *numbers;
  long int s; 
  long int i, k;
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
  
  table = malloc(count * sizeof(long int *));
  for (i = 0; i < count; i++) {
    table[i] = malloc((s + 2) * sizeof(long int));
  }
 
  for (i = 0; i < count; i++) {
    table[i][0] = numbers[i];
    table[i][1] = 0;
    for (k = 2; k < s + 2; k++) {
      table[i][k] = -1;
    }
  }
  k = numbers[0];
  while (k <= s) {
    table[0][k + 1] = k / numbers[0];
    k += numbers[0];
  }
  
  for (i = 1; i < count; i++) {
    for (k = 2; k < numbers[i] + 1; k++) {
      table[i][k] = table[i - 1][k];
    }
    for (k = numbers[i] + 1; k < s + 2; k++) {
      if ((table[i][k - numbers[i]] != -1) && table[i-1][k] != -1) {
        if (table[i][k - numbers[i]] + 1 <= table[i-1][k]) {
          table[i][k] = table[i][k - numbers[i]] + 1;
        } else {
          table[i][k] = table[i-1][k];    
        }
      }
      if ((table[i][k - numbers[i]] == -1) && table[i-1][k] != -1) {
        table[i][k] = table[i-1][k]; 
      }
      if ((table[i][k - numbers[i]] != -1) && table[i-1][k] == -1) {
        table[i][k] = table[i][k - numbers[i]] + 1;  
      }
    }
  }
  
  if (table[count - 1][s + 1] == -1) {
    result = -1;
    printf("%ld", result);
    for (i = 0; i < count; i++) {
      free(table[i]);
    }
    free(table);
    free(numbers);
    return 0;
  }
  
  printf("%ld\n", table[count - 1][s + 1]);
  
  i = count - 1; 
  k = s + 1;
  check = 0;
  while (check < table[count - 1][s + 1]) {
    if (i == 0) {
      printf("%ld ", numbers[i]);
      for (k = 0; k < count; k++) {
        free(table[k]);
      }
      free(table);
      free(numbers);
      return 0;
    }
    if (table[i][k] < table[i - 1][k]) {
      printf("%ld ", numbers[i]);
      check++;
      k -= numbers[i];
      i -= 1;
    } else {
      i -= 1;
    }
  }
  for (i = 0; i < count; i++) {
    free(table[i]);
  }
  free(table);
  free(numbers);
  return 0;
  
}