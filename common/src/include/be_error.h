/*
 * This software was developed at the National Institute of Standards and
 * Technology (NIST) by employees of the Federal Government in the course
 * of their official duties. Pursuant to title 17 Section 105 of the
 * United States Code, this software is not subject to copyright protection
 * and is in the public domain. NIST assumes no responsibility whatsoever for
 * its use by other parties, and makes no guarantees, expressed or implied,
 * about its quality, reliability, or any other characteristic.
 */

#ifndef __BE_ERROR_UTILITY__
#define __BE_ERROR_UTILITY__

#include <string>

namespace BiometricEvaluation 
{
	/**
	 * @brief
	 * Exceptions, and other error handling.
	 * @details
	 * The Error package contains classes for exceptions, and functions
	 * used for error handling, including signals generated by a process.
	 */
	namespace Error
	{
		/**
		 * Convert the value of errno to a human-readable
		 * error messsage.
		 *
		 * @return
		 * 	The current error message specified by errno.
		 */
		std::string errorStr();
	}
}
#endif

