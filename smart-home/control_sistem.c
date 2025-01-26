#include <curl/curl.h>

#define ARDUINOIP "http://192.168.1.34"

// Функция для отправки HTTP-запроса и получения ответа
size_t WriteCallback(void *contents, size_t size, size_t     nmemb, void *userp) {
    ((char *)userp)[size * nmemb] = '\0';
    strncat(userp, contents, size * nmemb);
    return size * nmemb;
}

char* send_http_request(const char *url) {
    CURL *curl;
    CURLcode res;
    char *respone = malloc(1024);
    memset(respone, 0, 1024);

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        url_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Wr    iteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, respon    se);
        res = curl_easy_perform(curl);
  
        if(res != CURLE_OK) {
            fprintf(stderr, "[smh] curl_easy_perform() f    ailed: %s\n", curl_easy_strerror(res));
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            free(response);
            return NULL;
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return response;
}
