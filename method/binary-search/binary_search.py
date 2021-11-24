# -*- encoding: utf-8 -*-
from typing import Any


def binary_search(key: Any, array: list) -> int:

    low = 0
    high = len(array) - 1

    while low <= high:
        mid = int((low + high) / 2)

        if array[mid] == key:
            return mid
        elif key < array[mid]:
            high = mid - 1
        else:
            low = mid + 1
    raise KeyError


if __name__ == "__main__":
    array = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    key = 0

    try:
        index = binary_search(key, array)
        print(f"Key({key}) index is {index}")
    except KeyError:
        print("Not found")
