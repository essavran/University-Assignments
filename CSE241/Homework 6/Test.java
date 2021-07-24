import java.util.Scanner;
/**
*	The Class Test
*	Test all functions
*	@author Emine Sultan Savran
*	@since 2021-01-24
*/
class Test{

	public static void main(String[] args){
		String choice;
		do{
			System.out.println("\n1) Testing HashSet Functions with String");
			System.out.println("2) Testing HashSet Functions with Integer");
			System.out.println("3) Testing ArrayList Functions with String");
			System.out.println("4) Testing ArrayList Functions with Integer");
			System.out.println("5) Testing LinkedList Functions with String");
			System.out.println("6) Testing LinkedList Functions with Integer");
			System.out.println("0) Exit");
			System.out.print("-->Please select: ");

		    Scanner scanner = new Scanner(System.in);
		    choice = scanner.nextLine();

		    if( choice.equals("0") ){
				System.out.println("Goodbye!");
		    } else if( choice.equals("1") ){
		    	testHashSetString();
		    } else if( choice.equals("2") ){
		    	testHashSetInteger();
		    } else if( choice.equals("3") ){
		    	testArrayListString();
		    } else if( choice.equals("4") ){
				testArrayListInteger();
		    } else if( choice.equals("5") ){
		    	testLinkedListString();
		    } else if( choice.equals("6") ){
		    	testLinkedListInteger();
		    } else{
				System.out.println("Invalid input.");
		    }
		} while( !choice.equals("0") );
	}

	@SuppressWarnings("unchecked")
	public static void testHashSetString(){
		System.out.println("\n-----Testing HashSet with String-----");
		HashSet<String> str = new HashSet<String>();
		str.add("Lothlorien");
		str.add("Tirion");
		str.add("Doriath");
		str.add("Lindon");
		HashSet<String> str2 = new HashSet<String>();
		str2.add("Nenya");
		str2.add("Narya");
		str2.add("Vilya");
		HashSet<String> str3 = new HashSet<String>();
		str3.add("Gondor");
		str3.add("Mordor");
		str3.add("Shire");
		HashSet<String> str4 = new HashSet<String>();
		str4.add("Nenya");
		str4.add("Gondor");
		str4.add("Lindon");

		//iterator
		System.out.println("\n***iterator()***\n");
		Iterator itr = str.iterator();
		System.out.println("--->iterator().hasNext(): "+itr.hasNext());
		System.out.println("--->iterator().next(): "+itr.next());
		System.out.println("---> before iterator().remove(): ");
		str.print();
		System.out.println("---> after iterator().remove(): ");
		itr.remove();
		str.print();
		//add
		System.out.println("\n***add()***\n");
		System.out.println("--->before add(\"Eregion\"):");
		str.print();
		str.add("Eregion");
		System.out.println("--->after add(\"Eregion\"):");
		str.print();
		//addAll
		System.out.println("\n***addAll()***\n");
		System.out.println("--->str2:");
		str2.print();
		System.out.println("--->before str.addAll(str2):");
		str.print();
		str.addAll(str2);
		System.out.println("--->after str.addAll(str2):");
		str.print();	
		//clear
		System.out.println("\n***clear()***\n");
		System.out.println("--->before clear()):");
		str3.print();
		str3.clear();
		System.out.println("--->after clear():");
		str3.print();
		//contains
		System.out.println("\n***contains()***\n");
		System.out.println("--->str:");
		str.print();
		System.out.println("--->str.contains(\"Eregion\"): "+str.contains("Eregion"));
		//containsAll
		System.out.println("\n***containsAll()***\n");
		System.out.println("--->str:");
		str.print();
		System.out.println("--->str4:");
		str4.print();
		System.out.println("--->str.containsAll(str4): "+str.containsAll(str4));
		//isEmpty
		System.out.println("\n***isEmpty***\n");
		System.out.println("--->str:");
		str.print();
		System.out.println("--->str.isEmpty(): "+str.isEmpty());
		System.out.println("--->str3:");
		str3.print();
		System.out.println("--->str3.isEmpty(): "+str3.isEmpty());
		//remove
		System.out.println("\n***remove()***\n");
		System.out.println("--->str:");
		str.print();
		System.out.println("--->str.remove(\"Eregion\"): ");	
		str.remove("Eregion");
		str.print();
		//removeAll
		System.out.println("\n***removeAll()***\n");
		System.out.println("--->str:");
		str.print();
		System.out.println("--->str4:");
		str4.print();
		System.out.println("--->str.removeAll(str4): ");
		str.removeAll(str4);
		str.print();
		//retainAll
		System.out.println("\n***retainAll()***\n");
		System.out.println("--->str2:");
		str2.print();
		System.out.println("--->str4:");
		str4.print();
		System.out.println("--->str2.retainAll(str4): ");
		str2.retainAll(str4);
		str2.print();
		//size
		System.out.println("\n***size()***\n");
		System.out.println("--->str:");
		str.print();
		System.out.println("--->str.size(): "+str.size());
		System.out.println("\n");

	}

