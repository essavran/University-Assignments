import java.util.*;
/** This class implements some of the methods of the Java ArrayList class. It
 does not implement the List interface.
*/
public class KWArrayList<E>{
	// Data Fields
	 /** The default initial capacity */
	private static final int INITIAL_CAPACITY = 10;
	 /** The underlying data array */
	private E[] theData;
	 /** The current size */
	private int size = 0;
	 /** The current capacity */
	private int capacity = 0;
	/**constructor of KWArrayList*/
	public KWArrayList() {
		capacity = INITIAL_CAPACITY;
		theData = (E[]) new Object[capacity];
	}
	/**return size of KWArrayList*/
	public int size(){
		return size;
	}

	public E get (int index) {
		if (index < 0 || index >= size) {
			throw new ArrayIndexOutOfBoundsException(index);
		} 
		return theData[index];
	}

	public E set (int index, E newValue) {
		if (index < 0 || index >= size) {
			throw new ArrayIndexOutOfBoundsException(index);
		}
			E oldValue = theData[index];
			theData[index] = newValue;
		return oldValue;
	}

	public boolean add(E anEntry) {
		if (size == capacity) {
			reallocate();
		}
		theData[size] = anEntry;
		size++;
		return true;
	}

	public void add(int index, E anEntry) {
		if (index < 0 || index > size) {
			throw new ArrayIndexOutOfBoundsException(index);
		}
		if (size == capacity) {
			reallocate();
		}
		// Shift data in elements from index to size ‐ 1
		for (int i = size; i > index; i--) {
			theData[i] = theData[i - 1];
		}
		 // Insert the new item.
		theData[index] = anEntry;
		size++;
	}

	public E remove(int index) {
		if (index < 0 || index >= size) {
			throw new ArrayIndexOutOfBoundsException(index);
		}
		E returnValue = theData[index];
		for (int i = index + 1; i < size; i++) {
			theData[i - 1] = theData[i];
		}
		size--;
		return returnValue;
	}

	public boolean remove(Object o) {
        if (o == null) {
            for (int index = 0; index < size; index++){
                if (theData[index] == null) {
                    remove(index);
                    return true;
                }	
            }

        } else {
            for (int index = 0; index < size; index++){
            	if (o.equals(theData[index])) {
                    remove(index);
                    return true;
                }
            }
        }
        return false;
    }

	private void reallocate() {
		capacity = 2 * capacity;
		theData = Arrays.copyOf(theData, capacity);
	}

	public int indexOf(Object o) {
        if (o == null) {
            for (int i = 0; i < size; i++){
                if (theData[i]==null)
                    return i;
            }
        } else {
            for (int i = 0; i < size; i++){
                if (o.equals(theData[i]))
                    return i;
            }
        }
        return -1;
    }

    public boolean contains(Object o) {
        return indexOf(o) >= 0;
    }
}