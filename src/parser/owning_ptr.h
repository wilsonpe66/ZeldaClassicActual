#pragma once

////////////////////////////////////////////////////////////////
// owning_ptr - Owns its pointer, calls clone() on copy

template <class Type>
class owning_ptr
{
	// Safe bool idiom.
	typedef void (owning_ptr::*safe_bool_type) () const;
	void safe_bool_func() const {}
	
public:
	explicit owning_ptr(Type* p = NULL) : data_(p) {}
	owning_ptr(owning_ptr const& other) : data_(other.clone()) {}
	template <class OtherType>
	owning_ptr(owning_ptr<OtherType> const& other)
			: data_(other.clone()) {}
	~owning_ptr() {delete data_;}
	owning_ptr& operator=(owning_ptr const& rhs)
	{
		delete data_;
		data_ = rhs.clone();
		return *this;
	}
	owning_ptr& operator=(Type* pointer)
	{
		delete data_;
		data_ = pointer;
		return *this;
	}

	// Return a clone of the contents, or NULL if none.
	Type* clone() const
	{
		if (data_) return data_->clone();
		return NULL;
	}

	operator safe_bool_type() const
	{
		return data_ ? &owning_ptr::safe_bool_func : NULL;
	}

	Type* get() {return data_;}
	Type const* get() const {return data_;}
	Type& operator*() {return *data_;}
	Type const& operator*() const {return *data_;}
	Type* operator->() {return data_;}
	Type const* operator->() const {return data_;}
	Type* release()
	{
		Type* temp = data_;
		data_ = NULL;
		return temp;
	}
	void reset(Type* p = NULL)
	{
		delete data_;
		data_ = p;
	}
	
private:
	Type* data_;
};

template <class Type, class Type2>
bool operator==(owning_ptr<Type> const& lhs, owning_ptr<Type2> const& rhs)
{
	return lhs.get() == rhs.get();
}

template <class Type, class Type2>
bool operator!=(owning_ptr<Type> const& lhs, owning_ptr<Type2> const& rhs)
{
	return lhs.get() != rhs.get();
}

template <class Type, class Type2>
bool operator==(owning_ptr<Type> const& lhs, Type2* rhs)
{
	return lhs.get() == rhs;
}

template <class Type, class Type2>
bool operator!=(owning_ptr<Type> const& lhs, Type2* rhs)
{
	return lhs.get() != rhs;
}

template <class Type, class Type2>
bool operator==(Type* lhs, owning_ptr<Type2> const& rhs)
{
	return lhs == rhs.get();
}

template <class Type, class Type2>
bool operator!=(Type* lhs, owning_ptr<Type2> const& rhs)
{
	return lhs != rhs.get();
}
