import java.util.*;
/** Class KWLinkedList implements a double‐linked list and
 a ListIterator. */
public class KWLinkedList<E> {
	// Data Fields
	/** A reference to the head of the list. */
	private Node<E> head = null;
	/** A reference to the end of the list. */
	private Node<E> tail = null;
	/** The size of the list. */
	private int size = 0;
	
	public ListIterator<E> listIterator(){
		return new KWListIter(0);
	}

	public ListIterator<E> listIterator(int index){
		return new KWListIter(index);
	}

	//private KWListIter listIterator 
	/** Add an item at position index.
	 @param index The position at which the object is to be
	 inserted
	 @param obj The object to be inserted
	 @throws IndexOutOfBoundsException if the index is out
	 of range (i < 0 || i > size())
	 */
	public void add(int index, E obj) {
		listIterator(index).add(obj);
	}
	public boolean add(E obj){
		add(size, obj);
		return true;
	}
	
	public E remove(int index){
		ListIterator<E> itr = listIterator(index);
		E removed = get(index);
		itr.next();
		itr.remove();
		return removed;
	}

	public E remove(){
		if( size == 0 ){
			System.out.println("There is no element to delete");
			return null;
		}
		E temp = remove(size);
		return temp;
	}

	public E remove(Object o){
		int index = indexOf(o);
		if( index != -1 ){
			E temp = remove(indexOf(o));
			return temp;
		}
		return null;
	}
	
	/** Get the element at position index.
	 @param index Position of item to be retrieved
	 @return The item at index
	 */
	public E get(int index) {
		return listIterator(index).next();
	}

	public void addFirst(E item) {
		add(0, item);
	}

	public void addLast(E item) {
		add(size, item);
	}

	public E getFirst() {
		return head.data;
	}

	public E getLast() {
		return tail.data;
	}

	public int indexOf(Object o){
		ListIterator<E> itr = listIterator();
		int i = 0,
			temp = 0;
		if (o == null) {
            while ( itr.hasNext() ){
                if (itr.next()==null)
	                return i;
    			i++;
            }
        } else {
            while ( itr.hasNext() ){
                if (o.equals(itr.next()))
                    return i;
                i++;	
            }
        }
        return -1;
	}

    public boolean contains(Object o) {
        return indexOf(o) >= 0;
    }

    public int size(){
    	return size;
    }

	/** Inner class to implement the ListIterator interface. */
	private class KWListIter implements ListIterator<E> {
		 /** A reference to the next item. */
		private Node<E> nextItem;
		 /** A reference to the last item returned. */
		private Node<E> lastItemReturned;
		 /** The index of the current item. */
		private int index = 0;
		/** Construct a KWListIter that will reference the ith item.
		@param i The index of the item to be referenced
		*/
		public KWListIter(int i) {
		 // Validate i parameter.
			if (i < 0 || i > size) {
				throw new IndexOutOfBoundsException("Invalid index " + i);
			}
			lastItemReturned = null; // No item returned yet.
			 // Special case of last item.
			if (i == size) {
				index = size;
				nextItem = null;
			} else { // Start at the beginning
				nextItem = head;
				for (index = 0; index < i; index++) {
					nextItem = nextItem.next;
				}
			}
		}
		/** Indicate whether movement forward is defined.
		 @return true if call to next will not throw an exception
		*/
		public boolean hasNext() {
			return nextItem != null;
		}

		/** Move the iterator forward and return the next item.
		 @return The next item in the list
		 @throws NoSuchElementException if there is no such object
		*/
		public E next() {
			if (!hasNext()) {
				throw new NoSuchElementException("There is no next element");
			}
			lastItemReturned = nextItem;
			nextItem = nextItem.next;
			index++;
			return lastItemReturned.data;
		}

		public int nextIndex(){
			return index;
		}

		public boolean hasPrevious() {
			return (nextItem == null && size != 0) || nextItem.prev != null;
		}

		public E previous() {
			if (!hasPrevious()) {
				throw new NoSuchElementException();
			}
			if (nextItem == null) { // Iterator past the last element
				nextItem = tail;
			}
			else {
				nextItem = nextItem.prev;
			}
			lastItemReturned = nextItem;
			index--;
			return lastItemReturned.data;
		}

		public int previousIndex(){
			return index-1;
		}

		public void add(E obj){
			if (head == null) {
				head = new Node<E>(obj);
				tail = head;
			} else if (nextItem == head) {
				Node<E> newNode = new Node<E>(obj);
				newNode.next = nextItem;
				nextItem.prev = newNode;
				head = newNode;
			} else if (nextItem == null) {
				Node<E> newNode = new Node<E>(obj);
				tail.next = newNode;
				newNode.prev = tail;
				tail = newNode;
			} else {
				Node<E> newNode = new Node<E>(obj);
				newNode.prev = nextItem.prev;
				nextItem.prev.next = newNode;
				newNode.next = nextItem;
				nextItem.prev = newNode;
			}
			lastItemReturned = null;
			size++;
			index++;
		}

		public void set(E obj){
			if (lastItemReturned == null)
                throw new IllegalStateException();
            lastItemReturned.data = obj;
		}

		public void remove(){
			if (head == null) {
				//no element
                throw new IllegalStateException("There is no element");
			} else if( size==1 ){
				head = null;
			} else if (lastItemReturned == head) {//first element
				head = lastItemReturned.next;
				lastItemReturned = null;
				head.prev = null;
			} else if (nextItem == null) {
			//	lastItemReturned.prev = null;
				tail = lastItemReturned.prev;
				lastItemReturned = null;
			} else {
				lastItemReturned.prev.next = nextItem;
				nextItem.prev = lastItemReturned.prev;
				lastItemReturned = null;
			}
			size--;
			index--;
		}
	}


	/** A Node is the building block for a double‐linked list. */
	private static class Node<E> {
		 /** The data value. */
		private E data;
		 /** The link to the next node. */
		private Node<E> next = null;
		 /** The link to the previous node. */
		private Node<E> prev = null;
		 /** Construct a node with the given data value.
		 @param dataItem The data value
		 */
		private Node(E dataItem) {
			data = dataItem;
		}
		/** Creates a new node that references another node.
		@param dataItem The data stored
		@param nodeRef The node referenced by new node
		*/
		private Node(E dataItem, Node<E> nodeRef) {
			data = dataItem;
			next = nodeRef;
		}
	}
}

