# coding: utf-8


def shell_sort(alist):
    """希尔排序"""
    n = len(alist)
    # 初始步长
    gap = n // 2  # python3中/是得小数，//是取整
    while gap > 0:
        # 按步长进行插入排序,与普通插入算法的区别为gap步长
        for j in range(gap, n):
            i = j
            # 插入排序
            while i > 0:
                if alist[i - gap] > alist[i]:
                    alist[i - gap], alist[i] = alist[i], alist[i - gap]
                    i -= gap
                else:
                    break
        # 得到新的步长
        gap //= 2


li = [54, 26, 93, 17, 77, 31, 44, 55, 30]
shell_sort(li)
print(li)
