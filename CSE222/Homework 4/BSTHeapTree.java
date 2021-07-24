import java.util.ArrayList;
import java.io.Serializable;

/**
* A class to represent a BSTHeapTree
*  by using an MaxHeap. The heap is structured
*  so that the "largest" item is at the top.
* @author Emine Sultan Savran
* @param <E> generic type which that extends Comparable interface
*/
public class BSTHeapTree<E extends Comparable<E>> implements Serializable{

	//Data fields
	/**The root of the tree*/
	private Node<E> root = null;
	/**The occurrence at the BSTHeapTree*/
	private int occurrence = 0;
	/**The maximum occurrence at the Node*/
	private int maxOccur = 0;

	//Methods
	/**Defualt constructor*/
	public BSTHeapTree() {
        root = null;
    }
	
	/**
	* Print the the BSTHeapTree
	* @return the BSTHeapTree
	*/
	@Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        preOrderTraverse(root, 1, sb);
        return sb.toString();
    }

    /**
	* Helper function to print the the BSTHeapTree
	* with preOrderTraverse
	* @param node the root
	* @param depth the length of the tree
	* @param sb the string
	*/
	private void preOrderTraverse(Node<E> node, int depth, StringBuilder sb) {
        for (int i = 1; i < depth; i++) {
            sb.append("  ");
        }
        if (node == null ||
        	node.heap == null ||
        	node.heap.size() <= 0) {
            sb.append("null\n");
        } else {
            sb.append(node.toString());
            sb.append("\n");
            preOrderTraverse(node.left, depth + 1, sb);
            preOrderTraverse(node.right, depth + 1, sb);
        }
    }

    /**
    * Find the item and returns the number of occurrences of the item in the BSTHeapTree
    * @param target the value to find
    * @return the number of occurrences of the item in the BSTHeapTree
    */
    public int find(E target) {
    	if( root == null ){
    		System.out.println("The find operation cannot done. The BSTHeapTree is empty.");
    		return 0;
    	}
    	if( find(root, target) == null ){
    		return 0;
    	}
        return occurrence;
    }

	/**
    * Helper function to find the item and returns the number of occurrences of the item in the BSTHeapTree
    * @param localRoot the current root
    * @param target the value to find
    * @return the value find
    */
    private E find(Node<E> localRoot, E target) {
        if (localRoot == null || localRoot.heap == null){
            return null;
        }
        occurrence = localRoot.find(target);  
        if( occurrence > 0 ){
        	return target;
        }
        int compResult = 0;
        if( localRoot.heap.get(0) != null ){
        	compResult = target.compareTo(localRoot.heap.get(0));
        	if (compResult == 0) {
	            return localRoot.heap.get(0);
	        } else if (compResult < 0) {
	            return find(localRoot.left, target);
	        } else {
	            return find(localRoot.right, target);
	        }
        }
        return localRoot.heap.get(0);
    }

    /**
    * Add the item and returns the number of occurrences of the item after insertion
    * @param item the value to find
    * @return the number of occurrences of the item in the BSTHeapTree
    */
	public int add(E item) {
        root = add(root, item);
        return find(item);
    }

	/**
    * Add the item and returns the number of occurrences of the item after insertion
    * @param localRoot the current root
    * @param item the value to find
    * @return the Node current to help recursion
    */
    private Node<E> add(Node<E> localRoot, E item) {
        if (localRoot == null) {
        	//tree boş
        	//heap oluşturup tree'nin rootuna ekliyorum
            return new Node<E>(item);
        } else if( localRoot.heap.search(item,1) != -1 ){
        	//bu rootta bu item var
        	//occurence 1 arrtır
        	localRoot.heap.add(localRoot.heap.search(item,1));
        } else if( localRoot.heap.size() < 7 ){
        	//burda eleman yok 
        	//yer var
        	localRoot.heap.insert(item);
        } else if( localRoot.heap.size() == 7 ){
        	//burda eleman yok 
        	//yer yok
        	if (item.compareTo(localRoot.heap.get(0)) < 0) {
            	// item is less than localRoot.data
            	localRoot.left = add(localRoot.left, item);
            	return localRoot;
        	} else {
            	// item is greater than localRoot.data
            	localRoot.right = add(localRoot.right, item);
            	return localRoot;
        	}
        }
        return localRoot;
    }

	/**
    * Remove the item and returns the number of occurrences of the item after removal
    * @param target the value to find
    * @return the number of occurrences of the item in the BSTHeapTree
    */    
    public int remove(E target) {
    	if( root == null ){
    		System.out.println("WARNING: The BSTHeapTree is empty so the item cannot deleted.");
    		return 0;
    	}
    	if( find(target) == 0 ){
    		System.out.println("WARNING: The Target is not here-> "+target);
    	}
        root = remove(root, target);
        return find(target);
    }

	/**
    * Remove the item and returns the number of occurrences of the item after removal
    * @param localRoot the current root
    * @param item the value to find
    * @return the Node current to help recursion
    */
    private Node<E> remove(Node<E> localRoot, E item) {
        if (localRoot == null) {
            // item is not in the tree.
            return localRoot;
        }
        int atHeap = localRoot.heap.search(item,1);
        if( atHeap == -1 ){
        	//bu rootun heapinde yok
        	int compResult = item.compareTo(localRoot.heap.get(0));
	        if (compResult < 0) {
	            // item is smaller than localRoot.data.
	            localRoot.left = remove(localRoot.left, item);
	            return localRoot;
	        } else if (compResult > 0) {
	            // item is larger than localRoot.data.
	            localRoot.right = remove(localRoot.right, item);
	            return localRoot;
	        }
        } else {
            //itemi sil 
            E theItem = localRoot.heap.get(atHeap);
            occurrence = localRoot.heap.get(atHeap,1).getOccurrence();
            if( occurrence > 1 ){
            	localRoot.heap.get(atHeap,1).decreaseOccurence();
            	return localRoot;
            }
            localRoot.heap.remove(atHeap,1);

            if( localRoot.heap == null ){
            	return localRoot;
            }

            if (localRoot.left == null && localRoot.right != null ) {
                //sağdaki elemanı kendime almam lazım
                localRoot.heap.insert( localRoot.right.heap.get(0) );
                localRoot.right.heap.remove(0,1);
                return localRoot;
            } else if (localRoot.right == null && localRoot.left != null) {
                //soldaki elemanı kendime almam lazım
            	localRoot.heap.insert( localRoot.left.heap.get(0) );
            	localRoot.left.heap.remove(0,1);
                return localRoot;
            } else {
                if ( localRoot.left != null && localRoot.left.right == null) {
                    //lefti kendime almam lazım
                    localRoot.heap.insert( localRoot.left.heap.get(0) );
                    localRoot.left.heap.remove(0,1);
                    localRoot.left.heap.insert( localRoot.left.left.heap.get(0) );
                    localRoot.left.left.heap.remove(0,1);
                    return localRoot;
                } else {
                	localRoot.heap.insert( findLargestChild(localRoot.left) );
                    return localRoot;
                }
            }
        }
        return localRoot;
    }

	/**
	* Helps to figure out which item to insert    
	* @param parent the current root
    * @return the value to insert
    */    
    private E findLargestChild(Node<E> parent) {
        // If the right child has no right child, it is
        // the inorder predecessor.
        if( parent == null ){
        	return null;
        }
        if (parent.right != null && parent.right.right == null) {
        	//rigthi kendime alıyorum
            E returnValue = parent.right.heap.get(0);
            parent.right.heap.insert( parent.right.left.heap.get(0) );
            return returnValue;
        } else {
            return findLargestChild(parent.right);
        }
    }

	/**
	* Find mode of the tree
	* @return ArrayList keeps modes
	*/
	public ArrayList<E> find_mode(){
		if( root == null ){
			System.out.println("WARNING: Cannot find the mode. The BSTHeapTree is empty.");
			return null;
		}
		find_maxOccur(root);
		ArrayList<E> modes = new ArrayList<E>();
		find_modes(root, modes);


    	return modes;
    }

    /**
    * Helper function to find mode.
    * Find maximum occurrence value
    * @param localRoot the current root
    * @return the Node current to help recursion
    */
    private Node<E> find_maxOccur(Node<E> localRoot){
    	if( localRoot == null ){
    		return null;
    	}

    	for(int i=0; i<localRoot.heap.size(); i++){
    		if( localRoot.heap.get(i,1).getOccurrence()>maxOccur ){
    			maxOccur = localRoot.heap.get(i,1).getOccurrence();
    		}
    	}

    	if( localRoot.left != null ){
    		find_maxOccur(localRoot.left);
    	}

    	if( localRoot.right != null ){
    		find_maxOccur(localRoot.right);
    	}

    	return localRoot;
    }
 	
 	/**
    * Helper function to find mode.
    * Find values that have maximum occurrence
    * and add to the arraylist 
    * @param localRoot the current root
    * @param modes to keep modes
    * @return the Node current to help recursion
    */	
    private Node<E> find_modes(Node<E> localRoot, ArrayList<E> modes){
    	if( localRoot == null ){
    		return null;
    	}

    	for(int i=0; i<localRoot.heap.size(); i++){
    		if( localRoot.heap.get(i,1).getOccurrence() == maxOccur ){
    			modes.add( localRoot.heap.get(i) );
    		}
    	}

    	if( localRoot.left != null ){
   			find_modes(localRoot.left, modes);
    	}

    	if( localRoot.right != null ){
    		find_modes(localRoot.right, modes);
    	}

    	return localRoot;
    }

	/**
	* A protected class to represent Node<E>
	* implements Serializable.
	* @param <E> generic type which that extends Comparable interface
	*/	
	private static class Node<E extends Comparable<E>> implements Serializable{
		//Data fields
		/**Max value to keep at the node*/
		private static final int CAPACITY = 7;
		/**to keep the dara*/
		public MaxHeap<E> heap = null;
		/**left child*/
		public Node<E> left = null;
		/**right child*/
		public Node<E> right = null;
		/**
		* Constructor with the data value
		* @param data to keep
		*/
		public Node(E data) {
			if(this.heap == null){
				heap = new MaxHeap();
			}
			heap.insert(data);
            left = null;
            right = null;
        }
		/**
		* Constructor with the heap value
		* @param heap to keep
		*/
        public Node(MaxHeap heap) {
        	this.heap = heap;	
            left = null;
            right = null;
        }
        /**
        * Find occurrenc of the data
        * @param data to find the occurrence
        * @return the occurrence
        */
        public int find(E data){
        	int index = heap.search(data,1);
        	if( index == -1 ){
        		return 0;
        	}
        	return heap.get(index,1).getOccurrence();
        }
		/**
	    * Print the heap with occurrence
	    * @return the value
	  	*/
        @Override
        public String toString() {
            return heap.toStringBST();
        }
        /**
		* Check whether objects are equals
		* @param Object the object
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
	    		return mo.heap.equals(heap);
			} catch(Exception e){
				System.out.println("There is some problems");
				return false;
			}
		}
	}       
    
}
