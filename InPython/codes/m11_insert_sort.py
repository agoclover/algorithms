# coding: utf-8


def insert_sort(a_list):
    """插入排序"""
    length = len(a_list)
    # 循环进行n-1次
    for j in range(1, length):  # 或range(1, length)
        # 已排好序列为a_list[0]到a_list[j-1]
        # 将已拍好和a_list[j]一起从右向左开始逐次排序
        for i in range(j, 0, -1):
            if a_list[i] < a_list[i - 1]:
                a_list[i], a_list[i - 1] = a_list[i - 1], a_list[i]
            else:
                break


if __name__ == "__main__":
    li = [54, 26, 93, 17, 77, 31, 44, 55, 20]
    insert_sort(li)
    print(li)
