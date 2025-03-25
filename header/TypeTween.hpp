/*
Easings from: https://easings.net/
*/

#ifndef TYPE_TWEEN_HPP
#define TYPE_TWEEN_HPP

// Namespace for the library
#ifndef TYPE_TWEEN_NAMEPSACE
#define TYPE_TWEEN_NAMEPSACE TypeTween
#endif // TYPE_TWEEN_NAMEPSACE

// Include the necessary C++ headers
#include <cmath>
#include <memory>
#include <functional>
#include <map>

namespace TYPE_TWEEN_NAMEPSACE {


	constexpr float pi = 3.14159265358979323846f;

#pragma region EasingFunctions
	enum class Ease {
		LINEAR,
		IN_SINE,
		OUT_SINE,
		IN_OUT_SINE,
		IN_QUAD,
		OUT_QUAD,
		IN_OUT_QUAD,
		IN_CUBIC,
		OUT_CUBIC,
		IN_OUT_CUBIC,
		IN_QUART,
		OUT_QUART,
		IN_OUT_QUART,
		IN_QUINT,
		OUT_QUINT,
		IN_OUT_QUINT,
		IN_EXPO,
		OUT_EXPO,
		IN_OUT_EXPO,
		IN_CIRC,
		OUT_CIRC,
		IN_OUT_CIRC,
		IN_BACK,
		OUT_BACK,
		IN_OUT_BACK,
		IN_ELASTIC,
		OUT_ELASTIC,
		IN_OUT_ELASTIC,
		IN_BOUNCE,
		OUT_BOUNCE,
		IN_OUT_BOUNCE
	};

