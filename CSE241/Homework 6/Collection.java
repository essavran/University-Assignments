/**
*	The Interface Collection
*	This is a generic class with one generic parameter which is the generic type E.
*	@author Emine Sultan Savran
*	@since 2021-01-24
* 	@param <E> generic type(template)
*/
public interface Collection<E>{
/**
*	Returns an iterator over the collection
*	@return Iterator
*/
	public Iterator<E> iterator();
/**
*	Ensures that this collection contains the specified element
*	@param e to add
*/
	public void add(E e);
/**
*	Adds all of the elements in the specified collection to this collection
*	@param c to add
*/
	public void addAll(Collection<E> c);
/**
*	Removes all of the elements from this collection
*/
	public void clear();
/**
*	Returns true if this collection contains the specified element.
*	@param e to search
*	@return true or false
*/
	public boolean contains(E e);
/**
*	Returns true if this collection contains all of the elements in the specified collection.
*	@param c to search
*	@return true or false
*/
	public boolean containsAll(Collection<E> c);
/**
*	Returns true if this collection contains no elements.
*	@return true or false
*/
	public boolean isEmpty();
/**
*	Removes a single instance of the specified element from this collection, if it is present
*	@param e to remove
*/	
	public void remove(E e);
/**
*	Removes all of this collection's elements that are also contained in the specified collection
*	@param c to remove
*/
	public void removeAll(Collection<E> c);
/**
*	Retains only the elements in this collection that are contained in the specified collection
*	@param c to compare
*/
	public void retainAll(Collection<E> c);
/**
*	Returns the number of elements in this collection.
*	@return size
*/
	public int size();

}