import java.util.ArrayList;
import java.util.Comparator;
import java.util.Iterator;

/**
* A class to represent a Max Heap
*  by using an ArrayList. The heap is structured
*  so that the "largest" item is at the top.
* @author Emine Sultan Savran
* @param <E> generic type which that extends Comparable interface
*/
public class MaxHeap<E extends Comparable<E>>{

	// Data Fields
	/** The ArrayList to hold the data. */
	private ArrayList< Node<E> > heap;
    /** An optional reference to a Comparator object. */
	Comparator<E> comparator = null;
	
	// Methods
	/** Default Constructor */
	MaxHeap(){
		heap = new ArrayList< Node<E> >();
	}

	/** 
	* To return the size of the Max-Heap 
	*	@return the size of the Max-Heap
	*/
	public int size(){
		return heap.size();
	}
	
	/**
	* To return a value in a given index as an E
	* @param index Index of the value
	* @return The value if there is the value
	*		  null if there is no the value
	* @throws IndexOutOfBoundsException if index is not valid
	*/
	public E get(int index){
		try {
			if(heap.size() > 0){
				return heap.get(index).getValue();
			}
			return null;
		}
		catch(IndexOutOfBoundsException  e) {
			System.out.println("WARNING: The index value is not valid.");
			return null;
		}
	}

	/**
	* To return a value in a given index as a Node<E>
	* @param index Index of the value
	* @param ignore To overload the function
	* @return The value if there is the value
	*		  null if there is no the value
	* @throws IndexOutOfBoundsException if index is not valid
	*/
	public Node<E> get(int index, int ignore){
		try {
			return heap.get(index);
		}
		catch(IndexOutOfBoundsException  e) {
			System.out.println("WARNING: The index value is not valid.");
			return null;
		}
	}

    /**
    * To return the MaxHeapIter which is the iterator of Max-Heap
    * @return the iterator of Max-Heap
    */
	public MaxHeapIter iterator(){
		return new MaxHeapIter();
	}

	/**
    * Insert an item into the Max-Heap.
    * @param value The item to be inserted
    * @throws NullPointerException if the item to be inserted is null.
    */
	public void insert(E value){
		if( value == null ){
			return;
		}
		Node<E> nodeValue = new Node<E>(value);
		heap.add(nodeValue);
		int child = heap.size() - 1;
		int parent = (child - 1) / 2;
		compareToParent(parent, child);
	}

	/**
	* The function was written for BSTMaxHeap which uses Max-Heap as a component
    * Insert an item into the Max-Heap.
    * Increases the occurrence instead of adding an already existing element
    * @param index Index of the adding element
    * @throws IndexOutOfBoundsException if the index is not valid
    */
	protected void add(int index){
		try {
			heap.get(index).increaseOccurence();
		}
		catch(IndexOutOfBoundsException  e) {
			System.out.println("WARNING: The index value is not valid.");
		}
	}

	/**
    * Remove an item from the Max-Heap.
    * @throws NullPointerException if the item to be deleted is null.
    */	
    public void remove(){
		remove(0, 0);
	}

	/**
    * Swap two elements at the Max-Heap.
    * @param value1 The first item
    * @param value2 The second item
    */
	private void swap(int value1, int value2){
		Node<E> temp = heap.get(value1);
		heap.set(value1, heap.get(value2));
		heap.set(value2, temp);	
	}

	/**
    * Compare two elements at the Max-Heap.
    * @param left The first item
	* @param right The second item
	* @return Negative int if left less than right,
    *         0 if left equals right,
    *         positive int if left > right
    * @throws ClassCastException if items are not Comparable
    */
	private int compare(E left, E right){
		if( comparator != null ){
			return comparator.compare(left, right);
		} else{
			return ((Comparable<E>)left).compareTo(right);
		}
	}

	/**
    * Searching the element at the Max-Heap.
    * @param value The item
	* @return Negative int if there is no the element or the heap is empty
    *         positive int if there is the element
    */
	public int search(E value){
		return search(value, 0);
	}

