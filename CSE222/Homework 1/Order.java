/**
*	The Class Company
*	This is a class that contains data related with the orders
*	@author Emine Sultan Savran
*	@since 2021-03-10
*/
public class Order{
	private Customer customer;
	private Product product;
	private Branch branch;
	private boolean onlineStore;
	private int buyNum = 0;

	Order(Customer customer, Branch branch, Product product, int buyNum, boolean onlineStore){
		this.customer = customer;
		this.branch = branch;
		this.product = product;
		this.onlineStore = onlineStore;
		this.buyNum = buyNum;
	}

	public void setCustomer(Customer customer){
		this.customer = customer;
	}

	public Customer getCustomer(){
		return customer;
	}
	
	public void setProduct(Product product){
		this.product = product;
	}

	public Product getProduct(){
		return product;
	}

	public void setBranch(Branch branch){
		this.branch = branch;
	}

	public Branch getBranch(){
		return branch;
	}

	public void setBuyNum(int buyNum){
		this.buyNum = buyNum;
	}

	public int getBuyNum(){
		return buyNum;
	}

	public boolean isSame(Order order){
		if( order.customer.isSame(this.customer) &&
			order.product.isSame(this.product) &&
			order.branch.isSame(this.branch) ) //not sure
			return true;
		return false;
	}

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
}