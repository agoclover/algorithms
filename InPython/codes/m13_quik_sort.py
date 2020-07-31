# coding: utf-8


def quik_sort(alist, first, last):
    """快速排序"""
    if first >= last:
        return

    low = first
    mid_value = alist[first]
    high = last
    while low < high:
        while low < high and alist[high] >= mid_value:
            high -= 1
        alist[low] = alist[high]
        while low < high and alist[low] < mid_value:
            low += 1
        alist[high] = alist[low]
    alist[low] = mid_value

    # 递归嵌套
    # 对low左边的元素快速排序
    quik_sort(alist, first, low - 1)
    # 对low右边的元素快速排序
    quik_sort(alist, low + 1, last)


if __name__ == "__main__":
    li = [54, 26, 93, 17, 77, 31, 44, 55, 30]
    print(li)
    quik_sort(li, 0, len(li) - 1)
    print(li)
