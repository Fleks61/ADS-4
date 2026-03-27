// Copyright 2025 NNTU-CS
#include <cstdint>
#include "alg.h"

int countPairs1(int *arr, int len, int value) {
  int count = 0;
  for (int i = 0; i < len; i++) {
    for (int j = i + 1; j < len; j++) {
      if (arr[i] + arr[j] == value) {
        count++;
      }
    }
  }
  return count;
}

int countPairs2(int *arr, int len, int value) {
  int count = 0;
  int left = 0;
  int right = len - 1;
  while (left < right) {
    int sum = arr[left] + arr[right];
    if (sum == value) {
      if (arr[left] == arr[right]) {
        int n = right - left + 1;
        count += n * (n - 1) / 2;
        break;
      }
      int leftCount = 1;
      int rightCount = 1;
      while (left + leftCount < right && arr[left] == arr[left + leftCount])
        leftCount++;
      while (right - rightCount > left && arr[right] == arr[right - rightCount])
        rightCount++;
      count += leftCount * rightCount;
      left += leftCount;
      right -= rightCount;
    } else if (sum < value) {
      left++;
    } else {
      right--;
    }
  }
  return count;
}

int countPairs3(int *arr, int len, int value) {
  int count = 0;
  for (int i = 0; i < len; i++) {
    if (i > 0 && arr[i] == arr[i - 1])
      continue;
    int target = value - arr[i];
    if (target < arr[i])
      break;
    int lo = -1;
    int hi = -1;
    int left = i + 1;
    int right = len - 1;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (arr[mid] == target) {
        lo = mid;
        right = mid - 1;
      } else if (arr[mid] < target) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    if (lo == -1)
      continue;
    left = lo;
    right = len - 1;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (arr[mid] == target) {
        hi = mid;
        left = mid + 1;
      } else if (arr[mid] < target) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    if (arr[i] == target) {
      int n = hi - i + 1;
      count += n * (n - 1) / 2;
      break;
    }
    int leftCount = 1;
    while (i + leftCount < len && arr[i + leftCount] == arr[i])
      leftCount++;
    count += leftCount * (hi - lo + 1);
  }
  return count;
}
