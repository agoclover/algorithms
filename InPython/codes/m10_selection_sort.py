# coding: utf-8:


def selection_sort(alist):
    """选择排序"""
    length = len(alist)
    # 循环进行length - 1次
    for j in range(0, length - 1):
        # 每次选为了排序的第一个数为最小数
        __min = j
        # 每次从__min后起，比较所有元素
        for i in range(j+1, length):
            if alist[__min] > alist[i]:
                __min = i
        # 如果选出的数据不在正确位置上
        if __min is not j:
            alist[__min], alist[j] = alist[j], alist[__min]


if __name__ == "__main__":
    li = [54, 26, 93, 17, 77, 31, 44, 55, 20]
    selection_sort(li)
    print(li)