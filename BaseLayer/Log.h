//
//  Log.h
//  PipesAndFiltersFramework
//
//  Created by Antti Juustila on 21.10.2013.
//  Copyright (c) 2013 Antti Juustila. All rights reserved.
//

#ifndef __PipesAndFiltersFramework__Log__
#define __PipesAndFiltersFramework__Log__

#include <iostream>
#include <string>
#include <chrono>


namespace OHARBase {
	
	/** A class for logging data in the Nodes. Is implemented following
	 the Singleton design pattern. The output stream can be changed by setStream() but
	 is usually the console (std::cout).
	 @todo Reimplement stream writing and formatting using C++11 paremetrisized templates, to get rid of the pesky
    .c_str() calls when using the Log class.
	 @author Antti Juustila
	 */
	class Log {
	public:
		virtual ~Log();
		static Log & getInstance();
		void setStream(std::ostream & os);
		
		void entry(const std::string & tag, const char * format, ...);
		
	private:
		Log();
		Log(const Log &) = delete;
		Log & operator = (const Log&) = delete;
		
	private:

		/** The stream to log to. Can be changed during runtime. */
		std::ostream * stream;
		/** The buffer to use in generating the logged string. */
		char * buffer;
		/** The size of the log string buffer. */
		const int bufSize;
		/** Guard to access the entry to the logging. Needed because multiple threads
		 may try to log at the same time, garbling the output string. Only one thread at a
		 time may construct the log buffer and print the buffer to the stream. */
		std::mutex guard;
		/** For putting timestamps in the log output. */
		std::chrono::system_clock::time_point started;
	};
	
	
} //namespace

#endif /* defined(__PipesAndFiltersFramework__Log__) */