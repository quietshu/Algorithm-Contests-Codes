/*
* Copyright (C) 2012 All rights reserved.
* File name:  guard.cpp
* Author:     Parabola_ds
* Creat time: 2012.05.19
*/
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <vector>
#include <cstdio>
#include <cmath>
#include <set>
#include <map>
#define LIMIT 100000
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;

int n, k, m, sum[LIMIT + 10], loc[LIMIT + 10];
vector<pair<int, int> > rangeZero, rangeOne, tmp;
vector<int> ans;
bool unava[LIMIT + 10];

int main(){
	scanf("%d%d%d", &n, &k, &m);
	rep(i, m){
		int s, t, d;
		scanf("%d%d%d", &s, &t, &d);
		if(!d)
			rangeZero.push_back(make_pair(s, t));
		else
			rangeOne.push_back(make_pair(s, t));
	}

	sort(rangeZero.begin(), rangeZero.end());
	int last = 0;
	for(int i = 0; i < rangeZero.size(); ++i){
		for(int j = max(last + 1, rangeZero[i].first); j <= rangeZero[i].second; ++j)
			unava[j] = 1;
		last = rangeZero[i].second;
	}

	rep(i, n)
		sum[i] = sum[i - 1] + !unava[i];
	last = 0;
	rep(i, n){
		if(!unava[i]) last = i;
		loc[i] = last;
	}
	if(sum[n] == k){
		rep(i, n)
			if(!unava[i]) printf("%d\n", i);
		return 0;
	}

	sort(rangeOne.begin(), rangeOne.end());
	last = n + 1;
	for(int i = rangeOne.size() - 1; i >= 0; --i)
		if(rangeOne[i].second < last){
			tmp.push_back(rangeOne[i]);
			last = rangeOne[i].second;
		}

	for(int i = 0; i < tmp.size(); ++i)
		if(sum[tmp[i].first - 1] + 1 == sum[tmp[i].second])
			if(!unava[loc[tmp[i].second]]){
				ans.push_back(loc[tmp[i].second]);
				unava[loc[tmp[i].second]] = 1;
			}
	rep(i, n)
		sum[i] = sum[i - 1] + !unava[i];
	last = 0;
	rep(i, n){
		if(!unava[i]) last = i;
		loc[i] = last;
	}

	sort(ans.begin(), ans.end());
	rangeOne.clear();
	for(int i = 0; i < tmp.size(); ++i){
		int l = lower_bound(ans.begin(), ans.end(), tmp[i].first) - ans.begin(),
			r = lower_bound(ans.begin(), ans.end(), tmp[i].second + 1) - ans.begin();
		if(l == r)
			rangeOne.push_back(tmp[i]);
	}

	sort(rangeOne.begin(), rangeOne.end());
	vector<int> f(rangeOne.size() + 1, 0);
	for(int i = rangeOne.size() - 1; i >= 0; --i){
		int next = lower_bound(rangeOne.begin(), rangeOne.end(),
				make_pair(loc[rangeOne[i].second] + 1, 0)) - rangeOne.begin();
		f[i] = f[next] + 1;
	}

	k -= ans.size(); last = 0;
	int cnt = 0;
	for(int i = 0; i < rangeOne.size(); ++i)
		if(rangeOne[i].first > last){
			int tail = loc[rangeOne[i].second];
			int next = lower_bound(rangeOne.begin(), rangeOne.end(),
					make_pair(loc[tail - 1] + 1, 0)) - rangeOne.begin();
			cnt++;
			if(cnt + f[next] > k) ans.push_back(tail);
			last = tail;
		}

	sort(ans.begin(), ans.end());
	if(!ans.size()) puts("-1");
	else
		for(int i = 0; i < ans.size(); ++i)
			printf("%d\n", ans[i]);

	return 0;
}

