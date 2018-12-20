
#ifndef _MYALGORITHM_H_DLHML_
#define _MYALGORITHM_H_DLHML_

namespace dlhml{

		// TEMPLATE CLASS auto_ptr
template<class _Ty>
	class auto_ptr_close;

template<class _Ty>
	struct auto_ptr_close_ref
		{	// proxy reference for auto_ptr copying
	auto_ptr_close_ref(auto_ptr_close<_Ty>& _Right)
		: _Ref(_Right)
		{	// construct from compatible auto_ptr
		}

	auto_ptr_close<_Ty>& _Ref;	// reference to constructor argument
	};

template<class _Ty>
	class auto_ptr_close
		{	// wrap an object pointer to ensure destruction
public:
	typedef _Ty element_type;

	explicit auto_ptr_close(_Ty *_Ptr = 0) throw ()
		: _Myptr(_Ptr)
		{	// construct from object pointer
		}

	auto_ptr_close(auto_ptr_close<_Ty>& _Right) throw ()
		: _Myptr(_Right.release())
		{	// construct by assuming pointer from _Right auto_ptr
		}

	auto_ptr_close(auto_ptr_close_ref<_Ty> _Right) throw ()
		: _Myptr(_Right._Ref.release())
		{	// construct by assuming pointer from _Right auto_ptr_ref
		}

	template<class _Other>
		operator auto_ptr_close<_Other>() throw ()
		{	// convert to compatible auto_ptr
		return (auto_ptr_close<_Other>(*this));
		}

	template<class _Other>
		operator auto_ptr_close_ref<_Other>() throw ()
		{	// convert to compatible auto_ptr_ref
		return (auto_ptr_close_ref<_Other>(*this));
		}

	template<class _Other>
		auto_ptr_close<_Ty>& operator=(auto_ptr_close<_Other>& _Right) throw ()
		{	// assign compatible _Right (assume pointer)
		reset(_Right.release());
		return (*this);
		}
/*
	template<class _Other>
		auto_ptr_close(auto_ptr_close<_Other>& _Right) throw ()
		: _Myptr(_Right.release())
		{	// construct by assuming pointer from _Right
		}
*/
	auto_ptr_close<_Ty>& operator=(auto_ptr_close<_Ty>& _Right) throw ()
		{	// assign compatible _Right (assume pointer)
		reset(_Right.release());
		return (*this);
		}

	auto_ptr_close<_Ty>& operator=(auto_ptr_close_ref<_Ty>& _Right) throw ()
		{	// assign compatible _Right._Ref (assume pointer)
		reset(_Right._Ref.release());
		return (*this);
		}

	~auto_ptr_close()
		{	// destroy the object
		if(_Myptr)
			_Myptr->close();
		}

	_Ty& operator*() const throw ()
		{	// return designated value
		return (*_Myptr);
		}

	_Ty *operator->() const throw ()
		{	// return pointer to class object
		return (&**this);
		}

	_Ty *get() const throw ()
		{	// return wrapped pointer
		return (_Myptr);
		}

	_Ty *release() throw ()
		{	// return wrapped pointer and give up ownership
		_Ty *_Tmp = _Myptr;
		_Myptr = 0;
		return (_Tmp);
		}

	void reset(_Ty* _Ptr = 0)
		{	// destroy designated object and store new pointer
		if (_Ptr != _Myptr){
			if(_Myptr)
				_Myptr->close();
			}
		_Myptr = _Ptr;
		}

private:
	_Ty *_Myptr;	// the wrapped object pointer
	};


}
#endif //_MYALGORITHM_H_DLHML_
