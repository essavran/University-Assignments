package HW7;

import java.util.Arrays;
import java.util.Random;
import java.util.NavigableSet;
import java.util.Iterator;
import java.util.SortedSet;
import java.util.Comparator;
import java.util.Collection;
import java.util.Collections;
import java.util.ArrayList;
import java.util.TreeSet;

public class SkipList<E extends Comparable<E>> implements NavigableSet<E>{

	/** Static class to contain the data and the links */
	static class SLNode<E> {
		SLNode<E>[] links;
		E data;
		/** Create a node of level m */
		SLNode (int m, E data) {
			links = (SLNode<E>[]) new SLNode[m]; // create links
			this.data = data; // store item
		}

		public String toString(){
			return (data.toString() + " |" + links.length + "|");
		}
	}
	
	//Data fields
	public SLNode<E> head;
	private int size;
	private int maxLevel;
	private int maxCap;
	/** Natural Log of 2 */
	static final double LOG2 = Math.log(2.0);
	static final int MIN = Integer.MIN_VALUE;
	private Random rand = new Random();

	//Methods 
	@SuppressWarnings({"unchecked","rawtypes"})
	public SkipList(){
		size = 0;
		maxLevel = 0;
		maxCap = computeMaxCap(maxLevel);
		head = new SLNode(maxLevel, MIN);
	}

	@SuppressWarnings("unchecked")
	/** Search for an item in the list
	@param item The item being sought
	@return A SLNode array which references the predecessors
	of the target at each level.
	*/
	private SLNode<E>[] search (E target) {
		SLNode<E>[] pred = (SLNode<E>[]) new SLNode[maxLevel];
		SLNode<E> current = head;
		for (int i = current.links.length-1; i >= 0; i--) {
			while (current.links[i] != null && current.links[i].data.compareTo(target) < 0) {
				current = current.links[i];
			}
			pred[i] = current;
		}
		return pred;
	}

	/** Find an object in the skip‐list
	@param target The item being sought
	@return A reference to the object in the skip‐list that matches
	the target. If not found, null is returned.
	*/
	public E find(E target) {
		SLNode<E>[] pred = search(target);
		if (pred[0].links[0] != null && pred[0].links[0].data.compareTo(target) == 0) {
			return pred[0].links[0].data;
		} else {
			return null;
		}
	}
	
	/** Method to generate a logarithmic distributed integer between
	1 and maxLevel. i.e., 1/2 of the values returned are 1, 1/4
	are 2, 1/8 are 3, etc.
	@return a random logarithmic distributed int between 1 and
	maxLevel
	*/
	private int logRandom() {
		int r = rand.nextInt(maxCap);
		int k = (int) (Math.log(r + 1) / LOG2);
		if (k > maxLevel - 1) {
			k = maxLevel - 1;
		}
		return maxLevel - k;
	}

	private int computeMaxCap(int level){
		return (int)Math.pow(2, level) - 1;
	}

	@SuppressWarnings("rawtypes")
	public String toString(){
		if(size == 0){
			return "Empty";
		}
		StringBuilder sc = new StringBuilder();
		SLNode itr = head;
		sc.append("Head: " + maxLevel);
		int lineMaker = 0;
		while(itr.links[0] != null){
			itr = itr.links[0];
			sc.append(" ---> " + itr.toString());
			lineMaker++;
			if(lineMaker == 10){
				sc.append("\n");
				lineMaker = 0;
			}
		}
		return sc.toString();
	}
//-----------------------------------
	public boolean add(E item){
		size++;
		SLNode<E>[] pred = search(item);
		if (size > maxCap) {
			maxLevel++;
			maxCap = computeMaxCap(maxLevel);
			head.links = Arrays.copyOf(head.links, maxLevel);
			pred = Arrays.copyOf(pred, maxLevel);
			pred[maxLevel - 1] = head;
		}
		SLNode<E> newNode = new SLNode<E>(logRandom(), item);
		for(int i=0; i<newNode.links.length; i++){
			newNode.links[i] = pred[i].links[i];
			pred[i].links[i] = newNode;
		}
		return true;
	}

	private boolean removeSL(E item){
		SLNode<E>[] pred = search(item);
	//	System.out.println(pred[0] + "      ...  " + pred[0].links[0].data);
		if(pred[0] == null || pred[0].links[0] == null || pred[0].links[0].data == null){
			return false;
		}
		if(pred[0].links != null && pred[0].links[0].data.compareTo(item) != 0){
			return false;//item is not in the list
		} else{
			size--;
			SLNode<E> deleteNode = pred[0];
			for(int i=0; i<deleteNode.links.length; i++){
				if(pred[i].links[i] != null){
					pred[i].links[i] = pred[i].links[i].links[i];
				}
			}
			return true;
		}
	}

