# coding: utf-8


class Node(object):  # 保存节点这个数据类型；2个数据；所有语言都适用
    """单链表的节点"""

    def __init__(self, elem):
        self.elem = elem
        self.next = None


class SingleCycleLinkList(object):
    """单链表"""

    def __init__(self, node=None):  # 默认参数，可在对象创建时修改；若不修改保持默认
        self.__head = node  # 双下划线，私有属性
        if node:
            node.next = node

    def is_empty(self):
        """链表是否为空"""
        return self.__head is None

    def length(self):
        """返回链表的长度"""
        # 如果链表为空，返回长度0
        if self.is_empty():
            return 0
        cur = self.__head
        count = 1
        # 不能用cur == self.__head;这里cur处于最后一个结点时，循环内不进行，所以用count=1
        while cur.next != self.__head:
            count += 1
            cur = cur.next
        return count  # 考虑一下空链表的特殊情况是否使用

    def travel(self):
        """遍历整个链表"""
        if self.is_empty():
            return
        cur = self.__head
        while cur.next != self.__head:
            print(cur.elem, end=" ")
            cur = cur.next
        # 退出循环，cur指向尾节点，但尾节点元素未打印
        print(cur.elem)

    def add(self, item):
        """链表头部添加元素，头插法"""
        node = Node(item)
        if self.is_empty():
            self.__head = node
            node.next = node
            return
        cur = self.__head
        while cur.next != self.__head:
            cur = cur.next
        # 退出循环，cur指向尾节点
        cur.next = node
        node.next = self.__head
        self.__head = node

    def append(self, item):
        """链表尾部添加元素，尾插法"""
        node = Node(item)
        if self.is_empty():
            self.__head = node
            node.next = node
        else:
            cur = self.__head
            while cur.next != self.__head:
                cur = cur.next
            cur.next = node
            node.next = self.__head

    def insert(self, pos, item):
        """指定位置添加元素
        :param 从0开始
        """
        if self.is_empty() or pos > (self.length() - 1):
            self.append(item)
        elif pos <= 0:
            self.add(item)
        else:
            # 跟单链表一种操作，因为不涉及尾
            pre = self.__head  # pre相当于cur换个名字
            count = 0  # 和"从0开始"保持一致
            # 游标移动到指定位置的前一个位置，pre与pos - 1很好地对应了; 故这里不能是0.
            while count < (pos - 1):
                count += 1
                pre = pre.next  # 循环停止前最后一次pre到了pos的前一位
            node = Node(item)
            node.next = pre.next
            pre.next = node

    def remove(self, item):
        """删除节点：删除链表中第一个item元素"""
        if self.is_empty():
            return
        pre = None
        cur = self.__head
        while cur.next is not self.__head:
            # 能够进入循环体
            if cur.elem == item:
                # 能够找到元素
                # 判断此节点是否是头结点
                if cur == self.__head:
                    # 头结点的情况
                    # 找尾节点
                    rear = self.__head
                    while rear.next is not self.__head:
                        rear = rear.next
                    self.__head = cur.next  # 先头再尾
                    rear.next = self.__head
                else:
                    # 中间节点
                    pre.next = cur.next
                return  # break是退出循环；return是退出函数
            else:
                # 游标移动
                pre = cur
                cur = cur.next
        # 退出循环，cur指向尾节点，最后结点没有被循环体处理
        if cur.elem == item:
            if cur == self.__head:
                # 链表只有一个结点
                self.__head = None
            else:
                # pre.next = cur.next
                pre.next = self.__head


    def search(self, item):
        """查找节点是否存在"""
        if self.is_empty():
            return False
        cur = self.__head  # cur现在指向链表的第一个节点（地址）
        while cur.next is not self.__head:
            if cur.elem == item:
                return True
            cur = cur.next
        if cur.elem == item:
            return True
        return False


if __name__ == "__main__":
    ll = SingleCycleLinkList()
    print(ll.is_empty())
    print(ll.length())

    ll.append(2)
    print(ll.is_empty())
    print(ll.length())

    ll.append(4)
    ll.add(1)
    ll.append(5)
    ll.append(6)
    ll.append(7)
    ll.append(8)
    ll.insert(2, 3)
    ll.travel()
    ll.insert(0, 0)
    ll.travel()

    ll.remove(0)
    ll.travel()
    ll.remove(2)
    ll.travel()
    ll.remove(8)
    ll.travel()