	// Compile time easing function
	template <Ease E>
	constexpr float apply_ease_const(float t) {
		using std::cos;
		using std::pow;
		using std::sin;
		using std::sqrt;

		if constexpr (E == Ease::LINEAR) {
			return t;
		}
		// Sine easing
		else if constexpr (E == Ease::IN_SINE) {
			return 1 - cos((t * pi) / 2);
		} else if constexpr (E == Ease::OUT_SINE) {
			return sin((t * pi) / 2);
		} else if constexpr (E == Ease::IN_OUT_SINE) {
			return -(cos(pi * t) - 1) / 2;
		}
		// Quadratic easing
		else if constexpr (E == Ease::IN_QUAD) {
			return t * t;
		} else if constexpr (E == Ease::OUT_QUAD) {
			return 1 - (1 - t) * (1 - t);
		} else if constexpr (E == Ease::IN_OUT_QUAD) {
			return (t < 0.5f) ? 2 * t * t : 1 - pow(-2 * t + 2, 2) / 2;
		}
		// Cubic easing
		else if constexpr (E == Ease::IN_CUBIC) {
			return t * t * t;
		} else if constexpr (E == Ease::OUT_CUBIC) {
			return 1 - pow(1 - t, 3);
		} else if constexpr (E == Ease::IN_OUT_CUBIC) {
			return (t < 0.5f) ? 4 * t * t * t : 1 - pow(-2 * t + 2, 3) / 2;
		}
		// Quartic easing
		else if constexpr (E == Ease::IN_QUART) {
			return pow(t, 4);
		} else if constexpr (E == Ease::OUT_QUART) {
			return 1 - pow(1 - t, 4);
		} else if constexpr (E == Ease::IN_OUT_QUART) {
			return (t < 0.5f) ? 8 * pow(t, 4) : 1 - pow(-2 * t + 2, 4) / 2;
		}
		// Quintic easing
		else if constexpr (E == Ease::IN_QUINT) {
			return pow(t, 5);
		} else if constexpr (E == Ease::OUT_QUINT) {
			return 1 - pow(1 - t, 5);
		} else if constexpr (E == Ease::IN_OUT_QUINT) {
			return (t < 0.5f) ? 16 * pow(t, 5) : 1 - pow(-2 * t + 2, 5) / 2;
		}
		// Exponential easing
		else if constexpr (E == Ease::IN_EXPO) {
			return (t == 0) ? 0 : pow(2, 10 * t - 10);
		} else if constexpr (E == Ease::OUT_EXPO) {
			return (t == 1) ? 1 : 1 - pow(2, -10 * t);
		} else if constexpr (E == Ease::IN_OUT_EXPO) {
			if (t == 0) return 0;
			if (t == 1) return 1;
			return (t < 0.5f) ? pow(2, 20 * t - 10) / 2 : (2 - pow(2, -20 * t + 10)) / 2;
		}
		// Circular easing
		else if constexpr (E == Ease::IN_CIRC) {
			return 1 - sqrt(1 - t * t);
		} else if constexpr (E == Ease::OUT_CIRC) {
			return sqrt(1 - pow(t - 1, 2));
		} else if constexpr (E == Ease::IN_OUT_CIRC) {
			return (t < 0.5f) ? (1 - sqrt(1 - pow(2 * t, 2))) / 2 : (sqrt(1 - pow(-2 * t + 2, 2)) + 1) / 2;
		}
		// Back easing (using common overshoot constants)
		else if constexpr (E == Ease::IN_BACK) {
			constexpr float c1 = 1.70158f;
			constexpr float c3 = c1 + 1;
			return c3 * t * t * t - c1 * t * t;
		} else if constexpr (E == Ease::OUT_BACK) {
			constexpr float c1 = 1.70158f;
			constexpr float c3 = c1 + 1;
			float tm = t - 1;
			return 1 + c3 * tm * tm * tm + c1 * tm * tm;
		} else if constexpr (E == Ease::IN_OUT_BACK) {
			constexpr float c1 = 1.70158f;
			constexpr float c2 = c1 * 1.525f;
			return (t < 0.5f) ? (pow(2 * t, 2) * ((c2 + 1) * 2 * t - c2)) / 2
				: (pow(2 * t - 2, 2) * ((c2 + 1) * (2 * t - 2) + c2) + 2) / 2;
		}
		// Elastic easing
		else if constexpr (E == Ease::IN_ELASTIC) {
			if (t == 0 || t == 1) return t;
			return -pow(2, 10 * t - 10) * sin((t * 10 - 10.75f) * (2 * pi) / 3);
		} else if constexpr (E == Ease::OUT_ELASTIC) {
			if (t == 0 || t == 1) return t;
			return pow(2, -10 * t) * sin((t * 10 - 0.75f) * (2 * pi) / 3) + 1;
		} else if constexpr (E == Ease::IN_OUT_ELASTIC) {
			if (t == 0 || t == 1) return t;
			if (t < 0.5f) {
				return -(pow(2, 20 * t - 10) * sin((20 * t - 11.125f) * (2 * pi) / 4.5f)) / 2;
			} else {
				return (pow(2, -20 * t + 10) * sin((20 * t - 11.125f) * (2 * pi) / 4.5f)) / 2 + 1;
			}
		}
		// Bounce easing
		else if constexpr (E == Ease::OUT_BOUNCE) {
			if (t < 1 / 2.75f) {
				return 7.5625f * t * t;
			} else if (t < 2 / 2.75f) {
				t -= 1.5f / 2.75f;
				return 7.5625f * t * t + 0.75f;
			} else if (t < 2.5f / 2.75f) {
				t -= 2.25f / 2.75f;
				return 7.5625f * t * t + 0.9375f;
			} else {
				t -= 2.625f / 2.75f;
				return 7.5625f * t * t + 0.984375f;
			}
		} else if constexpr (E == Ease::IN_BOUNCE) {
			return 1 - apply_ease_const<Ease::OUT_BOUNCE>(1 - t);
		} else if constexpr (E == Ease::IN_OUT_BOUNCE) {
			return (t < 0.5f) ? (1 - apply_ease_const<Ease::OUT_BOUNCE>(1 - 2 * t)) / 2
				: (1 + apply_ease_const<Ease::OUT_BOUNCE>(2 * t - 1)) / 2;
		} else {
			return t;
		}
	}

