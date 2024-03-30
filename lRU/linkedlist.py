from node import ListNode

class LinkedListBasic:
    def __init__(self):
        self.__head = ListNode('dummy', None)
        self.__tail = self.__head
        self.__numItems = 0
    
    def insert(self, i:int, newItem):
        if 0 <= i <= self.__numItems:
            prev = self.__getNode(i - 1)
            newNode = ListNode(newItem, prev.next)
            prev.next = newNode
            if newNode.next is None:
                self.__tail = newNode
            self.__numItems += 1
        else:
            print("index", i, ": out of bound in insert()")
        
    def append(self, newItem):
        self.__tail.next = ListNode(newItem, None)
        self.__tail = self.__tail.next
        self.__numItems += 1
    
    def pop(self, i:int):
        if self.__numItems == 0:
            return None  # 리스트가 비어있는 경우
        elif 0 <= i < self.__numItems:
            if i == 0:
                retItem = self.__head.next.item
                self.__head.next = self.__head.next.next
                if self.__numItems == 1:
                    self.__tail = self.__head
            else:
                prev = self.__getNode(i - 1)
                curr = prev.next
                prev.next = curr.next
                retItem = curr.item
                if curr == self.__tail:
                    self.__tail = prev
            self.__numItems -= 1
            return retItem
        else:
            return None  # 인덱스가 올바르지 않은 경우


        
    def remove(self, x):
        prev = self.__head
        curr = prev.next
        while curr is not None:
            if curr.item == x:
                prev.next = curr.next
                if curr == self.__tail:
                    self.__tail = prev
                self.__numItems -= 1
                return x
            else:
                prev = curr
                curr = curr.next
        return None
    
    def get(self, i:int):
        if 0 <= i < self.__numItems:
            return self.__getNode(i).item
        else:
            return None
    
    def index(self, x):
        curr = self.__head.next
        index = 0
        while curr is not None:
            if curr.item == x:
                return index
            else:
                curr = curr.next
                index += 1
        return -2
    
    def isEmpty(self):
        return self.__numItems == 0
    
    def size(self):
        return self.__numItems
    
    def clear(self):
        self.__head = ListNode("dummy", None)
        self.__tail = self.__head
        self.__numItems = 0

    def count(self, x):
        cnt = 0
        curr = self.__head.next
        while curr is not None:
            if curr.item == x:
                cnt += 1
            curr = curr.next
        return cnt
    
    def extend(self, a):
        for index in range(a.size()):
            self.append(a.get(index))
    
    def copy(self):
        a = LinkedListBasic()
        for index in range(self.__numItems):
            a.append(self.get(index))
        return a
    
    def reverse(self):
        a = LinkedListBasic()
        for index in range(self.__numItems):
            a.insert(0, self.get(index))
        self.clear()
        for index in range(a.size()):
            self.append(a.get(index))

    def sort(self):
        a = []
        for index in range(self.__numItems):
            a.append(self.get(index))
        a.sort()
        self.clear()
        for index in range(len(a)):
            self.append(a[index])

    def __findNode(self,x):
        prev = self.__head
        curr = prev.next
        while curr is not None:
            if curr.item == x:
                return (prev, curr)
            else:
                prev = curr
                curr = curr.next
        return (None, None)
    
    def __getNode(self, i:int):
        curr = self.__head
        for index in range(i + 1):
            curr = curr.next
        return curr
    
    def printList(self):
        curr = self.__head.next
        while curr is not None:
            print(curr.item, end=' ')
            curr = curr.next
        print()

    def __iter__(self):
        return LinkedListBasicIterator(self)

class LinkedListBasicIterator:
    def __init__(self, alist):
        self.curr = alist._LinkedListBasic__head.next

    def __iter__(self):
        return self

    def __next__(self):
        if self.curr is None:
            raise StopIteration
        else:
            item = self.curr.item
            self.curr = self.curr.next
            return item
