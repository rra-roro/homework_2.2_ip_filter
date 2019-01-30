#pragma once
#include <vector>
#include <string>

using ip_address_type = std::vector<std::string>;
using ip_pool_type = std::vector<ip_address_type>;
using pred_type = bool (*)(const ip_address_type& ip_addr);

ip_pool_type    get_ip_pool_from_stdin();
ip_address_type get_ip_address_from_string(const std::string& line);

void sort_ip_pool_inverse_lex(ip_pool_type& ip_pool);
void print_ip_pool(const ip_pool_type& ip_pool);

ip_pool_type filter(const ip_pool_type& ip_pool, pred_type pred);
