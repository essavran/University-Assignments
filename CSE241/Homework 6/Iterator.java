/**
*	The Class Iterator
*	@author Emine Sultan Savran
*	@since 2021-01-24
* 	@param <E> generic type(template)
*/
public class Iterator<E>{
	private E[] data;
	private Collection<E> c;
	private int size;
	private int cursor;
/**
*	Constructor
*	@param data elements
*	@param c Collection
*/	
	public Iterator(Collection<E> c, E[] data){
		this.cursor = 0;
		this.size = data.length;
		this.data = data;
		this.c = c;
	}
/**
*	Returns true if the iteration has more elements.
*	@return true or false
*/
	public boolean hasNext(){
		return cursor<size;
	}
/**
*	Returns the next element in the iteration and advances the iterator.
*	@return next element
*/	
	public E next(){
		return data[cursor++];
	}
/**
*	Removes from the underlying collection the last element returned by this iterator.
*/
	@SuppressWarnings("unchecked")
	public void remove(){
/*
		if( c instanceof Queue ){
			Throw new exception();
		}
*/
		if( !this.hasNext() ){
			data[cursor-1] = null;
		} else{
			while( this.hasNext() ){
				data[cursor-1] = data[cursor];
				data[cursor] = null;				
				cursor++;
			} 
		}
		E[] tempData = (E[]) new Object[size-1];
		for(int i=0; i<size-1; i++){
			tempData[i] = this.data[i];
		}
		c.clear();
		for(int i=0; i<size-1; i++){
			c.add(tempData[i]);
		}
		this.data = tempData;
		this.size = size-1;
		this.cursor = 0;//??
	}
}