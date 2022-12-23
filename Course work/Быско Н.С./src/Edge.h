#pragma once
struct EDGE {
	int start = -1, end = -1, weight = -1;
	EDGE() {
	}
	EDGE(int weightEdge, int from, int to) {
		this->weight = weightEdge;
		this->start = from;
		this->end = to;
	}
};