#include "../../TypeTween.hpp"
#include <chrono>
#include <iostream>
#include <string>

#define FILLED " "
#define EMPTY "#"

int constexpr ProgressBarWidth = 35;

/* Create a manager */
static TypeTween::Manager manager;

void DefaultExample();

int main() {

	DefaultExample();

	auto start = std::chrono::high_resolution_clock::now();
	while (true) {
		/* Calculate delta time */
		auto now = std::chrono::high_resolution_clock::now();
		auto dt = std::chrono::duration<float>(now - start).count();
		start = now;

		/* Update the manager */
		manager.Update(dt);
	}

	return 0;
}

void DefaultExample() {
	float startValue = 0.0f;
	float endValue = 10.0f;
	float duration = 10.0f;
	bool yoyo = false;
	bool repeat = false;
	TypeTween::Ease ease = TypeTween::Ease::IN_OUT_QUINT;

	/* Prompt user for start values */
	std::cout << "Enter start value: ";
	std::cin >> startValue;
	std::cout << "Enter end value: ";
	std::cin >> endValue;
	std::cout << "Enter duration: ";
	std::cin >> duration;
	std::cout << "Enter yoyo (0: false, 1: true): ";
	std::cin >> yoyo;
	std::cout << "Enter repeat (0: false, 1: true): ";
	std::cin >> repeat;
	std::cout << "Enter ease:\n"
		<< "  0: LINEAR           1: IN_SINE\n"
		<< "  2: OUT_SINE         3: IN_OUT_SINE\n"
		<< "  4: IN_QUAD          5: OUT_QUAD\n"
		<< "  6: IN_OUT_QUAD      7: IN_CUBIC\n"
		<< "  8: OUT_CUBIC        9: IN_OUT_CUBIC\n"
		<< " 10: IN_QUART         11: OUT_QUART\n"
		<< " 12: IN_OUT_QUART     13: IN_QUINT\n"
		<< " 14: OUT_QUINT        15: IN_OUT_QUINT\n"
		<< " 16: IN_EXPO          17: OUT_EXPO\n"
		<< " 18: IN_OUT_EXPO      19: IN_CIRC\n"
		<< " 20: OUT_CIRC         21: IN_OUT_CIRC\n"
		<< " 22: IN_BACK          23: OUT_BACK\n"
		<< " 24: IN_OUT_BACK      25: IN_ELASTIC\n"
		<< " 26: OUT_ELASTIC      27: IN_OUT_ELASTIC\n"
		<< " 28: IN_BOUNCE        29: OUT_BOUNCE\n"
		<< " 30: IN_OUT_BOUNCE\n"
		<< "Your selection: ";

	int easeInt;
	std::cin >> easeInt;
	ease = static_cast<TypeTween::Ease>(easeInt);

	/* Create a tween */
	TypeTween::Tween<float> tween;
	tween.From(startValue)
		.To(endValue)
		.Duration(duration)
		.Easing(ease)
		.Yoyo(yoyo)
		.Repeat(repeat)
		.OnUpdate(
			[](const float& value, float t) {

				/* Showcase progress in console */
				std::string result;
				result += "Progress: [";
				for (int i = 0; i < ProgressBarWidth; i++) {
					if (t * ProgressBarWidth >= i) {
						result += EMPTY;
					} else {
						result += FILLED;
					}
				}
				result += "]";
				result += " " + std::to_string(value);

				/* Set cursor to start again */
				std::cout << "\r";

				/* Print the progress bar */
				std::cout << result;
			}
		).OnComplete(
			/* Will not get called if repeat is true */
			[](const float& /*value*/) {
				std::cout << "\nTween completed!" << std::endl;
			}
		).OnCycleComplete(
			[](const float& /*value*/) {
				std::cout << "Cycle completed!" << std::endl;
			}
		);

	/* Add the tween to the manager */
	manager.AddTween(tween);
}