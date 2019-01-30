#include <regex>
#include <iostream>
#include <algorithm>
#include "ip_filter.h"

std::regex reg_exp(R"((\d+)\.(\d+)\.(\d+)\.(\d+)\t\w+\t\w+)", std::regex_constants::icase);

ip_address_type get_ip_address_from_string(const std::string& line)
{
      std::smatch match_str;
      std::regex_match(line, match_str, reg_exp);

      ip_address_type ip_addr;

      for (size_t i = 1; i < match_str.size(); ++i)
      {
            ip_addr.push_back(match_str.str(i));
      }

      return ip_addr;
}


ip_pool_type get_ip_pool_from_stdin()
{
      ip_pool_type ip_pool;

      for (std::string line; getline(std::cin, line);)
      {
            ip_address_type ip_addr = get_ip_address_from_string(line);

            if (!ip_addr.empty())
                  ip_pool.push_back(ip_addr);
      }

      return ip_pool;
}

// clang-format off
void sort_ip_pool_inverse_lex(ip_pool_type& ip_pool)
{
      auto cmp_str = [](const auto& a, const auto& b)
                     {
                           return (a.size() > b.size()) ? true : (a.size() == b.size()) ? a > b : false;
                     };

      auto sort_pred = [&](const auto& ip_addr1, const auto& ip_addr2)
                       {
                             return lexicographical_compare(ip_addr1.cbegin(), ip_addr1.cend(),
                                                            ip_addr2.cbegin(), ip_addr2.cend(), cmp_str);
                       };

      std::sort(ip_pool.begin(), ip_pool.end(), sort_pred);
}
// clang-format on

void print_ip_pool(const ip_pool_type& ip_pool)
{
      for (const auto& ip_addr : ip_pool)
      {
            std::cout << ip_addr[0] << ":"
                      << ip_addr[1] << ":"
                      << ip_addr[2] << ":"
                      << ip_addr[3] << "\n";
      }
}

ip_pool_type filter(const ip_pool_type& ip_pool, pred_type pred)
{
      ip_pool_type new_ip_pool;

      for (const auto& ip_addr : ip_pool)
      {
            if (pred(ip_addr))
                  new_ip_pool.push_back(ip_addr);
      }

      return new_ip_pool;
}
