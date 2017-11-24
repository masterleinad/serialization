#ifndef BOOST_ARCHIVE_BINARY_IARCHIVE_IMPL_HPP
#define BOOST_ARCHIVE_BINARY_IARCHIVE_IMPL_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// binary_iarchive_impl.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <istream>
#include <boost/archive/basic_binary_iprimitive.hpp>
#include <boost/archive/basic_binary_iarchive.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost { 
namespace archive {

namespace detail {
    template<class Archive> class interface_iarchive;
} // namespace detail

template<class Archive, class Elem, class Tr>
class BOOST_SYMBOL_VISIBLE binary_iarchive_impl : 
    public basic_binary_iprimitive<binary_iarchive_impl<Archive, Elem, Tr>, Elem, Tr>,
    public basic_binary_iarchive<binary_iarchive_impl<Archive, Elem, Tr> >
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    #if BOOST_WORKAROUND(BOOST_MSVC, < 1500)
        // for some inexplicable reason insertion of "class" generates compile erro
        // on msvc 7.1
        friend detail::interface_iarchive<binary_iarchive_impl<Archive, Elem, Tr> >;
        friend basic_binary_iarchive<binary_iarchive_impl<Archive, Elem, Tr> >;
        friend load_access;
    #else
        friend class detail::interface_iarchive<binary_iarchive_impl<Archive, Elem, Tr> >;
        friend class basic_binary_iarchive<binary_iarchive_impl<Archive, Elem, Tr> >;
        friend class load_access;
    #endif
#endif
    template<class T>
    void load_override(T & t){
        this->basic_binary_iarchive<binary_iarchive_impl<Archive, Elem, Tr> >::load_override(t);
    }
    void init(unsigned int flags){
        if(0 != (flags & no_header)){
            return;
        }
        #if ! defined(__MWERKS__)
            this->basic_binary_iarchive<binary_iarchive_impl<Archive, Elem, Tr> >::init();
            this->basic_binary_iprimitive<binary_iarchive_impl<Archive, Elem, Tr>, Elem, Tr>::init();
        #else
            basic_binary_iarchive<binary_iarchive_impl<Archive, Elem, Tr> >::init();
            basic_binary_iprimitive<binary_iarchive_impl<Archive, Elem, Tr>, Elem, Tr>::init();
        #endif
    }
    binary_iarchive_impl(
        std::basic_streambuf<Elem, Tr> & bsb, 
        unsigned int flags
    ) :
        basic_binary_iprimitive<binary_iarchive_impl<Archive, Elem, Tr>, Elem, Tr>(
            bsb, 
            0 != (flags & no_codecvt)
        ),
        basic_binary_iarchive<binary_iarchive_impl<Archive, Elem, Tr> >(flags)
    {
        init(flags);
    }
    binary_iarchive_impl(
        std::basic_istream<Elem, Tr> & is, 
        unsigned int flags
    ) :
        basic_binary_iprimitive<binary_iarchive_impl<Archive, Elem, Tr>, Elem, Tr>(
            * is.rdbuf(), 
            0 != (flags & no_codecvt)
        ),
        basic_binary_iarchive<binary_iarchive_impl<Archive, Elem, Tr> >(flags)
    {
        init(flags);
    }
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_ARCHIVE_BINARY_IARCHIVE_IMPL_HPP