	/**
    * Searching the element at the Max-Heap.
    * @param value The item
    * @param ignore to overload
	* @return Negative int if there is no the element or the heap is empty
    *         positive int if there is the element
    */
	protected int search(E value, int ignore){
		if( heap.size() == 0 ){
			if( ignore == 0 ){
				System.out.println("WARNING: The Heap is empty.");
			}
			return -1;
		}
		Node<E> nodeValue = new Node<E>(value);
		return heap.indexOf(nodeValue);
	}
	/**
    * Merge with another Max-Heap.
    * @param anotherHeap another heap
    */
	public void merge(MaxHeap<E> anotherHeap){
		for(int i=0; i<anotherHeap.size(); i++){
			this.insert(anotherHeap.get(i));
		}
	}

	/**
    * Removing ith largest element from the Max-Heap
    * @param ith ith largest element
    * @return removed element
    * @throws IndexOutOfBoundsException if the ith is not valid
    */	
    public E removeIthLargest(int ith){
		try {
			ArrayList< Node<E> > temp = new ArrayList< Node<E> >(heap);
			int index = findingIthLargest(temp, ith-1);
			return remove(index,0);		
		} catch(IndexOutOfBoundsException  e) {
			System.out.println("WARNING: The ith value is not valid.");
			return null;
		}
	}

	/**
	* Helper function
    * Sorting the Heap and finding ith largest element at the Max-Heap
    * @param temp the Max-Heap to will be sorted
    * @param ith ith largest element
    * @return index of the ith largest element
    */
	private int findingIthLargest(ArrayList< Node<E> > temp, int ith){
		for (int i = 0; i < temp.size(); i++) {
          	for (int j = temp.size() - 1; j > i; j--) {
              	if (compare(temp.get(i).getValue(), temp.get(j).getValue()) < 0 ) {
                	Node<E> tmp = temp.get(i);
                	temp.set(i,temp.get(j)) ;
                	temp.set(j,tmp);
            	}
        	}
    	}
		Node<E> ithLargest = temp.get(ith);
		return heap.indexOf(ithLargest);
	}

	/**
	* Compares the child with its parent if the condition is true, makes changes
	* @param parent The index of parent
	* @param child The index of child
	*/
	private void compareToParent(int parent, int child){
		//and change the value
		while( parent >= 0 && compare(heap.get(parent).getValue(), heap.get(child).getValue()) < 0 ){
			swap(parent, child);
			child = parent;
			parent = (child - 1) / 2;
		}
	}

	/**
	* Compares parent with its children if the condition is true, makes changes
	* @param parent The index of parent
	*/
	private void compareToChild(int parent){
		//and change the value
		while( true ){
			int leftChild = 2 * parent + 1;
			if( leftChild >= heap.size() ){
				break;
			}
			int rightChild = leftChild + 1;
			int maxChild = leftChild;
			if( rightChild < heap.size() 
				&& compare(heap.get(leftChild).getValue(), heap.get(rightChild).getValue()) < 0 ){
				maxChild = rightChild;
			} 
			if( compare(heap.get(parent).getValue(), heap.get(maxChild).getValue()) < 0 ){
				swap(parent, maxChild);
				parent = maxChild;
			} else{
				break;
			}
		}
	}

	/**
	* Deletes a value in a specific index
	* @param index the index of the item will be deleted
	* @throws IndexOutOfBoundsException If the index value is not valid
	* @throws NullPointerException If there is null
	*/
	protected E remove(int index, int ignore){
		try {
			Node<E> last = heap.remove(heap.size() - 1);
			E removed = heap.get(index).getValue();
			heap.set(index, last);
			compareToChild(index);
			return removed;		
		} catch(IndexOutOfBoundsException  e) {
			if( ignore == 0 )
				System.out.println("WARNING: Index is not valid. Cannot deleted.");
			//heap = null;//emin değilim
			return null;
		} catch(NullPointerException  e) {
			if( ignore == 0 )
				System.out.println("WARNING: There is no element.");
			//heap = null;//emin değilim
			return null;
		}
	}

	/**
	* Insert a value to a specific index
	* @param index the index 
	* @param value The item
	*/
	private void insert(int index, E value){
		Node<E> nodeValue = new Node<E>(value);
		heap.add(index, nodeValue);
		compareToParent(0, index);
		compareToChild(index);
	}

