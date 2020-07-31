# coding: utf-8


class Queue(object):
    """队列"""

    def __init__(self):
        self.__list = []

    def enqueue(self, item):
        """往队列中添加一个item元素"""
        self.__list.append(item)  # O(1)
        # self.__list.insert(0, item)  # O(n)

    def dequeue(self):
        """从队列头部删除一个元素"""
        return self.__list.pop(0)  # O(n)
        # return self.__list.pop()  # O(1)

    def is_empty(self):
        """判断一个队列是否为空"""
        return self.__list == []

    def size(self):
        """返回队列的大小"""
        return len(self.__list)


if __name__ == "__main__":
    q = Queue()
    q.enqueue(1)
    q.enqueue(2)
    q.enqueue(3)
    q.enqueue(4)
    print(q.dequeue())
    print(q.dequeue())
    print(q.dequeue())
    print(q.dequeue())