	@SuppressWarnings("unchecked")
	public static void testHashSetInteger(){
		System.out.println("\n-----Testing HashSet with Integer-----");
		HashSet<Integer> intArr = new HashSet<Integer>();
		intArr.add(3);
		intArr.add(5);
		intArr.add(8);
		intArr.add(2);
		HashSet<Integer> intArr2 = new HashSet<Integer>();
		intArr2.add(6);
		intArr2.add(3);
		intArr2.add(9);
		HashSet<Integer> intArr3 = new HashSet<Integer>();
		intArr3.add(1);
		intArr3.add(123);
		intArr3.add(23);
		HashSet<Integer> intArr4 = new HashSet<Integer>();
		intArr4.add(2);
		intArr4.add(4);
		intArr4.add(3);

		//iterator
		System.out.println("\n***iterator()***\n");
		Iterator itr = intArr.iterator();
		System.out.println("--->iterator().hasNext(): "+itr.hasNext());
		System.out.println("--->iterator().next(): "+itr.next());
		System.out.println("---> before iterator().remove(): ");
		intArr.print();
		System.out.println("---> after iterator().remove(): ");
		itr.remove();
		intArr.print();
		//add
		System.out.println("\n***add()***\n");
		System.out.println("--->before add(3):");
		intArr.print();
		intArr.add(3);
		System.out.println("--->after add(3):");
		intArr.print();
		//addAll
		System.out.println("\n***addAll()***\n");
		System.out.println("--->intArr2:");
		intArr2.print();
		System.out.println("--->before intArr.addAll(intArr2):");
		intArr.print();
		intArr.addAll(intArr2);
		System.out.println("--->after intArr.addAll(intArr2):");
		intArr.print();	
		//clear
		System.out.println("\n***clear()***\n");
		System.out.println("--->before clear()):");
		intArr3.print();
		intArr3.clear();
		System.out.println("--->after clear():");
		intArr3.print();
		//contains
		System.out.println("\n***contains()***\n");
		System.out.println("--->intArr:");
		intArr.print();
		System.out.println("--->intArr.contains(3): "+intArr.contains(3));
		//containsAll
		System.out.println("\n***containsAll()***\n");
		System.out.println("--->intArr:");
		intArr.print();
		System.out.println("--->intArr4:");
		intArr4.print();
		System.out.println("--->intArr.containsAll(intArr4): "+intArr.containsAll(intArr4));
		//isEmpty
		System.out.println("\n***isEmpty***\n");
		System.out.println("--->intArr:");
		intArr.print();
		System.out.println("--->intArr.isEmpty(): "+intArr.isEmpty());
		System.out.println("--->intArr3:");
		intArr3.print();
		System.out.println("--->intArr3.isEmpty(): "+intArr3.isEmpty());
		//remove
		System.out.println("\n***remove()***\n");
		System.out.println("--->intArr:");
		intArr.print();
		System.out.println("--->intArr.remove(3): ");	
		intArr.remove(3);
		intArr.print();
		//removeAll
		System.out.println("\n***removeAll()***\n");
		System.out.println("--->intArr:");
		intArr.print();
		System.out.println("--->intArr4:");
		intArr4.print();
		System.out.println("--->intArr.removeAll(intArr4): ");
		intArr.removeAll(intArr4);
		intArr.print();
		//retainAll
		System.out.println("\n***retainAll()***\n");
		System.out.println("--->intArr2:");
		intArr2.print();
		System.out.println("--->intArr4:");
		intArr4.print();
		System.out.println("--->intArr2.retainAll(intArr4): ");
		intArr2.retainAll(intArr4);
		intArr2.print();
		//size
		System.out.println("\n***size()***\n");
		System.out.println("--->intArr:");
		intArr.print();
		System.out.println("--->intArr.size(): "+intArr.size());
		System.out.println("\n");	
	}
	
