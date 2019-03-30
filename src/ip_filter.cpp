#include <regex>
#include <iostream>
#include <algorithm>
#include <charconv>
#include <string>
#include <cassert>

#include "ip_filter.h"

namespace roro_lib
{
      std::regex reg_exp(R"((\d+)\.(\d+)\.(\d+)\.(\d+)\t\w+\t\w+)", std::regex_constants::icase);

      std::optional<ip_address_type> get_ip_address_from_string(const std::string& line)
      {
            std::smatch match_str;
            std::regex_match(line, match_str, reg_exp);

            if (match_str.size() == 5)
            {
                  ip_address_type ip_addr = { 0 };
                  for (size_t i = 0; i < 4; ++i)
                  {
                        std::string s_octet = match_str.str(i + 1);
                        std::from_chars(s_octet.data(), s_octet.data() + s_octet.size(), ip_addr[i]);
                  }
                  return ip_addr;
            }
            return {};
      }


      ip_pool_type get_ip_pool_from_stdin()
      {
            ip_pool_type ip_pool;

            for (std::string line; getline(std::cin, line);)
            {
                  auto ip_addr = get_ip_address_from_string(line);

                  if (ip_addr.has_value())
                        ip_pool.push_back(ip_addr.value());
            }

            return ip_pool;
      }

      // clang-format off
      void sort_ip_pool_inverse_lex(ip_pool_type& ip_pool)
      {
            const auto cmp_str = [](const auto& a, const auto& b)
                                    {
                                          return a > b;
                                    };
            const auto sort_pred = [&](const auto& ip_addr1, const auto& ip_addr2)
                                    {
                                          return std::lexicographical_compare(ip_addr1.cbegin(), ip_addr1.cend(),
                                                                        ip_addr2.cbegin(), ip_addr2.cend(), cmp_str);
                                    };

            std::sort(ip_pool.begin(), ip_pool.end(), sort_pred);
      }
      // clang-format on

      void print_ip_pool(const ip_pool_type& ip_pool)
      {
            for (const auto& ip_addr : ip_pool)
            {
                  std::cout << +ip_addr[0] << "."
                            << +ip_addr[1] << "."
                            << +ip_addr[2] << "."
                            << +ip_addr[3] << "\n";
            }
      }

      ip_pool_type filter(const ip_pool_type& ip_pool, pred_type pred)
      {
            assert(pred != nullptr);

            ip_pool_type new_ip_pool;

            for (const auto& ip_addr : ip_pool)
            {
                  if (pred(ip_addr))
                        new_ip_pool.push_back(ip_addr);
            }

            return new_ip_pool;
      }
}
