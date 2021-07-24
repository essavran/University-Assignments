package HW7;

import java.util.NavigableSet;
import java.util.Iterator;
import java.util.SortedSet;

/**
* Tests for Part1
*/
public class Part1{

	/**
	* Test for Part1
	*/
	public void test(){
		System.out.println("\n\n****************Test for Part1****************\n\n");
		testSkipList();
		System.out.println("************************************************************\n");
		testAVLTree();
	}

	/**
	* Test for Part1 - SkipList
	*/
	public void testSkipList(){
		System.out.println("***using skip-list***\n");
		NavigableSet<Integer> skiplist1 = new SkipList<Integer>();
		for(int i=5; i<500; i*=2){
			System.out.println(" --> Insert " + i + " : " + skiplist1.add(i));
		}
		System.out.println("");
		System.out.println("The SkipList: \n" + skiplist1 + "\n");
		System.out.println(" --> Insert 233 : " + skiplist1.add(233));
		System.out.println(" --> Insert 601 : " + skiplist1.add(601));
		System.out.println(" --> Insert -55 : " + skiplist1.add(-55));
		System.out.println(" --> Insert 5 : " + skiplist1.add(5));

		System.out.println("");
		System.out.println("The SkipList: \n" + skiplist1 + "\n");
		System.out.println(" --> Remove -55 : " + skiplist1.remove(-55));
		System.out.println(" --> Remove 20 : " + skiplist1.remove(20));
		System.out.println(" --> Remove 601 : " + skiplist1.remove(601));
		System.out.println(" --> Remove 1000 : " + skiplist1.remove(1000));
		System.out.println(" NOTE: False means that there is no element so it cannot remove.");

		System.out.println("");
		System.out.println("The SkipList: \n" + skiplist1 + "\n");
		
		Iterator<Integer> itr1 = skiplist1.descendingIterator();
		System.out.println(" --> descendingIterator is created.");
		System.out.print(" --> Print with descendingIterator: ");
		while(itr1.hasNext()){
			System.out.print(itr1.next() + " ");
		}
		System.out.println("\n\n --> descendingIterator is reseted.");
		itr1 = skiplist1.descendingIterator();
		System.out.println(" --> hasNext() : " + itr1.hasNext());
		System.out.println(" --> next() : " + itr1.next());
		System.out.println(" --> remove() is called.");
		itr1.remove();
		System.out.println("");
		System.out.println("The SkipList: \n" + skiplist1 + "\n");
		System.out.println(" --> hasNext() : " + itr1.hasNext());
		System.out.println(" --> next() : " + itr1.next());
		System.out.println(" --> remove() is called.");
		itr1.remove();
		System.out.println("");
		System.out.println("The SkipList: \n" + skiplist1 + "\n");

		System.out.println(" --> hasNext() : " + itr1.hasNext());
		System.out.println(" --> next() : " + itr1.next());		
		System.out.println(" --> hasNext() : " + itr1.hasNext());
		System.out.println(" --> next() : " + itr1.next());		
		System.out.println(" --> hasNext() : " + itr1.hasNext());
		System.out.println(" --> next() : " + itr1.next());
		System.out.println(" --> remove() is called.");
		itr1.remove();
		System.out.println("");
		System.out.println("The SkipList: \n" + skiplist1 + "\n");
	}	

