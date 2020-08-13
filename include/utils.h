#ifndef __utils_h__
#define __utils_h__

namespace utils
{

  template < int N, class ... types >
  using nth_type_of = typename std :: tuple_element < N, std :: tuple < types ... > > :: type;

  namespace details
  {
    // struct to check the variable type (isinstance python-like)
    template < class, template < class, class ... > class >
    struct is_instance_impl : public std :: false_type {};

    // it is a struct with signature given by U < T, V ... > (like a step)
    template < template < class, class ... > class U, class ... Ts >
    struct is_instance_impl < U < Ts ... >, U > : public std :: true_type {};
  }

  // useful alias
  template < class T, template < class, class ... > class U >
  using is_instance = details :: is_instance_impl < std :: decay_t < T >, U >;

  namespace details
  {
    template < template < class, class ... > class base, class derived >
    struct is_base_of_step_impl
    {
      template < class T, class ... Ts >
      static constexpr std :: true_type  test (const base < T, Ts ... > * );

      static constexpr std :: false_type test (...);

      using type = decltype( test (std :: declval < std :: remove_cv_t < std :: remove_reference_t < derived > > * >() ) );
    };
  }

  template < template < class, class ... > class base, class derived >
  using is_base_of_step = typename details :: is_base_of_step_impl < base, derived > :: type;

  template < class T, template < class, class ... > class U >
  struct is_step_instance
  {
    static constexpr bool value = is_instance < T, Step > :: value || is_base_of_step < Step, T > :: value;
  };

  template < class T >
  struct has_symbol
  {
    template < class U, U >
    struct check;

    template < class U >
    static constexpr std :: true_type test ( check < char (*) ( ), & U :: symbol > * );

    template < class U >
    static constexpr std :: false_type test ( ... );

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
  struct is_variable < T, booltype < is_step_instance < T, Step > :: value > >
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
  struct is_step < T, booltype < is_step_instance < T, Step > :: value > >
  {
    // a variable is a step with a lambda function different from math :: Input
    static constexpr bool value = !std :: is_same < typename std :: remove_cv_t < std :: remove_reference_t < T > > :: lambda_func, decltype(math :: Input) > :: value;
  };

  // useful alias
  template < class T >
  constexpr bool is_step_v = is_step < T > :: value;


  // Get the equivalent step type
  template < class T, typename std :: enable_if < is_step < T > :: value > :: type * = nullptr >
  struct get_step_type
  {
    template < class C >
    struct get_template_type;

    template < template < class, class ... > class C, class Func, class ... types >
    struct get_template_type < C < Func, types ... > >
    {
      using type = Step < Func, types ... >;
    };

    using type = typename get_template_type < T > :: type;
  };


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
      static constexpr int value = :: utils :: num_operations < type > :: value + :: utils :: num_operations < types ... > :: value;
    };

    // it is a single step
    template < class func, class type >
    struct num_operations_impl < Step < func, type > >
    {
      static constexpr int value = :: utils :: num_operations < type > :: value;
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
    static constexpr int value = 1 + detail :: num_operations_impl < typename get_step_type < T > :: type > :: value;
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
    static constexpr int value = detail :: num_variables_impl < typename get_step_type < T > :: type > :: value;
  };

  // sizeo of the DAG

  template < class T, typename B = booltype < true > >
  struct dag_size
  {
    // if it is not a step the size is always 0
    static constexpr int value = 0;
  };

  template < class T >
  struct dag_size < T, booltype < is_step_instance < T, Step > :: value > >
  {
    // the size is given by the SUM of the number of variables and the number of operations
    static constexpr int value = num_operations < T > :: value + num_variables < T > :: value;
  };

  // Operation counter

  template < class T, typename std :: enable_if < utils :: is_step < T > :: value > :: type * = nullptr >
  struct OperationCount
  {
    static constexpr int num_operations = :: utils :: num_operations < T > :: value;
    static constexpr int num_variables = :: utils :: num_variables < T > :: value;
    static constexpr int num_nodes = num_operations + num_variables;
    // static constexpr int num_cached = 0;
  };

}

namespace detail
{
  template < class, class >
  struct join_tuples
  {};

  template < class ... left, class ... right >
  struct join_tuples < std :: tuple < left ... >, std :: tuple < right ... > >
  {
    using type = std :: tuple < left ..., right ... >;
  };

  template < class T, std :: size_t N >
  struct generate_tuple_type
  {
    using left  = typename generate_tuple_type < T, N / 2 > :: type;
    using right = typename generate_tuple_type < T, N / 2 + N % 2> :: type;
    using type  = typename join_tuples < left, right > :: type;
  };

  template < class T >
  struct generate_tuple_type < T, 1 >
  {
    using type = std :: tuple < T >;
  };

  template < class T >
  struct generate_tuple_type < T, 0 >
  {
    using type = std :: tuple < >;
  };


  template < std :: size_t n, class return_t, class ... Args >
  constexpr decltype(auto) make_n_tuple (Args ... args) noexcept
  {
    if constexpr (n > 0)
      return std :: tuple_cat(std :: make_tuple(return_t(args ...)), make_n_tuple < n - 1, return_t, Args ... >(args ...));

    else
      return std :: make_tuple(return_t(args ...));
  }
}


#if __cplusplus < 201700 && !_MSC_VER

namespace detail
{

template < class F, class Tuple, std :: size_t ... I >
inline constexpr decltype(auto) apply_impl ( F && f, Tuple && t, std :: index_sequence < I ... > )
{
  // This implementation is valid since C++20 (via P1065R2)
  // In C++17, a constexpr counterpart of std::invoke is actually needed here
  return f (std :: get < I >(std :: forward < Tuple >(t)) ... );
}


} // namespace detail


namespace std
{

template < class F, class Tuple >
inline constexpr decltype(auto) apply ( F && f, Tuple && t )
{
  return detail :: apply_impl( std :: forward < F >(f), std :: forward < Tuple >(t),
      std :: make_index_sequence < std :: tuple_size < std :: remove_reference_t < Tuple > > :: value > {});
}

}

#endif // old __cplusplus

#endif // __utils_h__
