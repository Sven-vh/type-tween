# Type-Tween

Single header C++ Tweening file

## What is it

A simple "library" that allows the user to create tweens easily. It supports:
- ``From`` | Start value
- ``To`` | End value
- ``Duration`` | Tween time
- ``Delay`` | Wait time
- ``Easing`` | See [Easing](#easing)
- ``Yoyo`` | tween back in reverse
- ``Repeat`` | When done, keep playing
- ``OnUpdate`` | Update callback
- ``OnComplete`` | Complete callback

## How to integrate

The Only thing you need is [``TypeTween.hpp``](https://github.com/Sven-vh/type-tween/blob/main/TypeTween.hpp). Download it and include it anywhere in your project.

![image](https://github.com/user-attachments/assets/aed9877f-c3c2-4b61-924d-cc0d6982dd4d)

## How to use

```cpp
/* Manager that holds all the tweens */
TypeTween::Manager manager;

/* Specify the type */
TypeTween::Tween<float> tween;

/* Set values of tween */
tween.From(startValue).To(endValue).Duration(duration).Easing(ease).Yoyo(yoyo).Repeat(repeat)
	.OnUpdate(
		[](const float& _value, float t) {
			std::cout << "Value: " << _value << " Time: " << t << std::endl;
		}
	).OnComplete(
		[](const float& value) {
			std::cout << "Done" << std::endl;
		}
	);

/* Add it to the manager */
manager.AddTween(tween);

/* In your main loop, update the manager */
while(true){
	float deltaTime = 1.0f/60.0f;
	manager.Update(deltaTime)
}
```

## Types

Since the tween is templated, any type that has a ``+``, ``-``, and ``*`` will work.

It also contains pointer support. The pointer will get updated, so there is no need for an ``OnUpdate`` callback.

## Easing

As of right now, it currently supports these easings:
![Screenshot_512](https://github.com/user-attachments/assets/598f65ab-aeca-4f9c-9ee4-9954a75eb951)
Source [easings.net](https://easings.net/)

## Example

This repo contains an example.sln. This is just a simple showcase of how to use it and check if everything works as expected.

![tweening](https://github.com/user-attachments/assets/f99f15cf-258d-4095-a11e-9b0472e08be1)
