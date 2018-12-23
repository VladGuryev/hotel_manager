# hotel_manager
This repo contains the code for the programming issue of Yandex online course on the Coursera: https://www.coursera.org/learn/c-plus-plus-red/programming/8O9dd/sistiema-bronirovaniia-otieliei

The program handles the following events:

BOOK time hotel_name client_id room_count — book by client the client_id room_count at the hotel_name at the time point in time. Time is measured in seconds, counted from some point.
CLIENTS hotel_name - display the number of different customers who have booked hotel_name in the hotel for the last 24 hours. The more formally interesting time range is described as follows: let current_time be the time of the last BOOK event, then this query should take into account all events with current_time - 86400 <time ⩽ current_time, where 86400 is the number of seconds in a day. The last booking is taken into account, and a reservation that happened exactly one day before is not to be taken into account.
ROOMS hotel_name - display the number of rooms booked for the last night in the hotel_name hotel.

For each CLIENTS and ROOMS request, will be printed a single integer - the answer to the request. If the hotel specified in the request does not yet have any reservations, 
output is 0.

Example of INPUT 
11
CLIENTS Marriott
ROOMS Marriott
BOOK 10 FourSeasons 1 2
BOOK 10 Marriott 1 1
BOOK 86409 FourSeasons 2 1
CLIENTS FourSeasons
ROOMS FourSeasons
CLIENTS Marriott
BOOK 86410 Marriott 2 10
ROOMS FourSeasons
ROOMS Marriott

OUTPUT:
0
0
2
3
1
1
10
