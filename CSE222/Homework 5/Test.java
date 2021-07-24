import java.lang.*;

public class Test{

    private static final int SMALL_SIZED = 10;
    private static final int MEDIUM_SIZED = 100;
    private static final int LARGE_SIZED = 1000;

	public static void main( String args[] ){
	//	driverPart2();
		testPart1();
		testPart2();
	}
	/*Driver for part2*/
	public static void driverPart2(){
		System.out.println("\n------------------------------------");
		System.out.println("----------DRIVER FOR PART2----------");
		System.out.println("------------------------------------\n");

		System.out.println("----> HashtableChain with Integer,Integer\n");
		HashtableChain<Integer, Integer> htChain = new HashtableChain<Integer, Integer>();
		System.out.println(" The HashtableChain with 11 CAPACITY: \n" + htChain);
		System.out.println(" -> size() ... " + htChain.size());
		System.out.println(" -> isEmpty() ... " + htChain.isEmpty());
		System.out.println("");
		for(int i=0; i<10; i++){
			System.out.println(" -> Put Key: " + (2*i+i) + " Value: " + i + " ... removed the old value: " + htChain.put(2*i+i,i));
		}
		System.out.println(" The new HashtableChain:\n" + htChain);
		System.out.println(" -> Put Key: " + 19 + " Value: " + 90 + " ... removed the old value: " + htChain.put(19,90));
		System.out.println(" -> Put Key: " + 13 + " Value: " + 20 + " ... removed the old value: " + htChain.put(13,20));
		System.out.println(" -> Put Key: " + 15 + " Value: " + 20 + " ... removed the old value: " + htChain.put(15,20));
		System.out.println(" -> Put Key: " + 35 + " Value: " + 4 + " ... removed the old value: " + htChain.put(35,20));

		System.out.println(" The new HashtableChain:\n" + htChain);
		System.out.println(" -> size() ... " + htChain.size());
		System.out.println(" -> isEmpty() ... " + htChain.isEmpty());
		System.out.println(" -> Get Key 19 ... found the value: " + htChain.get(19));
		System.out.println(" -> Get Key 100 ... found the value: " + htChain.get(100));
		System.out.println(" NOTE: null means that there is no the value.\n");

		System.out.println(" -> Remove Key 19 ... removed value: " + htChain.remove(19));
		System.out.println(" -> Remove Key 13 ... removed value: " + htChain.remove(13));
		System.out.println(" -> Remove Key 100 ... removed value: " + htChain.remove(100));
		System.out.println(" NOTE: null means that there is no the value so remove feature is failed.\n");
		System.out.println(" The new HashtableChain:\n" + htChain);

		/***************************************************************************************************/
		System.out.println("----> HashtableChainTreeSet with Integer,Integer\n");
		HashtableChainTreeSet<Integer, Integer> htChainTreeSet = new HashtableChainTreeSet<Integer, Integer>();
		System.out.println(" The HashtableChainTreeSet with 11 CAPACITY: \n" + htChainTreeSet);
		System.out.println(" -> size() ... " + htChainTreeSet.size());
		System.out.println(" -> isEmpty() ... " + htChainTreeSet.isEmpty());
		System.out.println("");
		for(int i=0; i<10; i++){
			System.out.println(" -> Put Key: " + (2*i+i) + " Value: " + i + " ... removed the old value: " + htChainTreeSet.put(2*i+i,i));
		}
		System.out.println(" The new HashtableChainTreeSet:\n" + htChainTreeSet);
		System.out.println(" -> Put Key: " + 19 + " Value: " + 90 + " ... removed the old value: " + htChainTreeSet.put(19,90));
		System.out.println(" -> Put Key: " + 13 + " Value: " + 20 + " ... removed the old value: " + htChainTreeSet.put(13,20));
		System.out.println(" -> Put Key: " + 15 + " Value: " + 20 + " ... removed the old value: " + htChainTreeSet.put(15,20));
		System.out.println(" -> Put Key: " + 35 + " Value: " + 4 + " ... removed the old value: " + htChainTreeSet.put(35,20));

		System.out.println(" The new HashtableChainTreeSet:\n" + htChainTreeSet);
		System.out.println(" -> size() ... " + htChainTreeSet.size());
		System.out.println(" -> isEmpty() ... " + htChainTreeSet.isEmpty());
		System.out.println(" -> Get Key 19 ... found the value: " + htChainTreeSet.get(19));
		System.out.println(" -> Get Key 100 ... found the value: " + htChainTreeSet.get(100));
		System.out.println(" NOTE: null means that there is no the value.\n");

		System.out.println(" -> Remove Key 19 ... removed value: " + htChainTreeSet.remove(19));
		System.out.println(" -> Remove Key 24 ... removed value: " + htChainTreeSet.remove(24));
		System.out.println(" -> Remove Key 100 ... removed value: " + htChainTreeSet.remove(100));
		System.out.println(" NOTE: null means that there is no the value so remove feature is failed.\n");
		System.out.println(" The new HashtableChainTreeSet:\n" + htChainTreeSet);

		/***************************************************************************************************/
		System.out.println("----> HashtableCoalesced with Integer,Integer\n");
		HashtableCoalesced<Integer, Integer> htCoalesced = new HashtableCoalesced<Integer, Integer>();
		System.out.println(" The HashtableCoalesced with 11 CAPACITY: \n" + htCoalesced);
		System.out.println(" -> size() ... " + htCoalesced.size());
		System.out.println(" -> isEmpty() ... " + htCoalesced.isEmpty());
		System.out.println("");
		for(int i=0; i<10; i++){
			System.out.println(" -> Put Key: " + (2*i+i) + " Value: " + i + " ... removed the old value: " + htCoalesced.put(2*i+i,i));
		}
		System.out.println(" The new HashtableCoalesced:\n" + htCoalesced);
		System.out.println(" -> Put Key: " + 19 + " Value: " + 90 + " ... removed the old value: " + htCoalesced.put(19,90));
		System.out.println(" -> Put Key: " + 13 + " Value: " + 20 + " ... removed the old value: " + htCoalesced.put(13,20));
		System.out.println(" -> Put Key: " + 15 + " Value: " + 20 + " ... removed the old value: " + htCoalesced.put(15,20));
		System.out.println(" -> Put Key: " + 35 + " Value: " + 4 + " ... removed the old value: " + htCoalesced.put(35,20));

		System.out.println(" The new HashtableCoalesced:\n" + htCoalesced);
		System.out.println(" -> size() ... " + htCoalesced.size());
		System.out.println(" -> isEmpty() ... " + htCoalesced.isEmpty());
		System.out.println(" -> Get Key 19 ... found the value: " + htCoalesced.get(19));
		System.out.println(" -> Get Key 100 ... found the value: " + htCoalesced.get(100));
		System.out.println(" NOTE: null means that there is no the value.\n");

		System.out.println(" -> Remove Key 19 ... removed value: " + htCoalesced.remove(19));
		System.out.println(" -> Remove Key 24 ... removed value: " + htCoalesced.remove(24));
		System.out.println(" -> Remove Key 100 ... removed value: " + htCoalesced.remove(100));
		System.out.println(" NOTE: null means that there is no the value so remove feature is failed.\n");
		System.out.println(" The new HashtableCoalesced:\n" + htCoalesced);
	}
	/*Testing Part1*/
	public static void testPart1(){
		System.out.println("\n----------------------------------");
		System.out.println("----------TEST FOR PART1----------");
		System.out.println("----------------------------------\n");
		IterHashMap<Integer, Integer> numbers = new IterHashMap<Integer, Integer>();
	    // Add keys and values
	    numbers.put(0, 100);
	    numbers.put(1, 101);
	    numbers.put(2, 102);
	    numbers.put(3, 103);
	    numbers.put(4, 104);
	    numbers.put(5, 105);
	    numbers.put(6, 106);
	    numbers.put(7, 107);
	    numbers.put(8, 108);
	    numbers.put(9, 109);
	    numbers.put(10, 110);
	    numbers.put(11, 111);
	    numbers.put(12, 112);
	    numbers.put(13, 113);
	    numbers.put(14, 114);
	    numbers.put(15, 115);
		System.out.println("----> Test MapIterator() with Integer,Integer\n");
	    System.out.println("The HashMap: "+numbers);
		MapIteratorInterface<Integer, Integer> iter = numbers.iter();
		System.out.println("\n -> Iterator is created.");
		System.out.print("Print with iterator: ");
		while(iter.hasNext()){
			System.out.print(iter.next()+"  ");
		}
		System.out.println("\n\n -> Now, the iterator is at the last value.");
		System.out.println("hasNext: "+iter.hasNext());
		System.out.println(" -> Because all elements are iterated.");
		System.out.println("next: "+iter.next());
		System.out.println(" -> It returns the first key because there is no not-iterated key in the Map.");
		iter = numbers.iter();
		System.out.println("\n -> Now, the iterator reset. The iterator is at the first value.");
		System.out.println("hasNext: "+iter.hasNext());
		System.out.println(" -> Because all elements are not iterated.");
		System.out.println("prev: "+iter.prev());
		System.out.println(" -> It returns the last key because the iterator is at the first key.");
		iter = numbers.iter();
		System.out.println("\n -> Now, the iterator reset again. The iterator is at the first value.");
		System.out.println("hasNext: "+iter.hasNext());
		System.out.println("next: "+iter.next());
		System.out.println("hasNext: "+iter.hasNext());
		System.out.println("next: "+iter.next());		
		System.out.println("hasNext: "+iter.hasNext());
		System.out.println("next: "+iter.next());		
		System.out.println("hasNext: "+iter.hasNext());
		System.out.println("next: "+iter.next());		
		System.out.println("hasNext: "+iter.hasNext());
		System.out.println("next: "+iter.next());
		System.out.println("hasNext: "+iter.hasNext());

		System.out.println("\n\n----> Test MapIterator(5) with Integer,Integer\n");
		System.out.println("The HashMap: "+numbers);
		MapIteratorInterface<Integer, Integer> iter2 = numbers.iter(5);
		System.out.println("\n -> Iterator an the Key 5 is created.");
		System.out.println("\n\n -> Now, the iterator is at the Key 5");
		System.out.println("hasNext: "+iter2.hasNext());
		System.out.println("next: "+iter2.next());
		System.out.println("hasNext: "+iter2.hasNext());
		System.out.println("next: "+iter2.next());
		System.out.println("hasNext: "+iter2.hasNext());
		System.out.println("next: "+iter2.next());		
		System.out.println("hasNext: "+iter2.hasNext());
		System.out.println("next: "+iter2.next());		
		System.out.println("hasNext: "+iter2.hasNext());
		System.out.println("next: "+iter2.next());		
		System.out.println("hasNext: "+iter2.hasNext());
		System.out.println("next: "+iter2.next());
		System.out.println("hasNext: "+iter2.hasNext());
		System.out.println("next: "+iter2.next());
		System.out.println("hasNext: "+iter2.hasNext());
		System.out.println("next: "+iter2.next());		
		System.out.println("hasNext: "+iter2.hasNext());
		System.out.println("next: "+iter2.next());		
		System.out.println("hasNext: "+iter2.hasNext());
		System.out.println("next: "+iter2.next());
		System.out.println("\n -> Now, the iterator is at the last value.");
		System.out.println("hasNext: "+iter2.hasNext());
		System.out.println(" -> Because all elements are not iterated. The iterator is started Key 5.");
		System.out.println("prev: "+iter2.prev());
		System.out.println("hasNext: "+iter2.hasNext());
		System.out.println("next: "+iter2.next());
		System.out.println("prev: "+iter2.prev());
		System.out.println("prev: "+iter2.prev());
		System.out.println("prev: "+iter2.prev());
		System.out.println("prev: "+iter2.prev());
		System.out.println("prev: "+iter2.prev());

		System.out.println("\n\n----> Test MapIterator(15) with Integer,Integer\n");
		System.out.println("The HashMap: "+numbers);
		MapIteratorInterface<Integer, Integer> iter3 = numbers.iter(15);
		System.out.println("\n -> Iterator an the Key 15 is created.");
		System.out.println("\n -> Now, the iterator is at the Key 15(the iterator is at the last value.)");
		System.out.println("hasNext: "+iter3.hasNext());
		System.out.println(" -> Because all elements are not iterated. The iterator is started Key 5.");
		System.out.println("prev: "+iter3.prev());
		System.out.println("");

		System.out.println("\n\n----> Test MapIterator((non-existing)2021) with Integer,Integer\n");
		System.out.println("The HashMap: "+numbers);
		MapIteratorInterface<Integer, Integer> iter4 = numbers.iter(2021);
		System.out.println("\n -> 2021 is not existing key. So normal iterator(at the first value) is created.");
		System.out.println("hasNext: "+iter4.hasNext());
		System.out.println("next(): "+iter4.next());
		System.out.println("prev: "+iter4.prev());
		System.out.println("");
	}
	/*Testing Part2*/
	public static void testPart2(){
		System.out.println("\n----------------------------------");
		System.out.println("----------TEST FOR PART2----------");
		System.out.println("----------------------------------");

		/*-----------------------------------------------------------------------------------------------*/
		HashtableChain<Integer, Integer> htChain = new HashtableChain<Integer, Integer>();
		HashtableChain<Integer, Integer> htChain2 = new HashtableChain<Integer, Integer>();
		HashtableChain<Integer, Integer> htChain3 = new HashtableChain<Integer, Integer>();
		System.out.println("\n ---> HashtableChain(CAPACITY 101)\n");
		long startTime = System.nanoTime();
		for(int i=0; i<SMALL_SIZED; i++){
			htChain.put(2*i+i,i);
		}
		long endTime = System.nanoTime();
		long duration = (endTime - startTime);
		System.out.println(" Adding 10 elements to empty table: "+ duration + " nanoseconds");

		startTime = System.nanoTime();
		for(int i=0; i<MEDIUM_SIZED; i++){
			htChain2.put(2*i+i,i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Adding 100 elements to empty table: "+ duration + " nanoseconds");

		startTime = System.nanoTime();
		for(int i=0; i<LARGE_SIZED; i++){
			htChain3.put(2*i+i,i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Adding 1000 elements to empty table: "+ duration + " nanoseconds");
		//access existing items
		startTime = System.nanoTime();
		for(int i=0; i<8; i++){
			htChain.get(2*i+i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Access existing items (10 elements table): "+ duration + " nanoseconds");

		startTime = System.nanoTime();
		for(int i=0; i<8; i++){
			htChain2.get(2*i+i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Access existing items (100 elements table): "+ duration + " nanoseconds");

		startTime = System.nanoTime();
		for(int i=0; i<8; i++){
			htChain3.get(2*i+i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Access existing items (1000 elements table): "+ duration + " nanoseconds");
		//access nonexisting items
		startTime = System.nanoTime();
		for(int i=5000; i<5008; i++){
			htChain.get(i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Access non-existing items (10 elements table): "+ duration + " nanoseconds");

		startTime = System.nanoTime();
		for(int i=5000; i<5008; i++){
			htChain2.get(i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Access non-existing items (100 elements table): "+ duration + " nanoseconds");

		startTime = System.nanoTime();
		for(int i=5000; i<5008; i++){
			htChain3.get(i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Access non-existing items (1000 elements table): "+ duration + " nanoseconds");
		//remove nonexisting
		startTime = System.nanoTime();
		for(int i=5000; i<5008; i++){
			htChain.remove(i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Remove non-existing items (10 elements table): "+ duration + " nanoseconds");

		startTime = System.nanoTime();
		for(int i=5000; i<5008; i++){
			htChain2.remove(i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Remove non-existing items (100 elements table): "+ duration + " nanoseconds");

		startTime = System.nanoTime();
		for(int i=5000; i<5008; i++){
			htChain3.remove(i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Remove non-existing items (1000 elements table): "+ duration + " nanoseconds");
		//remove existing
		startTime = System.nanoTime();
		for(int i=0; i<8; i++){
			htChain.remove(2*i+i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Remove existing items (10 elements table): "+ duration + " nanoseconds");

		startTime = System.nanoTime();
		for(int i=0; i<8; i++){
			htChain2.remove(2*i+i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Remove existing items (100 elements table): "+ duration + " nanoseconds");

		startTime = System.nanoTime();
		for(int i=0; i<8; i++){
			htChain3.remove(2*i+i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Remove existing items (1000 elements table): "+ duration + " nanoseconds");
		/*-----------------------------------------------------------------------------------------------*/
		HashtableChainTreeSet<Integer, Integer> htChainTreeSet = new HashtableChainTreeSet<Integer, Integer>();
		HashtableChainTreeSet<Integer, Integer> htChainTreeSet2 = new HashtableChainTreeSet<Integer, Integer>();
		HashtableChainTreeSet<Integer, Integer> htChainTreeSet3 = new HashtableChainTreeSet<Integer, Integer>();
		System.out.println("\n ---> HashtableChainTreeSet(CAPACITY 101)\n");
		startTime = System.nanoTime();
		for(int i=0; i<SMALL_SIZED; i++){
			htChainTreeSet.put(2*i+i,i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Adding 10 elements to empty table: "+ duration + " nanoseconds");

		startTime = System.nanoTime();
		for(int i=0; i<MEDIUM_SIZED; i++){
			htChainTreeSet2.put(2*i+i,i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Adding 100 elements to empty table: "+ duration + " nanoseconds");

		startTime = System.nanoTime();
		for(int i=0; i<LARGE_SIZED; i++){
			htChainTreeSet3.put(2*i+i,i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Adding 1000 elements to empty table: "+ duration + " nanoseconds");
		//access existing items
		startTime = System.nanoTime();
		for(int i=0; i<8; i++){
			htChainTreeSet.get(2*i+i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Access existing items (10 elements table): "+ duration + " nanoseconds");

		startTime = System.nanoTime();
		for(int i=0; i<8; i++){
			htChainTreeSet2.get(2*i+i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Access existing items (100 elements table): "+ duration + " nanoseconds");

		startTime = System.nanoTime();
		for(int i=0; i<8; i++){
			htChainTreeSet3.get(2*i+i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Access existing items (1000 elements table): "+ duration + " nanoseconds");
		//access nonexisting items
		startTime = System.nanoTime();
		for(int i=5000; i<5008; i++){
			htChainTreeSet.get(i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Access non-existing items (10 elements table): "+ duration + " nanoseconds");

		startTime = System.nanoTime();
		for(int i=5000; i<5008; i++){
			htChainTreeSet2.get(i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Access non-existing items (100 elements table): "+ duration + " nanoseconds");

		startTime = System.nanoTime();
		for(int i=5000; i<5008; i++){
			htChainTreeSet3.get(i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Access non-existing items (1000 elements table): "+ duration + " nanoseconds");
		//remove nonexisting
		startTime = System.nanoTime();
		for(int i=5000; i<5008; i++){
			htChainTreeSet.remove(i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Remove non-existing items (10 elements table): "+ duration + " nanoseconds");

		startTime = System.nanoTime();
		for(int i=5000; i<5008; i++){
			htChainTreeSet2.remove(i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Remove non-existing items (100 elements table): "+ duration + " nanoseconds");

		startTime = System.nanoTime();
		for(int i=5000; i<5008; i++){
			htChainTreeSet3.remove(i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Remove non-existing items (1000 elements table): "+ duration + " nanoseconds");
		//remove existing
		startTime = System.nanoTime();
		for(int i=0; i<8; i++){
			htChainTreeSet.remove(2*i+i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Remove existing items (10 elements table): "+ duration + " nanoseconds");

		startTime = System.nanoTime();
		for(int i=0; i<8; i++){
			htChainTreeSet2.remove(2*i+i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Remove existing items (100 elements table): "+ duration + " nanoseconds");

		startTime = System.nanoTime();
		for(int i=0; i<8; i++){
			htChainTreeSet3.remove(2*i+i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Remove existing items (1000 elements table): "+ duration + " nanoseconds");
		/*-----------------------------------------------------------------------------------------------*/
		HashtableCoalesced<Integer, Integer> htCoalesced = new HashtableCoalesced<Integer, Integer>();
		HashtableCoalesced<Integer, Integer> htCoalesced2 = new HashtableCoalesced<Integer, Integer>();
		HashtableCoalesced<Integer, Integer> htCoalesced3 = new HashtableCoalesced<Integer, Integer>();

		System.out.println("\n ---> HashtableCoalesced(CAPACITY 101)\n");
		startTime = System.nanoTime();
		for(int i=0; i<SMALL_SIZED; i++){
			htCoalesced.put(2*i+i,i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Adding 10 elements to empty table: "+ duration + " nanoseconds");

		startTime = System.nanoTime();
		for(int i=0; i<MEDIUM_SIZED; i++){
			htCoalesced2.put(2*i+i,i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Adding 100 elements to empty table: "+ duration + " nanoseconds");

		startTime = System.nanoTime();
		for(int i=0; i<LARGE_SIZED; i++){
			htCoalesced3.put(2*i+i,i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Adding 1000 elements to empty table: "+ duration + " nanoseconds");
		//access existing items
		startTime = System.nanoTime();
		for(int i=0; i<8; i++){
			htCoalesced.get(2*i+i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Access existing items (10 elements table): "+ duration + " nanoseconds");

		startTime = System.nanoTime();
		for(int i=0; i<8; i++){
			htCoalesced2.get(2*i+i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Access existing items (100 elements table): "+ duration + " nanoseconds");

		startTime = System.nanoTime();
		for(int i=0; i<8; i++){
			htCoalesced3.get(2*i+i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Access existing items (1000 elements table): "+ duration + " nanoseconds");
		//access nonexisting items
		startTime = System.nanoTime();
		for(int i=5000; i<5008; i++){
			htCoalesced.get(i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Access non-existing items (10 elements table): "+ duration + " nanoseconds");

		startTime = System.nanoTime();
		for(int i=5000; i<5008; i++){
			htCoalesced2.get(i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Access non-existing items (100 elements table): "+ duration + " nanoseconds");

		startTime = System.nanoTime();
		for(int i=5000; i<5008; i++){
			htCoalesced3.get(i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Access non-existing items (1000 elements table): "+ duration + " nanoseconds");
		//remove nonexisting
		startTime = System.nanoTime();
		for(int i=5000; i<5008; i++){
			htCoalesced.remove(i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Remove non-existing items (10 elements table): "+ duration + " nanoseconds");

		startTime = System.nanoTime();
		for(int i=5000; i<5008; i++){
			htCoalesced2.remove(i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Remove non-existing items (100 elements table): "+ duration + " nanoseconds");

		startTime = System.nanoTime();
		for(int i=5000; i<5008; i++){
			htCoalesced3.remove(i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Remove non-existing items (1000 elements table): "+ duration + " nanoseconds");
		//remove existing
		startTime = System.nanoTime();
		for(int i=0; i<8; i++){
			htCoalesced.remove(2*i+i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Remove existing items (10 elements table): "+ duration + " nanoseconds");

		startTime = System.nanoTime();
		for(int i=0; i<8; i++){
			htCoalesced2.remove(2*i+i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Remove existing items (100 elements table): "+ duration + " nanoseconds");

		startTime = System.nanoTime();
		for(int i=0; i<8; i++){
			htCoalesced3.remove(2*i+i);
		}
		endTime = System.nanoTime();
		duration = (endTime - startTime);
		System.out.println(" Remove existing items (1000 elements table): "+ duration + " nanoseconds");
	}
} 
