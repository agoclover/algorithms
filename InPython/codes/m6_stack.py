# coding: utf-8


class Stack(object):
    """栈"""
    def __init__(self):
        """创建一个新的空栈"""
        self.__stack = []

    def push(self, item):
        """添加一个新的元素item到栈顶"""
        self.__stack.append(item)

    def pop(self):
        """弹出栈顶元素"""
        return self.__stack.pop()

    def peek(self):
        """返回栈顶元素"""
        return self.__stack[len(self.__stack)-1]

    def is_empty(self):
        """判断栈是否为空"""
        return self.__stack == []

    def size(self):
        """返回栈的元素个数"""
        return len(self.__stack)


if __name__ == "__main__":
    # 创建一个空栈
    s = Stack()
    # 判断s是否为空
    print("s is empty? ", s.is_empty())
    # 增加元素1, 2, 3, 4
    s.push(1)
    s.push(2)
    s.push(3)
    s.push(4)
    # 判断s是否为空
    print("s is empty? ", s.is_empty())
    # 返回栈顶元素
    print("peek number of s is %d" % s.peek())
    # s元素个数
    print("sizes of s is %d" % s.size())
    # 取出最上方元素
    print(s.pop())
    print(s.pop())
    print(s.pop())
    print(s.pop())