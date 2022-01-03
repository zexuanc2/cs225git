/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    ListNode* head_ = NULL;
    ListNode* tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1


  return head_;
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return NULL;
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  if (length_ == 0) {
    return;
  }
  while (head_ != NULL) {
    ListNode * headnext = head_->next;
    delete head_;
    head_ = headnext;
  }
  head_ = NULL;
  tail_ = NULL;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
	if (length_ == 0) {
    tail_ = newNode;
    head_ = newNode;
    length_ = 1;
    return;
  }
  head_->prev = newNode;
  newNode->next = head_;
	newNode->prev = NULL;
  head_ = newNode;
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode* newTail = new ListNode(ndata);
  if (length_ == 0) {
    head_ = newTail;
    tail_ = newTail;
    length_ = 1;
    return;

  }
  newTail -> prev = tail_;
  tail_ -> next = newTail;
  tail_ = newTail;
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  if (start == NULL) {
    return NULL;
  }
  if (length_ < splitPoint) {
    return NULL;
  }
  if (splitPoint < 1) {
    return start;
  }
 
  ListNode * curr = start;

  for (int i = 0; i < splitPoint-1 && curr != NULL; i++) {
    if (curr->next != NULL) {
      curr = curr->next;
    }
    
  }

  if (curr != NULL) {
    curr = curr->next;
    curr->prev->next = NULL;
    tail_ = curr->prev;
    curr->prev = NULL;
    return curr;
  }

  return NULL;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  ListNode * a;
  ListNode * b;
  ListNode * c;
  ListNode * curr;
  curr = head_;
  while (curr != NULL) {
    a = curr;
    if (a -> next== NULL) {
      break;
    } else {
      b = a -> next;
    }
    if (b -> next == NULL) {
      break;
    } else {
      c = b -> next;
    }
    if (a == head_) {
      head_ = b;
    }
    if (c == tail_) {
      tail_ = a;
    }
    b -> prev = a -> prev;
    if (b -> prev != NULL) {
      b -> prev -> next = b;
    }
    a -> next = c -> next;
    if (a -> next != NULL) {
      a -> next -> prev = a;
    }
    a -> prev = c;
    c -> next = a;
    curr = a -> next;
  }
  
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  if (startPoint == endPoint) {
    return;
  }
  ListNode* temp = nullptr;
  ListNode* curr = startPoint;
  ListNode* oldStart = startPoint;
  ListNode* oldPrev = startPoint->prev;
  ListNode* oldEnd = endPoint;
  ListNode* oldNext = endPoint->next;
  while(curr != endPoint) {
    temp = curr->prev;
    curr->prev = curr->next;
    curr->next = temp;
    curr = curr->prev;
  }
  endPoint = oldStart;
  endPoint->next = oldNext;
  temp = curr->prev;
  curr->prev = oldPrev;
  curr->next = temp;
  

  if(oldPrev == nullptr){
    head_ = curr;
  } else {
    oldPrev->next = oldEnd;
  }
  if(oldNext == nullptr) {
    tail_ = oldStart;
  } else {
    oldNext->prev = oldStart;
  }

}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  if(length_ == 0 || length_ == 1) return;
  ListNode *startPoint = head_;
  ListNode *endPoint = head_;

  while (endPoint != nullptr){
    for (int i = 0; i < n - 1; i++) {
      if (endPoint->next == nullptr){
        reverse(startPoint, endPoint);
        return;
      }
      endPoint = endPoint->next;
    }
    reverse(startPoint, endPoint);
    if (endPoint->next == nullptr) return;
    else {
      startPoint = endPoint->next;
      endPoint = startPoint;
    }
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  ListNode* newHead;
  if (first->data < second->data) {
    newHead = first;
    first = first->next;
  } else {
    newHead = second;
    second = second->next;
  }
  ListNode* curr = newHead;
  while (first != NULL && second != NULL) {
    if (first->data < second->data) {
      curr->next = first;
      first->prev = curr;
      first = first->next;
    } else {
      curr->next = second;
      second->prev = curr;
      second = second->next;
    }
    curr = curr->next;
  }
  if (first != nullptr) curr->next = first;
  if (second != nullptr) curr->next = second;

  return newHead; 
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (chainLength == 0 || chainLength == 1) {
    return start;
  }
  ListNode* left = start;
  ListNode* right = split(start, chainLength/2);
  left = mergesort(left,chainLength/2);
  right = mergesort(right,chainLength - chainLength/2);
  return merge(left,right);
}
