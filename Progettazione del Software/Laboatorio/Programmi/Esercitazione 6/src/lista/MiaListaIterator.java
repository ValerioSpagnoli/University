package lista;

import java.util.*;

public class MiaListaIterator<E> implements Iterator<E> {
	private Object[] element;
	private int size;
	private int index;
	
	public MiaListaIterator(Object[] element, int size) {
		this.element = element;
		this.size = size;
		this.index = 0;
	}

	@Override
	public boolean hasNext() {
		return index < size;
	}

	@Override
	public E next() {
		if(!hasNext()) {
			throw new NoSuchElementException();
		}
		return (E)element[index++];
	}

}