	/**
	* Test for Part1 - AVLTree
	*/
	public void testAVLTree(){
		System.out.println("***using AVL tree***\n");
		NavigableSet<Integer> avl1 = new AVLTree<Integer>();
		for(int i=5; i<500; i*=2){
			System.out.println(" --> Insert " + i + " : " + avl1.add(i));
		}
		System.out.println("");
		System.out.println("The AVLTree: \n" + avl1 + "\n");
		System.out.println(" --> Insert 233 : " + avl1.add(233));
		System.out.println(" --> Insert 601 : " + avl1.add(601));
		System.out.println(" --> Insert -55 : " + avl1.add(-55));
		System.out.println(" --> Insert 5 : " + avl1.add(5));
		System.out.println(" NOTE: False means that there already exists the element.");

		System.out.println("");
		System.out.println("The AVLTree: \n" + avl1 + "\n");
		
		System.out.println(" --> SortedSet<E> headSet(40) : ");
		SortedSet<Integer> sortedSet1 = avl1.headSet(40);
		System.out.println("   " + sortedSet1);

		System.out.println(" --> NavigableSet<E> headSet(40, true) : ");
		NavigableSet<Integer> navigableSet1 = avl1.headSet(40, true);
		System.out.println("   " + navigableSet1);

		System.out.println(" --> NavigableSet<E> headSet(40, false) : ");
		NavigableSet<Integer> navigableSet2 = avl1.headSet(40, false);
		System.out.println("   " + navigableSet2);

		System.out.println("");

		System.out.println(" --> SortedSet<E> tailSet(40) : ");
		SortedSet<Integer> sortedSet2 = avl1.tailSet(40);
		System.out.println("   " + sortedSet2);

		System.out.println(" --> NavigableSet<E> tailSet(40, true) : ");
		NavigableSet<Integer> navigableSet3 = avl1.tailSet(40, true);
		System.out.println("   " + navigableSet3);

		System.out.println(" --> NavigableSet<E> tailSet(40, false) : ");
		NavigableSet<Integer> navigableSet4 = avl1.tailSet(40, false);
		System.out.println("   " + navigableSet4);

		System.out.println("");

		System.out.println(" --> SortedSet<E> headSet(-111) : ");
		SortedSet<Integer> sortedSet3 = avl1.headSet(-111);
		System.out.println("   " + sortedSet3);

		System.out.println(" --> NavigableSet<E> headSet(-111, true) : ");
		NavigableSet<Integer> navigableSet5 = avl1.headSet(-111, true);
		System.out.println("   " + navigableSet5);

		System.out.println(" --> NavigableSet<E> headSet(-111, false) : ");
		NavigableSet<Integer> navigableSet6 = avl1.headSet(-111, false);
		System.out.println("   " + navigableSet6);

		System.out.println("");

		System.out.println(" --> SortedSet<E> tailSet(888) : ");
		SortedSet<Integer> sortedSet4 = avl1.tailSet(888);
		System.out.println("   " + sortedSet4);

		System.out.println(" --> NavigableSet<E> tailSet(888, true) : ");
		NavigableSet<Integer> navigableSet7 = avl1.tailSet(888, true);
		System.out.println("   " + navigableSet7);

		System.out.println(" --> NavigableSet<E> tailSet(888, false) : ");
		NavigableSet<Integer> navigableSet8 = avl1.tailSet(888, false);
		System.out.println("   " + navigableSet8);

		System.out.println("");

		Iterator<Integer> itr1 = avl1.iterator();
		System.out.println(" --> iterator is created.");
		System.out.print(" --> Print with iterator: ");
		while(itr1.hasNext()){
			System.out.print(itr1.next() + " ");
		}
		System.out.println("\n\n --> iterator is reseted.");
		itr1 = avl1.iterator();
		System.out.println(" --> hasNext() : " + itr1.hasNext());
		System.out.println(" --> next() : " + itr1.next());
		System.out.println(" --> remove() is called.");
		itr1.remove();
		System.out.println("");
		System.out.println("The AVLTree: \n" + avl1 + "\n");
		System.out.println(" --> hasNext() : " + itr1.hasNext());
		System.out.println(" --> next() : " + itr1.next());
		System.out.println(" --> remove() is called.");
		itr1.remove();
		System.out.println("");
		System.out.println("The AVLTree: \n" + avl1 + "\n");

		System.out.println(" --> hasNext() : " + itr1.hasNext());
		System.out.println(" --> next() : " + itr1.next());		
		System.out.println(" --> hasNext() : " + itr1.hasNext());
		System.out.println(" --> next() : " + itr1.next());		
		System.out.println(" --> hasNext() : " + itr1.hasNext());
		System.out.println(" --> next() : " + itr1.next());
		
		System.out.println(" --> remove() is called.");
		itr1.remove();
		System.out.println("");
		System.out.println("The AVLTree: \n" + avl1 + "\n");

	}
}