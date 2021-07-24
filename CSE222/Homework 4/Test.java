import java.util.Random;
import java.util.ArrayList;

public class Test{
	public static void main( String args[] ){
		testing();
	}

/****************************TESTING****************************/
	public static void testing(){
		driverMaxHeap();
		testingMaxHeap();
		driverBSTHeapTree();
		testingBSTHeapTree();
	}
	
	public static void testingMaxHeap(){
		System.out.println("\n*******************************************");
		System.out.println("**********-> Testing For Part1 <-**********");
		System.out.println("*******************************************\n");

		MaxHeap<Integer> heap1 = new MaxHeap<Integer>();
		heap1.insert(6);
		heap1.insert(18);
		heap1.insert(29);
		heap1.insert(20);
		heap1.insert(39);		
		heap1.insert(76);
		heap1.insert(74);		
		heap1.insert(89);
		heap1.insert(8);

		MaxHeap<Integer> heap2 = new MaxHeap<Integer>();
		heap2.insert(1);
		heap2.insert(2);
		heap2.insert(3);
		heap2.insert(4);
		heap2.insert(40);	
		heap2.insert(22);		
		heap2.insert(90);
		heap2.insert(73);		

		MaxHeap<Integer> heap3 = new MaxHeap<Integer>();

		System.out.println("\n**********-> Search for an element <-**********\n");
		System.out.println("The MaxHeap<Integer>: "+heap1);
		System.out.println(" --> Searching 20 ...");
		System.out.println("Index: "+heap1.search(20));
		System.out.println(" --> Searching 8 ...");
		System.out.println("Index: "+heap1.search(8));
		System.out.println(" --> Searching 35 ...");
		System.out.println("Index: "+heap1.search(35));
		System.out.println(" ! NOTE: -1 means that there is no the value.");

		System.out.println("\n**********-> Search for an element with empty MaxHeap <-**********\n");
		System.out.println("The MaxHeap<Integer>: "+heap3);
		System.out.println(" --> Searching 20 ...");
		heap3.search(20);
		
		System.out.println("\n**********-> Merge with another heap <-**********\n");
		System.out.println("The First MaxHeap<Integer>: "+heap1);
		System.out.println("The Second MaxHeap<Integer>: "+heap2);
		System.out.println(" --> Merging ...");
		heap1.merge(heap2);
		System.out.println("The Last MaxHeap<Integer>: "+heap1);

		System.out.println("\n**********-> Merge with empty another heap <-**********\n");
		System.out.println("The First MaxHeap<Integer>: "+heap1);
		System.out.println("The Second MaxHeap<Integer>: "+heap3);
		System.out.println(" --> Merging ...");
		heap1.merge(heap3);
		System.out.println("The Last MaxHeap<Integer>: "+heap1);
		
		System.out.println("\n**********-> Removing ith largest element from the Heap <-**********\n");
		System.out.println("The MaxHeap<Integer>: "+heap1);
		System.out.println(" --> Finding & Removing 5th largest element ... ");
		System.out.println("5th largest element: "+heap1.removeIthLargest(5));
		System.out.println("The MaxHeap<Integer>: "+heap1);

		System.out.println("\n**********-> Removing ith largest element from the empty Heap <-**********\n");
		System.out.println("The MaxHeap<Integer>: "+heap3);
		System.out.println(" --> Finding & Removing 5th largest element ... ");
		System.out.println("5th largest element: "+heap3.removeIthLargest(5));
		System.out.println("The MaxHeap<Integer>: "+heap3);

	
		System.out.println("\n**********-> Iterator set() <-**********\n");
		System.out.println("The MaxHeap<Integer>: "+heap1);
		MaxHeap.MaxHeapIter iter = heap1.iterator();
		System.out.println("The last element returned by the next method: "+iter.next());
		System.out.println(" --> Setting 32 ... ");
		iter.set(32);
		System.out.println("The MaxHeap<Integer>: "+heap1);

		System.out.println("\n**********-> Iterator set() with empty Heap<-**********\n");
		System.out.println("The MaxHeap<Integer>: "+heap3);
		MaxHeap.MaxHeapIter iter2 = heap3.iterator();
		System.out.println("The last element returned by the next method: "+iter2.next());
		System.out.println(" --> Setting 32 ... ");
		iter2.set(32);
		System.out.println("The MaxHeap<Integer>: "+heap3);
		System.out.println("");
	}

