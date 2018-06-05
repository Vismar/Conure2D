#pragma once

/**************************/
/*        LOGGING         */
/**************************/
/*!
 * \brief Simple log call.
 */
#define LOG(logLevel, message) Engine::GetLogSystem().AddEntry(logLevel, message)

#ifdef DEV_BUILD
 /*!
 * \brief Log call which will be build-in only for development builds.
 */
#define DEV_LOG(logLevel, message) Engine::GetLogSystem().AddEntry(logLevel, message)
#else
/*!
 * \brief Log call which will be build-in only for development builds.
 */
#define DEV_LOG(logLevel, message) do { } while (0);
#endif