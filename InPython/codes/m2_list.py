# coding: utf-8

from timeit import Timer


def test1():
    li = []  # 往空列表中加
    for i in range(10000):
        li.append(i)


def test2():
    li = []  # 往空列表中加
    for i in range(10000):
        li += [i]  # +=是有优化的,li = li + [i]没优化


def test3():
    li = [i for i in range(10000)]  # 列表生成器


def test4():
    li = list(range(10000))  # 将可迭代对象直接转换为列表；python3 返回可迭代对象


def test5():
    li = []
    for i in range(10000):  # extend; append只能添加单个元素，但extend能添加列表
        li.extend([i])


time1 = Timer("test1()", "from __main__ import test1")  # 先字符串；再测试
print("append:", time1.timeit(1000))

time2 = Timer("test2()", "from __main__ import test2")  # 先字符串；再测试
print("+:", time2.timeit(1000))

time3 = Timer("test3()", "from __main__ import test3")  # 先字符串；再测试
print("[i for i in range]:", time3.timeit(1000))

time4 = Timer("test4()", "from __main__ import test4")  # 先字符串；再测试
print("list(range()):", time4.timeit(1000))

time5 = Timer("test5()", "from __main__ import test5")  # 先字符串；再测试
print("extend:", time5.timeit(1000))


def test6():
    li = []
    for i in range(10000):
        li.append(i)


def test7():
    li = []
    for i in range(10000):
        li.insert(0, i)


# 事实是append要比insert快很多
time6 = Timer("test6()", "from __main__ import test6")  # 先字符串；再测试
print("append:", time6.timeit(1000))

time7 = Timer("test7()", "from __main__ import test7")  # 先字符串；再测试
print("insert:", time7.timeit(1000))
