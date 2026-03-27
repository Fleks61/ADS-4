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
      int leftCount = 1;
      int rightCount = 1;
      while (left + leftCount < right && arr[left] == arr[left + leftCount])
        leftCount++;
      while (right - rightCount > left && arr[right] == arr[right - rightCount])
        rightCount++;
      if (arr[left] == arr[right]) {
        int total = leftCount + rightCount;
        count += total * (total - 1) / 2;
      } else {
        count += leftCount * rightCount;
      }
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

int lowerBound(int *arr, int left, int right, int target) {
  int result = -1;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (arr[mid] == target) {
      result = mid;
      right = mid - 1;
    } else if (arr[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return result;
}

int upperBound(int *arr, int left, int right, int target) {
  int result = -1;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (arr[mid] == target) {
      result = mid;
      left = mid + 1;
    } else if (arr[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return result;
}

int countPairs3(int *arr, int len, int value) {
  int count = 0;
  for (int i = 0; i < len; i++) {
    if (i > 0 && arr[i] == arr[i - 1])
      continue;
    int target = value - arr[i];
    if (target < arr[i]) break;
    int lo = lowerBound(arr, i + 1, len - 1, target);
    if (lo == -1) continue;
    int hi = upperBound(arr, i + 1, len - 1, target);
    if (arr[i] == target) {
      int groupSize = hi - lo + 1 + 1;
      count += groupSize * (groupSize - 1) / 2;
      break;
    } else {
      int leftCount = upperBound(arr, 0, len - 1, arr[i])
                    - lowerBound(arr, 0, len - 1, arr[i]) + 1;
      count += leftCount * (hi - lo + 1);
    }
  }
  return count;
}
