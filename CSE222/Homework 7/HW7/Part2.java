package HW7;
/**
*	Functions of Part2 and tests for Part2 
*/
public class Part2{
	/**
	* Test for the part2s
	*/
	public void test(){
		System.out.println("\n\n**************** Test for Part2 ****************\n\n");

		BinarySearchTree<Integer> bst1 = new BinarySearchTree<Integer>();
		BinarySearchTree<Integer> bst2 = new BinarySearchTree<Integer>();
		bst1.add(12, true);
		bst1.add(8, false);
		bst1.add(18, true);
		bst1.add(5, false);
		bst1.add(11, true);
		bst1.add(17, true);
		bst1.add(4, true);
		System.out.println("************************************************************\n");
		System.out.println("bst1: \n" + bst1);
		checksAVLorRBT(bst1);

		System.out.println("\n************************************************************\n");
		bst2.add(4, false);
		bst2.add(2, true);
		bst2.add(6, true);
		bst2.add(1, false);
		bst2.add(3, false);
		bst2.add(5, false);
		bst2.add(8, false);
		bst2.add(7, true);
		bst2.add(9, true);
		System.out.println("bst2: \n" + bst2);
		checksAVLorRBT(bst2);

	}
	/**
	* Checks whether AVL, RebBlackTree
	*/
	public <E extends Comparable<E>> boolean checksAVLorRBT(BinarySearchTree<E> bst){
		if( bst.size() == 0 ){
			System.out.println(" -> The BST is empty");
			return false;
		}
		if( isAVLTree(bst) ){
			System.out.println(" -> The BST is an AVLTree");
		} else{
			System.out.println(" -> The BST NOT an AVLTree");
		}
		if( isRedBlackTree(bst) ){
			System.out.println(" -> The BST is a RedBlackTree");
		} else{
			System.out.println(" -> The BST is NOT a RedBlackTree");
		}
		return true;
	}
	private boolean check = true;

	private <E extends Comparable<E>> boolean isRedBlackTree(BinarySearchTree<E> bst){
		//The root is always black
		// A red node always has black children(a null reference is considered to refer to a black node)
		//The number of black nodes in any path from the root to a leaf is the same
		if( ((BinaryTree<E>)bst).isRed() ){
			//The root is red
			return false;
		}
		traverse(bst);
		if( !check ){
			return false;
		}

		if( !path((BinaryTree<E>)bst) ){
			return false;
		}
		
		return true;
	}

	private <E extends Comparable<E>> void traverse(BinaryTree<E> bst){
		if( bst == null ){
			return;
		}
		traverse(bst.getLeftSubtree());
		if( check && bst.isRed() && (!((bst.getLeftSubtree().isRed())) || !((bst.getRightSubtree()).isRed())) ){
			check = false;
		}
    	//values.add(root.data);
    	traverse(bst.getRightSubtree());
	}

	private <E extends Comparable<E>> boolean path(BinaryTree<E> bst){
		if( bst == null ){
			return true;
		}
		if( findPath(bst) ){//&& path(bst.getLeftSubtree()) && path(bst.getRightSubtree()) ){
			return true;
		}
		return false;
	}
	private int path = 0;

	private <E extends Comparable<E>> boolean findPath(BinaryTree<E> bst){
		check = true;
		path = 0;
		blackPath(bst.getRightSubtree());
		int pathR = path;
		path = 0;
		check = true;
		blackPath(bst.getLeftSubtree());
		int pathL = path;
		return pathR == pathL;
	}


	private <E extends Comparable<E>> void blackPath(BinaryTree<E> bst){
	    if( bst == null ){
	    	check = false;
	        return;
	    }
	    if( check && !bst.isRed() )
	    	path++;

	    if(check)	blackPath(bst.getLeftSubtree());
	    if(check)	blackPath(bst.getRightSubtree());
	}



//*************************************************************************************************************
	private <E extends Comparable<E>> boolean isAVLTree(BinarySearchTree<E> bst){
		return balance((BinaryTree<E>)bst);
	}

	private <E extends Comparable<E>> boolean balance(BinaryTree<E> bst){
		if( bst == null ){
			return true;
		}
		if( Math.abs(findBalance(bst))<=1 && balance(bst.getLeftSubtree()) && balance(bst.getRightSubtree()) ){
			return true;
		}
		return false;
	}

	private <E extends Comparable<E>> int findBalance(BinaryTree<E> bst){
		return height(bst.getRightSubtree()) - height(bst.getLeftSubtree());
	}

	private <E extends Comparable<E>> int height(BinaryTree<E> bst){
	    if( bst == null ){
	        return 0;
	    }
	    return Math.max(height(bst.getLeftSubtree()), height(bst.getRightSubtree())) + 1;	
	}

/*
	private boolean balance(BinaryTree<E> bst){
		if( bst == null ){
			return false;
		}
		
		int balance = findBalance(bst);
		if( balance<-1 || balance>1 ){
			return false;
		}

		BinaryTree<E> temp1 = bst;
		while( temp1 != null ){
			balance = findBalance(temp1);
			if( balance<-1 || balance>1 ){
				return false;
			}
			temp1 = temp1.getLeftSubtree();
		}

		BinaryTree<E> temp2 = bst;
		while( temp2 != null ){
			balance = findBalance(temp2);
			if( balance<-1 || balance>1 ){
				return false;
			}
			temp2 = temp2.getRightSubtree();
		}
		return true;
	}
*/
}