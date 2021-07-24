/**
* The class that keeps informations 
* of products
*/
public class Product implements Comparable<Product>{

	//Data fields
	/**Product's ID*/
	private String id;
	/**Product's name*/
	private String name;
	/**Product's category tree*/
	private String category;
	/**Product's price*/
	private long price;
	/**Product's discounted price*/
	private long discountedPrice;
	/**Product's description price*/
	private String description;
	/**Product's trader*/
	private Trader trader;

	//Methods
	Product(String id, String name, String category, long price, long discountedPrice, String description, Trader trader){
		setID(id);
		setName(name);
		setCategory(category);
		setPrice(price);
		setDiscountedPrice(discountedPrice);
		setDescription(description);
		setTrader(trader);
	}

	public void setID(String id){
		this.id = id;
	}

	public String getID(){
		return id;
	}
	
	public void setName(String name){
		this.name = name;
	}

	public String getName(){
		return name;
	}

	public void setCategory(String category){
		this.category = category;
	}

	public String getCategory(){
		return category;
	}
	
	public void setPrice(long price){
		this.price = price;
	}

	public long getPrice(){
		return price;
	}

	public void setDiscountedPrice(long discountedPrice){
		this.discountedPrice = discountedPrice;
	}

	public long getDiscountedPrice(){
		return discountedPrice;
	}

	public void setDescription(String description){
		this.description = description;
	}

	public String getDescription(){
		return description;
	}

	public void setTrader(Trader trader){
		this.trader = trader;
	}

	public Trader getTrader(){
		return trader;
	}

	@Override
    public int compareTo( final Product o) {
        return this.name.compareTo(o.getName());
    }

    @Override
    public String toString(){
    	return "Product: \n" + id + "\n" + name + "\n" + category + "\n" + price + "\n" + discountedPrice + "\n" + description + "\n" + trader + "\n";	
    }
}