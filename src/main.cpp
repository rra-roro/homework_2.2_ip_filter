#include <iostream>
#include "lib.h"
#include "CLParser.h"
#include "ip_filter.h"

using namespace std;
using namespace roro_lib;

void help()
{
      cout << R"(
 This tool gets ip_filter.tsv from stdin. It extracts IPs from them,
 then it sortes and filters IPs. The result will be sent to stdout

    ip_filter  [-version | -? ]
       Options:  
       -version    -get version of program
       -?          -about program (this info)

 Example to use (Linux):
    ip_filter.tsv | ip_filter

 Example to use (Windows):
    ip_filter < ip_filter.tsv)"
           << endl;
}

void version_ip_filter()
{
      cout << "Version ip_filter: " << version() << endl;
}

// clang-format off
static inline auto pred_octet1_eq_1 = [](const ip_address_type& ip_addr)
                                      {
                                            return ip_addr[0] == 1;
                                      };

static inline auto pred_octet1_eq_46_and_octet2_eq_70 = [](const ip_address_type& ip_addr)
                                                        {
                                                              return ip_addr[0] == 46 &&
                                                                     ip_addr[1] == 70;
                                                        };

static inline auto pred_any_octet_eq_46 = [](const ip_address_type& ip_addr)
                                          {
                                                return ip_addr[0] == 46 || ip_addr[1] == 46 ||
                                                       ip_addr[2] == 46 || ip_addr[3] == 46;
                                          };
// clang-format on

#ifndef _TEST

int main(int argc, char* argv[])
{
      try
      {
            ParserCommandLine PCL;
            PCL.AddFormatOfArg("?", no_argument, '?');
            PCL.AddFormatOfArg("help", no_argument, '?');
            PCL.AddFormatOfArg("version", no_argument, 'v');

            PCL.SetShowError(false);
            PCL.Parser(argc, argv);

            if (PCL.Option['?'])
            {
                  help();
                  return 0;
            }
            if (PCL.Option['v'])
            {
                  version_ip_filter();
                  return 0;
            }

            auto ip_pool = get_ip_pool_from_stdin();

            sort_ip_pool_inverse_lex(ip_pool);

            print_ip_pool(ip_pool);

            print_ip_pool(filter(ip_pool, pred_octet1_eq_1));
            print_ip_pool(filter(ip_pool, pred_octet1_eq_46_and_octet2_eq_70));
            print_ip_pool(filter(ip_pool, pred_any_octet_eq_46));

            return 0;
      }
      catch (const std::exception& ex)
      {
            cerr << "Error: " << ex.what() << endl;
            return EXIT_FAILURE;
      }
      catch (...)
      {
            cerr << "Error: unknown exception" << endl;
            return EXIT_FAILURE;
      }
}

#endif
