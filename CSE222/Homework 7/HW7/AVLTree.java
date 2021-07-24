package HW7;

import java.util.Iterator;
import java.util.SortedSet;
import java.util.Comparator;
import java.util.Collection;
import java.util.ArrayList;
import java.util.TreeSet;
import java.util.NavigableSet;

/**
* Self‐balancing binary search tree using the algorithm defined
* by Adelson‐Velskii and Landis.
*/
public class AVLTree<E extends Comparable<E>> extends BinarySearchTreeWithRotate<E> implements NavigableSet<E>{
	
	/** Class to represent an AVL Node. It extends the
	* BinaryTree.Node by adding the balance field.
	*/
	private static class AVLNode<E> extends Node<E> {
		/** Constant to indicate left‐heavy */
		public static final int LEFT_HEAVY = -1;
		/** Constant to indicate balanced */
		public static final int BALANCED = 0;
		/** Constant to indicate right‐heavy */
		public static final int RIGHT_HEAVY = 1;
		/** balance is right subtree height – left subtree height */
		private int balance;
		
		// Methods
		/**
		* Construct a node with the given item as the data field.
		* @param item The data field
		*/
		public AVLNode(E item) {
			super(item);
			balance = BALANCED;
		}
		/** 
		* Return a string representation of this object.
		* The balance value is appended to the contents.
		* @return String representation of this object
		*/
		@Override
		public String toString() {
			return balance + ": " + super.toString();
		}
	}

	// Data Fields
	/** Flag to indicate that height of tree has increased. */
	private boolean increase;

	/** Flag to indicate that height of tree has decreased */
	private boolean decrease;


	private int sizeAVL = 0;

	/** 
	* add starter method.
	* //@pre the item to insert implements the Comparable interface.
	* @param item The item being inserted.
	* @return true if the object is inserted; false
	* if the object already exists in the tree
	* @throws ClassCastException if item is not Comparable
	*/
	@Override
	public boolean add(E item) {
		increase = false;
	//	System.out.println("---------------------------------------");
	//	System.out.println("adding " + item);
		root = add((AVLNode<E>) root, item);
	//	System.out.println(this);
		if(addReturn) sizeAVL++;
		return addReturn;
	}

	/** 
	* Recursive add method. Inserts the given object into the tree.
	* //@post addReturn is set true if the item is inserted,
	* //false if the item is already in the tree.
	* @param localRoot The local root of the subtree
	* @param item The object to be inserted
	* @return The new local root of the subtree with the item inserted
	*/
	private AVLNode<E> add(AVLNode<E> localRoot, E item){
		if (localRoot == null) {
			addReturn = true;
			increase = true;
		//	System.out.println("deneme---------1");
			return new AVLNode<E>(item);
		}

		if (item.compareTo(localRoot.data) == 0) {
		//	System.out.println("minnos1");

			// Item is already in the tree.
			increase = false;
			addReturn = false;
			//System.out.println("deneme2");
			return localRoot;
		}

		else if (item.compareTo(localRoot.data) < 0) {
			// item < data
			//left
		//	System.out.println("deneme3");
			localRoot.left = add((AVLNode<E>) localRoot.left, item);
			if (increase) {
				decrementBalance(localRoot);
				if (localRoot.balance < AVLNode.LEFT_HEAVY) {
					increase = false;
					return rebalanceLeft(localRoot);
				}
			}
			return localRoot; // Rebalance not needed.
		}
		
		else {
			// item > data
			//right
		//	System.out.println("deneme4");
			localRoot.right = add( (AVLNode<E> ) localRoot.right, item);
			if (increase) {
				//System.out.println("*** ince girmeden önce: "+localRoot.data);
		//		System.out.println("deneme5 " + localRoot.data);
				incrementBalance(localRoot);
				//System.out.println("*** ince çıktıktan sonra: "+localRoot.data);
		//							System.out.println("ooff " + localRoot.data + " " + localRoot.balance);

				if (localRoot.balance > AVLNode.RIGHT_HEAVY) {
		//							System.out.println("minnos233 " + localRoot.data + " " + localRoot.balance);

					increase = false;
					return rebalanceRight(localRoot);
				}
			}
			return localRoot;	
		}
	}


