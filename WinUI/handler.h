#pragma once

class Handler
{
public:
	Handler();
	virtual ~Handler();

	virtual void handleEvent() = 0;
};

