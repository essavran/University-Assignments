/**
*	The Class Product
*	This is a class that contains data related with the product
*	@author Emine Sultan Savran
*	@since 2021-03-10
*/
public class Product{
	private String type, model, color;
	private int stock;//int is enough?
	private String needSuply;
	private int requestedAmount = 1;
	private Branch atBranch;//setter getter

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

	public void setType(String type){
		this.type = type;
	}
	
	public String getType(){
		return type;
	}

	public void setModel(String model){
		this.model = model;
	}

	public String getModel(){
		return model;
	}

	public void setColor(String color){
		this.color = color;
	}

	public String getColor(){
		return color;
	}

	public void setStock(String stock){
		try{
		    this.stock = Integer.parseInt(stock);
		}catch (NumberFormatException ex) {
		    //handle exception here
		}
	}

	public String getStock(){
		return String.valueOf(stock);
	}

	public void setNeedSupply(String needSuply){
		this.needSuply = needSuply;
	}

	public String getNeedSupply(){
		return needSuply;
	}

	public void setBranch(Branch atBranch){
		this.atBranch = atBranch;
	}

	public Branch getBranch(){
		return atBranch;
	}
	
	public boolean isSame(Product newProduct){
		if( this.type.equals( newProduct.getType() ) &&
			this.model.equals( newProduct.getModel() ) &&
			this.color.equals( newProduct.getColor() ) )
			return true;
		return false;
	}

	@Override
	public String toString(){
		return "-> Product Type: " + this.type + " / Product Model: " + this.model + " / Product Color: " 
				+ this.color + " / Where: " + this.atBranch.getName() + " / Amount: " + this.stock + "\n";
	}
}