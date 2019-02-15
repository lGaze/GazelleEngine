/***************************************************************************/
/* @filename gzStdHeaders
/* @author Gazelle
/* @date 2019/02/12
/* @brief Header for the STD libraries
/***************************************************************************/

#pragma once

/***************************************************************************/
/* C type objects                                                          */
/***************************************************************************/

#include <cmath>

/***************************************************************************/
/* STL containers                                                          */
/***************************************************************************/

#include <vector>
#include <stack>
#include <map>
#include <string>
#include <set>
#include <list>
#include <deque>
#include <queue>
#include <bitset>
#include <array>
#include <forward_list>
#include <unordered_map>
#include <unordered_set>


/***************************************************************************/
/* Windows specifics                                                       */
/***************************************************************************/

#if GZ_PLATFORM == GZ_PLATFORM_WIN32
  //Undefine min & max
# undef min
# undef max

# if !defined(NOMINMAX) && defined(_MSC_VER)
#   define NOMINMAX     //Required to stop windows.h messing up std::min
# endif
# if defined( __MINGW32__ )
#   include <unistd.h>
# endif
#endif


/***************************************************************************/
/* Standard containers                                                     */
/***************************************************************************/

/**
 * @brief 
 */
template<typename T, typename A = std::allocator<T>>
using Deque = std::deque<T, A>;

/**
 * @brief
 */
template<typename T, typename A = std::allocator<T>>
using Vector = std::vector <T, A>;


/**
 * @brief 
 */
template<typename T, typename A = std::allocator<T>>
using List = std::list<T, A>;

/**
 * @brief
 */
template<typename T, typename A = std::allocator<T>>
using ForwardList = std::forward_list<T, A>;

/**
 * @brief
 */
template<typename T, typename A = std::allocator<T>>
using Queue = std::queue<T, A>;

/**
 * @brief
 */
template<typename T, typename P = std::less<T>, typename A = std::allocator<T>>
using Set = std::set<T, P, A>;

/**
 * @brief 
 */
template<typename K,
         typename V,
         typename P = std::less<K>,
         typename A = std::allocator<std::pair<const K, V>>>
using Map = std::map<K, V, P, A>;

/**
 * @brief 
 */
template<typename T, typename P = std::less<T>, typename A = std::allocator<T>>
using MultiSet = std::multiset<T, P, A>;

/**
 * @brief
 */
template<typename K,
         typename V,
         typename P = std::less<K>,
         typename A = std::allocator<std::pair<const K, V>>>
using MultiMap = std::multimap<K, V, P, A>;

/**
 * @brief 
 */
template<typename T,
         typename H = std::hash<T>,
         typename C = std::equal_to<T>,
         typename A = std::allocator<T>>
using UnorderedSet = std::unordered_set<T, H, C, A>;

/**
 * @brief
 */
template<typename K,
         typename H = std::hash<K>,
         typename C = std::equal_to<K>,
         typename A = std::allocator<K>>
using UnorderedMap = std::unordered_map<K, H, C, A>;

/**
 * @brief 
 */
template<typename K,
         typename H = std::hash<K>,
         typename C = std::equal_to<K>,
         typename A = std::allocator<K>>
using UnorderedMultimap = std::unordered_multimap<K, H, C, A>;

/***************************************************************************/
/*                                                                         */
/***************************************************************************/

