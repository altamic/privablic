// Generate a static data member of type Stub::type in which to store
// the address of a private member.  It is crucial that Stub does not
// depend on the /value/ of the the stored address in any way so that
// we can access it from ordinary code without directly touching
// private data.
template <class Stub>
struct stowed
{
  static typename Stub::type value;
}; 
template <class Stub> 
typename Stub::type stowed<Stub>::value;

// Generate a static data member whose constructor initializes
// stowed<Stub>::value. This type will only be named in an explicit
// instantiation, where it is legal to pass the address of a private
// member.
template <class Stub, typename Stub::type x>
struct stow_private
{
  stow_private() { stowed<Stub>::value = x; }
  static stow_private instance;
};
template <class Stub, typename Stub::type x> 
stow_private<Stub, x> stow_private<Stub, x>::instance;

template<typename Stub>
struct result {
  /* export it ... */
  typedef typename Stub::type type;
  static type ptr;
};

template<typename Stub>
typename result<Stub>::type result<Stub>::ptr;

template<typename Stub, typename Stub::type p>
struct stowed_method : result<Stub> {
  /* fill it ... */
  struct _stowed_method {
    _stowed_method() { result<Stub>::ptr = p; }
  };
  static _stowed_method stowed_method_obj;
};

template<typename Stub, typename Stub::type p>
typename stowed_method<Stub, p>::_stowed_method stowed_method<Stub, p>::stowed_method_obj;

