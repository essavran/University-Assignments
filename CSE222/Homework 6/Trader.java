import java.io.BufferedReader;  
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.File;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Iterator;

/**
* The class that keeps informations 
* of traders
*/
public class Trader extends User{
	
	//Data fields
	/**Trader's name*/
	private String name;
	/**List of products of the trader*/
	private LinkedList<Product> products;
	/**List of orders of the trader*/
	private Queue<Order> orders;

	//Methods
	Trader(long id, String password, String name){
		super(id,password);
		setName(name);
		productsOfTrader();
		ordersOfTraders(false);
	}

	Trader(long id, String name){
		super(id,"123456");
		setName(name);
	//	productsOfTrader();
	//	ordersOfTraders(false);
	}

	public void setName(String name){
		this.name = name;
	}

	public String getName(){
		return name;
	}

	/**
	* Adding the product to Product.txt and products(LL)
	* @param product to add
	* @return if add, returns true
	*			otherwise false
	*/
	public boolean addProduct(Product product){
		try{  
			FileWriter productsWriter = new FileWriter("Products.txt", true);
			productsWriter.write(product.getID() + "\n");
			productsWriter.write(product.getName() + "\n");
			productsWriter.write(product.getCategory() + "\n");
			productsWriter.write(product.getPrice() + "\n");
			productsWriter.write(product.getDiscountedPrice() + "\n");
			productsWriter.write(product.getDescription() + "\n");
			productsWriter.write(this.getName() + "\n");
			productsWriter.write( "\n" );
      		productsWriter.close();
			System.out.println("The product is added.");
			products.add(product);
     		return true; 
		} catch(Exception e){
			System.out.println("There is a problem! Product cannot added.");
			return false;
		}
	}

	/**
	* If exist, removing the product to Product.txt and products(LL)
	* @param idProduct to remove
	* @return if remove, returns true
	*			otherwise false
	*/
	public boolean removeProduct(String idProduct){
		String row = "";
		int count = 0;
		String traderName = "";
		try{  
			FileReader pathToProducts = new FileReader("Products.txt");
			BufferedReader productsReader = new BufferedReader(pathToProducts);
			while ( (row = productsReader.readLine()) != null ){
				//reading a row
				if( row.equals( idProduct ) ){
					count = 0;
					while( row != null && count < 8 ){

						row = productsReader.readLine();
						if( count == 5 )	traderName = row;
						count++;
					}
				}
				if( row != null && !row.equals(idProduct) ){
					FileWriter productsWriter = new FileWriter("temp.txt", true);
					count = 0;
					while( row != null && count < 7 ){
						productsWriter.write( row + "\n" );
						row = productsReader.readLine();
						count++;
					}
					productsWriter.write( "\n" );
					productsWriter.close();
				}
			}
			productsReader.close();
			File f1 = new File("temp.txt");           //file to be delete  
			File f2 = new File("Products.txt");
			productsOfTrader();
			if( name.equals(traderName) ){
				System.out.println(" -> The product is removed. ");
				f2.delete();			
				f1.renameTo(f2);
				return true;
			} else if( !traderName.equals("") && !name.equals(traderName) ){
				System.out.println(" -> The product is not removed. It is not your product.");
				f1.delete();
				return false;
			} else if( traderName.equals("") ){
				System.out.println(" -> The product is not removed. There is no the product.");
				f1.delete();
				return false;
			}
			return true;
		} catch (Exception e){
			return false;
		} 
	}

