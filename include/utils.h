#ifndef __utils_h__
#define __utils_h__

namespace utils
{

  template < int N, typename ... types >
  using nth_type_of = typename std :: tuple_element < N, std :: tuple < types ... > > :: type;

  // struct to check the variable type (isinstance python-like)
  template < class, template < class ... > class, class ... >
  struct is_instance : public std :: false_type {};

  // it is a struct with signature given by U < T, V ... > (like a step)
  template < class T, template < class ... > class U, class ... V >
  struct is_instance < U < T, V ... >, U > : public std :: true_type {};

  template < class T >
  struct has_symbol
  {
    template < class U, U >
    struct check;

    template < class U >
    static std :: true_type test ( check < char (*) ( ), & U :: symbol > * );

    template < class U >
    static std :: false_type test ( ... );

    static const bool value = decltype( test < T > (0) ) :: value;
  };

  // useful struct
  template < bool b >
  struct booltype
  {};

  // it is just a std variable
  template < class T, typename B = booltype < true > >
  struct is_variable
  {
    static constexpr bool value = true; // no-step variables are however variables!
  };

  // it is a step variable
  template < class T >
  struct is_variable < T, booltype < is_instance < T, Step > :: value > >
  {
    // a variable is a step with a lambda function equal to math :: Input
    static constexpr bool value = std :: is_same < typename T :: lambda_func, decltype(math :: Input) > :: value;
  };

  // useful alias
  template < class T >
  constexpr bool is_variable_v = is_variable < T > :: value;


  // it is a common variable
  template < class T, typename B = booltype < true > >
  struct is_step
  {
    // if it is not a step variable it is always false
    static constexpr bool value = false;
  };

  // it is a step instance
  template < class T >
  struct is_step < T, booltype < is_instance < T, Step > :: value > >
  {
    // a variable is a step with a lambda function different from math :: Input
    static constexpr bool value = !std :: is_same < typename T :: lambda_func, decltype(math :: Input) > :: value;
  };

  // useful alias
  template < class T >
  constexpr bool is_step_v = is_step < T > :: value;


  // Number of operations in the DAG

  // forward declaration
  template < class T, typename B = booltype < true >, class ... types >
  struct num_operations;

  namespace detail
  {

    // it is just a variable
    template < class func, class ... types >
    struct num_operations_impl
    {
      static constexpr int value = 0;
    };

    // it is a step with multiple inputs
    template < class func, class type, class ... types >
    struct num_operations_impl < Step < func, type, types ... > >
    {
      static constexpr int value = num_operations < type > :: value + num_operations < types ... > :: value;
    };

    // it is a single step
    template < class func, class type >
    struct num_operations_impl < Step < func, type > >
    {
      static constexpr int value = num_operations < type > :: value;
    };

  } // end namespace

  // it is a leaf (aka a variable)
  template < class T, typename B, class ... types >
  struct num_operations
  {
    static constexpr int value = 0;
  };

  // it is a step of the dag
  template < class T, class ... types >
  struct num_operations < T, booltype < is_step < T > :: value >, types ... >
  {
    // +1 is the current step
    static constexpr int value = 1 + detail :: num_operations_impl < T > :: value;
  };

  // Number of variables in DAG

  // forward declaration
  template < class T, typename B = booltype < true >, class ... types >
  struct num_variables;

  namespace detail
  {

    // it is a leaf
    template < class func, class ... types >
    struct num_variables_impl
    {
      static constexpr int value = 1;
    };

    // it is a step with multiple inputs
    template < class func, class type, class ... types >
    struct num_variables_impl < Step < func, type, types ... > >
    {
      static constexpr int value = num_variables < type > :: value + num_variables < types ... > :: value;
    };

    // it is a step on a single variable
    template < class func, class type >
    struct num_variables_impl < Step < func, type > >
    {
      static constexpr int value = num_variables < type > :: value;
    };

  } // end namespace

  // it is just a variable
  template < class T, typename B, class ... types >
  struct num_variables
  {
    static constexpr int value = 1;
  };

  // it is a step of the dag
  template < class T, class ... types >
  struct num_variables < T, booltype < is_step < T > :: value >, types ... >
  {
    static constexpr int value = detail :: num_variables_impl < T > :: value;
  };

  // sizeo of the DAG

  template < class T, typename B = booltype < true > >
  struct dag_size
  {
    // if it is not a step the size is always 0
    static constexpr int value = 0;
  };

  template < class T >
  struct dag_size < T, booltype < is_instance < T, Step > :: value > >
  {
    // the size is given by the SUM of the number of variables and the number of operations
    static constexpr int value = num_operations < T > :: value + num_variables < T > :: value;
  };

  // Operation counter

  template < typename lambda, typename ... types >
  struct OperationCount {};

  template < typename lambda, typename ... types >
  struct OperationCount < Step < lambda, types ... > >
  {
    static constexpr int num_operations = num_operations < Step < lambda, types ... > > :: value;
    static constexpr int num_variables = num_variables < Step < lambda, types ... > > :: value;
    static constexpr int num_nodes = num_operations + num_variables;
    // static constexpr int num_cached = 0;
  };

}


#if __cplusplus < 201700

namespace detail
{

template < class F, class Tuple, std :: size_t ... I >
constexpr decltype(auto) apply_impl ( F && f, Tuple && t, std :: index_sequence < I ... > )
{
  // This implementation is valid since C++20 (via P1065R2)
  // In C++17, a constexpr counterpart of std::invoke is actually needed here
  return f (std :: get < I >(std :: forward < Tuple >(t)) ... );
}


} // namespace detail


namespace std
{

template < class F, class Tuple >
constexpr decltype(auto) apply ( F && f, Tuple && t )
{
  return detail :: apply_impl( std :: forward < F >(f), std :: forward < Tuple >(t),
      std :: make_index_sequence < std :: tuple_size < std :: remove_reference_t < Tuple > > :: value > {});
}

}

#endif

#endif // __utils_h__