	/**
	* Print the Max-Heap
	* @return the Max-Heap
	*/
	@Override
	public String toString(){
		if( heap == null )
			return null;
		return heap.toString();
	}

	/**
	* The function was written for BSTMaxHeap which uses Max-Heap as a component
    * Print the Max-Heap with occurrence
    * @return the Max-Heap
  	*/
	protected String toStringBST(){
		if( heap == null )
			return null;
		String output = "";
		for(int i=0; i<heap.size(); i++){
			output += heap.get(i).toStringBST();
			if( i < heap.size()-1 ){
				output += ", ";
			}
		}
		return output;
	}

	/**
	* A protected class to represent MaxHeapIter
	* implements Iterator<E>.
	*/
	protected class MaxHeapIter implements Iterator<E>{

		//Data fields
		/**To hold the where the iterator*/
		private int cursor;

		//Methods
		/**Default constructor*/
		MaxHeapIter(){
			cursor = 0;
		}

		/**
		* Returns whether the iterator has next element
		* @return true if the iterator has next element
		*		  false if the iterator does not has
		*/
		public boolean hasNext(){
			return heap.size()>cursor;
		}

		/**
		* Returns next element
		* @return next element
		*/
		public E next(){
			try{
				return heap.get(cursor++).getValue();
			} catch(Exception e){
				System.out.println("Cannot next operation.");
				return null;
			}
		}

		/**
		* Remove the item which is returned by next()
		*/
		public void remove(){
			MaxHeap.this.remove(--cursor, 0);
			cursor = 0;
		}

		/**
		* to set the value (value passed as parameter) of 
		* the last element returned by the next methods.
		*/
		public void set(E value){
			try{
				heap.remove(cursor-1);
				insert(cursor-1, value);
			} catch(Exception e){
				System.out.println("Cannot setting.");
			}
		}
	}

	/**
	* A protected class to represent Node<E>
	* implements Comparable<E>.
	* @param <E> generic type which that extends Comparable interface
	*/
	protected static class Node<E extends Comparable<E>> implements Comparable<E> {

		//Data fields
		/**To hold the data*/
		private E value;
		/**To hold the data's occurrence*/
		private int occurrence;
		
		//Methods
		/**
		* Constructor
		* @param valueItem the data
		*/
		public Node(E valueItem) {
			value = valueItem;
			occurrence = 1;
		}

		/**
		* getting the value
		* @return the value
		*/
		public E getValue(){
			return value;
		}

		/**
		* Setting the value
		* @param value the value
		*/
		public void setValue(E value){
			this.value = value;
		}

		/**
		* getting the occurrence
		* @return the occurrence
		*/
		public int getOccurrence(){
			return occurrence;
		}

		/**Increasing the occurrence*/
		public void increaseOccurence(){
			occurrence++;
		}

		/**Decreasing the occurrence*/
		public void decreaseOccurence(){
			occurrence--;
		}

		/**
		* Comparing objects
		* @param o the object
		* @return Negative int if there is no the element or the heap is empty
	    *         positive int if there is the element		
	    */
		public int compareTo(E o){
			if(this.value.compareTo(o) > 0) return 1; 
		    if(this.value.compareTo(o) < 0) return -1;
		    else	return 0;
		}

		/**
		* To print the value without occurrence
		* @return the value
		*/
		@Override
		public String toString(){
			if (value == null) {
           		return "null";
	        } else {
				return value.toString();
			}
		}
		
		/**
		* The function was written for BSTMaxHeap which uses Max-Heap as a component
	    * Print the value with occurrence
	    * @return the value
	  	*/
		public String toStringBST(){
			if (value == null) {
           		return "null";
           	}
			return "("+value+","+occurrence+") ";
		}

		/**
		* Check whether objects are equals
		* @param o the object
		* @return if same, true
		*		  not, false
		*/
		@Override
		public boolean equals(Object o) {
			if( o == this )
				return true;
			if( o == null )
				return false;
			if( o.getClass() != getClass() )
				return false;
			try{
				Node mo = (Node)o;
	    		return mo.value.equals(value);
			} catch(Exception e){
				System.out.println("There is some problems");
				return false;
			}
		}
	}
}
