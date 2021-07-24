/**
*	The Class LinkedList
*	Implements both List and Queue functions
*	@author Emine Sultan Savran
*	@since 2021-01-24
* 	@param <E> generic type(template)
*/
public class LinkedList<E> implements List<E>, Queue<E>{

	private E[] elements;
	private int	size = 0;

	@SuppressWarnings("unchecked")
	public LinkedList(){
	//	size = 1;
		elements = (E[]) new Object[1];
		elements[0] = null;
	}

	@Override
	public final int size(){
		return elements.length;
	}

	@Override
	public Iterator<E> iterator(){
		return new Iterator<E>(this,elements);
	}

	@SuppressWarnings("unchecked")
	@Override
	public void add(E e){
		if( this.size == 0 ){
			this.elements[0] = e;
		} else{
			E[] temp = (E[]) new Object[size+1];
			for(int i=0; i<size; i++){
				temp[i] = this.elements[i];
			}
			int tempSize = size;
			elements = null;
			size = tempSize;
			temp[size] = e;
			this.elements = (E[]) new Object[size+1];
			this.elements = temp;
		}
		size++;
	}
	

	@Override
	public void addAll(Collection<E> c){
		Iterator<E> itr = c.iterator();
		E temp = itr.next();
		while( itr.hasNext() ){
			this.add( temp );
			temp = itr.next();
		}
		this.add( temp );
	}

	@Override
	public void clear(){
		for(int i=0; i<elements.length; i++ ){
			elements[i] = null;
		}
		size = 0;
	}

	@Override
	public boolean contains(E e){
		for( E element : elements ){
			if( element != null && element.equals(e) ){
				return true;
			}	
		}
		return false;
	}

	@Override
	public boolean containsAll(Collection c){
		int count = 0;
		Iterator<E> itr = c.iterator();
		E temp;
		while( itr.hasNext() ){
			count = 0;
			temp = itr.next();
			for(int i=0; i<elements.length; i++){
				if( !elements[i].equals( temp ) ){
					count++;
				}
			}

			if( elements.length == count ){
				return false;
			}
		}

		if( elements.length == count ){
			return false;
		}
		return true;
	}
	
	@Override
	public boolean isEmpty(){
		int count = 0;
		for( E element : elements ){
			if( element == null )	count++;
		}
		if( count == size || size == 0 ) return true;
		return false;
	}
	@SuppressWarnings("unchecked")
	@Override
	public void remove(E e){
		int index = 0;
		if( contains(e) ){
			int tempLength = elements.length;
			E[] temp = (E[]) new Object[tempLength-1];
			for(int i=0; i<tempLength; i++){
				if( elements[i] != null && elements[i].equals( e ) ){
					index = i;
					i = 100;
				}
			}
			for(int i=0; i<tempLength; i++){
				if( i < index ){
					temp[i] = elements[i];
				} else if( i > index ){
					temp[i-1] = elements[i];
				}
			}
			elements = null;
			elements = (E[]) new Object[tempLength-1];
			elements = temp;
			temp = null;
			size = tempLength-1;
		}
	}

	@Override
	public void removeAll(Collection c){
		int tempLength = elements.length;
		Iterator<E> itr = c.iterator();
		E temp;
		while( itr.hasNext() ){
			temp = itr.next();
			for(int i=0; i<tempLength; i++){
				if( elements[i] != null && elements[i].equals( temp ) ){
					remove(temp);
					tempLength = elements.length;
					i = 0;
				}
			}
		}
	}
	@SuppressWarnings("unchecked")	
	@Override
	public void retainAll(Collection c){
		int tempLength = elements.length;
		Iterator<E> itr = c.iterator();
		E temp; 
		E[] arr = (E[]) new Object[tempLength];
		int index = 0;
		//= itr.next();
		while( itr.hasNext() ){
			temp = itr.next();
			for(int i=0; i<tempLength; i++){
				if( (elements[i].equals( temp )) ){
					arr[index] = temp;
					index++;
				}
			}
		}
		E[] arr2 = (E[]) new Object[index];
		for(int i=0; i<index; i++){
			arr2[i] = arr[i];
		}
		elements = arr2;
		size = elements.length;
	}

	@Override
	public E element(){
		E temp;
		temp = elements[0];
		return temp;
	}

	@Override
	public void offer(E e){
		add(e);
	}

	@Override
	public E poll(){
		E head;	
		if( !isEmpty() ){
			head = element();
			remove(head);
		} else{
			throw new RuntimeException("Empty Queue!");
		}
		return head;
	}

	public void print(){
		for(int i=0; i<size; i++){
			System.out.print("->");
			System.out.println(elements[i]);				
		}
	}
}