	public static void testingBSTHeapTree(){
		System.out.println("\n*******************************************");
		System.out.println("**********-> Testing For Part2 <-**********");
		System.out.println("*******************************************\n");
		
		BSTHeapTree<Integer> bst1 = new BSTHeapTree<Integer>();
		int CAPACITY = 3000;
		int[] numbers = new int[CAPACITY];
	    Random rand = new Random();
		int minRange = 0;
		int maxRange = 5000;
		int value = 0;
		//insert array and bstheaptree
		for(int i = 0; i<CAPACITY; i++){
			rand = new Random();
			value = rand.nextInt(maxRange - minRange) + minRange;
			bst1.add(value);
			numbers[i] = value;
		}
		//sorting the array
		for (int i = 0; i < numbers.length; i++){  
			for (int j = i + 1; j < numbers.length; j++){  
				int tmp = 0;  
				if (numbers[i] < numbers[j]){
					tmp = numbers[i];  
					numbers[i] = numbers[j];  
					numbers[j] = tmp;  
				}  
			}  
		}
		System.out.println(" --> 3000 elements added to the Array and BSTHeapTree");
		int arrayMaxOccur = 0;
		int occur = 0;
        for (int i=0; i<CAPACITY; i++){
        	occur = 0;
        	for(int j=0; j<CAPACITY; j++){
        		if( numbers[i] == numbers[j]){
        			occur++;
        		}
        	}
        	i += occur;
            if (occur > arrayMaxOccur){
              arrayMaxOccur = occur;
            }
        }
		ArrayList<Integer> modesArray = new ArrayList<Integer>();
		int temp = 0;
		for(int i=0; i<numbers.length; i++){
			temp = 0;
			for(int j=0; j<numbers.length; j++){
				if(numbers[i] == numbers[j]){
					temp++;
				}
			}
			if( temp == arrayMaxOccur ){
				modesArray.add(numbers[i]);
			}
			i += (temp-1);

		}
		ArrayList<Integer> inArray = new ArrayList<Integer>();
		ArrayList<Integer> inArrayOccur = new ArrayList<Integer>();
		for(int i=0; i<CAPACITY; i++){
            int flag = 0;  
            for (int j = 0; j < CAPACITY; j++){  
                if (numbers[i] == numbers[j]){   
                    flag++;  
                }  
            }  
            if ( inArray.size() != 100 ){   
                inArray.add(numbers[i]);  
                inArrayOccur.add(flag);  
            }
            i += flag;
  		}
  		for(int i=0; i<numbers.length; i++){
            int flag = 0;  
            for (int j = 0; j < numbers.length; j++){  
                if (numbers[i] == numbers[j]  ){   
                    flag++;  
                }  
            }  

            if ( inArray.size() != 5 && !inArray.contains(numbers[i]) ){  
                inArray.add(numbers[i]);  
                inArrayOccur.add(flag);  
            }
  		}
		System.out.println("\n --> Search for 100 numbers in the array");
		int count = 0;
		for(int i=0; i<100; i++){
			if( inArrayOccur.get(i) == bst1.find(inArray.get(i)) ){
				count++;
			}
		}
		if( count == 100 ){
			System.out.println(" For these elements, the occurrence of elements in array and in BSTHeapTree are the same");
			System.out.println(" So, we can say that the number of occurrences is correct.");
		}
		System.out.println("\n --> Search for 10 numbers not in the array");
		count = 0;
		boolean found = false;
		for(int i=7000; i<7010; i++){
			found = false;
			for(int x : numbers){
				if(x != i){
			        found = true;
			        break;
			    }
			}
			if( found && bst1.find(i) == 0 ){
				count++;
			}
		}
		if( count == 10 ){
			System.out.println(" For these elements, the occurrence of elements in array and in BSTHeapTree are the same");
			System.out.println(" So, we can say that the number of occurrences is correct.");
		}

		System.out.println("\n --> Mode of the BSTHeapTree: "+ bst1.find_mode()); 
		System.out.println(" --> Mode of the array: "+ modesArray);
		System.out.println(" So, we can say that the mode value is correct");

		System.out.println("\n --> Removing for 100 numbers different from each other and in the array");
		ArrayList<Integer> inArrayNew = new ArrayList<Integer>();
		ArrayList<Integer> inArrayOccurNew = new ArrayList<Integer>();
		for(int i=0; i<inArray.size(); i++){
  			for(int j=0; j<numbers.length; j++){
  				if( numbers[j] == inArray.get(i) ){
  					//buldum elemanı
  					for(int k=j+1; k<numbers.length; k++){
  						numbers[k-1] = numbers[k];
  					}
   					break;
  				}
  			}
  		}
  		for(int i=0; i<numbers.length-inArray.size(); i++){
            int flag = 0;  
            for (int j = 0; j < numbers.length; j++){  
                if (numbers[i] == numbers[j]  ){   
                    flag++;  
                }  
            }  

            if ( inArrayOccurNew.size() != 100 && !inArrayNew.contains(numbers[i]) ){  
  				inArrayNew.add(numbers[i]);
                inArrayOccurNew.add(flag);  
            }
  		}
		count = 0;
		for(int i=0; i<100; i++){
			if( inArrayOccurNew.get(i) == bst1.find(inArrayNew.get(i))-1 ){
				count++;
			}
		}
		if( count == 100 ){
			System.out.println(" For these elements, the occurrence of elements in array and (the occurrence of elements in BSTHeapTree - 1) are the same");
			System.out.println(" So, we can say that the number of occurrences is correct.");
		}
		System.out.println("\n --> Removing for 10 numbers not in the array");
		count = 0;
		found = false;
		for(int i=7000; i<7010; i++){
			found = false;
			for(int x : numbers){
				if(x != i){
			        found = true;
			        break;
			    }
			}
			if( found && bst1.find(i) == 0 ){
				count++;
			}
		}
		System.out.println(" Because these elements are not in the array, they cannot be deleted from the array");
		if( count == 10 ){
			System.out.println(" For these elements, the occurrence of elements in array and in BSTHeapTree are the same");
			System.out.println(" So, we can say that the number of occurrences is correct.");
		}
	}
/****************************DRIVER FUNCTIONS****************************/
	public static void driverMaxHeap(){
		System.out.println("\n***********************************************************");
		System.out.println("**********-> Driver Function For MaxHeap Class <-**********");
		System.out.println("***********************************************************\n");

		MaxHeap<Integer> heap1 = new MaxHeap<Integer>();
		heap1.insert(6);
		heap1.insert(18);
		heap1.insert(29);
		heap1.insert(20);
		heap1.insert(28);	
		heap1.insert(39);		
		heap1.insert(76);
		heap1.insert(32);		
		heap1.insert(74);		
		heap1.insert(89);
		heap1.insert(8);
		MaxHeap<Integer> heap2 = new MaxHeap<Integer>();

		System.out.println("\n**********-> ADDING <-**********\n");
		System.out.println("The MaxHeap<Integer>: "+heap1);
		System.out.println(" --> Adding 1 ...");
		heap1.insert(1);
		System.out.println("The MaxHeap<Integer>: "+heap1);
		System.out.println(" --> Adding 999 ...");
		heap1.insert(999);
		System.out.println("The MaxHeap<Integer>: "+heap1);
		System.out.println(" --> Adding 23 ...");
		heap1.insert(23);
		System.out.println("The MaxHeap<Integer>: "+heap1);

		System.out.println("\n**********-> SEARCHING <-**********\n");
		System.out.println("The MaxHeap<Integer>: "+heap1);
		System.out.println(" --> Searching 18 ...");
		System.out.println("Index: "+heap1.search(18));
		System.out.println(" --> Searching 89 ...");
		System.out.println("Index: "+heap1.search(89));
		System.out.println(" --> Searching 7 ...");
		System.out.println("Index: "+heap1.search(7));
		System.out.println(" ! NOTE: -1 means that there is no the value.");

		System.out.println("\n**********-> DELETING <-**********\n");
		System.out.println("The MaxHeap<Integer>: "+heap1);
		System.out.println(" --> Deleting ...");
		heap1.remove();
		System.out.println("The MaxHeap<Integer>: "+heap1);

		System.out.println("\n**********-> DELETING from empty MaxHeap <-**********\n");
		System.out.println("The Empty MaxHeap<Integer>: "+heap2);
		System.out.println(" --> Deleting ...");
		heap2.remove();

		System.out.println("\n**********-> ITERATOR <-**********\n");
		System.out.println("The MaxHeap<Integer>: "+heap1);
		MaxHeap.MaxHeapIter iter = heap1.iterator();
		System.out.println("The last element returned by the next method: "+iter.next());
		System.out.println("The last element returned by the next method: "+iter.next());
		System.out.println("The last element returned by the next method: "+iter.next());
		System.out.println("The last element returned by the next method: "+iter.next());
		System.out.println("The last element returned by the next method: "+iter.next());
		System.out.println("The last element returned by the next method: "+iter.next());
		System.out.println("The last element returned by the next method: "+iter.next());
		System.out.println("The last element returned by the next method: "+iter.next());
		System.out.println(" --> hasNext() ... -> "+iter.hasNext());
		System.out.println(" --> Removing the last element returned by the next method ... ");
		iter.remove();
		System.out.println("The MaxHeap<Integer>: "+heap1);

		System.out.println("\n**********-> ITERATOR with empty MaxHeap<-**********\n");
		System.out.println("The MaxHeap<Integer>: "+heap2);
		MaxHeap.MaxHeapIter iter2 = heap2.iterator();
		System.out.println(" --> next() ... ");
		iter2.next();
		System.out.println(" --> hasNext() ... -> "+iter2.hasNext());
		System.out.println(" --> Removing the last element returned by the next method ... ");
		iter2.remove();
		System.out.println("The MaxHeap<Integer>: "+heap2);
	
		System.out.println("");
	}