	@SuppressWarnings("unchecked")
	public static void testArrayListString(){
		System.out.println("\n-----Testing ArrayList with String-----");
		ArrayList<String> str = new ArrayList<String>();
		str.add("Lothlorien");
		str.add("Tirion");
		str.add("Doriath");
		str.add("Lindon");
		ArrayList<String> str2 = new ArrayList<String>();
		str2.add("Nenya");
		str2.add("Narya");
		str2.add("Vilya");
		ArrayList<String> str3 = new ArrayList<String>();
		str3.add("Gondor");
		str3.add("Mordor");
		str3.add("Shire");
		ArrayList<String> str4 = new ArrayList<String>();
		str4.add("Nenya");
		str4.add("Gondor");
		str4.add("Lindon");

		//iterator
		System.out.println("\n***iterator()***\n");
		Iterator itr = str.iterator();
		System.out.println("--->iterator().hasNext(): "+itr.hasNext());
		System.out.println("--->iterator().next(): "+itr.next());
		System.out.println("---> before iterator().remove(): ");
		str.print();
		System.out.println("---> after iterator().remove(): ");
		itr.remove();
		str.print();
		//add
		System.out.println("\n***add()***\n");
		System.out.println("--->before add(\"Eregion\"):");
		str.print();
		str.add("Eregion");
		System.out.println("--->after add(\"Eregion\"):");
		str.print();
		//addAll
		System.out.println("\n***addAll()***\n");
		System.out.println("--->str2:");
		str2.print();
		System.out.println("--->before str.addAll(str2):");
		str.print();
		str.addAll(str2);
		System.out.println("--->after str.addAll(str2):");
		str.print();	
		//clear
		System.out.println("\n***clear()***\n");
		System.out.println("--->before clear()):");
		str3.print();
		str3.clear();
		System.out.println("--->after clear():");
		str3.print();
		//contains
		System.out.println("\n***contains()***\n");
		System.out.println("--->str:");
		str.print();
		System.out.println("--->str.contains(\"Eregion\"): "+str.contains("Eregion"));
		//containsAll
		System.out.println("\n***containsAll()***\n");
		System.out.println("--->str:");
		str.print();
		System.out.println("--->str4:");
		str4.print();
		System.out.println("--->str.containsAll(str4): "+str.containsAll(str4));
		//isEmpty
		System.out.println("\n***isEmpty***\n");
		System.out.println("--->str:");
		str.print();
		System.out.println("--->str.isEmpty(): "+str.isEmpty());
		System.out.println("--->str3:");
		str3.print();
		System.out.println("--->str3.isEmpty(): "+str3.isEmpty());
		//remove
		System.out.println("\n***remove()***\n");
		System.out.println("--->str:");
		str.print();
		System.out.println("--->str.remove(\"Eregion\"): ");	
		str.remove("Eregion");
		str.print();
		//removeAll
		System.out.println("\n***removeAll()***\n");
		System.out.println("--->str:");
		str.print();
		System.out.println("--->str4:");
		str4.print();
		System.out.println("--->str.removeAll(str4): ");
		str.removeAll(str4);
		str.print();
		//retainAll
		System.out.println("\n***retainAll()***\n");
		System.out.println("--->str2:");
		str2.print();
		System.out.println("--->str4:");
		str4.print();
		System.out.println("--->str2.retainAll(str4): ");
		str2.retainAll(str4);
		str2.print();
		//size
		System.out.println("\n***size()***\n");
		System.out.println("--->str:");
		str.print();
		System.out.println("--->str.size(): "+str.size());
		System.out.println("\n");
	}

