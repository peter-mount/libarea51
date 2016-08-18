
#include <stdlib.h>
#include <curl/curl.h>
#include <area51/curl.h>
#include <area51/log.h>

/**
 * A simple http get request
 * @param url url to retrieve
 * @param buf charbuffer to accept content
 * @return 0 if successful, 1 on error or http code if not http 200
 */
int curl_get(char *url, CharBuffer *buf) {
    int ret = 1;

    CURL *curl = curl_pool_poll();
    if (curl) {
        curl_easy_reset(curl);

        curl_easy_setopt(curl, CURLOPT_URL, url);

        charbuffer_reset(buf);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, charbuffer_curl_write);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, buf);

        CURLcode res = curl_easy_perform(curl);

        long httpCode = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);

        if (res != CURLE_OK) {
            logconsole("Failed to submit %s %s\n", url, curl_easy_strerror(res));
        } else if (httpCode == 200) {
            ret = 0;
        } else {
            ret = httpCode;
            logconsole("Failed to submit %s %d\n", url, ret);
        }
    }
    curl_pool_offer(curl);

    return ret;
}
