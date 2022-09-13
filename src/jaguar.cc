


#include <curl/curl.h>

#include "jaguar.hh"

#ifdef ENABLE_DEVEL
	#include <iostream>
#endif


namespace jaguar
{




namespace sampler
{

	Sampler::Config::Config() : type(Sampler::Type::none),response(NULL),display(false)
	{

	}
	Sampler::Sampler(const Sampler::Config& c) : config(&c)
	{

	}




	
	Http::Http(const Sampler::Config& c) : Sampler(c)
	{

	}

	size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
	{
	   return size * nmemb;
	}
	bool Http::run() const
	{
		CURL *curl;
  		CURLcode res;
 
  		/* In windows, this will init the winsock stuff */
  		curl_global_init(CURL_GLOBAL_ALL);
 
  		/* get a curl handle */
  		curl = curl_easy_init();
  		if(curl) 
		{
    		/* First set the URL that is about to receive our POST. This URL can
       		just as well be a https:// URL if that is what should receive the
       		data. */
			if(config->server.empty()) return false;
			std::string url = config->server;
			if(not config->path.empty()) url += config->path;	
#ifdef ENABLE_DEVEL
			std::cout << "url : " << url << "\n";
#endif
    		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			if(config->response)
			{				
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, config->response);
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
			}
			else if(not config->display)
			{
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
			}
    		/* Now specify the POST data */
			if(config->type != Sampler::Type::none and config->params.size() > 0)
			{
				std::string params;
				for(unsigned int i = 0; i < config->params.size() - 1; i++)
				{
					params += config->params[i].name + "=" + config->params[i].value + "&";
				}
				params += config->params.back().name + "=" + config->params.back().value;
#ifdef ENABLE_DEVEL
				std::cout << "params : " << params << "\n";
#endif
    			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params.c_str());
			}  
 
    		/* Perform the request, res will get the return code */
    		res = curl_easy_perform(curl);
    		/* Check for errors */
    		//if(res != CURLE_OK) fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
			//std::cout << "HTTP : " << res << "\n";
			if(res != CURLE_OK) return false;
#ifdef ENABLE_DEVEL
			char *redirect = NULL;
    		curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &redirect);
    		if(redirect) printf("Redirect to: %s\n", redirect);
#endif
			
    		/* always cleanup */
    		curl_easy_cleanup(curl);
  		}
  		curl_global_cleanup();

		return true;
	}
}


}