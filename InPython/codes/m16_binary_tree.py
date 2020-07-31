# coding: utf-8


class Node(object):
    """二叉树结点"""

    def __init__(self, item):
        self.elem = item
        self.lchild = None
        self.rchild = None


class Tree(object):
    """二叉树"""

    def __init__(self):
        self.root = None

    def add(self, item):
        """添加元素"""
        node = Node(item)
        if self.root is None:
            self.root = node
            return
        queue = [self.root]
        while queue:
            cur_node = queue.pop(0)
            if cur_node.lchild is None:
                cur_node.lchild = node
                return
            else:
                queue.append(cur_node.lchild)
            if cur_node.rchild is None:
                cur_node.rchild = node
                return
            else:
                queue.append(cur_node.rchild)

    def breadth_travel(self):
        """广度遍历"""
        queue = [self.root]
        while queue:
            cur_node = queue.pop(0)
            print(cur_node.elem, end=" ")
            if cur_node.lchild is not None:
                queue.append(cur_node.lchild)
            if cur_node.rchild is not None:
                queue.append(cur_node.rchild)

    def preorder_travel(self, node):
        """先序遍历"""
        if node is None:
            return
        print(node.elem, end=" ")
        self.preorder_travel(node.lchild)
        self.preorder_travel(node.rchild)

    def inorder_travel(self, node):
        """先序遍历"""
        if node is None:
            return
        self.inorder_travel(node.lchild)
        print(node.elem, end=" ")
        self.inorder_travel(node.rchild)

    def postorder_travel(self, node):
        """先序遍历"""
        if node is None:
            return
        self.postorder_travel(node.lchild)
        self.postorder_travel(node.rchild)
        print(node.elem, end=" ")


if __name__ == "__main__":
    tree = Tree()
    tree.add(0)
    tree.add(1)
    tree.add(2)
    tree.add(3)
    tree.add(4)
    tree.add(5)
    tree.add(6)
    tree.add(7)
    tree.add(8)
    tree.add(9)
    tree.breadth_travel()
    print(" ")
    tree.preorder_travel(tree.root)
    print(" ")
    tree.inorder_travel(tree.root)
    print(" ")
    tree.postorder_travel(tree.root)