	@SuppressWarnings("unchecked")
	public static void testArrayListInteger(){
		System.out.println("\n-----Testing ArrayList with Integer-----");
		ArrayList<Integer> intArr = new ArrayList<Integer>();
		intArr.add(3);
		intArr.add(5);
		intArr.add(8);
		intArr.add(2);
		ArrayList<Integer> intArr2 = new ArrayList<Integer>();
		intArr2.add(6);
		intArr2.add(3);
		intArr2.add(9);
		ArrayList<Integer> intArr3 = new ArrayList<Integer>();
		intArr3.add(1);
		intArr3.add(123);
		intArr3.add(23);
		ArrayList<Integer> intArr4 = new ArrayList<Integer>();
		intArr4.add(2);
		intArr4.add(4);
		intArr4.add(3);

		//iterator
		System.out.println("\n***iterator()***\n");
		Iterator itr = intArr.iterator();
		System.out.println("--->iterator().hasNext(): "+itr.hasNext());
		System.out.println("--->iterator().next(): "+itr.next());
		System.out.println("---> before iterator().remove(): ");
		intArr.print();
		System.out.println("---> after iterator().remove(): ");
		itr.remove();
		intArr.print();
		//add
		System.out.println("\n***add()***\n");
		System.out.println("--->before add(3):");
		intArr.print();
		intArr.add(3);
		System.out.println("--->after add(3):");
		intArr.print();
		//addAll
		System.out.println("\n***addAll()***\n");
		System.out.println("--->intArr2:");
		intArr2.print();
		System.out.println("--->before intArr.addAll(intArr2):");
		intArr.print();
		intArr.addAll(intArr2);
		System.out.println("--->after intArr.addAll(intArr2):");
		intArr.print();	
		//clear
		System.out.println("\n***clear()***\n");
		System.out.println("--->before clear()):");
		intArr3.print();
		intArr3.clear();
		System.out.println("--->after clear():");
		intArr3.print();
		//contains
		System.out.println("\n***contains()***\n");
		System.out.println("--->intArr:");
		intArr.print();
		System.out.println("--->intArr.contains(3): "+intArr.contains(3));
		//containsAll
		System.out.println("\n***containsAll()***\n");
		System.out.println("--->intArr:");
		intArr.print();
		System.out.println("--->intArr4:");
		intArr4.print();
		System.out.println("--->intArr.containsAll(intArr4): "+intArr.containsAll(intArr4));
		//isEmpty
		System.out.println("\n***isEmpty***\n");
		System.out.println("--->intArr:");
		intArr.print();
		System.out.println("--->intArr.isEmpty(): "+intArr.isEmpty());
		System.out.println("--->intArr3:");
		intArr3.print();
		System.out.println("--->intArr3.isEmpty(): "+intArr3.isEmpty());
		//remove
		System.out.println("\n***remove()***\n");
		System.out.println("--->intArr:");
		intArr.print();
		System.out.println("--->intArr.remove(3): ");	
		intArr.remove(3);
		intArr.print();
		//removeAll
		System.out.println("\n***removeAll()***\n");
		System.out.println("--->intArr:");
		intArr.print();
		System.out.println("--->intArr4:");
		intArr4.print();
		System.out.println("--->intArr.removeAll(intArr4): ");
		intArr.removeAll(intArr4);
		intArr.print();
		//retainAll
		System.out.println("\n***retainAll()***\n");
		System.out.println("--->intArr2:");
		intArr2.print();
		System.out.println("--->intArr4:");
		intArr4.print();
		System.out.println("--->intArr2.retainAll(intArr4): ");
		intArr2.retainAll(intArr4);
		intArr2.print();
		//size
		System.out.println("\n***size()***\n");
		System.out.println("--->intArr:");
		intArr.print();
		System.out.println("--->intArr.size(): "+intArr.size());
		System.out.println("\n");	
	}

