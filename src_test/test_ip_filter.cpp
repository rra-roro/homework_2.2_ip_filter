#include <string>
#include "gtest/gtest.h"
#include "gtest/gtest_prod.h"

#include "lib.h"

#define _TEST 1

#include "ip_filter.h"
#include "../src/main.cpp"

TEST(version, test1)
{
      ASSERT_TRUE(version() > 0);
}

TEST(ip_address, get_from_string)
{
      std::vector<std::string> ip_strings = {
            "113.162.145.156\t111\t0",
            "157.39.22.224\t5\t6",
            "79.180.73.190\t2\t1",
            " 79. 180. 73 . 190  2  1",
            "79,180,73,190\t2\t1",
            "179.210.145.4\t22\t0",
            "Hello World",
            "\n",
            "ip:179.210.145.4\t22\t0",
            "219.102.120.135\t486\t\t0",
            "67.232.81.208 1 0"
      };

      ip_pool_type ip_pool;

      for (std::string& line : ip_strings)
      {
            auto ip_addr = get_ip_address_from_string(line);

            if (ip_addr.has_value())
                  ip_pool.push_back(ip_addr.value());
      }

      ASSERT_TRUE(ip_pool.size() == 4);
      ASSERT_TRUE(ip_pool[0] == (ip_address_type{ 113, 162, 145, 156 }));
      ASSERT_TRUE(ip_pool[1] == (ip_address_type{ 157, 39, 22, 224 }));
      ASSERT_TRUE(ip_pool[2] == (ip_address_type{ 79, 180, 73, 190 }));
      ASSERT_TRUE(ip_pool[3] == (ip_address_type{ 179, 210, 145, 4 }));
}



TEST(sort, inverse_lexicographical)
{
      ip_pool_type ip_pool = {
            { 186, 46, 222, 194 },
            { 5, 189, 203, 46 },
            { 46, 251, 197, 23 },
            { 186, 204, 34, 46 },
            { 46, 49, 43, 85 },
            { 185, 46, 85, 78 },
            { 185, 46, 87, 231 },
            { 39, 46, 86, 85 },
            { 68, 46, 218, 208 },
            { 46, 223, 254, 56 }
      };

      sort_ip_pool_inverse_lex(ip_pool);

      ASSERT_TRUE(ip_pool.size() == 10);
      ASSERT_TRUE(ip_pool[0] == (ip_address_type{ 186, 204, 34, 46 }));
      ASSERT_TRUE(ip_pool[1] == (ip_address_type{ 186, 46, 222, 194 }));
      ASSERT_TRUE(ip_pool[2] == (ip_address_type{ 185, 46, 87, 231 }));
      ASSERT_TRUE(ip_pool[3] == (ip_address_type{ 185, 46, 85, 78 }));
      ASSERT_TRUE(ip_pool[4] == (ip_address_type{ 68, 46, 218, 208 }));
      ASSERT_TRUE(ip_pool[5] == (ip_address_type{ 46, 251, 197, 23 }));
      ASSERT_TRUE(ip_pool[6] == (ip_address_type{ 46, 223, 254, 56 }));
      ASSERT_TRUE(ip_pool[7] == (ip_address_type{ 46, 49, 43, 85 }));
      ASSERT_TRUE(ip_pool[8] == (ip_address_type{ 39, 46, 86, 85 }));
      ASSERT_TRUE(ip_pool[9] == (ip_address_type{ 5, 189, 203, 46 }));
}

TEST(filter, pred_octet1_eq_1)
{
      ip_pool_type ip_pool = {
            { 12, 13, 14, 15 },
            { 1, 13, 14, 15 },
            { 22, 13, 14, 15 }
      };

      ip_pool_type new_ip_pool = filter(ip_pool, pred_octet1_eq_1);

      ASSERT_TRUE(new_ip_pool.size() == 1);
      ASSERT_TRUE(new_ip_pool[0] == (ip_address_type{ 1, 13, 14, 15 }));
}

TEST(filter, pred_octet1_eq_46_and_octet2_eq_70)
{
      ip_pool_type ip_pool = {
            { 46, 13, 14, 15 },
            { 1, 13, 14, 15 },
            { 46, 70, 14, 15 },
            { 22, 70, 14, 15 }
      };

      ip_pool_type new_ip_pool = filter(ip_pool, pred_octet1_eq_46_and_octet2_eq_70);

      ASSERT_TRUE(new_ip_pool.size() == 1);
      ASSERT_TRUE(new_ip_pool[0] == (ip_address_type{ 46, 70, 14, 15 }));
}


TEST(filter, pred_any_octet_eq_46)
{
      ip_pool_type ip_pool = {
            { 46, 13, 14, 15 },
            { 1, 13, 14, 15 },
            { 222, 70, 46, 15 },
            { 22, 70, 14, 15 },
            { 222, 46, 46, 15 },
            { 222, 70, 11, 46 }
      };

      ip_pool_type new_ip_pool = filter(ip_pool, pred_any_octet_eq_46);

      ASSERT_TRUE(new_ip_pool.size() == 4);
      ASSERT_TRUE(new_ip_pool[0] == (ip_address_type{ 46, 13, 14, 15 }));
      ASSERT_TRUE(new_ip_pool[1] == (ip_address_type{ 222, 70, 46, 15 }));
      ASSERT_TRUE(new_ip_pool[2] == (ip_address_type{ 222, 46, 46, 15 }));
      ASSERT_TRUE(new_ip_pool[3] == (ip_address_type{ 222, 70, 11, 46 }));
}
