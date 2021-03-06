#include "test_runner.h"
#include "booking.h"
#include "profile.h"
#include <random>

void Test1(){
  HotelManager booker;
  ASSERT_EQUAL(booker.Clients("M"), 0);
  ASSERT_EQUAL(booker.Rooms("M"), 0);
  booker.Book(10, "F", 1,2);
  booker.Book(10, "M", 1,1);
  booker.Book(86409, "F", 2,1);
  ASSERT_EQUAL(booker.Clients("F"), 2);
  ASSERT_EQUAL(booker.Rooms("F"), 3);
  ASSERT_EQUAL(booker.Clients("M"), 1);
  booker.Book(86410, "M", 2,10);
  ASSERT_EQUAL(booker.Rooms("F"), 1);
  ASSERT_EQUAL(booker.Rooms("M"), 10);
 // -------------------------------
  booker.Book(86410 * 3, "M", 2, 8);
  ASSERT_EQUAL(booker.Rooms("M"), 8);

  booker.Book(86410 * 3, "M", 1, 8);
  ASSERT_EQUAL(booker.Rooms("M"), 16);

  booker.Book(86410 * 2 + 1, "M", 1, 1);
  ASSERT_EQUAL(booker.Rooms("M"), 17);
  //---------------------------------
  booker.Book(86410 * 3, "F", 2, 8);
  ASSERT_EQUAL(booker.Rooms("F"), 8);

  booker.Book(86410 * 3, "F", 1, 8);
  ASSERT_EQUAL(booker.Rooms("F"), 16);

  booker.Book(86410 * 2 + 1, "F", 1, 1);
  ASSERT_EQUAL(booker.Rooms("F"), 17);
}

