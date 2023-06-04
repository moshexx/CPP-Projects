#include <boost/thread.hpp>


namespace boost
{

  template <typename Mutex>
  class BOOST_THREAD_SCOPED_CAPABILITY lock_guard
  {
  private:
    Mutex& m;

  public:
    typedef Mutex mutex_type;
    BOOST_THREAD_NO_COPYABLE( lock_guard )

    explicit lock_guard(Mutex& m_) BOOST_THREAD_ACQUIRE(m_) :
      m(m_)
    {
      m.lock();
    }

    lock_guard(Mutex& m_, adopt_lock_t) BOOST_THREAD_REQUIRES(m_) :
      m(m_)
    {
#if ! defined BOOST_THREAD_PROVIDES_NESTED_LOCKS
      BOOST_ASSERT(is_locked_by_this_thread(m));
#endif
    }

#if ! defined BOOST_THREAD_NO_CXX11_HDR_INITIALIZER_LIST
    lock_guard(std::initializer_list<thread_detail::lockable_wrapper<Mutex> > l_) :
      m(*(const_cast<thread_detail::lockable_wrapper<Mutex>*>(l_.begin())->m))
    {
      m.lock();
    }

    lock_guard(std::initializer_list<thread_detail::lockable_adopt_wrapper<Mutex> > l_) :
      m(*(const_cast<thread_detail::lockable_adopt_wrapper<Mutex>*>(l_.begin())->m))
    {
#if ! defined BOOST_THREAD_PROVIDES_NESTED_LOCKS
      BOOST_ASSERT(is_locked_by_this_thread(m));
#endif
    }

#endif
    ~lock_guard() BOOST_THREAD_RELEASE()
    {
      m.unlock();
    }
  };