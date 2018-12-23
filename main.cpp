#include <iostream>
#include <string>

#include "booking.h"
#include "test_runner.h"
#include "tests.cpp"
using namespace std;

int main()
{
  TestRunner tr;
  RUN_TEST(tr, Test1);
  RUN_TEST(tr, Test2);
  RUN_TEST(tr, Test3);
  RUN_TEST(tr, Test4);
  RUN_TEST(tr, Test5);
//  RUN_TEST(tr, TimeTest); // 202ms
  RUN_TEST(tr, Test6);

// ios::sync_with_stdio(false);
// cin.tie(nullptr);

  HotelManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;

    if (query_type == "BOOK") {
      int64_t time;
      cin >> time;
      string hotel_name;
      cin >> hotel_name;
      ulong client_id, room_count;
      cin >> client_id >> room_count;
      manager.Book(time, hotel_name, client_id, room_count);
    } else {
      string hotel_name;
      cin >> hotel_name;
      if (query_type == "CLIENTS") {
        cout << manager.Clients(hotel_name) << "\n";
      } else if (query_type == "ROOMS") {
        cout << manager.Rooms(hotel_name) << "\n";
      }
    }
  }
  return 0;
}
