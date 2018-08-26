//File: Pair.java
//Date: Fri Aug 16 17:43:03 2013 +0800



public class Pair<T1, T2> {
	/**
	 * First element.
	 */
	public T1 first;

	/**
	 * Second element.
	 */
	public T2 second;

	public Pair(T1 first, T2 second) {
		this.first = first;
		this.second = second;
	}

	@Override
	public String toString() {
		return "(" + first.toString() + "," + second.toString() + ")";
	}

	@Override
	public int hashCode() {
		return first.hashCode() ^ second.hashCode();
	}

	@Override
	public boolean equals(Object ob) {
		if (ob == null) {
			return false;
		}
		return ob.getClass() == this.getClass()
			   && ((Pair <? , ? >) ob).first.equals(this.first)
			   && ((Pair <? , ? >) ob).second.equals(this.second);
	}
}