	// Run time easing function
	inline float apply_ease(float t, Ease ease) {
		switch (ease) {
		case Ease::LINEAR:
			return apply_ease_const<Ease::LINEAR>(t);
		case Ease::IN_SINE:
			return apply_ease_const<Ease::IN_SINE>(t);
		case Ease::OUT_SINE:
			return apply_ease_const<Ease::OUT_SINE>(t);
		case Ease::IN_OUT_SINE:
			return apply_ease_const<Ease::IN_OUT_SINE>(t);
		case Ease::IN_QUAD:
			return apply_ease_const<Ease::IN_QUAD>(t);
		case Ease::OUT_QUAD:
			return apply_ease_const<Ease::OUT_QUAD>(t);
		case Ease::IN_OUT_QUAD:
			return apply_ease_const<Ease::IN_OUT_QUAD>(t);
		case Ease::IN_CUBIC:
			return apply_ease_const<Ease::IN_CUBIC>(t);
		case Ease::OUT_CUBIC:
			return apply_ease_const<Ease::OUT_CUBIC>(t);
		case Ease::IN_OUT_CUBIC:
			return apply_ease_const<Ease::IN_OUT_CUBIC>(t);
		case Ease::IN_QUART:
			return apply_ease_const<Ease::IN_QUART>(t);
		case Ease::OUT_QUART:
			return apply_ease_const<Ease::OUT_QUART>(t);
		case Ease::IN_OUT_QUART:
			return apply_ease_const<Ease::IN_OUT_QUART>(t);
		case Ease::IN_QUINT:
			return apply_ease_const<Ease::IN_QUINT>(t);
		case Ease::OUT_QUINT:
			return apply_ease_const<Ease::OUT_QUINT>(t);
		case Ease::IN_OUT_QUINT:
			return apply_ease_const<Ease::IN_OUT_QUINT>(t);
		case Ease::IN_EXPO:
			return apply_ease_const<Ease::IN_EXPO>(t);
		case Ease::OUT_EXPO:
			return apply_ease_const<Ease::OUT_EXPO>(t);
		case Ease::IN_OUT_EXPO:
			return apply_ease_const<Ease::IN_OUT_EXPO>(t);
		case Ease::IN_CIRC:
			return apply_ease_const<Ease::IN_CIRC>(t);
		case Ease::OUT_CIRC:
			return apply_ease_const<Ease::OUT_CIRC>(t);
		case Ease::IN_OUT_CIRC:
			return apply_ease_const<Ease::IN_OUT_CIRC>(t);
		case Ease::IN_BACK:
			return apply_ease_const<Ease::IN_BACK>(t);
		case Ease::OUT_BACK:
			return apply_ease_const<Ease::OUT_BACK>(t);
		case Ease::IN_OUT_BACK:
			return apply_ease_const<Ease::IN_OUT_BACK>(t);
		case Ease::IN_ELASTIC:
			return apply_ease_const<Ease::IN_ELASTIC>(t);
		case Ease::OUT_ELASTIC:
			return apply_ease_const<Ease::OUT_ELASTIC>(t);
		case Ease::IN_OUT_ELASTIC:
			return apply_ease_const<Ease::IN_OUT_ELASTIC>(t);
		case Ease::IN_BOUNCE:
			return apply_ease_const<Ease::IN_BOUNCE>(t);
		case Ease::OUT_BOUNCE:
			return apply_ease_const<Ease::OUT_BOUNCE>(t);
		case Ease::IN_OUT_BOUNCE:
			return apply_ease_const<Ease::IN_OUT_BOUNCE>(t);
		default:
			return t;
		}
	}
#pragma endregion

	//simple interface
	class ITween {
	public:
		virtual ~ITween() = default;
		virtual void Update(float delta_time) = 0;
		virtual bool IsFinished() const = 0;
		virtual std::unique_ptr<ITween> Clone() const = 0;
	};

	// Templated tween class
	template <typename T>
	class Tween : public ITween {
		// Underlying type: if T is a pointer, ValueType is the pointed-to type.
		using ValueType = std::remove_pointer_t<T>;

	public:
		// Default constructor—for when you want to use callbacks only.
		Tween() = default;

		// Constructor for pointer types (e.g. Transform*)
		template <typename U = T, typename = std::enable_if_t<std::is_pointer_v<U>>>
		Tween(U src) : source(src), start(*src) {}

		// Constructor for value types (e.g. glm::vec3) passed by reference.
		template <typename U = T, typename = std::enable_if_t<!std::is_pointer_v<U>>>
		Tween(U& src) : source(&src), start(src) {}

		// Accept a value...
		Tween& From(const ValueType& s) {
			start = s;
			pStart = nullptr;
			return *this;
		}
		// ...or a pointer
		Tween& From(ValueType* sPtr) {
			pStart = sPtr;
			return *this;
		}

		// Fluent setters for the end value.
		Tween& To(const ValueType& e) {
			end = e;
			pEnd = nullptr;
			return *this;
		}
		Tween& To(ValueType* ePtr) {
			pEnd = ePtr;
			return *this;
		}

		/// <summary>
		/// Duration of the tween, in seconds.
		/// </summary>
		/// <param name="d"></param>
		/// <returns></returns>
		Tween& Duration(float d) {
			duration = d;
			return *this;
		}
		/// <summary>
		/// Delay before the tween starts, in seconds.
		/// </summary>
		/// <param name="d"></param>
		/// <returns></returns>
		Tween& Delay(float d) {
			delay = d;
			return *this;
		}
		/// <summary>
		/// Easing function to use for the tween.
		/// </summary>
		/// <param name="e">Ease type (see easings.net)</param>
		/// <returns></returns>
		Tween& Easing(Ease e) {
			ease = e;
			return *this;
		}
		/// <summary>
		/// OnUpdate callback, called every frame with the current value and the normalized time.
		/// </summary>
		/// <param name="f">Function callback</param>
		/// <returns></returns>
		Tween& OnUpdate(std::function<void(const ValueType&, float)> f) {
			onUpdate = f;
			return *this;
		}
		/// <summary>
		/// OnComplete callback, called when the tween finishes with the final value.
		/// </summary>
		/// <param name="f">Function callback</param>
		/// <returns></returns>
		Tween& OnComplete(std::function<void(const ValueType&)> f) {
			onComplete = f;
			return *this;
		}
		/// <summary>
		/// Repeat the tween indefinitely. Can be stopped with Stop().
		/// </summary>
		/// <param name="rep"></param>
		/// <returns></returns>
		Tween& Repeat(bool rep) {
			repeat = rep;
			return *this;
		}
		/// <summary>
		/// Yoyo the tween. If true, the tween will reverse after reaching the end.
		/// </summary>
		/// <param name="y"></param>
		/// <returns></returns>
		Tween& Yoyo(bool y) {
			yoyo = y;
			return *this;
		}

