# coding: utf-8


class Deque(object):
    """双端队列"""
    def __init__(self):
        """创建一个空的双端队列"""
        self.__list = []

    def add_front(self, item):
        """从队头加入一个item元素"""
        self.__list.insert(0, item)

    def add_rear(self, item):
        """从队尾加入一个item元素"""
        self.__list.append(item)

    def pop_front(self):
        """从队头删除一个item元素"""
        return self.__list.pop(0)

    def pop_rear(self):
        """从队尾删除一个item元素"""
        return self.__list.pop()

    def is_empty(self):
        """判断双端队列是否为空"""
        return self.__list == []

    def size(self):
        """返回队列的大小"""
        return len(self.__list)


if __name__ == "__main__":
    dq = Deque()
