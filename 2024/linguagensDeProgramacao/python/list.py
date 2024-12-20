class ConsCell:
  def __init__(self, h, t):
    """Creates a new cell with head == h, and tail == t."""
    self.head = h
    self.tail = t

class List:
  """Describes a simple list data type."""

  def __init__(self, n):
    """creates a new list with n as the first element."""
    self.start = n

  def cons(self, e):
    """Adds a new element into the list; hence, procuding a new list."""
    return List(ConsCell(e, self.start))

  def length(self):
    """Returns the number of elements in the list."""
    len = 0
    cell = self.start
    while cell != 0:
       len += 1
       cell = cell.tail
    return len
  
  def contains(self, x):
    cell = self.start

    while cell != 0:
        if cell.head == x: return True
        cell = cell.tail

    return False
  
  def equals(self, y):
    cellx = self.start
    celly = y.start

    while (cellx != 0 and celly !=0):
        if cellx.head != celly.head: return False
        cellx = cellx.tail
        celly = celly.tail
  
    return cellx == celly
  
  def copy(self):
    
  
    def append(self, y):
        """Appends another list y to the end of this list."""
        if self.start == 0:
            return y.copy()  # If the current list is empty, return a copy of y

        # Create a deep copy of the current list
        x = self.copy()
        cellx = x.start

        # Navigate to the last cell of the copied list
        while cellx.tail != 0:
            cellx = cellx.tail

        # Append a deep copy of y to the end of the copied list
        cellx.tail = y.copy().start
        return x



  def __str__(self):
    """Returns a textual representation of this list."""
    ans = "["
    cell = self.start
    while cell != 0:
      ans = ans + repr(cell.head)
      cell = cell.tail
      if cell != 0:
        ans = ans + ", "
    ans = ans + "]"
    return ans

def test():
  a = List(0)
  b = a.cons(2)
  c = b.cons("Hi!")
  d = b.cons(True)
  e = d.cons(False)

  print ("List a = ", a.__str__(), " Length(a) = ", a.length())
  print ("List b = ", b.__str__(), " Length(b) = ", b.length())
  print ("List c = ", c.__str__(), " Length(c) = ", c.length())
  print ("List d = ", d.__str__(), " Length(d) = ", d.length())
  print ("List e = ", e.__str__(), " Length(e) = ", e.length())

  x = e.append(b)
  print ("List x = e.append(b) ", x.__str__(), " Length(x) = ", x.length())

test()