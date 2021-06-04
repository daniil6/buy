#include <curl/curl.h>
#include <string>
#include <thread>

#include <windows.h>

// BOOL Beep()
// {
//     DWORD dwFreq;     // частота звука
//     DWORD dwDuration; // длительность звучания
// }

int g_count = 0;

size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data)
{
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

void WriteFile(std::string buffer, int count)
{
    FILE* file;

    std::string name = std::to_string(count).append(".html");

    file = fopen(name.data(), "w");

    fprintf(file, buffer.data());

    fclose(file);
}

int main(int argc, char** argv)
{
    int count = 0;

    std::string response_string;
    std::string readBuffer;
    std::string headerData;

    // std::string string_url = "https://www.mvideo.ru/products/videokarta-msi-geforce-gt-710-2gb-silent-lp-30030949";

    // std::string string_url = "https://www.dns-shop.ru/product/0d68b886a66a2ff1/"
    //                          "videokarta-palit-geforce-rtx-3080-ti-gamerock-ned308t019kb-1020g/";

    std::string string_url =
        //    "https://www.dns-shop.ru/product/e2f76961adfe2ff1/videokarta-kfa2-geforce-rtx-3080-ti-sg-38iom5md99dk/";

        "https://www.dns-shop.ru/product/fbed7b887b263332/"
        "videokarta-gigabyte-geforce-rtx-3080-gaming-oc-waterforce-wb-gv-n3080gamingoc-wb-10gd/";

    // "www.google.com";

    std::string user_agent = "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US) AppleWebKit/525.13 (KHTML, like Gecko) "
                             "Chrome/0.A.B.C Safari/525.13";

    // CURLcode code;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL* curl = curl_easy_init();
    if(curl != nullptr) {

        while(1) {

            curl_easy_setopt(curl, CURLOPT_URL, string_url.c_str());

            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 0);
            curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 0);

            curl_easy_setopt(curl, CURLOPT_USERAGENT, user_agent.c_str());

            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headerData);

            curl_easy_perform(curl);

            WriteFile(readBuffer, count++);

            printf("succes: get");

            /*int position = 0;

            if((position = readBuffer.find("price"), position) != -1) {

                char ch = 0;
                while((ch = readBuffer.at(position++)) != ',' && position < 10)
                    std::cout << ch;
                std::cout << std::endl;
            }

            if((position = readBuffer.find("Купить")) != -1) {
                std::cout << "Купить" << std::endl;
            }*/

            std::this_thread::sleep_for(std::chrono::seconds(10));
        }

        curl_easy_cleanup(curl);
        curl_global_cleanup();
    }

    // Beep(500, 1000);

    getchar();
    return 0;
}

/*

curl_easy_setopt(curl, CURLOPT_URL, string_url.c_str());

curl_easy_setopt(curl, CURLOPT_TIMEOUT, 0);
// curl_easy_setopt(curl, CURLOPT_RETURNTRANSFER, 1);
curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 0);

// curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
// curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
// curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

// curl_easy_setopt(curl, CURLOPT_HEADER, true);

// curl_easy_setopt(curl, CURLOPT_RETURNTRANSFER, true);
curl_easy_setopt(curl, CURLOPT_USERAGENT, user_agent.c_str());
curl_easy_setopt(curl, CURLOPT_COOKIE,
    "NID=67="
    "pdjIQN5CUKVn0bRgAlqitBk7WHVivLsbLcr7QOWMn35Pq03N1WMy6kxYBPORtaQUPQrfMK4Yo0vVz8tH97ejX3q7P2lNuPjTOhwqaI2bXC"
    "gPGSDKkdFoiYIqXubR0cTJ48hIAaKQqiQi_lpoe6edhMglvOO9ynw; "
    "PREF=ID=52aa671013493765:U=0cfb5c96530d04e3:FF=0:LD=en:TM=1370266105:LM=1370341612:GM=1:S="
    "Kcc6KUnZwWfy3cOl; OTZ=1800625_34_34__34_; S=talkgadget=38GaRzFbruDPtFjrghEtRw; "
    "SID=DQAAALoAAADHyIbtG3J_u2hwNi4N6UQWgXlwOAQL58VRB_0xQYbDiL2HA5zvefboor5YVmHc8Zt5lcA0LCd2Riv4WsW53ZbNCv8Qu_"
    "THhIvtRgdEZfgk26LrKmObye1wU62jESQoNdbapFAfEH_IGHSIA0ZKsZrHiWLGVpujKyUvHHGsZc_"
    "XZm4Z4tb2bbYWWYAv02mw2njnf4jiKP2QTxnlnKFK77UvWn4FFcahe-XTk8Jlqblu66AlkTGMZpU0BDlYMValdnU; "
    "HSID=A6VT_ZJ0ZSm8NTdFf; SSID=A9_PWUXbZLazoEskE; APISID=RSS_BK5QSEmzBxlS/ApSt2fMy1g36vrYvk; "
    "SAPISID=ZIMOP9lJ_E8SLdkL/A32W20hPpwgd5Kg1J");

// curl_easy_setopt(curl, CURLOPT_AUTOREFERER, true);
// curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);
// curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 20);
// curl_easy_setopt(curl, CURLOPT_POST, true);
// curl_easy_setopt(curl, CURLOPT_POSTFIELDS, $fields_string);

curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);

curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headerData);

code = curl_easy_perform(curl);
curl_easy_cleanup(curl);
curl_global_cleanup();

*/