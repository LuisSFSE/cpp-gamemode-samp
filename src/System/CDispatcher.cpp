#include <System/CDispatcher.hpp>


void CDispatcher::Dispatch(Func_t &&func)
{
	boost::mutex::scoped_lock lock(m_QueueMtx);
	return m_Queue.push(std::move(func));
}

void CDispatcher::Process()
{
	boost::mutex::scoped_lock lock(m_QueueMtx);
	while (m_Queue.empty() == false)
	{
		m_Queue.front()();
		m_Queue.pop();
	}
}
