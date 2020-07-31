# coding: utf-8


class Node(object):  # 保存节点这个数据类型；2个数据；所有语言都适用
    """单链表的节点"""

    def __init__(self, elem):
        self.elem = elem
        self.next = None


# (elem, None)元组也能实现


class SingleLinkList(object):
    """单链表"""

    def __init__(self, node=None):  # 默认参数，可在对象创建时修改；若不修改保持默认
        self.__head = node  # 双下划线，私有属性

    # 对象方法：对一个链表类的具体对象操作
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
        node.next = self.__head
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

    def insert(self, pos, item):
        """指定位置添加元素
        :param 从0开始
        """
        if self.is_empty() or pos > (self.length() - 1):
            self.append(item)
        elif pos <= 0:
            self.add(item)
        else:
            pre = self.__head  # pre相当于cur换个名字
            count = 0  # 和"从0开始"保持一致
            while count < (pos - 1):  # 游标移动到指定位置的前一个位置，pre与pos - 1很好地对应了; 故这里不能是0.
                count += 1
                pre = pre.next  # 循环停止前最后一次pre到了pos的前一位
            node = Node(item)
            node.next = pre.next
            pre.next = node

    def remove(self, item):
        """删除节点：删除链表中第一个item元素"""
        pre = None
        cur = self.__head  # pre现在指向链表的第一个节点（地址）
        while cur is not None:  #
            if cur.elem == item:
                # 判断此节点是否是头结点
                # 头结点
                if  cur == self.__head:
                    self.__head = cur.next
                else:
                    pre.next = cur.next
                break
            else:
                pre = cur
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
    ll = SingleLinkList()
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



