# coding: utf-8


def bubble_sort(alist):
    """冒泡排序"""
    # 控制元素循环次数，range(a,b,-1) 从a开始到b+1结束，逆序
    for j in range(len(alist) - 1, 0, -1):
        # 控制游标
        count = 0
        for i in range(j):
            if alist[i] > alist[i + 1]:
                alist[i], alist[i + 1] = alist[i + 1], alist[i]
                count += 1
        if 0 == count:
            return


li = [54, 26, 93, 17, 77, 31, 44, 55, 20]
bubble_sort(li)
print(li)

# print([x for x in range(10, 0, -1)])
