public class HybridList<E> {
	// Data Fields
	 /** The default initial capacity */
	private static final int MAX_NUMBER = 10;
	 /** The underlying data ll */
	private KWLinkedList< KWArrayList<E> > theData;
	 /** The current size */
	private int size = 0;
	private int numOfLL = 0;
	public HybridList(){
		theData = new KWLinkedList< KWArrayList<E> >();
	}

	public int size(){
		return size;
	}

	public E get (int index) {
		int temp = 0;
		for(int i=0; i<theData.size(); i++){
			for(int j=0; j<theData.get(i).size(); j++ ){
				if( temp == index ){
					return theData.get(i).get(j);
				}
				temp++;
			}
		}
		return null;
	}

	public boolean add(E anEntry) {
		reallocate();
		for(int i=0; i<theData.size(); i++){
			if( theData.get(i).size() != MAX_NUMBER ){
				//boş yer buldum ekleme yaptım
				theData.get(i).add(anEntry);
				size++;
				return true;
			}
		}
		return true;
	}

	public boolean remove(E anEntry) {
		for(int i=0; i<theData.size(); i++){
			for(int j=0; j<theData.get(i).size(); j++ ){
				if( anEntry.equals( theData.get(i).get(j) ) ){
					theData.get(i).remove(anEntry);
					size--;
					return true;
				}
			}
		}
		reallocate();
        return false;
    }
    
	private void reallocate() {
		//tüm arraylistler max elemanlıysa
		int countMAX = 0;
		for(int i=0; i<theData.size(); i++){
			if( theData.get(i).size() >= MAX_NUMBER ){
				countMAX++;
			}
			if( theData.get(i).size() == 0 ){
				//ya da elemansız arraylist varsa
				theData.remove(i);
			}
		}
		if( countMAX == theData.size() ){
			theData.add( new KWArrayList<E>() );
			numOfLL++;
		}
	}

	public int indexOf(E anEntry) {
		int temp = 0;
		for(int i=0; i<theData.size(); i++){
			for(int j=0; j<theData.get(i).size(); j++ ){
				if( anEntry.equals( theData.get(i).get(j) ) ){
					return temp;
				}
				temp++;
			}
		}
        return -1;
    }

    public boolean contains(E o) {
        return indexOf(o) >= 0;
    }
    public int getNumOfLL(){
    	return numOfLL;
    }
}

