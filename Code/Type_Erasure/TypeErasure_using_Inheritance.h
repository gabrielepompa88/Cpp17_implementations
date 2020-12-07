#ifndef TYPE_ERASURE_USING_INHERITANCE_H
#define TYPE_ERASURE_USING_INHERITANCE_H

// Type-erasure implementation using inheritance from http://www.cplusplus.com/articles/oz18T05o/

class Object {

	class Concept {
	public:
		virtual ~Concept() {}

		// Concept's interface: pure-virtual 
		virtual void operator()() const = 0;

	};

	template<class T>
	class Model : public Concept {

		T m_instance;

	public:
		Model(const T& instance) : m_instance{ instance } {}

		// Model's interface: delegating to m_instance
		virtual void operator()() const override { return m_instance(); }
	};

	Concept* m_concept;

public:

	template<class U>
	Object(const U& input) : m_concept{new Model<U>(input) } {}

	void operator()() const { m_concept->operator()(); }

};

#endif