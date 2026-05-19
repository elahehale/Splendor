#pragma once
#include <string>
#include  "raylib.h"

enum TextType {
	Question = 0,
	Info,
	Warning
};
struct Message {
	TextType type;
	std::string content;
	int steps;
	int current_step;
	Message() : type(TextType::Info), content(""), steps(60), current_step(0) {} // Default constructor
	Message(TextType type, const std::string& content) {
		this->type = type;
		this->content = content;
		this->steps = 200;
		this->current_step = 0;
	}
	void update_message() {
		if (current_step < steps) {
			current_step++;
		}
	}
	void show_message() {
		Color color = get_color_from_text_type(type);
		DrawText(content.c_str(), 600, 40, 20, color);
	}
	Color get_color_from_text_type(TextType type) {
		switch (type) {
		case TextType::Question:
			return BLUE;
		case TextType::Info:
			return BLACK;
		case TextType::Warning:
			return RED;
		default:
			return GRAY;
		}
	};

};

struct MessageHandler {
	Message current_message;
	bool active = false;
	MessageHandler() {
		current_message = Message(TextType::Info, "");
	}
	void set_message(TextType type, const std::string& content) {
		current_message = Message(type, content);
		active = true;
	}
	void update() {
		if (!active) return;
		current_message.update_message();
		if (current_message.current_step >= current_message.steps) {
			active = false;
		}
	}
	void show() {
		if (!active) return;
		current_message.show_message();
	}
};