		/// <summary>
		/// Reset the tween to the start.
		/// </summary>
		void Reset() { elapsed = 0.0f; }

		/// <summary>
		/// Stop the tween. If repeating, the tween will stop after the current cycle.
		/// </summary>
		void Stop() { elapsed = delay + duration; }

		void Update(float delta_time) override {
			elapsed += delta_time;

			// If the total elapsed time is less than the delay, do nothing.
			if (elapsed < delay) return;

			// Compute the effective elapsed time, subtracting the delay.
			float effectiveElapsed = elapsed - delay;

			// Determine the full cycle duration.
			float cycleDuration = yoyo ? duration * 2.0f : duration;

			// If not repeating, clamp effectiveElapsed to the cycle duration.
			if (!repeat && effectiveElapsed > cycleDuration) {
				effectiveElapsed = cycleDuration;
			}

			float t = 0.0f;

			// If this is the final frame (and not repeating), force t to end value.
			if (!repeat && effectiveElapsed >= cycleDuration) {
				t = yoyo ? 0.0f : 1.0f;
			} else {
				// Compute the current cycle time (wrap around if repeating).
				float cycleTime = std::fmod(effectiveElapsed, cycleDuration);
				if (yoyo && cycleTime >= duration) {
					// Reverse phase for yoyo: map cycleTime in [duration, cycleDuration] to t in [1, 0].
					t = 1.0f - ((cycleTime - duration) / duration);
					t = 1.0f - apply_ease(1.0f - t, ease);
				} else {
					// Forward phase.
					t = cycleTime / duration;
					t = apply_ease(t, ease);
				}
			}

			// Compute the current tweened value.
			ValueType current = EffectiveStart() + (EffectiveEnd() - EffectiveStart()) * t;

			// Update the source pointer, if provided.
			if (source) *source = current;

			// Notify via the on_update callback.
			if (onUpdate) onUpdate(current, t);

			// If not repeating and the tween has finished, call on_complete.
			if (!repeat && effectiveElapsed >= cycleDuration) {
				if (onComplete) onComplete(current);
			}
		}

		/// <summary>
		/// Check if the tween has finished.
		/// </summary>
		/// <returns></returns>
		bool IsFinished() const override {
			if (repeat) return false;
			float cycleDuration = yoyo ? duration * 2.0f : duration;
			return elapsed >= (delay + cycleDuration);
		}

		std::unique_ptr<ITween> Clone() const override { return std::make_unique<Tween>(*this); }

	private:
		ValueType EffectiveStart() const { return pStart ? *pStart : start; }
		ValueType EffectiveEnd() const { return pEnd ? *pEnd : end; }

		ValueType start{};
		ValueType end{};
		ValueType* pStart = nullptr;
		ValueType* pEnd = nullptr;
		ValueType* source = nullptr;

		float duration = 0.0f;
		float elapsed = 0.0f;
		float delay = 0.0f;
		bool repeat = false;
		bool yoyo = false;
		Ease ease = Ease::LINEAR;

		std::function<void(const ValueType&, float)> onUpdate;
		std::function<void(const ValueType&)> onComplete;
	};

	class Manager {
	public:
		Manager() = default;

		size_t AddTween(ITween& tween) {
			size_t id = nextId++;
			tweens[id] = tween.Clone();
			return id;
		}

		bool RemoveTween(size_t id) {
			auto it = tweens.find(id);
			if (it != tweens.end()) {
				tweens.erase(it);
				return true;
			}
			return false;
		}

		void ClearAllTweens() {
			tweens.clear();
		}

		void Update(float delta_time) {
			// Update all tweens
			for (auto& tween : tweens) {
				if (tween.second->IsFinished()) continue;
				tween.second->Update(delta_time);
			}

			// Remove finished tweens
			auto it = tweens.begin();
			while (it != tweens.end()) {
				if (it->second->IsFinished()) {
					it = tweens.erase(it);
				} else {
					++it;
				}
			}
		}

	private:
		size_t nextId = 0;
		std::map<size_t, std::unique_ptr<ITween>> tweens;
	};
}

#endif // TYPE_TWEEN_HPP