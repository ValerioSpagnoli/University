package lista;


import java.lang.reflect.Array;
import java.util.*;

public class MiaLista<E> implements List<E>, Cloneable {
	private Object[] element;
	int size;
	
	public MiaLista() {
		element = new Object[13];
		size = 0;	
	}
	
	public int size() {
		return size;
	}
	
	public boolean isEmpty() {
		return size == 0;
	}
	
	public boolean contains(Object o) {
		for(int i = 0; i<size; i++) {
			if(element[i].equals(o)) {
				return true;
			}
		}
		return false;
	}
	
	public boolean add(E e) {
		//rialloca l'array con dimensione doppia
		if(size >= element.length) {
			element = Arrays.copyOf(element, element.length * 2);
		}
		element[size] = e;
		size++;
		return true;
	}
	
	public boolean checkBounds(int index) {
		return index >=0 && index<size;
	}
	
	public void add(int index, E e) {
		if(!checkBounds(index)) {
			throw new IndexOutOfBoundsException();
		}
		//rialloca l'array di dimensione doppia
		if(size>=element.length) {
			element = Arrays.copyOf(element, element.length * 2);
		}
		for(int i = index; i<size-1; i++) {
			element[i+1] = element[i];
		}
		element[index] = e;
		size++;

	}
	
	public boolean remove(Object o) {
		if(!contains(o)) return false;
		remove(indexOf(o));
		return true;
	}
	
	public E remove(int index) {
		if(!checkBounds(index)) {
			throw new IndexOutOfBoundsException();
		}
		E old = (E) element[index];
		
		//traslo gli elementi dell'array a sinistra per colmare lo spazio
		for(int i = index; i<size-1; i++) {
			element[i] = element[i+1];
		}
		size--;
		
		//rialloca l'array con dimensione pari alla metà della dimensione attuale
		if(element.length>13 && size < element.length / 2) {
			element = Arrays.copyOf(element, element.length / 2);
		}
		return old;
	}
	
	
	
	public void clear() {
		element = new Object[13];
		size = 0;
	}
	
	public E get(int index) {
		if(!checkBounds(index)) {
			throw new IndexOutOfBoundsException();
		}
		E r = (E)element[index];
		return r;
	}
	
	public E set(int index, E e) {
		if(!checkBounds(index)) {
			throw new IndexOutOfBoundsException();
		}
		E old = (E) element[index];
		element[index] = e;
		return old;
		
	}
	
	public int indexOf(Object o) {
		for(int i = 0; i<size; i++) {
			if(element[i].equals(o)) {
				return i;
			}
		}
		return -1;
	}
	
	public int lastIndexOf(Object o) {
		int lastIndex = -1;
		for(int i = 0; i<size; i++) {
			if(element[i].equals(o)) {
				lastIndex = i;
			}
		}
		return lastIndex;
	}
	
	public Iterator<E> iterator(){
		return new MiaListaIterator<E>(element, size);
	}
	
	public boolean equals(Object o) {
		if(o == null || !getClass().equals(o.getClass())) {
			return false;
		}
		
		MiaLista other = (MiaLista) o;
		Iterator<E> it1 = iterator();
		Iterator<?> it2 = other.iterator();
		
		while(it1.hasNext() && it2.hasNext()) {
			E o1 = it1.next();
			Object o2 = it2.next();
			if(!(o1==null ? o2 == null : o1.equals(o2))) {
				return false;
			}
		}
		return !(it1.hasNext() || it2.hasNext());
	}
	
	public Object clone() {
		try {
			MiaLista<E> copia = (MiaLista<E>) super.clone();
			copia.element = element.clone();
			copia.size = size;
			return copia;
		}
		catch(CloneNotSupportedException e) {
			throw new InternalError(e.toString());
		}
	}
	
	public List<E> subList(int fromIndex, int toIndex){
		if(fromIndex<0 || toIndex>size || fromIndex > toIndex) {
			throw new IndexOutOfBoundsException();
		}
		MiaLista<E> copia = new MiaLista<>();
		for(int  i = fromIndex; i < toIndex; i++) {
			copia.add((E) element[i]);
		}
		return copia;
	}
	
	public boolean containsAll(Collection<?> c) {
		for(Object o : c) {
			if(!contains(o)) {
				return false;
			}
		}
		return true;
	}
	
	public boolean addAll(Collection <? extends E> c) {
		boolean modified = false;
		for(E e : c) {
			modified = modified || add(e);
		}
		return modified;
	}
	
	public boolean addAll(int index, Collection<? extends E> c) {
		boolean modified = false;
		int offset = 0;
		for(E e : c) {
			add(index + offset++, e);
			modified = true;
		}
		return modified;
	}
	
	public boolean retainAll(Collection<?> c) {
		boolean modified = false;
		for(E e : this) {
			if(!c.contains(e)) {
				modified = modified || remove(e);
			}
		}
		return modified;
	}
	
	public boolean removeAll(Collection<?> c) {
		boolean modified = false;
		for(Object e : c) {
				modified = modified || remove(e);
			}
		return modified;
	}
	
	public Object[] toArray() {
		return Arrays.copyOf(element, size);
	}
	
	public <T> T[] toArray(T[] a) {
		T[] array = (T[]) Array.newInstance(a.getClass().getComponentType(), size);
		for(int i = 0; i<size; i++) {
			array[i] =  (T) element[i];
		}
		return array;
	}
	
	public String toString() {
		return Arrays.toString(Arrays.copyOf(element, size));
	}
	
	public ListIterator<E> listIterator(){
		throw new UnsupportedOperationException();
	}
	
	public ListIterator<E> listIterator(int index){
		throw new UnsupportedOperationException();
	}
	
}