	@SuppressWarnings("unchecked")
	public static void testLinkedListString(){
		System.out.println("\n-----Testing LinkedList with String-----");
		LinkedList<String> str = new LinkedList<String>();
		str.add("Lothlorien");
		str.add("Tirion");
		str.add("Doriath");
		str.add("Lindon");
		LinkedList<String> str2 = new LinkedList<String>();
		str2.add("Nenya");
		str2.add("Narya");
		str2.add("Vilya");
		LinkedList<String> str3 = new LinkedList<String>();
		str3.add("Gondor");
		str3.add("Mordor");
		str3.add("Shire");
		LinkedList<String> str4 = new LinkedList<String>();
		str4.add("Nenya");
		str4.add("Gondor");
		str4.add("Lindon");

		//iterator
		System.out.println("\n***iterator()***\n");
		Iterator itr = str.iterator();
		System.out.println("--->iterator().hasNext(): "+itr.hasNext());
		System.out.println("--->iterator().next(): "+itr.next());
		System.out.println("---> before iterator().remove(): ");
		str.print();
		System.out.println("---> after iterator().remove(): ");
		itr.remove();
		str.print();
		//add
		System.out.println("\n***add()***\n");
		System.out.println("--->before add(\"Eregion\"):");
		str.print();
		str.add("Eregion");
		System.out.println("--->after add(\"Eregion\"):");
		str.print();
		//addAll
		System.out.println("\n***addAll()***\n");
		System.out.println("--->str2:");
		str2.print();
		System.out.println("--->before str.addAll(str2):");
		str.print();
		str.addAll(str2);
		System.out.println("--->after str.addAll(str2):");
		str.print();	
		//clear
		System.out.println("\n***clear()***\n");
		System.out.println("--->before clear()):");
		str3.print();
		str3.clear();
		System.out.println("--->after clear():");
		str3.print();
		//contains
		System.out.println("\n***contains()***\n");
		System.out.println("--->str:");
		str.print();
		System.out.println("--->str.contains(\"Eregion\"): "+str.contains("Eregion"));
		//containsAll
		System.out.println("\n***containsAll()***\n");
		System.out.println("--->str:");
		str.print();
		System.out.println("--->str4:");
		str4.print();
		System.out.println("--->str.containsAll(str4): "+str.containsAll(str4));
		//isEmpty
		System.out.println("\n***isEmpty***\n");
		System.out.println("--->str:");
		str.print();
		System.out.println("--->str.isEmpty(): "+str.isEmpty());
		System.out.println("--->str3:");
		str3.print();
		System.out.println("--->str3.isEmpty(): "+str3.isEmpty());
		//remove
		System.out.println("\n***remove()***\n");
		System.out.println("--->str:");
		str.print();
		System.out.println("--->str.remove(\"Eregion\"): ");	
		str.remove("Eregion");
		str.print();
		//removeAll
		System.out.println("\n***removeAll()***\n");
		System.out.println("--->str:");
		str.print();
		System.out.println("--->str4:");
		str4.print();
		System.out.println("--->str.removeAll(str4): ");
		str.removeAll(str4);
		str.print();
		//retainAll
		System.out.println("\n***retainAll()***\n");
		System.out.println("--->str2:");
		str2.print();
		System.out.println("--->str4:");
		str4.print();
		System.out.println("--->str2.retainAll(str4): ");
		str2.retainAll(str4);
		str2.print();
		//size
		System.out.println("\n***size()***\n");
		System.out.println("--->str:");
		str.print();
		System.out.println("--->str.size(): "+str.size());
		//element
		System.out.println("\n***element()***\n");
		System.out.println("--->str:");
		str.print();
		System.out.println("--->str.element(): "+str.element());
		//offer
		System.out.println("\n***offer()***\n");
		System.out.println("--->before offer(\"Eregion\"):");
		str.print();
		str.add("Eregion");
		System.out.println("--->after offer(\"Eregion\"):");
		str.print();		
		//poll
		System.out.println("\n***poll()***\n");
		System.out.println("--->str:");
		str.print();
		System.out.println("--->str.poll(): "+str.poll());
		str.print();

		System.out.println("\n");

	}
	@SuppressWarnings("unchecked")
	public static void testLinkedListInteger(){
		System.out.println("\n-----Testing LinkedList with Integer-----");
		LinkedList<Integer> intArr = new LinkedList<Integer>();
		intArr.add(3);
		intArr.add(5);
		intArr.add(8);
		intArr.add(2);
		LinkedList<Integer> intArr2 = new LinkedList<Integer>();
		intArr2.add(6);
		intArr2.add(3);
		intArr2.add(9);
		LinkedList<Integer> intArr3 = new LinkedList<Integer>();
		intArr3.add(1);
		intArr3.add(123);
		intArr3.add(23);
		LinkedList<Integer> intArr4 = new LinkedList<Integer>();
		intArr4.add(2);
		intArr4.add(4);
		intArr4.add(3);

		//iterator
		System.out.println("\n***iterator()***\n");
		Iterator itr = intArr.iterator();
		System.out.println("--->iterator().hasNext(): "+itr.hasNext());
		System.out.println("--->iterator().next(): "+itr.next());
		System.out.println("---> before iterator().remove(): ");
		intArr.print();
		System.out.println("---> after iterator().remove(): ");
		itr.remove();
		intArr.print();
		//add
		System.out.println("\n***add()***\n");
		System.out.println("--->before add(3):");
		intArr.print();
		intArr.add(3);
		System.out.println("--->after add(3):");
		intArr.print();
		//addAll
		System.out.println("\n***addAll()***\n");
		System.out.println("--->intArr2:");
		intArr2.print();
		System.out.println("--->before intArr.addAll(intArr2):");
		intArr.print();
		intArr.addAll(intArr2);
		System.out.println("--->after intArr.addAll(intArr2):");
		intArr.print();	
		//clear
		System.out.println("\n***clear()***\n");
		System.out.println("--->before clear()):");
		intArr3.print();
		intArr3.clear();
		System.out.println("--->after clear():");
		intArr3.print();
		//contains
		System.out.println("\n***contains()***\n");
		System.out.println("--->intArr:");
		intArr.print();
		System.out.println("--->intArr.contains(3): "+intArr.contains(3));
		//containsAll
		System.out.println("\n***containsAll()***\n");
		System.out.println("--->intArr:");
		intArr.print();
		System.out.println("--->intArr4:");
		intArr4.print();
		System.out.println("--->intArr.containsAll(intArr4): "+intArr.containsAll(intArr4));
		//isEmpty
		System.out.println("\n***isEmpty***\n");
		System.out.println("--->intArr:");
		intArr.print();
		System.out.println("--->intArr.isEmpty(): "+intArr.isEmpty());
		System.out.println("--->intArr3:");
		intArr3.print();
		System.out.println("--->intArr3.isEmpty(): "+intArr3.isEmpty());
		//remove
		System.out.println("\n***remove()***\n");
		System.out.println("--->intArr:");
		intArr.print();
		System.out.println("--->intArr.remove(3): ");	
		intArr.remove(3);
		intArr.print();
		//removeAll
		System.out.println("\n***removeAll()***\n");
		System.out.println("--->intArr:");
		intArr.print();
		System.out.println("--->intArr4:");
		intArr4.print();
		System.out.println("--->intArr.removeAll(intArr4): ");
		intArr.removeAll(intArr4);
		intArr.print();
		//retainAll
		System.out.println("\n***retainAll()***\n");
		System.out.println("--->intArr2:");
		intArr2.print();
		System.out.println("--->intArr4:");
		intArr4.print();
		System.out.println("--->intArr2.retainAll(intArr4): ");
		intArr2.retainAll(intArr4);
		intArr2.print();
		//size
		System.out.println("\n***size()***\n");
		System.out.println("--->intArr:");
		intArr.print();
		System.out.println("--->intArr.size(): "+intArr.size());
		//element
		System.out.println("\n***element()***\n");
		System.out.println("--->intArr:");
		intArr.print();
		System.out.println("--->intArr.element(): "+intArr.element());
		//offer
		System.out.println("\n***offer()***\n");
		System.out.println("--->before offer(3):");
		intArr.print();
		intArr.add(3);
		System.out.println("--->after offer(3):");
		intArr.print();		
		//poll
		System.out.println("\n***poll()***\n");
		System.out.println("--->intArr:");
		intArr.print();
		System.out.println("--->intArr.poll(): "+intArr.poll());
		intArr.print();

		System.out.println("\n");	
	}
}