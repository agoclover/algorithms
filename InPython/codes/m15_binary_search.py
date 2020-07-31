# coding: utf-8


def binary_search_resu(alist, item):
    """二分查找，递归版本"""
    n = len(alist)
    if n > 1:
        mid = n//2
        if alist[mid] == item:
            return True
        elif item < alist[mid]:
            return binary_search_resu(alist[:mid], item)
        else:
            return binary_search_resu(alist[mid:], item)
    return False


def binary_search(alsit, item):
    """二分查找，非递归版本"""
    n = len(alsit)
    first = 0
    last = n - 1
    while first <= last:
        mid = (first + last) // 2
        if alsit[mid] == item:
            return True
        elif item < alsit[mid]:
            last = mid - 1
        else:
            first = mid + 1
    return False


if __name__ == "__main__":
    li = [17, 20, 26, 31, 44, 54, 55, 77, 93]
    print(binary_search(li, 55))
    print(binary_search(li, 100))
