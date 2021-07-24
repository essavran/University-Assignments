/**
*	The Queue Collection
*	Queues order elements in a FIFO (first-in-first-out) manner.
*	@author Emine Sultan Savran
*	@since 2021-01-24
* 	@param <E> generic type(template)
*/
public interface Queue<E> extends Collection<E>{
/**
*	Inserts the specified element into this queue
*	@param e to add
*/
	public void add(E e);
/**
*	Retrieves, but does not remove, the head of this queue
*	@return head
*/
	public E element();
/**
*	Inserts the specified element into this queue
*	@param e to insert
*/
	public void offer(E e);
/**
*	Retrieves and removes the head of this queue
*	@return head
*/
	public E poll();
}