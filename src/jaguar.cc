


#include <curl/curl.h>

#include "jaguar.hh"

#ifdef ENABLE_DEVEL
	#include <iostream>
#endif


namespace jaguar
{




namespace sampler
{

	Sampler::Config::Config() : response(NULL),display(false)
	{

	}
	Sampler::Sampler(const Sampler::Config& c) : config(&c)
	{

	}




	
	Http::Config::Config() : type(Http::Type::none)
	{

	}
	Http::Http(const Http::Config& c) : Sampler(c)
	{

	}

	size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
	{
	   return size * nmemb;
	}
	bool Http::run() const
	{
#ifdef ENABLE_DEVEL
				std::cout << "Test : ---" << config->name << "---\n";
#endif
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
			if(static_cast<const Http::Config*>(config)->server.empty()) return false;
			std::string url = static_cast<const Http::Config*>(config)->server;
			if(not static_cast<const Http::Config*>(config)->path.empty()) url += static_cast<const Http::Config*>(config)->path;	
#ifdef ENABLE_DEVEL
			std::cout << "url : " << url << "\n";
#endif
			
    		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
			//curl_easy_setopt(curl, CURLOPT_REDIR_PROTOCOLS, CURLPROTO_HTTP|CURLPROTO_HTTPS);
			 
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
			std::string params;
			if(static_cast<const Http::Config*>(config)->type == Http::Type::post and static_cast<const Http::Config*>(config)->params.size() > 0)
			{
				for(unsigned int i = 0; i < static_cast<const Http::Config*>(config)->params.size() - 1; i++)
				{
					params += static_cast<const Http::Config*>(config)->params[i].name + "=" + static_cast<const Http::Config*>(config)->params[i].value + "&";
				}
				params += static_cast<const Http::Config*>(config)->params.back().name + "=" + static_cast<const Http::Config*>(config)->params.back().value;
#ifdef ENABLE_DEVEL
				std::cout << "params : '" << params << "'\n";
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
			long response_code;

			res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
      		if((res == CURLE_OK) && ((response_code / 100) != 3)) 
			{
				/* a redirect implies a 3xx response code */
				fprintf(stderr, "Not a redirect.\n");
      		}
      		else 
			{
		    	res = curl_easy_getinfo(curl, CURLINFO_REDIRECT_URL, &redirect);	 
		    	if((res == CURLE_OK) && redirect) 
				{
		      		printf("Redirected to: %s\n", redirect);
		    	}
			}
#endif
			
    		/* always cleanup */
    		curl_easy_cleanup(curl);
  		}
  		curl_global_cleanup();

#ifdef ENABLE_DEVEL
				std::cout << "----------------\n";
#endif
		return true;
	}
}


}