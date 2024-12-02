#pragma once

 
struct Status
{
	short single_alive = 0,
		two_alive = 0,
		three_alive = 0,
		four_alive = 0,
		alive = 0;
};

void clear_stats(Status& st1, Status& st2);
void change_status(Status& st, const short size);
void show_stats(Status& st1, Status& st2);
