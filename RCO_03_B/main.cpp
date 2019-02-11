#include <iostream>

#include <string>
#include <vector>

#include <chrono>
#include <queue>
#include <stack>

using namespace std;

inline int readInt() {
	int val;
	cin >> val;
	return val;
}

const int Care = 1;
const int Harvest = 2;

struct Output {
	int com = 2;
	int x = 0;
	int y = 0;

	bool operator<(const Output& other) const {
		return this->com < other.com;
	}


};

class Stopwatch {
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Stopwatch() = default;

	/// <summary>
	/// 計測を開始する
	/// </summary>
	inline void start() noexcept {
		s = std::chrono::high_resolution_clock::now();
		e = s;
	}
	/// <summary>
	/// 計測を停止する
	/// </summary>
	inline void stop() noexcept {
		e = std::chrono::high_resolution_clock::now();
	}

	/// <summary>
	/// 計測時間を取得する(ナノ秒)
	/// </summary>
	/// <returns>計測時間(ナノ秒)</returns>
	inline const long long nanoseconds() const noexcept { return std::chrono::duration_cast<std::chrono::nanoseconds>(e - s).count(); }
	/// <summary>
	/// 計測時間を取得する(マイクロ秒)
	/// </summary>
	/// <returns>計測時間(マイクロ秒)</returns>
	inline const long long microseconds() const noexcept { return std::chrono::duration_cast<std::chrono::microseconds>(e - s).count(); }
	/// <summary>
	/// 計測時間を取得する(ミリ秒)
	/// </summary>
	/// <returns>計測時間(ミリ秒)</returns>
	inline const long long millisecond() const noexcept { return std::chrono::duration_cast<std::chrono::milliseconds>(e - s).count(); }
	/// <summary>
	/// 計測時間を取得する(秒)
	/// </summary>
	/// <returns>計測時間(秒)</returns>
	inline const long long second() const noexcept { return std::chrono::duration_cast<std::chrono::seconds>(e - s).count(); }
	/// <summary>
	/// 計測時間を取得する(分)
	/// </summary>
	/// <returns>計測時間(分)</returns>
	inline const long long minutes() const noexcept { return std::chrono::duration_cast<std::chrono::minutes>(e - s).count(); }
	/// <summary>
	/// 計測時間を取得する(時)
	/// </summary>
	/// <returns>計測時間(時)</returns>
	inline const long long hours() const noexcept { return std::chrono::duration_cast<std::chrono::hours>(e - s).count(); }

	/// <summary>
	/// 単位付きの計測時間の文字列を得る(ナノ秒)
	/// </summary>
	/// <returns>計測時間の文字列(ナノ秒)</returns>
	inline const std::string toString_ns() const { return std::to_string(nanoseconds()) + "ns"; }
	/// <summary>
	/// 単位付きの計測時間の文字列を得る(マイクロ秒)
	/// </summary>
	/// <returns>計測時間の文字列(マイクロ秒)</returns>
	inline const std::string toString_us() const { return std::to_string(microseconds()) + "us"; }
	/// <summary>
	/// 単位付きの計測時間の文字列を得る(ミリ秒)
	/// </summary>
	/// <returns>計測時間の文字列(ミリ秒)</returns>
	inline const std::string toString_ms() const { return std::to_string(millisecond()) + "ms"; }
	/// <summary>
	/// 単位付きの計測時間の文字列を得る(秒)
	/// </summary>
	/// <returns>計測時間の文字列(秒)</returns>
	inline const std::string toString_s() const { return std::to_string(second()) + "s"; }
	/// <summary>
	/// 単位付きの計測時間の文字列を得る(分)
	/// </summary>
	/// <returns>計測時間の文字列(分)</returns>
	inline const std::string toString_m() const { return std::to_string(minutes()) + "m"; }
	/// <summary>
	/// 単位付きの計測時間の文字列を得る(時)
	/// </summary>
	/// <returns>計測時間の文字列(時)</returns>
	inline const std::string toString_h() const { return std::to_string(hours()) + "h"; }

private:

	std::chrono::time_point<std::chrono::high_resolution_clock> s;
	std::chrono::time_point<std::chrono::high_resolution_clock> e;

};

class MilliSecTimer {
private:

	std::chrono::time_point<std::chrono::high_resolution_clock> s;
	unsigned long long int startCycle = 0;
	long long time = 0;

	const double CyclePerMilliSec = 2794000.0;

#ifndef _MSC_VER
	unsigned long long int getCycle() const {
		unsigned int low, high;
		__asm__ volatile ("rdtsc" : "=a" (low), "=d" (high));
		return ((unsigned long long int)low) | ((unsigned long long int)high << 32);
	}
#endif // _MSC_VER

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	MilliSecTimer() = default;
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_time">設定時間(ミリ秒)</param>
	MilliSecTimer(const std::chrono::milliseconds& _time) noexcept { time = _time.count(); }

	/// <summary>
	/// 時間を設定する
	/// </summary>
	/// <param name="_time">設定時間(ミリ秒)</param>
	void set(const std::chrono::milliseconds& _time) noexcept { time = _time.count(); }

	/// <summary>
	/// タイマーを開始させる
	/// </summary>
	void start() noexcept {
#ifdef _MSC_VER
		s = std::chrono::high_resolution_clock::now();
#else
		startCycle = getCycle();
#endif // _MSC_VER
	}

	/// <summary>
	/// 設定時間経過したかを得る
	/// </summary>
	/// <returns>経過していれば true, それ以外は false</returns>
	inline const bool check() const noexcept {
#ifdef _MSC_VER
		const auto e = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::milliseconds>(e - s).count() >= time;
#else
		return (getCycle() - startCycle) / CyclePerMilliSec >= time;
#endif // _MSC_VER
	}