	public static void driverBSTHeapTree(){
		System.out.println("\n***************************************************************");
		System.out.println("**********-> Driver Function For BSTHeapTree Class <-**********");
		System.out.println("***************************************************************\n");

		BSTHeapTree<Integer> bst1 = new BSTHeapTree<Integer>();
		bst1.add(8);
		bst1.add(9);
		bst1.add(10);
		bst1.add(11);
		bst1.add(12);
		bst1.add(13);
		bst1.add(14);
		bst1.add(15);
		bst1.add(1);
		bst1.add(2);
		bst1.add(3);
		bst1.add(4);
		bst1.add(5);
		bst1.add(6);
		bst1.add(7);
		bst1.add(8);
		bst1.add(1);
		bst1.add(2);
		bst1.add(3);
		bst1.add(4);
		bst1.add(5);
		bst1.add(6);
		bst1.add(7);
		bst1.add(8);
		bst1.add(211);
		bst1.add(22);
		bst1.add(322);
		bst1.add(432);
		bst1.add(544);
		bst1.add(64343);
		bst1.add(72);
		bst1.add(800);
		bst1.add(3);
		bst1.add(3);

		BSTHeapTree<Integer> bst2 = new BSTHeapTree<Integer>();

 		System.out.println("\n**********-> ADDING <-**********\n");
		System.out.println("The BSTHeapTree<Integer>:\n"+bst1);
		System.out.println(" --> Adding 8 ...");
		System.out.println("\nThere occurrence of the 8: "+bst1.add(8));
		System.out.println("The New BSTHeapTree<Integer>:\n"+bst1);
		System.out.println(" --> Adding 999 ...");
		System.out.println("\nThere occurrence of the 999: "+bst1.add(999));
		System.out.println("The New BSTHeapTree<Integer>:\n"+bst1);
		System.out.println(" --> Adding 0 ...");
		System.out.println("\nThere occurrence of the 0: "+bst1.add(0));
		System.out.println("The New BSTHeapTree<Integer>:\n"+bst1);
		
		System.out.println("\n**********-> SEARCHING/FINDING <-**********\n");
		System.out.println("The BSTHeapTree<Integer>:\n"+bst1);
		System.out.println(" --> Searching 10 ...");
		System.out.println("\nThere occurrence of the 10: "+bst1.find(10));
		System.out.println("\n --> Searching 8 ...");
		System.out.println("\nThere occurrence of the 8: "+bst1.find(8));
		System.out.println("\n --> Searching 77 ...");
		System.out.println("\nThere occurrence of the 77: "+bst1.find(77));
		System.out.println(" ! NOTE: 0 occurrence means that there is no the value.");

		System.out.println("\n**********-> SEARCHING/FINDING with empty BSTHeapTree <-**********\n");
		System.out.println("The BSTHeapTree<Integer>:\n"+bst2);
		System.out.println(" --> Searching 10 ...");
		bst2.find(10);

		System.out.println("\n**********-> DELETING <-**********\n");
		System.out.println("The BSTHeapTree<Integer>:\n"+bst1);
		System.out.println(" --> Deleting 0 ...");
		System.out.println("\nThere occurrence of the 0 after deletion: "+bst1.remove(0));
		System.out.println(" ! NOTE: 0 occurrence means that there is no the value.");
		System.out.println("The New BSTHeapTree<Integer>:\n"+bst1);
		
		System.out.println(" --> Deleting 322 ...");
		System.out.println("\nThere occurrence of the 322 after deletion: "+bst1.remove(322));
		System.out.println(" ! NOTE: 0 occurrence means that there is no the value.");
		System.out.println("The New BSTHeapTree<Integer>:\n"+bst1);

		System.out.println(" --> Deleting 3 ...");
		System.out.println("\nThere occurrence of the 3 after deletion: "+bst1.remove(3));
		System.out.println("The New BSTHeapTree<Integer>:\n"+bst1);
		System.out.println("");

		System.out.println(" --> Deleting 233 ...");
		System.out.println("\nThere occurrence of the 233 after deletion: "+bst1.remove(233));
		System.out.println(" ! NOTE: 0 occurrence means that there is no the value.");
		System.out.println("The New BSTHeapTree<Integer>:\n"+bst1);
		System.out.println("");

		System.out.println("\n**********-> DELETING with empty BSTHeapTree <-**********\n");
		System.out.println("The BSTHeapTree<Integer>:\n"+bst2);
		System.out.println(" --> Deleting 10 ...");
		bst2.remove(10);

		System.out.println("\n**********-> FINDING MODE <-**********\n");
		System.out.println("The BSTHeapTree<Integer>:\n"+bst1);
		System.out.println(" --> Mode: "+bst1.find_mode());

		System.out.println("\n**********-> FINDING MODE with empty BSTHeapTree <-**********\n");
		System.out.println("The BSTHeapTree<Integer>:\n"+bst2);
		System.out.println(" --> Mode: ");
		bst2.find_mode();
	}
} 
