#include "booking.h"

void HotelManager::setGlobalTime(int64_t global_time)
{
  this->m_global_time = global_time;
}

int64_t HotelManager::getGlobalTime() const
{
  return this->m_global_time;
}

void HotelManager::RoomBooker(int64_t time, const string &hotel_name, room_count room_count){
  if(!(hotel_rooms.count(hotel_name) < 1)){
    queue<time_room>& client_queue = hotel_rooms.at(hotel_name);
    time_room& previous_in_queue = client_queue.back();
    auto pair = std::make_pair(time, previous_in_queue.second + room_count);
    client_queue.push(pair);
  } else {
    queue<time_room> first_room;
    auto pair = std::make_pair(time, room_count);
    first_room.push(pair);
    hotel_rooms[hotel_name] = first_room;
  }
}

void HotelManager::AdjustRooms(const string &hotel_name){
  queue<time_room>& client_queue = hotel_rooms.at(hotel_name);
  int64_t current_time = getGlobalTime();
  ulong col{0};
  int64_t poping_number = client_queue.front().first;
  while(!client_queue.empty() && (poping_number <= (current_time - TIME_WINDOW_SIZE))
        && (poping_number != current_time)){
    col = client_queue.front().second;
    client_queue.pop();
    poping_number = client_queue.front().first;
  }
  hotel_rooms.at(hotel_name).back().second -= col;
}

void HotelManager::ClientBooker(int64_t time, const string &hotel_name, client_id client_id){
  if(!(hotel_clients.count(hotel_name) < 1)){
    queue<time_client>& client_queue = hotel_clients.at(hotel_name);
    client_queue.push({time, client_id});

    map<HotelManager::client_id, size_t>& second_map = client_id_number.at(hotel_name);
    second_map[client_id] += 1;
  } else {
    map<HotelManager::client_id, size_t> first_map;
    first_map[client_id] = 1;
    client_id_number[hotel_name] = first_map;
    queue<time_client> first_client;
    first_client.push({time, client_id});
    hotel_clients[hotel_name] = first_client;
  }
}

void HotelManager::AdjustClients(const string &hotel_name){
  queue<time_client>& client_queue = hotel_clients.at(hotel_name);
  int64_t current_time = getGlobalTime();
  int64_t poping_time = client_queue.front().first;
  client_id oldest_client_id = client_queue.front().second;
  map<client_id, size_t>& client_time_stamp = client_id_number.at(hotel_name);

  while(!client_queue.empty() && (poping_time <= (current_time - TIME_WINDOW_SIZE))
        && (poping_time != current_time)){
    client_time_stamp[oldest_client_id] = client_time_stamp[oldest_client_id] - 1;
    if(client_time_stamp.at(oldest_client_id) < 1){
      client_time_stamp.erase(oldest_client_id);
    }
    client_queue.pop();
    poping_time = client_queue.front().first;
    oldest_client_id = client_queue.front().second;
  }
}
