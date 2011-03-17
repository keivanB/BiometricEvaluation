/*
 * This software was developed at the National Institute of Standards and
 * Technology (NIST) by employees of the Federal Government in the course
 * of their official duties. Pursuant to title 17 Section 105 of the
 * United States Code, this software is not subject to copyright protection
 * and is in the public domain. NIST assumes no responsibility whatsoever for
 * its use by other parties, and makes no guarantees, expressed or implied,
 * about its quality, reliability, or any other characteristic.
 */

#include <libgen.h>
#include <openssl/evp.h>

#include <iomanip>
#include <sstream>

#include <be_utility.h>

string
BiometricEvaluation::Utility::digest(
    const void *buffer,
    const size_t buffer_size,
    const string &digest)
    throw (Error::StrategyError)
{
	/* This need only be called once per executable */
	static bool digests_loaded = false;
	if (!digests_loaded) {
		OpenSSL_add_all_digests();
		digests_loaded = true;
	}

	/* Supports any digest type supported by OpenSSL (MD5, SHA1, ...) */
	const EVP_MD *md;
	md = EVP_get_digestbyname(digest.c_str());
	if (!md)
		throw Error::StrategyError("Unknown message digest: " + digest);

	EVP_MD_CTX mdctx;
	EVP_MD_CTX_init(&mdctx);

	EVP_DigestInit_ex(&mdctx, md, NULL);
	EVP_DigestUpdate(&mdctx, buffer, buffer_size);

	unsigned char md_value[EVP_MAX_MD_SIZE];
	unsigned int md_size;
	EVP_DigestFinal_ex(&mdctx, md_value, &md_size);

	/*
	 * While the EVP_MD_CTX may be safely reused, we have no way of knowing
	 * when an app is finished with it, forcing us to free the structure 
	 * every time.
	 */
	EVP_MD_CTX_cleanup(&mdctx);

	stringstream ret;
	for (int i = 0; i < md_size; i++)
		ret << hex << setw(2) << setfill('0') << (int)md_value[i];

	return ret.str();
}

