/**
*	The Class Company
*	This is a class that contains data related with the orders
*	@author Emine Sultan Savran
*	@since 2021-03-10
*/
public class Order{
	/**owner of the order*/
	private Customer customer;
	/**ordered product*/
	private Product product;
	/**where the product is ordered*/
	private Branch branch;
	/**check whether the online shop*/
	private boolean onlineStore;
	/**amount of ordered product*/
	private int buyNum = 0;
/**
*	Constructor
*	@param customer
*	@param branch
*	@param product
*	@param amount of product
*	@param check onlineStore
*/
	Order(Customer customer, Branch branch, Product product, int buyNum, boolean onlineStore){
		this.customer = customer;
		this.branch = branch;
		this.product = product;
		this.onlineStore = onlineStore;
		this.buyNum = buyNum;
	}
/**
*	Set the customer
*	@param customer
*/	
	public void setCustomer(Customer customer){
		this.customer = customer;
	}
/**
*	get the customer
*	@return customer
*/
	public Customer getCustomer(){
		return customer;
	}
/**
*	Set the product
*	@param product
*/		
	public void setProduct(Product product){
		this.product = product;
	}
/**
*	get the product
*	@return product
*/
	public Product getProduct(){
		return product;
	}
/**
*	Set the branch
*	@param branch
*/	
	public void setBranch(Branch branch){
		this.branch = branch;
	}
/**
*	get the branch
*	@return branch
*/
	public Branch getBranch(){
		return branch;
	}
/**
*	Set the buyNum
*	@param buyNum
*/	
	public void setBuyNum(int buyNum){
		this.buyNum = buyNum;
	}
/**
*	get the buyNum
*	@return buyNum
*/
	public int getBuyNum(){
		return buyNum;
	}
/**To print order's information*/
	@Override
	public String toString(){
		String str1 = "Customer's Name and Surname: " + customer.getName() + " " + customer.getSurname() + "\n" +
					"Product's Type: " + product.getType() + "\n" + 
					"Product's Model: " + product.getModel() + "\n" +
					"Product's Color: " + product.getColor() + "\n" +
					"Number of Sold Product: " + this.buyNum + "\n";

		String str2 = "";

		if( onlineStore ){
			str2 = "Branch where the product was purchased: Online Store" + "\n" + 
					"Customer's Address: " + customer.getAddress() + "\n" + "Customer's number: " + customer.getPhoneNumber() + "\n";
		} else{
			str2 = "Branch where the product was purchased: " + branch.getName();
		}
		return str1 + str2 + "\n";
	}
/**
*	To compare order objects
*	@param o object that will be compared
*	@return true if they are same, otherwise false
*/
	@Override
	public boolean equals(Object o){
		if( o == this )
			return true;
		if( o == null )
			return false;
		if( o.getClass() != getClass() )
			return false;
		try{
			Order temp = (Order) o;
			return temp.customer.equals(this.customer) &&
					temp.product.equals(this.product) &&
					temp.branch.equals(this.branch);
		} catch( Exception e ){
			System.out.println("There is some problems");
			return false;
		}
	}
}