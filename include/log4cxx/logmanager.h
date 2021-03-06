/***************************************************************************
                          logmanager.h  -  class LogManager
                             -------------------
    begin                : jeu avr 17 2003
    copyright            : (C) 2003 by Michael CATANZARITI
    email                : mcatan@free.fr
 ***************************************************************************/

/***************************************************************************
 * Copyright (C) The Apache Software Foundation. All rights reserved.      *
 *                                                                         *
 * This software is published under the terms of the Apache Software       *
 * License version 1.1, a copy of which has been included with this        *
 * distribution in the LICENSE.txt file.                                   *
 ***************************************************************************/

#ifndef _LOG4CXX_LOG_MANAGER_H
#define _LOG4CXX_LOG_MANAGER_H

#include <log4cxx/helpers/tchar.h>
#include <vector>
#include <log4cxx/spi/repositoryselector.h>

namespace log4cxx
{
    class Logger;
    typedef helpers::ObjectPtr<Logger> LoggerPtr;
    typedef std::vector<LoggerPtr> LoggerList;

    namespace spi
    {
		class LoggerFactory;
		typedef helpers::ObjectPtr<LoggerFactory> LoggerFactoryPtr;
    };
    
    /**
    * Use the <code>LogManager</code> class to retreive Logger
    * instances or to operate on the current 
    * LoggerRepository. When the <code>LogManager</code> class is loaded
    * into memory the default initialization procedure is inititated.
	*/
    class LogManager
    {
    private:
        static void * guard;
        static spi::RepositorySelectorPtr repositorySelector;
 
    public:
        /**
        Sets <code>LoggerFactory</code> but only if the correct
        <em>guard</em> is passed as parameter.

        <p>Initally the guard is null.  If the guard is
        <code>null</code>, then invoking this method sets the logger
        factory and the guard. Following invocations will throw a {@link
        helpers::IllegalArgumentException IllegalArgumentException},
		unless the previously set <code>guard</code> is passed as the second
		parameter.

        <p>This allows a high-level component to set the {@link
        spi::RepositorySelector RepositorySelector} used by the 
		<code>LogManager</code>.
		*/

        static void setRepositorySelector(spi::RepositorySelectorPtr selector,
			void * guard);

        static spi::LoggerRepositoryPtr getLoggerRepository();

        /**
        Retrieve the appropriate root logger.
        */
        static LoggerPtr getRootLogger();

        /**
        Retrieve the appropriate Logger instance.
        */
        static LoggerPtr getLogger(const tstring& name);

        /**
        Retrieve the appropriate Logger instance.
        */
        static LoggerPtr getLogger(const tstring& name,
			spi::LoggerFactoryPtr factory);

        static LoggerPtr exists(const tstring& name);

        static LoggerList getCurrentLoggers();

        static void shutdown();

        static void resetConfiguration();
    }; // class LogManager
}; // namespace log4cxx

#endif //_LOG4CXX_LOG_MANAGER_H
