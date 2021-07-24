/**
*	The Class Product
*	This is a class that contains data related with the product
*	@author Emine Sultan Savran
*	@since 2021-03-10
*/
public class Product{
	/**type, model and color of product*/
	private String type, model, color;
	/**stock amount of product*/
	private int stock;
	/**to check need to supply*/
	private String needSuply;
	/**requested amount of product*/
	private int requestedAmount = 1;
	/**to know which branch have this product*/
	private Branch atBranch;
/**
*	The constructor
*	@param type of product
*	@param model of product
*	@param color of product
*	@param stock of prodcut
*	@param atBranch which have this product
*/	
	public Product(String type, String model, String color, String stock, Branch atBranch){
		setType(type);
		setModel(model);
		setColor(color);
		setStock(stock);
		if( this.stock<=requestedAmount )
			setNeedSupply("Need");
		else
			setNeedSupply("No need");
		setBranch(atBranch);
	}
/**
*	Set the type
*	@param type
*/	
	public void setType(String type){
		this.type = type;
	}
/**
*	get the type
*	@return type
*/	
	public String getType(){
		return type;
	}
/**
*	Set the model
*	@param model
*/	
	public void setModel(String model){
		this.model = model;
	}
/**
*	get the model
*	@return model
*/
	public String getModel(){
		return model;
	}
/**
*	Set the color
*	@param color
*/	
	public void setColor(String color){
		this.color = color;
	}
/**
*	get the color
*	@return color
*/
	public String getColor(){
		return color;
	}
/**
*	Set the stock
*	@param stock
*/	
	public void setStock(String stock){
		try{
		    this.stock = Integer.parseInt(stock);
		}catch (NumberFormatException ex) {
		    //handle exception here
		}
	}
/**
*	get the stock
*	@return stock
*/
	public String getStock(){
		return String.valueOf(stock);
	}
/**
*	Set the need supply
*	@param needSuply need supply
*/	
	public void setNeedSupply(String needSuply){
		this.needSuply = needSuply;
	}
/**
*	get the need supply
*	@return company
*/
	public String getNeedSupply(){
		return needSuply;
	}
/**
*	Set the branch
*	@param atBranch branch
*/	
	public void setBranch(Branch atBranch){
		this.atBranch = atBranch;
	}
/**
*	get the branch
*	@return branch
*/
	public Branch getBranch(){
		return atBranch;
	}
/**To print product's information*/
	@Override
	public String toString(){
		return "-> Product Type: " + this.type + " / Product Model: " + this.model + " / Product Color: " 
				+ this.color + " / Where: " + this.atBranch.getName() + " / Amount: " + this.stock + "\n";
	}
/**
*	To compare product objects
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
			Product temp = (Product) o;
			return this.type.equals( temp.getType() ) &&
			this.model.equals( temp.getModel() ) &&
			this.color.equals( temp.getColor() );
		} catch( Exception e ){
			System.out.println("There is some problems");
			return false;
		}
	}
}