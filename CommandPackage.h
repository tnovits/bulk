#pragma once

#include "ISubscriber.h"
#include <memory>


class CommandPackage
{
private:
    using SubscriberType = std::shared_ptr<ISubscriber>;
    using SubscribersListType = std::vector<SubscriberType>;
    using CommandListType = std::vector<std::string>;

public:
    CommandPackage() = delete;

    CommandPackage(size_t blockCommandCount)
    {
        m_BlockCommandCount = blockCommandCount;
        m_CommandList.reserve(blockCommandCount);
    }

    virtual ~CommandPackage() = default;

    void addCommand(std::string& command)
    {
        if( command == "{" )
        {
            if( !m_BlockStarted )
            {
                update();
                m_BlockStarted = true;
            }

            ++m_BlocksCount;
        }
        else if ( command ==  "}" )
        {
            if( m_BlockStarted && m_BlocksCount > 0 && --m_BlocksCount == 0)
            {
                m_BlockStarted = false;
                update();
            }
        }
        else
        {
            if(m_BlockTime == 0)
            {
                m_BlockTime = std::time(nullptr);
            }
            m_CommandList.push_back( command );

            if( !m_BlockStarted  && m_CommandList.size() == m_BlockCommandCount )
            {
                update();
            }
        }
    }

    void update()
    {
        if(!m_BlockStarted && m_CommandList.size() != 0)
        {
            for( const auto& subscriber: m_SubscribersList )
            {
                subscriber->update( m_BlockTime, m_CommandList );
            }

            m_CommandList.clear();
            m_BlockTime = 0;
        }
    }

    void addSubscriber(SubscriberType subscriber)
    {
        m_SubscribersList.push_back(subscriber);
    }

private:
    size_t m_BlockCommandCount = 0;
    SubscribersListType m_SubscribersList;
    CommandListType m_CommandList;
    bool m_BlockStarted = false;
    size_t m_BlocksCount = 0;
    std::time_t m_BlockTime = 0;
};
