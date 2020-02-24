//
// Created by 21927 on 23.02.2020.
//

#ifndef GRAPITO_UTILS_H
#define GRAPITO_UTILS_H
#include <type_traits>


template <template <typename...> class Base, typename Derived>
struct is_base_of_template
{
    using U = typename std::remove_cv<Derived>::type;

    template <typename... Args>
    static std::true_type test(Base<Args...>*);

    static std::false_type test(void*);

    using type = decltype(test(std::declval<U*>()));
};

template <template <typename...> class Base, typename Derived>
using is_base_of_template_t = typename is_base_of_template<Base, Derived>::type;


template <typename Type, template <typename> class Condition>
struct Where {
protected:
/*
 * TODO
 *  Currently Condition must contain type definition
 *  and to provide logic aka throw error on bad Type
 *  it must raise Compilation error by static_assert
 * */
typedef typename Condition<Type>::type type;
};

#endif //GRAPITO_UTILS_H