	/// <summary>
	/// 設定時間経過したかを得る
	/// </summary>
	/// <returns>経過していれば true, それ以外は false</returns>
	operator bool() const noexcept { return check(); }

	/// <summary>
	/// 経過時間を取得する(ミリ秒)
	/// </summary>
	/// <returns>計測時間(ミリ秒)</returns>
	inline const long long interval() const noexcept {
#ifdef _MSC_VER
		const auto e = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::milliseconds>(e - s).count();
#else
		return static_cast<long long int>((getCycle() - startCycle) / CyclePerMilliSec);
#endif // _MSC_VER
	}

};

struct XorShift {
	unsigned int x;
	XorShift() : x(2463534242U) {}
	unsigned int rand() {
		x ^= (x << 13);
		x ^= (x >> 17);
		x ^= (x << 5);
		return x;
	}

};

class AI {
private:

	const int N;
	const int M;
	const vector<vector<int>>& field;

	const int K = 9;

	XorShift random;

	int getScore(const vector<vector<int>>& table, const Output& last) const {

		vector<vector<int>> check = table;

		stack<Output> sta;
		sta.push(last);

		check[last.y][last.x] = 0;

		int count = 0;

		while (!sta.empty())
		{
			const auto pos = sta.top();
			sta.pop();
			count++;

			if (pos.x > 0 && table[pos.y][pos.x - 1] == K && check[pos.y][pos.x - 1] > 0)
			{
				sta.push({ table[pos.y][pos.x - 1],pos.x - 1,pos.y });
				check[pos.y][pos.x - 1] = 0;
			}
			if (pos.x < N - 1 && table[pos.y][pos.x + 1] == K && check[pos.y][pos.x + 1] > 0)
			{
				sta.push({ table[pos.y][pos.x + 1],pos.x + 1,pos.y });
				check[pos.y][pos.x + 1] = 0;
			}
			if (pos.y > 0 && table[pos.y - 1][pos.x] == K && check[pos.y - 1][pos.x] > 0)
			{
				sta.push({ table[pos.y - 1][pos.x],pos.x,pos.y - 1 });
				check[pos.y - 1][pos.x] = 0;
			}
			if (pos.y < N - 1 && table[pos.y + 1][pos.x] == K && check[pos.y + 1][pos.x] > 0)
			{
				sta.push({ table[pos.y + 1][pos.x],pos.x,pos.y + 1 });
				check[pos.y + 1][pos.x] = 0;
			}
		}

		return count >= K ? count * K : 0;
	}

	pair<vector<Output>, vector<vector<int>>> make() {

		vector<Output> answer;

		auto table = field;
		vector<vector<int>> check = table;

		priority_queue<Output> search;

		int x = random.rand() % N;
		int y = random.rand() % N;
		search.push({ table[y][x],x,y });
		check[y][x] = 0;

		while ((int)answer.size() < M - 1)
		{
			const auto pos = search.top();
			search.pop();

			for (int i = pos.com; i < K; i++)
			{
				answer.push_back({ Care,pos.x,pos.y });
			}
			table[pos.y][pos.x] = K;

			if (pos.x > 0 && check[pos.y][pos.x - 1] > 0)
			{
				search.push({ table[pos.y][pos.x - 1],pos.x - 1,pos.y });
				check[pos.y][pos.x - 1] = 0;
			}
			if (pos.x < N - 1 && check[pos.y][pos.x + 1] > 0)
			{
				search.push({ table[pos.y][pos.x + 1],pos.x + 1,pos.y });
				check[pos.y][pos.x + 1] = 0;
			}
			if (pos.y > 0 && check[pos.y - 1][pos.x] > 0)
			{
				search.push({ table[pos.y - 1][pos.x],pos.x,pos.y - 1 });
				check[pos.y - 1][pos.x] = 0;
			}
			if (pos.y < N - 1 && check[pos.y + 1][pos.x] > 0)
			{
				search.push({ table[pos.y + 1][pos.x],pos.x,pos.y + 1 });
				check[pos.y + 1][pos.x] = 0;
			}

		}

		answer.resize(M - 1);
		answer.push_back({ Harvest,x,y });

		return { answer,table };
	}


public:

	AI(int _N, int _M, const vector<vector<int>>& _field) : N(_N), M(_M), field(_field) {

	}

	vector<Output> think() {

		const auto p = make();

		vector<Output> bestAnswer = p.first;
		int bestScore = getScore(p.second, bestAnswer.back());


		MilliSecTimer timer;
		timer.set(chrono::milliseconds(1900));

		timer.start();
		while (!timer.check())
		{
			const auto next = make();
			int score = getScore(next.second, next.first.back());

			if (bestScore < score)
			{
				bestScore = score;
				bestAnswer = next.first;
			}

		}

		cerr << bestScore << endl;

		return bestAnswer;
	}


};

int main() {

	const int N = readInt();
	const int M = readInt();

	vector<vector<int>> field(N);
	for (auto& line : field) line.resize(N);

	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			field[y][x] = readInt();
		}
	}

	vector<Output> answer(M);

	AI ai(N, M, field);

	Stopwatch sw;
	sw.start();
	answer = ai.think();
	sw.stop();

	cerr << sw.toString_ms() << endl;

	for (const auto& ans : answer)
	{
		cout << ans.com << " " << ans.y << " " << ans.x << endl;
	}

	return 0;
}
