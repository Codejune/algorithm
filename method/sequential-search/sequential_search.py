# -*- encoding: utf-8 -*-
from typing import Any


def sequential_search(key: Any, array: list) -> int:
    for index, value in enumerate(array):
        if value == key:
            return index
    raise KeyError


if __name__ == "__main__":
    array = [1, 5, 4, 3, 12, 14, 2, 7, 9]
    key = 13
    try:
        index = sequential_search(key, array)
        print(f"Key({key}) index is {index}")
    except KeyError:
        print("Not found")
