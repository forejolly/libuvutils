#ifndef MS_TIMER_HPP
#define MS_TIMER_HPP
#include <stdint.h>
#include <uv.h>

class Timer {
public:
	class Listener {
	public:
		virtual ~Listener() = default;

	public:
		virtual void OnTimer(Timer *timer) = 0;
	};

public:
	explicit Timer(Listener *listener);
	Timer& operator=(const Timer&) = delete;
	Timer(const Timer&) = delete;
	~Timer();

public:
	void Close();
	void Start(uint64_t timeout, uint64_t repeat = 0);
	void Stop();
	void Reset();
	void Restart();
	uint64_t GetTimeout() const;
	uint64_t GetRepeat() const;
	bool IsActive() const;

	/* Callbacks fired by UV events. */
public:
	void OnUvTimer();

private:
	// Passed by argument.
	Listener *listener { nullptr };
	// Allocated by this.
	uv_timer_t *uvHandle { nullptr };
	// Others.
	bool closed { false };
	uint64_t timeout { 0 };
	uint64_t repeat { 0 };
};

/* Inline methods. */

inline uint64_t Timer::GetTimeout() const {
	return this->timeout;
}

inline uint64_t Timer::GetRepeat() const {
	return this->repeat;
}

inline bool Timer::IsActive() const {
	return uv_is_active(reinterpret_cast<uv_handle_t*>(this->uvHandle)) != 0;
}

#endif
