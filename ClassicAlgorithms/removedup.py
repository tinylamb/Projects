#!/bin/env python
#coding=utf-8
import random
class Node():
    def __init__(self, data = None, next = None):
        self.data = data
        self.next = next
    def __str__(self):
        return str(self.data)

class Linked():
    def __init__(self):
        self.length = 0
        self.head = None
    def printList(self):
        h = self.head
        while(h):
            print h.data,
            h = h.next
        print
    def addFirst(self,data): # 在头节点添加Node
        node = Node(data)
        node.next = self.head
        self.head = node
        self.length += 1
    def rmdup(self):
        if self.head == None:
            return
        hashmap = {}
        p = self.head
        q = self.head.next
        hashmap[p.data] = 1
        while(q):
            if(hashmap.get(q.data,0)):
                p.next = q.next
                q = p.next
            else:
                hashmap[q.data] = 1
                p = q
                q = q.next

def main():
    l = Linked()
    for i in range(10):
        l.addFirst(random.randint(0,10))
    l.printList()
    l.rmdup()
    l.printList()

if __name__ == '__main__':
    main()


