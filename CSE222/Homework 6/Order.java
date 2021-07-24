/**
* The class that keeps informations 
* of order
*/
public class Order implements Comparable<Order>{

	//Data fields
	/**Orders's ID*/
	private String orderID;
	private long customerID;
	private String productID;
	private String traderName;
	private String status;

	//Methods
	Order(String orderID, long customerID, String productID, String traderName, String status){
		setOrderID(orderID);
		setCustomerID(customerID);
		setProductID(productID);
		setTraderName(traderName);
		setStatus(status);
	}

	public void setOrderID(String orderID){
		this.orderID = orderID;
	}

	public String getOrderID(){
		return orderID;
	}
	
	public void setCustomerID(long customerID){
		this.customerID = customerID;
	}

	public long getCustomerID(){
		return customerID;
	}


	public void setProductID(String productID){
		this.productID = productID;
	}

	public String getProductID(){
		return productID;
	}
	
	public void setTraderName(String traderName){
		this.traderName = traderName;
	}

	public String getTraderName(){
		return traderName;
	}

	public void setStatus(String status){
		this.status = status;
	}

	public String getStatus(){
		return status;
	}

	@Override
    public int compareTo( final Order o) {
        return this.orderID.compareTo(o.getOrderID());
    }

    @Override
    public String toString(){
    	return this.orderID + "	" + customerID + "	" + productID + "	" + traderName + "	" + status;
    }
}