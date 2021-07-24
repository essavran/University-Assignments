import java.io.BufferedReader;  
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.File;
import java.util.PriorityQueue;
import java.util.ArrayList;
import java.util.Collections;

/**
* The class that keeps informations 
* of customers	
*/
public class Customer extends User{
	
	//Data fields
	private ArrayList<Product> sortedArray;
	//Methods
	Customer(long id, String password){
		super(id,password);
	}

	/**
	* Searches for "target" on Products.txt and stores the producst in data structures as it finds it
	* Sorts the products it finds with heapsort
	* @param target to find
	* @return true or false
	*/
    public boolean search(String target){

    	PriorityQueue<Product> heap = new PriorityQueue<Product>(1000,Collections.reverseOrder());
    	boolean flag = false;
		String idProduct = "";
		String name = "";
		String category = "";
		long price = -1;
		long discountedPrice = -1;
		String description = "";		
		String traderName = "";
		try{  
			FileReader pathToProducts = new FileReader("Products.txt");
			BufferedReader productsReader = new BufferedReader(pathToProducts);
			while ( (idProduct = productsReader.readLine()) != null ){
				name = productsReader.readLine();
				category = productsReader.readLine();
				price = Long.parseLong(productsReader.readLine());
				discountedPrice = Long.parseLong(productsReader.readLine());
				description = productsReader.readLine();
				traderName = productsReader.readLine();
				if( name.contains(target) || category.contains(target) ){
			    	Product product = new Product(idProduct, name, category, price, discountedPrice, description, new Trader(0,"",traderName));
			    	heap.add(product);
			    	flag = true;
				}
				productsReader.readLine();
			}
			sortedArray = new ArrayList<Product>();
			sortedArray.addAll(heap);
			shrinkHeap();
			if(flag)	printArray();
			return flag;
		} catch (Exception e){
			return false;
		} 	
    }

	/**
	* Sorting by price with shellsort
	*/
    public void sortByPrice(){
    	shellSort();
    	printArray();
    }

	/**
	* Sorting by the percentage of the discount with shellsort
	*/
    public void sortByDiscount(){
    	insertionSort();
    	printArray();
    }
	
	/**
	* Sorting by the name
	*/
    public void sortByName(){
    	selectionSort();
    	printArray();
    }

    //HEAP SORT
    /**
	* Heapsort
    */
    private void shrinkHeap() {
		int n = sortedArray.size();
		while (n > 0) {
			n--;
			swap(0, n);
			int parent = 0;
			while (true) {
				int leftChild = 2 * parent + 1;
				if (leftChild >= n) {
					break; // No more children.
				}
				int rightChild = leftChild + 1;
				int maxChild = leftChild;
				if (rightChild < n && sortedArray.get(leftChild).compareTo(sortedArray.get(rightChild)) > 0) {
					maxChild = rightChild;
				}
				if (sortedArray.get(parent).compareTo(sortedArray.get(maxChild)) > 0) {
					swap(parent, maxChild);
					parent = maxChild;
				} else { // Heap property is restored.
					break; // Exit the loop.
				}
			}
		}
	}
	/**
	* swapping ith and jth datas
	* @param i first index
	* @param j second index
	*/
	private void swap(int i, int j) {
		Product temp = sortedArray.get(i);
		sortedArray.set(i, sortedArray.get(j));
		sortedArray.set(j, temp);
	}

	// SHELL SORT
	/**
	* Shellsort
	*/
	private void shellSort(){
		int gap = sortedArray.size()/2;
		while(gap>0){
			for(int nextPos=gap; nextPos<sortedArray.size(); nextPos++){
				insertShell(nextPos,gap);
			}
			if(gap==2){
				gap = 1;
			} else{
				gap = (int)(gap/2.2);
			}
		}
	}

	/**
	* helper function for shellsort
	* @param nextPos next position
	* @param gap the gap value
	*/
	private void insertShell(int nextPos, int gap){
		Product nextVal = sortedArray.get(nextPos);
		while((nextPos>gap-1) && 
			(nextVal.getPrice() > sortedArray.get(nextPos-gap).getPrice())){
			//(nextVal.compareTo(sortedArray.get(nextPos-gap))<0)){
			sortedArray.set(nextPos, sortedArray.get(nextPos-gap));
			nextPos -= gap;
		}
		sortedArray.set(nextPos, nextVal);
	}

	// INSERTION SORT
	/**
	* insertion sort
	*/
	private void insertionSort(){
		for(int nextPos=1; nextPos<sortedArray.size(); nextPos++){
			insertInsertion(nextPos);
		}
	}

