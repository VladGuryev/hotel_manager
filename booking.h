#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <queue>
#include <map>
#include <deque>
#include <set>
#include <algorithm>
#include <utility>
#include <iostream>
using namespace std;

//use PIMPL idiom
class HotelManager {
  typedef ulong room_count;
  typedef ulong client_id;
  typedef pair<int64_t, room_count> time_room;
  typedef pair<int64_t, client_id> time_client;
  int64_t m_global_time = 0;
  map<string, queue<time_room>> hotel_rooms;
  map<string, queue<time_client>> hotel_clients;
  map<string, map<client_id, size_t>> client_id_number;
  static const int TIME_WINDOW_SIZE = 86400;

  void setGlobalTime(int64_t m_global_time);
  int64_t getGlobalTime() const;

  void RoomBooker(int64_t time, const string& hotel_name, room_count room_count);
  void ClientBooker(int64_t time, const string& hotel_name,client_id client_id);
  void AdjustClients(const string& hotel_name);
  void AdjustRooms(const string& hotel_name);
public:
  void Book(int64_t time, const string& hotel_name, client_id client_id,
            room_count room_count){
    if(room_count != 0 || hotel_name != ""){
      setGlobalTime(time);
      RoomBooker(time, hotel_name, room_count);
      ClientBooker(time, hotel_name, client_id);
    }
  }

  ulong Rooms(const string& hotel_name){
    if(!(hotel_rooms.count(hotel_name) < 1)){
      AdjustRooms(hotel_name);
      return hotel_rooms.at(hotel_name).back().second;
    } else
      return 0;
  }

  ulong Clients(const string& hotel_name){
    if(!(client_id_number.count(hotel_name) < 1)){
      AdjustClients(hotel_name);
      return client_id_number.at(hotel_name).size();
    } else
      return 0;
  }
};
