package HW7;
import java.util.Random;
import java.util.Iterator;
/**
*	Functions of Part3 and tests for Part3 
* 	@param <E> generic type. Must be Comparable
*/
public class Part3<E extends Comparable<E>> {
	private static final int TEN_THOUSAND = 10000;
	private static final int TWENTY_THOUSAND = 20000;
	private static final int FORTY_THOUSAND = 40000;
	private static final int EIGHTY_THOUSAND = 80000;
	private static final int ONE_HUNDRED = 100;
	private static final int RANDOM = 999999;
	/**
	* Print the part3
	*/
	public void part3(){
		System.out.println("\n\n**************** Part3 ****************\n\n");
		createInsertMeasure(TEN_THOUSAND);
		createInsertMeasure(TWENTY_THOUSAND);
		createInsertMeasure(FORTY_THOUSAND);
		createInsertMeasure(EIGHTY_THOUSAND);
	}
	/**
	* Creates data structures with given capacity, adds elements, makes measurements, calculates the average time.
	* @param capacity size of the data structures(10k,20k,40k,80k)
	*/
	private void createInsertMeasure(int capacity){
		long total = 0;
		System.out.println("********************************************************************************************************\n");
		System.out.println("*** " + capacity + " ***\n");
		BinarySearchTree<Integer> bst1 = new BinarySearchTree<Integer>();
		BinarySearchTree<Integer> bst2 = new BinarySearchTree<Integer>();
		BinarySearchTree<Integer> bst3 = new BinarySearchTree<Integer>();
		BinarySearchTree<Integer> bst4 = new BinarySearchTree<Integer>();
		BinarySearchTree<Integer> bst5 = new BinarySearchTree<Integer>();
		BinarySearchTree<Integer> bst6 = new BinarySearchTree<Integer>();
		BinarySearchTree<Integer> bst7 = new BinarySearchTree<Integer>();
		BinarySearchTree<Integer> bst8 = new BinarySearchTree<Integer>();
		BinarySearchTree<Integer> bst9 = new BinarySearchTree<Integer>();
		BinarySearchTree<Integer> bst10 = new BinarySearchTree<Integer>();
		Random rand = new Random();
		int num;
		while( bst1.size()<capacity ){
			num = rand.nextInt(RANDOM);
			bst1.add(num);
		}

		rand = new Random();
		while( bst2.size()<capacity ){
			num = rand.nextInt(RANDOM);
			bst2.add(num);
		}

		rand = new Random();
		while( bst3.size()<capacity ){
			num = rand.nextInt(RANDOM);
			bst3.add(num);
		}

		rand = new Random();
		while( bst4.size()<capacity ){
			num = rand.nextInt(RANDOM);
			bst4.add(num);
		}

		rand = new Random();
		while( bst5.size()<capacity ){
			num = rand.nextInt(RANDOM);
			bst5.add(num);
		}

		rand = new Random();
		while( bst6.size()<capacity ){
			num = rand.nextInt(RANDOM);
			bst6.add(num);
		}

		rand = new Random();
		while( bst7.size()<capacity ){
			num = rand.nextInt(RANDOM);
			bst7.add(num);
		}

		rand = new Random();
		while( bst8.size()<capacity ){
			num = rand.nextInt(RANDOM);
			bst8.add(num);
		}

		rand = new Random();
		while( bst9.size()<capacity ){
			num = rand.nextInt(RANDOM);
			bst9.add(num);
		}

		rand = new Random();
		while( bst10.size()<capacity ){
			num = rand.nextInt(RANDOM);
			bst10.add(num);
		}

		System.out.println(" --> 10 BinarySearchTree created and " + capacity + " elements added each.");

		RedBlackTree<Integer> rbt1 = new RedBlackTree<Integer>();
		RedBlackTree<Integer> rbt2 = new RedBlackTree<Integer>();
		RedBlackTree<Integer> rbt3 = new RedBlackTree<Integer>();
		RedBlackTree<Integer> rbt4 = new RedBlackTree<Integer>();
		RedBlackTree<Integer> rbt5 = new RedBlackTree<Integer>();
		RedBlackTree<Integer> rbt6 = new RedBlackTree<Integer>();
		RedBlackTree<Integer> rbt7 = new RedBlackTree<Integer>();
		RedBlackTree<Integer> rbt8 = new RedBlackTree<Integer>();
		RedBlackTree<Integer> rbt9 = new RedBlackTree<Integer>();
		RedBlackTree<Integer> rbt10 = new RedBlackTree<Integer>();
		rand = new Random();
		while( rbt1.size()<capacity ){
			num = rand.nextInt(RANDOM);
			rbt1.add(num);
		}

		rand = new Random();
		while( rbt2.size()<capacity ){
			num = rand.nextInt(RANDOM);
			rbt2.add(num);
		}

		rand = new Random();
		while( rbt3.size()<capacity ){
			num = rand.nextInt(RANDOM);
			rbt3.add(num);
		}

		rand = new Random();
		while( rbt4.size()<capacity ){
			num = rand.nextInt(RANDOM);
			rbt4.add(num);
		}

		rand = new Random();
		while( rbt5.size()<capacity ){
			num = rand.nextInt(RANDOM);
			rbt5.add(num);
		}

		rand = new Random();
		while( rbt6.size()<capacity ){
			num = rand.nextInt(RANDOM);
			rbt6.add(num);
		}

		rand = new Random();
		while( rbt7.size()<capacity ){
			num = rand.nextInt(RANDOM);
			rbt7.add(num);
		}

		rand = new Random();
		while( rbt8.size()<capacity ){
			num = rand.nextInt(RANDOM);
			rbt8.add(num);
		}

		rand = new Random();
		while( rbt9.size()<capacity ){
			num = rand.nextInt(RANDOM);
			rbt9.add(num);
		}

		rand = new Random();
		while( rbt10.size()<capacity ){
			num = rand.nextInt(RANDOM);
			rbt10.add(num);
		}
	
		System.out.println(" --> 10 RedBlackTree created and " + capacity + " elements added each.");

		BTree<Integer> bt1 = new BTree<Integer>(4);
		BTree<Integer> bt2 = new BTree<Integer>(4);
		BTree<Integer> bt3 = new BTree<Integer>(4);
		BTree<Integer> bt4 = new BTree<Integer>(4);
		BTree<Integer> bt5 = new BTree<Integer>(4);
		BTree<Integer> bt6 = new BTree<Integer>(4);
		BTree<Integer> bt7 = new BTree<Integer>(4);
		BTree<Integer> bt8 = new BTree<Integer>(4);
		BTree<Integer> bt9 = new BTree<Integer>(4);
		BTree<Integer> bt10 = new BTree<Integer>(4);

		AVLTree<Integer> numbers1 = new AVLTree<Integer>();
		rand = new Random();
		num = rand.nextInt(RANDOM);
		numbers1.add( num );

		while( numbers1.size()<capacity ){
			num = rand.nextInt(RANDOM);
			numbers1.add( num );
		}

		Iterator<Integer> itr1 = numbers1.iterator();
		while(itr1.hasNext()){
			num = itr1.next();
			bt1.add( num );
			bt2.add( num );
			bt3.add( num );
			bt4.add( num );
			bt5.add( num );
			bt6.add( num );
			bt7.add( num );
			bt8.add( num );
			bt9.add( num );
			bt10.add( num );
		}

		System.out.println(" --> 10 BTree created and " + capacity + " elements added each.");

		SkipList<Integer> sl1 = new SkipList<Integer>();
		SkipList<Integer> sl2 = new SkipList<Integer>();
		SkipList<Integer> sl3 = new SkipList<Integer>();
		SkipList<Integer> sl4 = new SkipList<Integer>();
		SkipList<Integer> sl5 = new SkipList<Integer>();
		SkipList<Integer> sl6 = new SkipList<Integer>();
		SkipList<Integer> sl7 = new SkipList<Integer>();
		SkipList<Integer> sl8 = new SkipList<Integer>();
		SkipList<Integer> sl9 = new SkipList<Integer>();
		SkipList<Integer> sl10 = new SkipList<Integer>();

		AVLTree<Integer> numbers2 = new AVLTree<Integer>();
		rand = new Random();
		num = rand.nextInt(RANDOM);
		numbers2.add( num );

		while( numbers2.size()<capacity ){
			num = rand.nextInt(RANDOM);
			numbers2.add( num );
		}

		Iterator<Integer> itr2 = numbers2.iterator();
		while(itr2.hasNext()){
			num = itr2.next();
			sl1.add( num );
			sl2.add( num );
			sl3.add( num );
			sl4.add( num );
			sl5.add( num );
			sl6.add( num );
			sl7.add( num );
			sl8.add( num );
			sl9.add( num );
			sl10.add( num );
		}
		System.out.println(" --> 10 SkipList created and "+ capacity + " elements added each.");
//------------------------------------------------------------------------------------------------------------
		System.out.println("\n*** BinarySearchTree ***");
		total = 0;
		long startTime = System.nanoTime();
		rand = new Random();
		while( bst1.size()<capacity+ONE_HUNDRED ){
			num = rand.nextInt(RANDOM);
			bst1.add(num);
		}
		long endTime = System.nanoTime();
		long duration = (endTime - startTime);
		System.out.println("\n --> Insert 100 extra random numbers into the bst1: " + duration + " nanoseconds");
		total += duration;

		startTime = System.nanoTime();
		rand = new Random();
		while( bst2.size()<capacity+ONE_HUNDRED ){
			num = rand.nextInt(RANDOM);
			bst2.add(num);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the bst2: " + duration + " nanoseconds");
		total += duration;

		startTime = System.nanoTime();
		rand = new Random();
		while( bst3.size()<capacity+ONE_HUNDRED ){
			num = rand.nextInt(RANDOM);
			bst3.add(num);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the bst3: " + duration + " nanoseconds");
		total += duration;
		
		startTime = System.nanoTime();
		rand = new Random();
		while( bst4.size()<capacity+ONE_HUNDRED ){
			num = rand.nextInt(RANDOM);
			bst4.add(num);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the bst4: " + duration + " nanoseconds");
		total += duration;
		
		startTime = System.nanoTime();
		rand = new Random();
		while( bst5.size()<capacity+ONE_HUNDRED ){
			num = rand.nextInt(RANDOM);
			bst5.add(num);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the bst5: " + duration + " nanoseconds");
		total += duration;
		
		startTime = System.nanoTime();
		rand = new Random();
		while( bst6.size()<capacity+ONE_HUNDRED ){
			num = rand.nextInt(RANDOM);
			bst6.add(num);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the bst6: " + duration + " nanoseconds");
		total += duration;
		
		startTime = System.nanoTime();
		rand = new Random();
		while( bst7.size()<capacity+ONE_HUNDRED ){
			num = rand.nextInt(RANDOM);
			bst7.add(num);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the bst7: " + duration + " nanoseconds");
		total += duration;
		
		startTime = System.nanoTime();
		rand = new Random();
		while( bst8.size()<capacity+ONE_HUNDRED ){
			num = rand.nextInt(RANDOM);
			bst8.add(num);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the bst8: " + duration + " nanoseconds");
		total += duration;
		
		startTime = System.nanoTime();
		rand = new Random();
		while( bst9.size()<capacity+ONE_HUNDRED ){
			num = rand.nextInt(RANDOM);
			bst9.add(num);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the bst9: " + duration + " nanoseconds");
		total += duration;
		
		startTime = System.nanoTime();
		rand = new Random();
		while( bst10.size()<capacity+ONE_HUNDRED ){
			num = rand.nextInt(RANDOM);
			bst10.add(num);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the bst10: " + duration + " nanoseconds");
		total += duration;

		System.out.println("\n ----> Insert 100 extra random numbers into the BinarySearchTree(Average Time): " + (double)total/10 + " nanoseconds");

//------------------------------------------------------------------------------------------------------------
		System.out.println("\n*** RedBlackTree ***");
		total = 0;
		startTime = System.nanoTime();
		rand = new Random();
		while( rbt1.size()<capacity+ONE_HUNDRED ){
			num = rand.nextInt(RANDOM);
			rbt1.add(num);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println("\n --> Insert 100 extra random numbers into the rbt1: " + duration + " nanoseconds");
		total += duration;

		startTime = System.nanoTime();
		rand = new Random();
		while( rbt2.size()<capacity+ONE_HUNDRED ){
			num = rand.nextInt(RANDOM);
			rbt2.add(num);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the rbt2: " + duration + " nanoseconds");
		total += duration;

		startTime = System.nanoTime();
		rand = new Random();
		while( rbt3.size()<capacity+ONE_HUNDRED ){
			num = rand.nextInt(RANDOM);
			rbt3.add(num);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the rbt3: " + duration + " nanoseconds");
		total += duration;

		startTime = System.nanoTime();
		rand = new Random();
		while( rbt4.size()<capacity+ONE_HUNDRED ){
			num = rand.nextInt(RANDOM);
			rbt4.add(num);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the rbt4: " + duration + " nanoseconds");
		total += duration;

		startTime = System.nanoTime();
		rand = new Random();
		while( rbt5.size()<capacity+ONE_HUNDRED ){
			num = rand.nextInt(RANDOM);
			rbt5.add(num);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the rbt5: " + duration + " nanoseconds");
		total += duration;

		startTime = System.nanoTime();
		rand = new Random();
		while( rbt6.size()<capacity+ONE_HUNDRED ){
			num = rand.nextInt(RANDOM);
			rbt6.add(num);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the rbt6: " + duration + " nanoseconds");
		total += duration;

		startTime = System.nanoTime();
		rand = new Random();
		while( rbt7.size()<capacity+ONE_HUNDRED ){
			num = rand.nextInt(RANDOM);
			rbt7.add(num);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the rbt7: " + duration + " nanoseconds");
		total += duration;

		startTime = System.nanoTime();
		rand = new Random();
		while( rbt8.size()<capacity+ONE_HUNDRED ){
			num = rand.nextInt(RANDOM);
			rbt8.add(num);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the rbt8: " + duration + " nanoseconds");
		total += duration;

		startTime = System.nanoTime();
		rand = new Random();
		while( rbt9.size()<capacity+ONE_HUNDRED ){
			num = rand.nextInt(RANDOM);
			rbt9.add(num);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the rbt9: " + duration + " nanoseconds");
		total += duration;

		startTime = System.nanoTime();
		rand = new Random();
		while( rbt10.size()<capacity+ONE_HUNDRED ){
			num = rand.nextInt(RANDOM);
			rbt10.add(num);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the rbt10: " + duration + " nanoseconds");
		total += duration;
		System.out.println("\n ----> Insert 100 extra random numbers into the RedBlackTree(Average Time): " + (double)total/10 + " nanoseconds");

//------------------------------------------------------------------------------------------------------------

		System.out.println("\n*** BTree ***");
		total = 0;
		rand = new Random();
		while( numbers1.size()<capacity+ONE_HUNDRED ){
			num = rand.nextInt(RANDOM);
			numbers1.add( num );
		}

		int count = 0;
		itr1 = numbers1.iterator();
		startTime = System.nanoTime();
		while(itr1.hasNext()){
			count++;
			num = itr1.next();
			if(count>=capacity && count<capacity+ONE_HUNDRED){
				bt1.add( num );
			}
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println("\n --> Insert 100 extra random numbers into the bt1: " + duration + " nanoseconds");
		total += duration;

		count = 0;
		itr1 = numbers1.iterator();
		startTime = System.nanoTime();
		while(itr1.hasNext()){
			count++;
			num = itr1.next();
			if(count>=capacity && count<capacity+ONE_HUNDRED){
				bt2.add( num );
			}
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the bt2: " + duration + " nanoseconds");
		total += duration;

		count = 0;
		itr1 = numbers1.iterator();
		startTime = System.nanoTime();
		while(itr1.hasNext()){
			count++;
			num = itr1.next();
			if(count>=capacity && count<capacity+ONE_HUNDRED){
				bt3.add( num );
			}
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the bt3: " + duration + " nanoseconds");
		total += duration;

		count = 0;
		itr1 = numbers1.iterator();
		startTime = System.nanoTime();
		while(itr1.hasNext()){
			count++;
			num = itr1.next();
			if(count>=capacity && count<capacity+ONE_HUNDRED){
				bt4.add( num );
			}
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the bt4: " + duration + " nanoseconds");
		total += duration;

		count = 0;
		itr1 = numbers1.iterator();
		startTime = System.nanoTime();
		while(itr1.hasNext()){
			count++;
			num = itr1.next();
			if(count>=capacity && count<capacity+ONE_HUNDRED){
				bt5.add( num );
			}
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the bt5: " + duration + " nanoseconds");
		total += duration;

		count = 0;
		itr1 = numbers1.iterator();
		startTime = System.nanoTime();
		while(itr1.hasNext()){
			count++;
			num = itr1.next();
			if(count>=capacity && count<capacity+ONE_HUNDRED){
				bt6.add( num );
			}
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the bt6: " + duration + " nanoseconds");
		total += duration;

		count = 0;
		itr1 = numbers1.iterator();
		startTime = System.nanoTime();
		while(itr1.hasNext()){
			count++;
			num = itr1.next();
			if(count>=capacity && count<capacity+ONE_HUNDRED){
				bt7.add( num );
			}
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the bt7: " + duration + " nanoseconds");
		total += duration;

		count = 0;
		itr1 = numbers1.iterator();
		startTime = System.nanoTime();
		while(itr1.hasNext()){
			count++;
			num = itr1.next();
			if(count>=capacity && count<capacity+ONE_HUNDRED){
				bt8.add( num );
			}
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the bt8: " + duration + " nanoseconds");
		total += duration;

		count = 0;
		itr1 = numbers1.iterator();
		startTime = System.nanoTime();
		while(itr1.hasNext()){
			count++;
			num = itr1.next();
			if(count>=capacity && count<capacity+ONE_HUNDRED){
				bt9.add( num );
			}
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the bt9: " + duration + " nanoseconds");
		total += duration;

		count = 0;
		itr1 = numbers1.iterator();
		startTime = System.nanoTime();
		while(itr1.hasNext()){
			count++;
			num = itr1.next();
			if(count>=capacity && count<capacity+ONE_HUNDRED){
				bt10.add( num );
			}
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the bt10: " + duration + " nanoseconds");
		total += duration;
		System.out.println("\n ----> Insert 100 extra random numbers into the BTree(Average Time): " + (double)total/10 + " nanoseconds");

//------------------------------------------------------------------------------------------------------------

		System.out.println("\n*** SkipList ***");
		total = 0;
		rand = new Random();
		while( numbers2.size()<capacity+ONE_HUNDRED ){
			num = rand.nextInt(RANDOM);
			numbers2.add( num );
		}

		count = 0;
		itr2 = numbers2.iterator();
		startTime = System.nanoTime();
		while(itr2.hasNext()){
			count++;
			num = itr2.next();
			if(count>=capacity && count<capacity+ONE_HUNDRED){
				bt1.add( num );
			}
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println("\n --> Insert 100 extra random numbers into the sl1: " + duration + " nanoseconds");
		total += duration;

		count = 0;
		itr2 = numbers2.iterator();
		startTime = System.nanoTime();
		while(itr2.hasNext()){
			count++;
			num = itr2.next();
			if(count>=capacity && count<capacity+ONE_HUNDRED){
				bt2.add( num );
			}
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the sl2: " + duration + " nanoseconds");
		total += duration;

		count = 0;
		itr2 = numbers2.iterator();
		startTime = System.nanoTime();
		while(itr2.hasNext()){
			count++;
			num = itr2.next();
			if(count>=capacity && count<capacity+ONE_HUNDRED){
				bt3.add( num );
			}
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the sl3: " + duration + " nanoseconds");
		total += duration;

		count = 0;
		itr2 = numbers2.iterator();
		startTime = System.nanoTime();
		while(itr2.hasNext()){
			count++;
			num = itr2.next();
			if(count>=capacity && count<capacity+ONE_HUNDRED){
				bt4.add( num );
			}
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the sl4: " + duration + " nanoseconds");
		total += duration;

		count = 0;
		itr2 = numbers2.iterator();
		startTime = System.nanoTime();
		while(itr2.hasNext()){
			count++;
			num = itr2.next();
			if(count>=capacity && count<capacity+ONE_HUNDRED){
				bt5.add( num );
			}
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the sl5: " + duration + " nanoseconds");
		total += duration;

		count = 0;
		itr2 = numbers2.iterator();
		startTime = System.nanoTime();
		while(itr2.hasNext()){
			count++;
			num = itr2.next();
			if(count>=capacity && count<capacity+ONE_HUNDRED){
				bt6.add( num );
			}
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the sl6: " + duration + " nanoseconds");
		total += duration;

		count = 0;
		itr2 = numbers2.iterator();
		startTime = System.nanoTime();
		while(itr2.hasNext()){
			count++;
			num = itr2.next();
			if(count>=capacity && count<capacity+ONE_HUNDRED){
				bt7.add( num );
			}
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the sl7: " + duration + " nanoseconds");
		total += duration;

		count = 0;
		itr2 = numbers2.iterator();
		startTime = System.nanoTime();
		while(itr2.hasNext()){
			count++;
			num = itr2.next();
			if(count>=capacity && count<capacity+ONE_HUNDRED){
				bt8.add( num );
			}
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the sl8: " + duration + " nanoseconds");
		total += duration;

		count = 0;
		itr2 = numbers2.iterator();
		startTime = System.nanoTime();
		while(itr2.hasNext()){
			count++;
			num = itr2.next();
			if(count>=capacity && count<capacity+ONE_HUNDRED){
				bt9.add( num );
			}
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the sl9: " + duration + " nanoseconds");
		total += duration;

		count = 0;
		itr2 = numbers2.iterator();
		startTime = System.nanoTime();
		while(itr2.hasNext()){
			count++;
			num = itr2.next();
			if(count>=capacity && count<capacity+ONE_HUNDRED){
				bt10.add( num );
			}
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" --> Insert 100 extra random numbers into the sl10: " + duration + " nanoseconds");
		total += duration;
		System.out.println("\n ----> Insert 100 extra random numbers into the SkipList(Average Time): " + (double)total/10 + " nanoseconds");

	}
}