	/**
	* helper function for insertion sort
	* @param nextPos next position
	*/
	private void insertInsertion(int nextPos){
		Product nextVal = sortedArray.get(nextPos);
		while(nextPos>0 && ( 100*(nextVal.getPrice()-nextVal.getDiscountedPrice())/nextVal.getPrice() )
			> ( 100*(sortedArray.get(nextPos-1).getPrice()-sortedArray.get(nextPos-1).getDiscountedPrice())/sortedArray.get(nextPos-1).getPrice() ) ){
		// nextVal.compareTo(sortedArray.get(nextPos-1))<0){
			sortedArray.set(nextPos, sortedArray.get(nextPos-1));
			nextPos--;
		}
		sortedArray.set(nextPos, nextVal);
	}

	/**
	* printing the products(arraylist)
	*/
	private void printArray(){
        int n = sortedArray.size();
        for (int i=0; i<n; ++i)
            System.out.println(sortedArray.get(i));
        System.out.println();
    }

    //SELECTION SORT
    /**
    * selection sort
    */
	public void selectionSort(){
		int min = 0;
		for(int i=0; i<sortedArray.size()-1; i++){
			min = i;
			for(int j=i+1; j<sortedArray.size(); j++ ){
				if( sortedArray.get(j).getName().compareTo(sortedArray.get(min).getName()) > 0 ){
					min = j;
				}
			}
			Product temp = sortedArray.get(min);
			sortedArray.set(min, sortedArray.get(i));
			sortedArray.set(i, temp);
		}
	}

	/**
	* filter by category
	* @param target to find
	* @return always return true
	*/	
	public boolean filterCategory(String target){
		int size = sortedArray.size();
		for(int i=0; i<size; i++){
			String all = sortedArray.get(i).getCategory().substring(4);
			all = all.substring(0,((all.length())-4));
			String[] temps = all.split(" >> ");
			for(int j=0; j<temps.length; j++){
				if( temps[j].equals(target) ){
					System.out.println(sortedArray.get(i));
				}
			}
		}
		return true;
	}

	/**
	* filter by upper bound
	* @param target to upper
	* @return always return true
	*/
	public boolean filterUpper(long target){
		int size = sortedArray.size();
		for(int i=0; i<size; i++){
			if( sortedArray.get(i).getPrice() <= target ){
				System.out.println(sortedArray.get(i));
			}
			
		}
		return true;
	}

	/**
	* filter by lower bound
	* @param target to lower
	* @return always return true
	*/
	public boolean filterLower(long target){
		int size = sortedArray.size();
		for(int i=0; i<size; i++){
			
			if( sortedArray.get(i).getPrice() >= target ){
				System.out.println(sortedArray.get(i));
			}
			
		}
		return true;
	}

	/**
	* filter by upper and lower
	* @param upper to upper
	* @param lower to lower
	* @return always return true
	*/
	public boolean filterUpperLower(long upper, long lower){
		int size = sortedArray.size();
		for(int i=0; i<size; i++){
			
			if( sortedArray.get(i).getPrice() <= upper && sortedArray.get(i).getPrice() >= lower ){
				System.out.println(sortedArray.get(i));
			}
			
		}
		return true;
	}

	/**
	* displays trader's products(if exists)
	* @param target name of the trader
	* @return true if existing target
	*			false if target does not found
	*/
	public boolean displayTradersProduct(String target){
		PriorityQueue<Product> heap2 = new PriorityQueue<Product>();
		boolean flag = false;
		String idProduct = "";
		String name = "";
		String category = "";
		long price = -1;
		long discountedPrice = -1;
		String description = "";		
		String traderName = "";
		try{  
			FileReader pathToProducts = new FileReader("Products.txt");
			BufferedReader productsReader = new BufferedReader(pathToProducts);
			while ( (idProduct = productsReader.readLine()) != null ){
				name = productsReader.readLine();
				category = productsReader.readLine();
				price = Long.parseLong(productsReader.readLine());
				discountedPrice = Long.parseLong(productsReader.readLine());
				description = productsReader.readLine();
				traderName = productsReader.readLine();

				if( traderName.equals(target) ){
			    	Product product = new Product(idProduct, name, category, price, discountedPrice, description, new Trader(0,"",traderName));
			    	heap2.add(product);
			    	flag = true;
				//	System.out.println(product);
				}
				productsReader.readLine();
			}
			ArrayList<Product> sortedArray2 = new ArrayList<Product>();
			sortedArray2.addAll(heap2);
			//shrinkHeap();
			if(flag)	printArray();
			return flag;
		} catch (Exception e){
			return false;
		} 	
	}
}