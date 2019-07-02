// 20190408-01.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <numeric>
#include <queue>
#include <stack>

using namespace std;

template<typename T> void printVector(vector<T> vecs, int ppc = 4) {
	for (int i = 0; i < vecs.size(); i++) {
		std::cout << vecs[i] << ", ";
		if (i > 0 && (i % ppc) == 0)
			std::cout << endl;
	}
	std::cout << endl;
}

// 베스트앨범 - 장르별로 2곡씩 베스트앨범 만들기
// genres											plays						return
// {"classic", "pop", "classic", "classic", "pop"}	{500, 600, 150, 800, 2500}	{4, 1, 3, 0}
// 속한 노래가 많이 재생된 장르를 먼저 수록합니다.
// 장르 내에서 많이 재생된 노래를 먼저 수록합니다.
// 장르 내에서 재생 횟수가 같은 노래 중에서는 고유 번호가 낮은 노래를 먼저 수록합니다.

vector<int> solution42579(vector<string> genres, vector<int> plays) {
	vector<int> answer;

	struct SongVO {
		SongVO() {};
		SongVO(int i, int p, string g) {
			idx = i;
			play_cnt = p;
			genre = g;
		};

		int idx;
		int play_cnt = 0;
		string genre = "";
	};

	struct GenreVO {
		GenreVO() {};
		GenreVO(string g, int i, int cnt) {
			genre = g;
			play_cnt = cnt;

			songQ.push_back(SongVO(i, cnt, g));
		};

		void pushSong(int i, int cnt)
		{
			play_cnt += cnt;
			songQ.push_back(SongVO(i, cnt, genre));
		};

		string genre = "";
		int play_cnt = 0;

		std::vector<SongVO> songQ;
	};

	std::map<string, GenreVO> genresMap;

	int idx = 0;
	for_each(plays.begin(), plays.end(), [&](int pcnt) {
		if (genresMap.find(genres[idx]) == genresMap.end())
			genresMap[genres[idx]] = GenreVO(genres[idx], idx, pcnt);
		else
			genresMap[genres[idx]].pushSong(idx, pcnt);

		idx++; 
	});

	std::vector<GenreVO> g2;
	for_each(genresMap.begin(), genresMap.end(), [&g2](pair<string, GenreVO> a) {
		g2.push_back(a.second);
	});

	std::sort(g2.begin(), g2.end(), [&](GenreVO a, GenreVO b)->bool{
		return a.play_cnt > b.play_cnt;
	});

	for_each(g2.begin(), g2.end(), [&](GenreVO genre) {

		std::sort(genre.songQ.begin(), genre.songQ.end(), [&](SongVO a, SongVO b)->bool{
			return b.play_cnt == a.play_cnt ? b.idx > a.idx : b.play_cnt < a.play_cnt;
		});

		int cnt = 0;
		for (std::vector<SongVO>::iterator it = genre.songQ.begin(); it != genre.songQ.end(); it++) {
			answer.push_back(it->idx);
			cnt++;
			if (cnt > 1) break;
		};
	});

	return answer;
}

int main()
{
	printVector(solution42579( { "classic", "pop", "classic", "classic", "pop" }, {500, 600, 150, 800, 2500} ));
	return 0;
}
