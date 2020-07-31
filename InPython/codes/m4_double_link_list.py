# coding: utf-8


class Node(object):
    """结点"""

    def __init__(self, item):
        self.elem = item
        self.next = None
        self.prev = None


class DoubleLinkList(object):
    """双链表"""
    # 可以考虑继承来减少函数的数量(面向对象)，通过继承，一样的函数就不用写了，不一样的再写。

    def __init__(self, node=None):
        self.__head = node

    def is_empty(self):
        """链表是否为空"""
        return self.__head is None

    def length(self):
        """链表长度"""  # 从头到尾的遍历过程
        # cur 游标，用来移动遍历节点
        cur = self.__head
        # count记录数据
        count = 0
        while cur is not None:  # not cur.next == None另一种循环条件，不适用
            count += 1
            cur = cur.next
        return count  # 考虑一下空链表的特殊情况是否使用

    def travel(self):
        """遍历整个链表"""
        cur = self.__head
        while cur is not None:
            print(cur.elem, end=" ")
            cur = cur.next
        print("")

    def add(self, item):
        """链表头部添加元素，头插法"""
        node = Node(item)
        if self.is_empty():
            # 如果是空链表，将__head指向node
            self.__head = node
        else:
            # 将node的next指向__head的头结点
            node.next = self.__head
            # 头结点所指向的还没有变；将__head的头结点的prev指向node
            self.__head.prev = node
            # 将__head指向node，即改变头结点
            self.__head = node

    def append(self, item):
        """链表尾部添加元素，尾插法"""
        node = Node(item)
        if self.is_empty():
            self.__head = node
        else:
            cur = self.__head
            while cur.next is not None:
                cur = cur.next
            cur.next = node
            node.prev = cur

    def insert(self, pos, item):
        """指定位置添加元素
        :param 从0开始
        """
        if self.is_empty() or pos > (self.length() - 1):
            self.append(item)
        elif pos <= 0:
            self.add(item)
        else:
            cur = self.__head
            count = 0  # 和"从0开始"保持一致
            while count < pos:  # 游标移动到指定位置的前一个位置，pre与pos - 1很好地对应了; 故这里不能是0.
                count += 1
                cur = cur.next
            # 循环停止前最后一次pre到了pos
            node = Node(item)
            # 以下这四句话最好和图结合着写；代码不唯一
            node.next = cur
            node.prev = cur.prev
            cur.prev.next = node
            cur.prev = node

    def remove(self, item):
        """删除节点：删除链表中第一个item元素"""
        cur = self.__head
        while cur is not None:  #
            if cur.elem == item:
                # 判断此节点是否是头结点
                # 头结点
                if cur == self.__head:
                    self.__head = cur.next
                    if cur.next:
                        # 判断链表是否只有一个结点
                        cur.next.prev = None
                else:
                    cur.prev.next = cur.next
                    if cur.next:
                        # 判断被删结点是否是最后一个结点
                        cur.next.prev = cur.prev
                break
            else:
                cur = cur.next

    def search(self, item):
        """查找节点是否存在"""
        cur = self.__head  # cur现在指向链表的第一个节点（地址）
        while cur is not None:  # 判断当前节点是否为空
            if cur.elem == item:
                return True
            cur = cur.next
        return False


if __name__ == "__main__":
    dll = DoubleLinkList()
    print(dll.is_empty())
    print(dll.length())

    dll.append(2)
    print(dll.is_empty())
    print(dll.length())

    dll.append(4)
    dll.add(1)
    dll.append(5)
    dll.append(6)
    dll.append(7)
    dll.append(8)
    dll.insert(2, 3)
    dll.travel()
    dll.insert(0, 0)
    dll.travel()

    dll.remove(0)
    dll.travel()
    dll.remove(2)
    dll.travel()
    dll.remove(8)
    dll.travel()