	/**
	* Creates products(LL) with reading Products.txt
	*/
	private void productsOfTrader(){
		products = new LinkedList<Product>();
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
				if( this.name.equals( traderName ) ){
			    	Product product = new Product(idProduct, name, category, price, discountedPrice, description, this);
					products.add(product);
				}
				productsReader.readLine();
			}
		} catch (Exception e){
			//return null;
		} 	
	}

	/**
	* Looking at whether there is a product with this id
	* @param idProduct to search
	* @return if exists, returns true
	*			otherwise false
	*/
	public boolean containsProduct(String idProduct){
		for(int i=0; i<products.size(); i++){
			if( products.get(i).getID().compareTo( idProduct ) == 0 )
				return true;
		}
		return false;
	}

	/**
	* Editing the product with new product
	* @param product to update old product with new values
	* @return if editing, returns true
	*			otherwise false
	*/
	public boolean editProduct(Product product){
		String row = "";
		int count = 0;
		String traderName = "";
		try{  
			FileReader pathToProducts = new FileReader("Products.txt");
			BufferedReader productsReader = new BufferedReader(pathToProducts);
			while ( (row = productsReader.readLine()) != null ){
				//reading a row
				if( row.equals( product.getID() ) ){
					FileWriter productsWriter = new FileWriter("temp.txt", true);
					productsWriter.write(product.getID() + "\n");
					productsWriter.write(product.getName() + "\n");
					productsWriter.write(product.getCategory() + "\n");
					productsWriter.write(product.getPrice() + "\n");
					productsWriter.write(product.getDiscountedPrice() + "\n");
					productsWriter.write(product.getDescription() + "\n");
					productsWriter.write(this.getName() + "\n");
					productsWriter.write( "\n" );
					productsWriter.close();
					count = 0;
					while( row != null && count < 8 ){
						row = productsReader.readLine();
						if( count == 5 )	traderName = row;
						count++;
					}
				}
				if( row != null && !row.equals( product.getID() ) ){
					FileWriter productsWriter = new FileWriter("temp.txt", true);
					count = 0;
					while( row != null && count < 7 ){
						productsWriter.write( row + "\n" );
						row = productsReader.readLine();
						count++;
					}
					productsWriter.write( "\n" );
					productsWriter.close();
				}
			}
			productsReader.close();
			File f1 = new File("temp.txt");           //file to be delete  
			File f2 = new File("Products.txt");
			productsOfTrader();
			if( name.equals(traderName) ){
				System.out.println(" -> The product is edited. ");
				f2.delete();			
				f1.renameTo(f2);
				return true;
			} else if( !traderName.equals("") && !name.equals(traderName) ){
				System.out.println(" -> The product is not edited. It is not your product.");
				f1.delete();
				return false;
			} else if( traderName.equals("") ){
				System.out.println(" -> The product is not edited. There is no the product.");
				f1.delete();
				return false;
			}
			return true;
		} catch (Exception e){
			return false;
		} 
	}

	/**
	* Creating orders of the trader
	* @param flag if true, print the found order
	*				not, do not
	*/
	private void ordersOfTraders(boolean flag){
		orders = new LinkedList<Order>();
		String orderID;
		long customerID;
		String productID;
		String traderName;
		String status;	
		try{  
			FileReader pathToOrders = new FileReader("Orders.txt");
			BufferedReader ordersReader = new BufferedReader(pathToOrders);
			while ( (orderID = ordersReader.readLine()) != null ){
				customerID = Long.parseLong(ordersReader.readLine());
				productID = ordersReader.readLine();
				traderName = ordersReader.readLine();
				status = ordersReader.readLine();
				if( this.name.equals( traderName ) ){
			    	Order order = new Order(orderID, customerID, productID, traderName, status);
			    	if(flag)	System.out.println(order);
					orders.offer(order);
				}
				ordersReader.readLine();
			}
		} catch (Exception e){
			//return null;
		}
	}

	/**
	* Updating orders of the trader and print the found orders
	*/
	public void seeListOfOrders(){
		ordersOfTraders(true);
	}

	/**
	* Meet or cancel the product
	* @param flag if true, meet
	*			if false, cancel
	* @param orderID to changing status of the order
	* @return if everything is okey, returns true
	*			otherwise false
	*/
	public boolean meet(boolean flag, String orderID){
		ordersOfTraders(false);
 		Iterator it = orders.iterator();
   		int num = 0;
	    while (it.hasNext()) {
	        Order e = (Order)it.next();
	        if ( e.compareTo(new Order(orderID,0,"","","")) != 0 ){
	        	num++;
	        }
	    }
	    if( num == orders.size() ){
			System.out.println(" -> Invalid Order ID. ");
	    	return false;
	    }
		String row = "";
		int count = 0;
		try{  
			FileReader pathToOrders = new FileReader("Orders.txt");
			BufferedReader ordersReader = new BufferedReader(pathToOrders);
			while ( (row = ordersReader.readLine()) != null ){
				//reading a row
				if( row.equals( orderID ) ){
					FileWriter ordersWriter = new FileWriter("temp2.txt", true);
					count = 0;
					while( row != null && count != 4 ){
						ordersWriter.write( row + "\n" );
						row = ordersReader.readLine();
						count++;
					}
					if(flag)	ordersWriter.write( "Meet\n");
					else	ordersWriter.write( "Cancel\n");
					ordersWriter.write( "\n" );
					ordersWriter.close();
					row = ordersReader.readLine();
					row = ordersReader.readLine();
				}
				if( row != null && !row.equals( orderID ) ){
					FileWriter ordersWriter = new FileWriter("temp2.txt", true);
					count = 0;
					while( row != null && count < 5 ){
						ordersWriter.write( row + "\n" );
						row = ordersReader.readLine();
						count++;
					}
					ordersWriter.write( "\n" );
					ordersWriter.close();
				}
			}

			ordersReader.close();
			File f1 = new File("temp2.txt");           //file to be delete  
			File f2 = new File("Orders.txt");
			ordersOfTraders(false);
			System.out.println(" -> The order is edited. ");
			f2.delete();			
			f1.renameTo(f2);
			return true;
		} catch (Exception e){
			return false;
		} 
	}

    @Override
    public String toString(){
    	return name;	
    }
}