void Test2(){
  HotelManager booker;
  booker.Book(1, "a", 100, 1);
  booker.Book(1, "a", 10, 2);
  ASSERT_EQUAL(booker.Rooms("a"), 3);
  ASSERT_EQUAL(booker.Clients("a"), 2);
  booker.Book(1, "b", 100, 1);
  booker.Book(1, "b", 10, 2);
  ASSERT_EQUAL(booker.Rooms("b"), 3);
  ASSERT_EQUAL(booker.Clients("b"), 2);
  HotelManager booker2;
  ASSERT_EQUAL(booker2.Rooms("a"), 0);
  ASSERT_EQUAL(booker2.Clients("a"), 0);
  ASSERT_EQUAL(booker2.Rooms("b"), 0);
  ASSERT_EQUAL(booker2.Clients("b"), 0);
  booker2.Book(10,"xxx", 777, 3);
  booker2.Book(11, "xxx", 777, 4);
  ASSERT_EQUAL(booker2.Rooms("xxx"), 7);
  ASSERT_EQUAL(booker2.Clients("xxx"), 1);
  HotelManager booker3;
  for(int i = 0; i <  86400 * 10; i++){
    booker3.Book(i, "m", i, 1);
  }
  ASSERT_EQUAL(booker3.Rooms("m"), 86400);
  ASSERT_EQUAL(booker3.Clients("m"), 86400);
  HotelManager booker4;
  for(int i = 0; i < 86400 * 10; i++){
    booker4.Book(i, "a", i, 1);
    booker4.Book(i, "a", i, 1);
  }
  ASSERT_EQUAL(booker4.Rooms("a"), 172'800);
  ASSERT_EQUAL(booker4.Clients("a"), 86'400);
}

void Test3() {
    HotelManager manager;

    // Test empty bookings
    ASSERT_EQUAL(manager.Clients("mariott"), 0);
    ASSERT_EQUAL(manager.Rooms("mariott"), 0);

    manager.Book(0, "mariott", 1, 10);
    manager.Book(0, "mariott", 2, 1);
    manager.Book(0, "mariott", 3, 1);
    manager.Book(0, "mariott", 4, 1);
    manager.Book(0, "hilton", 1, 1);
    manager.Book(1, "hilton", 2, 1);

    // Test correctness
    ASSERT_EQUAL(manager.Clients("mariott"), 4);
    ASSERT_EQUAL(manager.Rooms("mariott"), 13);
    ASSERT_EQUAL(manager.Clients("hilton"), 2);
    ASSERT_EQUAL(manager.Rooms("hilton"), 2);

    // Test event past 1 day resets statics
    manager.Book(86400, "mariott", 1, 1);
    ASSERT_EQUAL(manager.Clients("mariott"), 1);
    ASSERT_EQUAL(manager.Rooms("mariott"), 1);
    ASSERT_EQUAL(manager.Clients("hilton"), 1);
    ASSERT_EQUAL(manager.Rooms("hilton"), 1);

    // Test no clients and room for the last day
    manager.Book(86401, "mariott", 5, 1);
    ASSERT_EQUAL(manager.Clients("mariott"), 2);
    ASSERT_EQUAL(manager.Rooms("mariott"), 2);
    ASSERT_EQUAL(manager.Clients("hilton"), 0);
    ASSERT_EQUAL(manager.Rooms("hilton"), 0);
}

void Test4(){
  HotelManager booker;
  for(uint i = 0; i < 10000; i++)
    booker.Book(1,"m", 777, i);
  ASSERT_EQUAL(booker.Rooms("m"), 49'995'000);
  ASSERT_EQUAL(booker.Clients("m"), 1);
  for(uint i = 0; i < 10000; i++)
    booker.Book(86401,"m", i, 1);
  ASSERT_EQUAL(booker.Rooms("m"), 10000);
  ASSERT_EQUAL(booker.Clients("m"), 10000);
}

void Test5(){
  HotelManager booker;
  int j = 0;
  int64_t i_max = 80000;
  for(int64_t i = 0; i < i_max; i++){
    booker.Book(-1'000'000'000'000'000'000 + i, "a", i, j + 1);
    j++;
  }
  long result  = long((double(i_max + 1) / 2) * i_max);
  ASSERT_EQUAL(booker.Rooms("a"), result);
  ASSERT_EQUAL(booker.Clients("a"), i_max);
}

void TimeTest(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  size_t Q = 100'000;
  int64_t t1 = -1000'000'000'000'000'000;
  int64_t t2 = 1000'000'000'000'000'000;

  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<int64_t> random_time(t1, t2);
  std::uniform_int_distribution<ulong> random_id(1, 1000'000'000);
  std::uniform_int_distribution<ulong> random_room(1, 1000);

  std::uniform_int_distribution<size_t> random_query_index(0, Q - 1);

  vector<int64_t> v_time;
  vector<string> v_hotel = {"a", "abcdye", "jhbdsfvkb", "dnlkenrkj", "a","b",
                           "b", "kjnfvjnl", "jn;kelr", "a", "cccc", "xxxx", "csc", "xxxx"};
  std::uniform_int_distribution<size_t> random_query_index_hotel(0, v_hotel.size() - 1);
  vector<ulong> v_id;
  vector<ulong> v_room;
  vector<ulong> v_index_hotel;
  vector<size_t> v_query_index;

  for(size_t i = 0; i < Q; i++){
    v_time.push_back(random_time(gen));
    v_id.push_back(random_id(gen));
    v_room.push_back(random_room(gen));
    v_index_hotel.push_back(random_query_index_hotel(gen));
    v_query_index.push_back(random_query_index(gen));
  }
  sort(v_time.begin(), v_time.end());
  for(auto& i: v_time)
    cout << i << " ";
  cout << endl;
//  cout <<" v_time.size()=" << v_time.size() << endl;
//  cout <<" v_id.size()=" << v_id.size() << endl;
//  cout <<" v_hotel.size()=" << v_hotel.size() << endl;
//  cout <<" v_room.size()=" << v_room.size() << endl;
//  cout <<" v_index_hotel.size()=" << v_index_hotel.size() << endl;

  LOG_DURATION("Booker");
  HotelManager booker;
  for(size_t i = 0; i < double(2 * Q) / 3; ++i){
   booker.Book(v_time.at(v_query_index.at(i)), v_hotel.at(v_index_hotel.at(i)),
               v_id.at(v_query_index.at(i)), v_room.at(v_query_index.at(i)));
  }
  for(size_t i = 0; i < double(Q)/ 6; ++i){
      cout << booker.Rooms(v_hotel.at(v_index_hotel.at(i))) << " ";
  }
  cout << "\n";
  for(size_t i = 0; i < double(Q) / 6; ++i){
      cout << booker.Clients(v_hotel.at(v_index_hotel.at(i))) << " ";
  }
  cout << "\n";
}

void Test6() {
    HotelManager manager;

    // Test empty bookings
    ASSERT_EQUAL(manager.Clients("mariott"), 0);
    ASSERT_EQUAL(manager.Rooms("mariott"), 0);

    manager.Book(0, "mariott", 1, 10);
    manager.Book(0, "mariott", 2, 1);
    manager.Book(0, "mariott", 3, 1);
    manager.Book(0, "mariott", 4, 1);
    manager.Book(0, "hilton", 1, 1);
    manager.Book(1, "hilton", 2, 1);

    // Test correctness
    ASSERT_EQUAL(manager.Clients("mariott"), 4);
    ASSERT_EQUAL(manager.Rooms("mariott"), 13);
    ASSERT_EQUAL(manager.Clients("hilton"), 2);
    ASSERT_EQUAL(manager.Rooms("hilton"), 2);

    // Test event past 1 day resets statics
    manager.Book(86400, "mariott", 1, 1);
    ASSERT_EQUAL(manager.Clients("mariott"), 1);
    ASSERT_EQUAL(manager.Rooms("mariott"), 1);
    ASSERT_EQUAL(manager.Clients("hilton"), 1);
    ASSERT_EQUAL(manager.Rooms("hilton"), 1);

    // Test no clients and room for the last day
    manager.Book(86401, "mariott", 5, 1);
    ASSERT_EQUAL(manager.Clients("mariott"), 2);
    ASSERT_EQUAL(manager.Rooms("mariott"), 2);
    ASSERT_EQUAL(manager.Clients("hilton"), 0);
    ASSERT_EQUAL(manager.Rooms("hilton"), 0);

    manager.Book(999999999999999000, "hilton", 3, 5);
    manager.Book(999999999999999900, "hilton", 4, 3);
    manager.Book(999999999999999990, "mariot", 6, 1);
    manager.Book(999999999999999999, "mariot", 6, 2);
    ASSERT_EQUAL(manager.Rooms("hilton"), 8);
    ASSERT_EQUAL(manager.Clients("hilton"), 2);
    ASSERT_EQUAL(manager.Rooms("mariot"), 3);
    ASSERT_EQUAL(manager.Clients("mariot"), 1);
}