	/** 
	* Method to rebalance left.
	* //@pre localRoot is the root of an AVL subtree that is critically left‐heavy.
	* //@post Balance is restored.
	* @param localRoot Root of the AVL subtree that needs rebalancing
	* @return a new localRoot
	*/
	private AVLNode<E> rebalanceLeft(AVLNode<E> localRoot) {
		// Obtain reference to left child.
		//System.out.println("minnos rebalanceLeft");

		AVLNode<E> leftChild = (AVLNode<E>) localRoot.left;
		// See whether left‐right heavy.
		if (leftChild.balance > AVLNode.BALANCED) {
		// Obtain reference to left‐right child.
			AVLNode<E> leftRightChild = (AVLNode<E>) leftChild.right;
			/** Adjust the balances to be their new values after
			the rotations are performed.
			*/

			if (leftRightChild.balance < AVLNode.BALANCED) {
			// 	System.out.println("asd");
				leftChild.balance = AVLNode.BALANCED;
				leftRightChild.balance = AVLNode.BALANCED;
				localRoot.balance = AVLNode.RIGHT_HEAVY;

			}
			else {
				leftChild.balance = AVLNode.LEFT_HEAVY;
				leftRightChild.balance = AVLNode.BALANCED;
				localRoot.balance = AVLNode.BALANCED;
			} 
			// Perform left rotation.
			localRoot.left = rotateLeft(leftChild);
		} else { //Left‐Left case
			/** In this case the leftChild (the new root) and the root
			(new right child) will both be balanced after the rotation.
			*/
			//System.out.println("l4");
			leftChild.balance = AVLNode.BALANCED;
			localRoot.balance = AVLNode.BALANCED;
		}
		//System.out.println("l5");
		// Now rotate the local root right.
		increase = false;
		decrease = true;
		return (AVLNode<E>) rotateRight(localRoot);
	}


	private void decrementBalance(AVLNode<E> node) {
		// Decrement the balance.
		//System.out.println("decrementBalance fonksiyonu: "+node + " " + node.balance);
		node.balance--;
		if (node.balance == AVLNode.BALANCED) {
			/** If now balanced, overall height has not increased. */
			increase = false;
		} else if( node.balance == AVLNode.LEFT_HEAVY ){
			decrease = false;
		}
	}
	
//*******************************************************************************************************************


	private AVLNode <E> rebalanceRight(AVLNode<E> localRoot) {
	//	System.out.println("rebalanceRight fonksiyonu: "+localRoot);

		// Obtain reference to right child
		AVLNode<E> rightChild = (AVLNode<E>) localRoot.right;
		// See if right-left heavy
		
		if (rightChild.balance < AVLNode.BALANCED) {
		  	//System.out.println("r1");
			// Obtain reference to right-left child
			AVLNode<E> rightLeftChild = (AVLNode<E>) rightChild.left;

			if (rightLeftChild.balance > AVLNode.BALANCED) {
			//  	System.out.println("asd");
				rightChild.balance = AVLNode.RIGHT_HEAVY;
				rightLeftChild.balance = AVLNode.BALANCED;
				localRoot.balance = AVLNode.BALANCED;
			}
			else if (rightLeftChild.balance < AVLNode.BALANCED) {
			//	System.out.println("qwe");
				rightChild.balance = AVLNode.BALANCED;
				rightLeftChild.balance = AVLNode.BALANCED;
				localRoot.balance = AVLNode.LEFT_HEAVY;
			}
			else {
			//	System.out.println("zxc");
				rightChild.balance = AVLNode.BALANCED;
				rightLeftChild.balance = AVLNode.LEFT_HEAVY;
				//localRoot.balance = AVLNode.BALANCED;
				localRoot.balance = AVLNode.LEFT_HEAVY;
			}
			// Now rotate the local root right.
			increase = false;
			decrease = true;
			localRoot.right = rotateRight(rightChild);
			return (AVLNode<E>) rotateLeft(localRoot);
		} 
		if(rightChild.balance > AVLNode.BALANCED){
		// 	System.out.println("r3333");

			rightChild.balance = AVLNode.BALANCED;
			localRoot.balance = AVLNode.BALANCED;
			increase = false;
			decrease = true;
		}
		else if(rightChild.balance < AVLNode.BALANCED){
			//System.out.println("dsdsssssssssssssssssssssssssss");

			rightChild.balance = AVLNode.BALANCED;
			localRoot.balance = AVLNode.BALANCED;
			increase = false;
			decrease = true;
		}
		else {
		//  	System.out.println("r4");
		//	rightChild.balance = AVLNode.LEFT_HEAVY;
		//	localRoot.balance = AVLNode.RIGHT_HEAVY;
			rightChild.balance = AVLNode.LEFT_HEAVY;
			localRoot.balance = AVLNode.BALANCED;
		}

		//System.out.println("r5");
	//	System.out.println(this);

		return (AVLNode<E>) rotateLeft(localRoot);
	}


