#pragma once

struct ImGuiIO;
class UserInterface
{
protected:
	UserInterface();
	~UserInterface();

	void StartFrame();

	// To be defined and displays the contents of the window.
	virtual void Window() = 0;
	

private:
	ImGuiIO& io;

};

