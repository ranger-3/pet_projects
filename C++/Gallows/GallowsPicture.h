#pragma once

#include <iostream>

using namespace std;

class GallowsPicture
{
	int status;

public:

	GallowsPicture(const int& status) : status(status) {}
	GallowsPicture() : GallowsPicture(0) {}
	~GallowsPicture() {}

	void SetStatus(const int& status) { this->status = status; }
	void Show()const;
};