	private void incrementBalance(AVLNode<E> node) {
		// Decrement the balance.
		//System.out.println("incrementBalance fonksiyonu: "+node);
		node.balance++;
		if (node.balance == AVLNode.BALANCED) {
			/** If now balanced, overall height has not increased. */
		//	System.out.println("if");

			decrease = true;
			increase = true;
		} else if( node.balance == AVLNode.LEFT_HEAVY ){
			increase = false;
		//	System.out.println("else");

		}
	}

	@Override
	public boolean remove(Object o){
		//avlsize--
		//if( remove((E)o) != null ){
		//	return true;
		//}
		decrease = false;
		root = remove((AVLNode<E>)root, (E)o);
		if(deleteReturn != null){
			sizeAVL--;
			return true;
		}
		return false;
	}
/*
	public E remove(E item){
		//avlsize--
		decrease = false;
		root = remove((AVLNode<E>)root, item);
		return deleteReturn;
	}
*/
	private AVLNode<E> remove(AVLNode<E> localRoot, E item){
		if(localRoot == null){
			deleteReturn = null;
			return localRoot;
		}

		if(item.compareTo(localRoot.data) < 0){
		//	System.out.println("a1 "+ localRoot.data);
			localRoot.left = remove((AVLNode<E>)localRoot.left, item);
		//	System.out.println("a2 "+ localRoot.data);
			if(decrease){
				incrementBalance(localRoot);
		//		System.out.println("a3 "+ localRoot.data);
				if(localRoot.balance > AVLNode.RIGHT_HEAVY){
		//			System.out.println("a4 "+ localRoot.data);
					return rebalanceRight(localRoot);
				}
			}
			return localRoot;
		} else if(item.compareTo(localRoot.data) > 0){
		//	System.out.println("deneme132 "+ localRoot.data);

			localRoot.right=remove((AVLNode<E>)localRoot.right, item);
		//	System.out.println("deneme1111 "+ localRoot.data);

			if(decrease) {
		//		System.out.println("deneme15454 "+ localRoot.data);
				decrementBalance(localRoot);
				if(localRoot.balance<AVLNode.LEFT_HEAVY) {
		//			System.out.println("allahım\n "+ this);
					return rebalanceLeft(localRoot);
				}
			}
			return localRoot;
		} else{
            // item is at local root.
            deleteReturn = localRoot.data;
            if (localRoot.left == null) {
                // If there is no left child, return right child
                // which can also be null.
            //    System.out.println("deneme1 "+ localRoot.data);
                decrease = true;
                return (AVLNode<E>)localRoot.right;
            } else if (localRoot.right == null) {
                // If there is no right child, return left child.
            //    System.out.println("deneme12");
                decrease = false;
                return (AVLNode<E>)localRoot.left;
            } else {
                // Node being deleted has 2 children, replace the data
                // with inorder predecessor.
                //System.out.println("deneme13");

                if (localRoot.left.right == null) {
                    // The left child has no right child.
                    // Replace the data with the data in the
                    // left child.
                    localRoot.data = localRoot.left.data;
                    // Replace the left child with its left child.
                    localRoot.left = localRoot.left.left;
               	// 	System.out.println("deneme14");
                	decrease = true;
                	incrementBalance(localRoot);
                    return localRoot;
                } else {
                    // Search for the inorder predecessor (ip) and
                    // replace deleted node's data with ip.
                //    System.out.println("deneme15");
                    decrease = true;
                    localRoot.data = findLargestChild(localRoot.left);
                    if(decrease){
						incrementBalance(localRoot);
						if(localRoot.balance > AVLNode.RIGHT_HEAVY){
							return rebalanceRight(localRoot);
						}
					}
                    return localRoot;
                }
            }
        }
	}
    