	public boolean remove(Object o){
		
		return removeSL((E)o);
	}

	public Iterator<E> descendingIterator(){
		return new descendingIteratorSkipList(head);	
	}

/** Inner class to implement the Iterator interface. */
	private class descendingIteratorSkipList implements Iterator<E> {
	    private ArrayList<E> values;
	    private Iterator<E> iterator;
	    private int cursor;
	    public descendingIteratorSkipList(SLNode<E> head) {
	    	SLNode<E> current = head;
	    	values = new ArrayList<>();

			SLNode<E> itr = head;
			while(itr.links[0] != null){
				values.add(itr.links[0].data);
				itr = itr.links[0];
			}
			Collections.sort(values, Collections.reverseOrder());		
			iterator = values.iterator();
			//System.out.println(values);
			cursor = 0;
	    }

	    public E next() {
	    	cursor++;
			return iterator.next();	    
		}

	    public boolean hasNext() {
			return iterator.hasNext();	    
	    }

	    public void remove(){
	    	removeSL((E)values.get(--cursor));
			iterator.remove();
	    }
	}
	
	/*Returns a view of the portion of this set whose elements are less than (or equal to, if inclusive is true) toElement.*/
	public NavigableSet<E> headSet(E toElement, boolean inclusive){
		throw new UnsupportedOperationException("Invalid operation");
	}

	public SortedSet<E> headSet(E toElement){
		throw new UnsupportedOperationException("Invalid operation");
	}

	public NavigableSet<E> tailSet(E fromElement, boolean inclusive){
		throw new UnsupportedOperationException("Invalid operation");
	}
	
	public SortedSet<E> tailSet(E fromElement){
		throw new UnsupportedOperationException("Invalid operation");
	}


	public Iterator<E> iterator(){
		throw new UnsupportedOperationException("Invalid operation");
	}

	public E ceiling(E e){
		throw new UnsupportedOperationException("Invalid operation");
	}

	public NavigableSet<E> descendingSet(){
		throw new UnsupportedOperationException("Invalid operation");
	}

	public E pollFirst(){
		throw new UnsupportedOperationException("Invalid operation");
	}

	public E pollLast(){
		throw new UnsupportedOperationException("Invalid operation");
	}

	public E lower(E e){
		throw new UnsupportedOperationException("Invalid operation");
	}

	public E higher(E e){
		throw new UnsupportedOperationException("Invalid operation");
	}

	public E floor(E e){
		throw new UnsupportedOperationException("Invalid operation");
	}

	public NavigableSet<E> subSet(E fromElement, boolean fromInclusive, E toElement, boolean toInclusive){
		throw new UnsupportedOperationException("Invalid operation");
	}

	public SortedSet<E> subSet(E fromElement, E toElement){
		throw new UnsupportedOperationException("Invalid operation");
	}

	public E last(){
		throw new UnsupportedOperationException("Invalid operation");
	}

	public E first(){
		throw new UnsupportedOperationException("Invalid operation");
	}

	public Comparator<? super E> comparator(){
		throw new UnsupportedOperationException("Invalid operation");
	}

	public void clear(){
		throw new UnsupportedOperationException("Invalid operation");
	}

	public boolean removeAll(Collection<?> c){
		throw new UnsupportedOperationException("Invalid operation");
	}

	public boolean retainAll(Collection<?> c){
		throw new UnsupportedOperationException("Invalid operation");
	}

	public boolean addAll(Collection<? extends E> c){
		throw new UnsupportedOperationException("Invalid operation");
	}

	public boolean containsAll(Collection<?> c){
		throw new UnsupportedOperationException("Invalid operation");
	}

	public <T> T[] toArray(T[] a){
		throw new UnsupportedOperationException("Invalid operation");
	}

	public Object[] toArray(){
		throw new UnsupportedOperationException("Invalid operation");
	}

	public boolean contains(Object o){
		throw new UnsupportedOperationException("Invalid operation");
	}

	public boolean isEmpty(){
		throw new UnsupportedOperationException("Invalid operation");
	}

	public int size(){
		throw new UnsupportedOperationException("Invalid operation");
	}

}