    private E findLargestChild(Node<E> parent) {
        // If the right child has no right child, it is
        // the inorder predecessor.
        if (parent.right.right == null) {
            E returnValue = parent.right.data;
            parent.right = parent.right.left;
            return returnValue;
        } else {
            return findLargestChild(parent.right);
        }
    }
//NAVİGABLE SETTTTTTTTTTTT

	public Iterator<E> iterator(){
		return new avlIterator(root);
	}
	/*Returns a view of the portion of this set whose elements are less than (or equal to, if inclusive is true) toElement.*/
	public NavigableSet<E> headSet(E toElement, boolean inclusive){
		avlIterator itr = new avlIterator(root);
		ArrayList<E> temp = itr.newAVL();
		for(int i=0; i<temp.size(); i++){
			if( inclusive && temp.get(i).compareTo(toElement) > 0 ){
				temp.remove(i);
				i=-1;
			} else if( !inclusive && temp.get(i).compareTo(toElement) >= 0 ){
				temp.remove(i);
				i=-1;
			}
		}
		SortedSet<E> temp2 = new TreeSet<E>(temp);
		//temp2.addAll(temp1);
		return (NavigableSet<E>)temp2;
	}

	public SortedSet<E> headSet(E toElement){
		avlIterator itr = new avlIterator(root);
		ArrayList<E> temp = itr.newAVL();
		for(int i=0; i<temp.size(); i++){
			if( temp.get(i).compareTo(toElement) >= 0 ){
				temp.remove(i);
				i=-1;
			}
		}
		SortedSet<E> temp2 = new TreeSet<E>(temp);
		return temp2;
	}

	public NavigableSet<E> tailSet(E fromElement, boolean inclusive){
		avlIterator itr = new avlIterator(root);
		ArrayList<E> temp = itr.newAVL();
		for(int i=0; i<temp.size(); i++){
			if( inclusive && temp.get(i).compareTo(fromElement) < 0 ){
				temp.remove(i);
				i=-1;
			} else if( !inclusive && temp.get(i).compareTo(fromElement) <= 0 ){
				temp.remove(i);
				i=-1;
			}
		}
		SortedSet<E> temp2 = new TreeSet<E>(temp);
		//temp2.addAll(temp1);
		//System.out.println("lalalla: \n" + (NavigableSet<E>)temp2);

		return (NavigableSet<E>)temp2;
	}
	
	public SortedSet<E> tailSet(E fromElement){
		avlIterator itr = new avlIterator(root);
		ArrayList<E> temp = itr.newAVL();
		for(int i=0; i<temp.size(); i++){
			if( temp.get(i).compareTo(fromElement) < 0 ){
				temp.remove(i);
				i=-1;
			}
		}

		SortedSet<E> temp2 = new TreeSet<E>(temp);
		//temp2.addAll(temp1);
		//System.out.println("deneme: \n" + temp2);

		return temp2;
	}

	public Iterator<E> descendingIterator(){
		throw new UnsupportedOperationException("Invalid operation");
	}



/** Inner class to implement the Iterator interface. */
	private class avlIterator implements Iterator<E> {

	    private ArrayList<E> values;
	    private Iterator<E> iterator;
	    private int cursor;
	    public avlIterator(Node<E> root) {
	        values = new ArrayList<>();
	        traverse(root);
	    //    System.out.println(values);
		//	Collections.sort(values, Collections.reverseOrder());		
	        iterator = values.iterator();
	        cursor = 0;
	    }

    	private void traverse(Node<E> root){
    		if(root == null)
    			return;
    		traverse(root.left);
    		values.add(root.data);
    		traverse(root.right);
    	}

	    public E next() {
	    	cursor++;
	        return iterator.next();
	    }

	    public boolean hasNext() {
	        return iterator.hasNext();
	    }

	    public void remove(){
	    //	System.out.println("Silinecek: " + values.get(cursor-1));
			removeSL(values.get(--cursor));
	    	iterator.remove();
	    }

	    protected ArrayList<E> newAVL(){
	    	return values;
	    }
	}
	private boolean removeSL(E item){
		remove(item);
		return true;
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
		return sizeAVL;
	}
}